
//
//#include <WiFi.h>
//#include <WebSocketsClient.h>
//
//// Constants
//const char* ssid = "Totalplay-04A6";
//const char* password = "04A6DBCFCHH7muMQ";
//const char* webSocketServer = "192.168.100.172:8080/api"; // Dirección IP o URL del servidor WebSocket
//
//// Globals
//WebSocketsClient webSocket;
//
//// Called when WebSocket is connected
//void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
//  switch (type) {
//    case WStype_CONNECTED:
//      Serial.println("Connected to WebSocket server");
//      break;
//    case WStype_TEXT:
//      Serial.printf("Received message: %s\n", payload);
//      break;
//    case WStype_DISCONNECTED:
//      Serial.println("Disconnected from WebSocket server");
//      break;
//  }
//}
//
//void setup() {
//  Serial.begin(115200);
//
//  // Connect to Wi-Fi
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println();
//  Serial.println("Connected to Wi-Fi");
//
//  // Connect to WebSocket server
//  webSocket.begin(webSocketServer);
//  webSocket.onEvent(webSocketEvent);
//}
//
//void loop() {
//  webSocket.loop();
//
//  // Send message to WebSocket server
//  webSocket.sendTXT("Hello from ESP32");
//  delay(5000);
//}

//#include <WiFi.h>
//#include <WebSocketsServer.h>
//#include <HTTPClient.h>
//
//// Constants
//char ssid[] = "Totalplay-04A6";
//char password[] = "04A6DBCFCHH7muMQ";
//
//// Globals
//WebSocketsServer webSocket = WebSocketsServer(80);
//
//// Server URL
//const char* serverUrl = "http://localhost:8080";
//// Reemplaza con la IP y el puerto de tu servidor Node.js
//
//// Called when receiving any WebSocket message
//void onWebSocketEvent(uint8_t num,
//                      WStype_t type,
//                      uint8_t * payload,
//                      size_t length) {
//
//  // Figure out the type of WebSocket event
//  switch(type) {
//
//    // Client has disconnected
//    case WStype_DISCONNECTED:
//      Serial.printf("[%u] Disconnected!\n", num);
//      break;
//
//    // New client has connected
//    case WStype_CONNECTED:
//      {
//        IPAddress ip = webSocket.remoteIP(num);
//        Serial.printf("[%u] Connection from ", num);
//        Serial.println(ip.toString());
//      }
//      break;
//
//    // Echo text message back to client
//    case WStype_TEXT:
//      Serial.printf("[%u] Text: %s\n", num, payload);
//      
//      // Create an HTTPClient object
//      HTTPClient http;
//      
//      // Set the server URL
//      http.begin(serverUrl);
//      
//      // Set the content type header
//      http.addHeader("Content-Type", "text/plain");
//      
//      // Send the payload as the body of the POST request
//      int httpResponseCode = http.POST((const char*)payload);
//      
//      // Check the response code
//      if (httpResponseCode == HTTP_CODE_OK) {
//        String response = http.getString();
//        Serial.println("POST request sent successfully");
//        Serial.println("Response: " + response);
//      } else {
//        Serial.println("Error sending POST request");
//        Serial.print("HTTP response code: ");
//        Serial.println(httpResponseCode);
//      }
//      
//      // End the HTTP connection
//      http.end();
//      
//      break;
//
//    // For everything else: do nothing
//    case WStype_BIN:
//    case WStype_ERROR:
//    case WStype_FRAGMENT_TEXT_START:
//    case WStype_FRAGMENT_BIN_START:
//    case WStype_FRAGMENT:
//    case WStype_FRAGMENT_FIN:
//    default:
//    serial.println("no hay nada");
//      break;
//  }
//}
//
//void setup() {
//  // Start Serial port
//  Serial.begin(115200);
//
//  // Connect to access point
//  Serial.println("Connecting");
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//  // Print our IP address
//  Serial.println("Connected!");
//  Serial.print("My IP address: ");
//  Serial.println(WiFi.localIP());

// aquí empieza el bueno
  // Start


#include <WiFi.h>
#include <WebSocketsServer.h>

// Constants
char ssid[] = "Totalplay-04A6";
 char password[] = "04A6DBCFCHH7muMQ";
// Globals
WebSocketsServer webSocket = WebSocketsServer(5000);

// Called when receiving any WebSocket message
void onWebSocketEvent(uint8_t num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {

  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connection from ", num);
        Serial.println(ip.toString());
      }
      break;

    // Echo text message back to client
    case WStype_TEXT:
      Serial.printf("[%u] Text: %s\n", num, payload);
      webSocket.sendTXT(num, payload);
      break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
 }
}

void setup() {

  // Start Serial port
  Serial.begin(115200);

  // Connect to access point
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }

  // Print our IP address
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());

  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {

  // Look for and handle WebSocket data
  webSocket.loop();
}
