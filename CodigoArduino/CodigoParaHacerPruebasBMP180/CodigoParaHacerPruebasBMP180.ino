#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

// aquí comienza el codigo para enviar los datos al servidor en el puerto 1010
#include <WiFi.h>
//#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>
char ssid[] = "CCAI_TESE"; // Totalplay-04A6
char password[] = "TESE_ccai22"; //  04A6DBCFCHH7muMQ
const char* websockets_server_host = "192.168.166.30"; // IP do servidor websocket
const int websockets_server_port = 1010; // Porta de conexão do servidor
// Utilizamos o namespace de websocket para podermos utilizar a classe WebsocketsClient
using namespace websockets;
// Objeto websocket client
WebsocketsClient client;

//StaticJsonDocument<300> jsonDoc;



// aquí termina el codigo para enviarlo al servidor en el puerto 1010

/*aquí comienza el codigo para solo enviar datos*/
#include <HTTPClient.h>
const char* serverUrl = "http://192.168.166.103:3001/api/insert-data"; // URL del servidor Node.js



Adafruit_BMP085 bmp;
#include <Ticker.h>
Ticker envioConstante; // biblioteca ticker 
String data=""; // esta variable se va a mandar a atraves del protocolo http a nodejs , en cadena va a contener todos los valore que devuelven los sensores.
unsigned long tiempoInicio;

void setup() {
 ///envioConstante.attach(7,Envio7Segundos);

  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("No se pudo encontrar el sensor BMP180");
    while (1);
  }
  
    // Conectamos o wifi
    WiFi.begin(ssid, password);

    // Enquanto não conectar printamos um "."
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    // Exibimos "WiFi Conectado"
    Serial.println("Connected to Wifi, Connecting to server.");
  // Tentamos conectar com o websockets server
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/");

    // Se foi possível conectar
    if(connected) 
    {
        // Exibimos mensagem de sucesso
        Serial.println("Connected!");
        // Enviamos uma msg "Hello Server" para o servidor
        //client.send("Hello Server");
    }   // Se não foi possível conectar
    else 
    {
        // Exibimos mensagem de falha
        Serial.println("Not Connected!");
        return;
    }
    
    // Iniciamos o callback onde as mesagens serão recebidas
    client.onMessage([&](WebsocketsMessage message)
    {        
        // Exibimos a mensagem recebida na serial
        Serial.print("Got Message: ");
        Serial.println(message.data());
   
//        // Ligamos/Desligamos o led de acordo com o comando
//        if(message.data().equalsIgnoreCase("ON"))
//                   delay(1000);
//        else
//        if(message.data().equalsIgnoreCase("OFF"))
//                  delay(1000);
    });



  
}
int contador =0;
void loop() {
  unsigned long tiempoActual = millis(); // Obtener el valor actual de millis()

  /*aquí comienza el codigo para enviar a nodejs con exprees*/
//    String data = "temperature=25&pressure=50&altitud=140&air_quality=20"; // Ejemplo de datos, puedes ajustar esto según tus necesidades
//  HTTPClient http;
//  http.begin(serverUrl);
//  // Configurar los encabezados de la solicitud
//  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//   // Enviar los datos al servidor
//  int httpResponseCode = http.POST(data);
//  // Comprobar la respuesta del servidor
//  if (httpResponseCode > 0) {
//    String response = http.getString();
//    Serial.println("Respuesta del servidor: " + response);
//  } else {
//    Serial.print("Error en la solicitud. Código de respuesta HTTP: ");
//    Serial.println(httpResponseCode);
//  }
//
//  // Finalizar la solicitud
//  http.end();
 
// StaticJsonDocument<300> jsonDoc;
String response;
contador++;
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0; // Convertir a hPa

   float seaLevelPressure = 101325.0; // Valor de presión al nivel del mar en Pa
  float altitude = bmp.readAltitude(seaLevelPressure);
  
Serial.print("contador");
Serial.println(contador);

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Presión: ");
  Serial.print(pressure);
  Serial.println(" hPa");
Serial.println("");
  
//jsonDoc["contador"] = contador;
//jsonDoc["temperatura"] = temperature ;
//jsonDoc["presion"] = pressure;
//
//serializeJson(jsonDoc, response);
   


int CO2 = 13;
int uvIntensity = 9;

//  De tempo em tempo, o websockets client checa por novas mensagens recebidas
    if(client.available()) 
        client.poll();
        client.send(response);
        
    delay(300);
    // aquí empieza el codigo del sensor 
  data = "temperature="+String(temperature)+"&pressure="+String(pressure)+"&altitud="+String(altitude)+"&air_quality="+String(CO2)+"&UVRay="+String(uvIntensity); // Ejemplo de datos, puedes ajustar esto según tus necesidades
//   data = "temperature="+String(temperature)+"&pressure="+String(pressure)+"&altitud="+String(altitude)+"&air_quality="+String(CO2)+"&UVRay="+String(uvIntensity); // Ejemplo de datos, puedes ajustar esto según tus necesidades

//envioConstante.attach(1800,Envio30Minutos);
  Serial.println(data);
  
  if ( tiempoActual - tiempoInicio >= 7000 ) {

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
 tiempoInicio = tiempoActual;
}
}



void Envio7Segundos(){

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
