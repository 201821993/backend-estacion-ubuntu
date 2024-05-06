
// Variables para el sensor de rayos ultravioleta  Hardware pin definitions
int UVOUT = 32;    // Pin analógico para la salida del sensor UV
int REF_3V3 = 33;  // Pin analógico para la referencia de 3.3V en la placa ESP32
// fin variables de ultra violeta

#include <Wire.h>
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

// Codigo para el sensor de luz
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  float outputVoltage = 3.3 / refLevel * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);
// FIN del codigo  para el sensor de luz
}
