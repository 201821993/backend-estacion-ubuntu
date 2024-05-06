#include <Adafruit_BMP280.h>
//#define BLYNK_TEMPLATE_ID "TMPL2jwla9Bas"
//#define BLYNK_TEMPLATE_NAME "Meteorológica usando BMP280"
//#define BLYNK_AUTH_TOKEN "bPnYfdegw3W86lgdoAFvDlq_-q7ql53F"
//#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
//#include <BlynkSimpleEsp32.h>
//char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "CCAI_TESE";  // Este es el nombre del wifi
char pass[] = "TESE_ccai22";  // Esta es la contraseña del wifi
#include <HTTPClient.h>
const char* serverUrl = "http://192.168.166.103:3001/api/insert-data"; // URL del servidor Node.js
// aquí termina el codigo para enviar datos mediante el protocolo http

//BlynkTimer timer;
#include <Wire.h>
#include <SPI.h>   
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C
// Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
// Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

//codigo del sensor de gas MQ135
int sensorPin = 35; // Asigna el pin analógico A0 para leer la señal del sensor

float Vref = 5.0; // La referencia de voltaje del Arduino

float CO2Curve[3] = {2.3, 0.72, -0.34}; // Curva de calibración para el sensor MQ135

float Ro = 10; // Valor de resistencia de carga inicial para el sensor

float CO2; // La lectura de CO2

// aqui termina codigo de gas


// Hardware pin definitions
int UVOUT = 32;    // Pin analógico para la salida del sensor UV
int REF_3V3 = 33;  // Pin analógico para la referencia de 3.3V en la placa ESP32

#include <Ticker.h>
Ticker envioConstante; // biblioteca ticker 
String data=""; // esta variable se va a mandar a atraves del protocolo http a nodejs , en cadena va a contener todos los valore que devuelven los sensores.

unsigned long tiempoInicio;

void setup() 
{

  // envioConstante.attach(7,Envio7Segundos);

 // Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  //analogSetAttenuation(ADC_11db);

  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  
  Serial.println("ML8511 example");

   while ( !Serial ) delay(100);   // esperar usb nativo
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_DIRECCIÓN_ALT, BMP280_CHIPID);
  status = bmp.begin(0x77);
  if (!status) {
    Serial.println(F("No se pudo encontrar un sensor BMP280 válido, verifique el cableado o "
                      "¡Prueba con una dirección diferente!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probablemente significa una mala dirección, a BMP 180 o BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, 
                  Adafruit_BMP280::SAMPLING_X2, 
      Adafruit_BMP280::SAMPLING_X16, 
            Adafruit_BMP280::FILTER_X16, 
                  Adafruit_BMP280::STANDBY_MS_500);


}

void loop() 
{
      tiempoInicio = millis(); // Tomar el tiempo actual como referencia

//  HTTPClient http;
//  http.begin(serverUrl);
//  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  Serial.println("BMP280                Rayos Ultravioleta          Sensor de gas MQ135    ");
  // Configurar los encabezados de la solicitud

    float temperature = bmp.readTemperature(); // Leer la temperatura en grados Celsius
    //int temp =bmp.readTemperature();
    float pressure= bmp.readPressure() /100.0;
    float altitude=bmp.readAltitude(1013.25);

    //aqui inicia el sensor de gas MQ135

    int sensorValue = analogRead(sensorPin); // Lee el valor del sensor MQ135

  float Vout = (sensorValue / 1024.0) * Vref; // Convierte el valor analógico a voltaje

  float Rs = ((Vref - Vout) / Vout) * Ro; // Calcula la resistencia del sensor

  CO2 = pow(10, ((log(Rs / CO2Curve[0]) - CO2Curve[1]) / CO2Curve[2])); // Calcula la concentración de CO2 usando la curva de calibración

  //Aqui finaliza el sensor de gas MQ135
  

//    Serial.println("Se muetran los siguientes datos de Temperatura, Presión y Altitud cada 30 segundos");
//    Serial.print("Temperatura: ");
//    Serial.print(temperature);
bmp.readTemperature();
//    Serial.print(" *C");
//    Serial.print(" | ");
//    Serial.print(F("Presion: "));
//    //Serial.print(bmp.readPressure());
//    Serial.print(pressure);
//    Serial.print(" hPa");
//    Serial.print(" | ");
//    Serial.print(F("Altitud: "));
bmp.readAltitude(1013.25); /* ¡Ajustado al pronóstico local! */
//    Serial.print(" m");                    //Si no se sabe, se modificara hasta obtener su altitud actual
//    Serial.print(" | ");
//    Serial.print("CO2: "); // Imprime la lectura de CO2 en la consola
//    Serial.print(CO2);
//    Serial.println(" ppm");

//    Blynk.virtualWrite(V0, temperature);
//    Blynk.virtualWrite(V1, pressure);
//    Blynk.virtualWrite(V2, altitude);                                  //El "1019.66" es la presión (hPa) al nivel del mar por día en su región
//    
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  float outputVoltage = 3.3 / refLevel * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);
//
//  Serial.print("ML8511 voltage: ");
//  Serial.print(outputVoltage);
//
//  Serial.print(" / UV Intensity (mW/cm^2): ");
//  Serial.print(uvIntensity);
//
//  Serial.print(" UV Ray Intensity: ");
//  Serial.print(uvIntensity);
//  Serial.print(" mW/cm^2");

  

//  Blynk.virtualWrite(V3, uvIntensity);
//
//  Blynk.run();
//     timer.run();
//Serial.print(temperature);
//Serial.print(" *C");
// Serial.print(F("Presion: "));
bmp.readPressure();
//Serial.print(pressure);
//Serial.print(" hPa");

// *********** aquí se muestra la información *****/
Serial.println("Temperatura: "+ String(temperature)+" "+ "   Voltage: "+String(outputVoltage)+"               CO2: "+" "+String(CO2));
Serial.println("Presion: "+String(pressure)+"       UV Intensity: "+String(uvIntensity));
Serial.println("Altitud: "+String(altitude)+"      UV Ray Intensity: "+String(uvIntensity));
Serial.println("");
//creando cadena de caracteres que contiene todos los datos que se van a mandar al servidor
  //data = "temperature="+String(temperature)+"&pressure="+String(pressure)+"&altitud="+String(altitude)+"&air_quality="+String(CO2)+"&UVRay="+String(uvIntensity); // Ejemplo de datos, puedes ajustar esto según tus necesidades
  /* envio de los datos al servidor */
 data = "temperature="+String(temperature)+"&pressure="+String(pressure)+"&altitud="+String(altitude)+"&air_quality="+String(CO2)+"&UVRay="+String(uvIntensity); // Ejemplo de datos, puedes ajustar esto según tus necesidades
Serial.println(" ****************               Esta es la temperatura ");








  // Finalizar la solicitud
// data = "temperature="+String(temperature)+"&pressure="+String(pressure)+"&altitud="+String(altitude)+"&air_quality="+String(CO2)+"&UVRay="+String(uvIntensity); // Ejemplo de datos, puedes ajustar esto según tus necesidades
//   data = "temperature="+String(temperature)+"&pressure="+String(pressure)+"&altitud="+String(altitude)+"&air_quality="+String(CO2)+"&UVRay="+String(uvIntensity); // Ejemplo de datos, puedes ajustar esto según tus necesidades


if ( tiempoInicio >= 5000) {


    data = "temperature="+String(temperature)+"&pressure="+String(pressure)+"&altitud="+String(altitude)+"&air_quality="+String(CO2)+"&UVRay="+String(uvIntensity); // Ejemplo de datos, puedes ajustar esto según tus necesidades
//   data = "temperature="+String(temperature)+"&pressure="+String(pressure)+"&altitud="+String(altitude)+"&air_quality="+String(CO2)+"&UVRay="+String(uvIntensity); // Ejemplo de datos, puedes ajustar esto según tus necesidades

//envioConstante.attach(1800,Envio30Minutos);
  Serial.println(data);
   HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(data);
  // Comprobar la respuesta del servidor
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta del servidor: " + response);
  } else {
    Serial.print("Error en la solicitud. Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
  }
  http.end();



}

}
void Envio7Segundos(){
   Serial.print(data);
  Serial.print("Sí entre o no ");
   HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(data);
  // Comprobar la respuesta del servidor
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta del servidor: " + response);
  } else {
    Serial.print("Error en la solicitud. Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
  }
}
  void Envio30Minutos(){
    HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(data);
  
  // Comprobar la respuesta del servidor
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta del servidor: " + response);
  } else {
    Serial.print("Error en la solicitud. Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
  }
  
}

int averageAnalogRead(int pinToRead) 
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for (int x = 0; x < numberOfReadings; x++) 
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return (runningValue);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
