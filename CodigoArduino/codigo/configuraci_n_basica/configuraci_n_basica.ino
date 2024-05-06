#include <WiFi.h>

 char ssid[] = "Totalplay-04A6";
 char password[] = "04A6DBCFCHH7muMQ";

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.print("Conectando a la red WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    
  }
  Serial.println("se realizo la conexión");
  Serial.println("");
  Serial.println("Conexión WiFi establecida");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Aquí puedes agregar la lógica principal de tu programa
}
