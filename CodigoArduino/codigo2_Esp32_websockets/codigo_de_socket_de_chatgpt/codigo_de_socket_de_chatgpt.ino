#include <WebSocketsClient.h>
#include <WiFi.h>

char ssid[] = "Totalplay-04A6";
char pass[] = "04A6DBCFCHH7muMQ";  
const char* webSocketServer = "ws://localhost:5000";

WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);

  // Conexión WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conexión WiFi establecida");

  // Conexión WebSocket
  webSocket.begin(webSocketServer,5000); // aquí marca un error la conola 
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Desconectado del servidor WebSocket");
      break;
    case WStype_CONNECTED:
      Serial.println("Conectado al servidor WebSocket");
      break;
    case WStype_TEXT:
      Serial.print("Mensaje recibido: ");
      Serial.println((char*)payload);
      break;
  }
}


//
//#include <WiFi.h>
//#include <WebSocketsServer.h>
//
//  char ssid[] = "Totalplay-04A6";
//  char pass[] = "04A6DBCFCHH7muMQ";      // Contraseña de tu red WiFi
//const uint16_t webSocketPort = 8080;         // Puerto del servidor WebSocket
//
//WebSocketsServer webSocket = WebSocketsServer(webSocketPort);
//
//void setup() {
//  Serial.begin(115200);
//
//  // Conexión WiFi
//  WiFi.begin(ssid, pass);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(1000);
//    Serial.println("Conectando a WiFi...");
//  }
//  Serial.println("Conexión WiFi establecida");
//
//  // Inicia el servidor WebSocket
//  webSocket.begin();
//  webSocket.onEvent(webSocketEvent);
//}
//
//void loop() {
//  webSocket.loop();
//}
//
//void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
//  switch (type) {
//    case WStype_DISCONNECTED:
//      Serial.println("Cliente desconectado");
//      break;
//    case WStype_CONNECTED:
//      Serial.println("Cliente conectado");
//      break;
//    case WStype_TEXT:
//      Serial.print("Mensaje recibido del cliente ");
//      Serial.print(num);
//      Serial.print(": ");
//      Serial.println((char*)payload);
//      
//      // Envía un mensaje de respuesta al cliente
//      webSocket.sendTXT(num, "¡Hola, cliente!");
//
//      // Envía el mismo mensaje a todos los clientes conectados
//      // webSocket.broadcastTXT((char*)payload);
//      break;
//  }
//}
