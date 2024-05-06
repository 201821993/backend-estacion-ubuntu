//#include <ETH.h>
#include <WiFi.h>

#include <ArduinoWebsockets.h>

char ssid[] = "netis_70F8D0";
char password[] = "carlos4523";
const char* websockets_server_host = "192.168.100.103"; // IP do servidor websocket
const int websockets_server_port = 1010; // Porta de conexão do servidor

// Utilizamos o namespace de websocket para podermos utilizar a classe WebsocketsClient
using namespace websockets;

// Objeto websocket client
WebsocketsClient client;

// aquí va todo el codigo del sensor
int UVOUT = 32;    // Pin analógico para la salida del sensor
int REF_3V3 = 33;  // Pin analógico para la referencia de 3.3V en la placa ESP32
 
//aqui termina 


void setup() 
{
    // Iniciamos a serial com velocidade de 115200
   

Serial.println("tons que papi");
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
        client.send("Hello Server");
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
//aqui comienza el codigo del sensor 
Serial.begin(9600);

  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
 
  Serial.println("ML8511 example");
    // aquí termina
}
void loop() 
{
    //  De tempo em tempo, o websockets client checa por novas mensagens recebidas
    if(client.available()) 
        client.poll();
        
    delay(300);
    // aquí empieza el codigo del sensor 
     Serial.print("michalngelo");
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  // Usar el pin de referencia de 3.3V para obtener un valor de salida muy preciso del sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); // Convertir el voltaje a un nivel de intensidad de UV
 
  Serial.print("output: ");
  Serial.print(refLevel);
 
  Serial.print(" / ML8511 output: ");
  Serial.print(uvLevel);
 
  Serial.print(" / ML8511 voltage: ");
  Serial.print(outputVoltage);
 
  Serial.print(" / UV Intensity (mW/cm^2): ");
  Serial.print(uvIntensity);

  Serial.print(" UV Ray Intensity: ");
  Serial.print(uvIntensity);
  Serial.print(" mW/cm^2");
  
  Serial.println();
  
  delay(2000);
    // aquí termina
}
// Tomar el promedio de lecturas en un pin dado
// Devuelve el promedio
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
   return(runningValue);
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
