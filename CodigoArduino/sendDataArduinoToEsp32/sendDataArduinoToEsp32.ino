// bibliotcas para conexión a internet
#include <Wire.h>
// aquí comienza el codigo para enviar los datos al servidor en el puerto 1010
#include <WiFi.h>
char ssid[] = "queso 1"; // Totalplay-04A6  CCAI_TESE
char password[] = "123456781"; //   TESE_ccai22

#include <HTTPClient.h>
const char* serverUrl = "http://192.168.166.122:3001/api/miriams"; // URL del servidor Node.


// puertos tx y rx 
#define RXp2 16
#define TXp2 17
String aux = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // configura desde serial2 los puertos tx y rx
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);

// aquí inicía la conexión a internet
    WiFi.begin(ssid, password);

    // Enquanto não conectar printamos um "."
        while(WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            delay(1000);
        }
            // Exibimos "WiFi Conectado"
        Serial.println("Connected to Wifi, Connecting to server.");
        
    // aquí termina la conexión a internet
}
void loop() {
    Serial.println("Message Received: ");
    Serial.println(Serial2.readString());
    // aquí en aux se almacena 
    aux = Serial2.readString();
    Serial.println(" Codigo recivido "+aux);

 
   HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(aux);
  // Comprobar la respuesta del servidor
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respuesta del servidor: " + response);
  } else {
    Serial.print("Error en la solicitud. Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);
  }
    
//    for(int i = 0; i < strlen(aux) ; i++){
//        Serial.println(i);
//         
//      }
    
}
