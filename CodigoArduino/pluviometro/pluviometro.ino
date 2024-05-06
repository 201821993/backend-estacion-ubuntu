//#include <WiFi.h>

//char ssid[] = "CCAI_TESE"; // Totalplay-04A6
//char password[] = "TESE_ccai22"; //  04A6DBCFCHH7muMQwifi
//#include <HTTPClient.h>
//const char* serverUrl = "http://192.168.166.30:3001/api/pluviometro"; // URL del servidor Node donde se guarda los datos del pluviometro.


// el cable verde esta conectado al pin2 del ESP32 y el clable naranja es en el cable 5v, solo así funciono 
 
const byte Sensor = 2;
const int umbralTiempo = 300;
volatile int ISRContador = 0;
int contador = 0;
float litros = 0;
long tiempoContador = 0;
long tiempoHora = 0;
String dataPluviometro = "";

void setup(){


   // Conectamos o wifi
   // WiFi.begin(ssid, password);

    // Enquanto não conectar printamos um "."
//    while(WiFi.status() != WL_CONNECTED)
//    {
//        Serial.print(".");
//        delay(1000);
//    }
      // fin codigo para hacer la conexión wife
      //comienzo del codigo de pluviometro 
  pinMode( Sensor  , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Sensor), contadorLitros, RISING);
  Serial.begin(9600);   
     

}
void contadorLitros(){
  
     
  if(millis()>(tiempoContador+umbralTiempo)){
    ISRContador++;
    tiempoContador = millis();
  
    }
   
 }
void loop() {
        Serial.println(ISRContador);
      // fin del codigo del pluviometro
////  // put your main code here, to run repeatedly:
  if(millis()<tiempoHora){
      tiempoHora = 0;
     }
    if(millis()-tiempoHora>1100000){ // millis()-tiempoHora>3600000UL
      tiempoHora = millis();
      litros = ISRContador * 0.27945; //0.011   y viento de 1.492 MPH
      Serial.println("Litros por m2 caidos en una Hora (L/m2");
      Serial.println(litros);
      Serial.print("");
      delay(10000);    
      //envioServidor(litros);
      ISRContador = 0;
      contador = 0;
      
      }
      delay(300);
 
}
//void envioServidor(float litros){
//   HTTPClient http;
//  http.begin(serverUrl);
//  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//   dataPluviometro = "litrosm2="+String(litros); // Ejemplo de datos, puedes ajustar esto según tus necesidades
//
//  int httpResponseCode = http.POST(dataPluviometro);
//  // Comprobar la respuesta del servidor
//  if (httpResponseCode > 0) {
//    String response = http.getString();
//    Serial.println("Respuesta del servidor: " + response);
//  } else {
//    Serial.print("Error en la solicitud. Código de respuesta HTTP: ");
//    Serial.println(httpResponseCode);
// }
//  
// }
