const int analogPin = A0;  // Pin analógico A0 para la lectura

// Arrays para almacenar los valores de dirección, voltaje y resistencia
float directions[] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180, 202.5, 225, 247.5, 270, 292.5, 315, 337.5};
float voltages[] = {3.84, 1.98, 2.25, 0.41, 0.45, 0.32, 0.90, 0.62, 1.40, 1.19, 3.08, 2.93, 4.62, 4.04, 4.78, 3.43};
float resistances[] = {33e3, 6.57e3, 8.2e3, 891, 1e
3, 688, 2.2e3, 1.41e3, 3.9e3, 3.14e3, 16e3, 14.12e3, 120e3, 42.12e3, 64.9e3, 21.88e3};

void setup() {
  Serial.begin(9600);  // Inicializar la comunicación serial
}

void loop() {
  int rawValue = analogRead(analogPin);  // Leer el valor analógico desde A0
  Serial.println("");
  Serial.print("Este valor me lo manda analogpin");
  Serial.println(rawValue);
  //
  
 // float voltage = (5 / 1023.0) * rawValue;  // Calcular el voltaje en base al valor leído
 
//4095  
float voltage = (3.3 / 4095.0) * rawValue;  // Calcular el voltaje en base al valor leído
  Serial.println(" resultado   ");
  Serial.println(voltage);



  float measuredDirection = -1;  // Inicializar la dirección medida como -1 (no encontrada)

  // Buscar la dirección medida en el array de direcciones
  for (int i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
    if (voltage >= voltages[i] - 0.05 && voltage <= voltages[i] + 0.05) {
      measuredDirection = directions[i];
      break;  // Salir del bucle cuando se encuentra una dirección coincidente
    }
  }

  // Si se encontró una dirección coincidente, imprimir los valores
  if (measuredDirection != -1) {
    int index = 0;
    for (int i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
      if (directions[i] == measuredDirection) {
        index = i;
        break;
      }
    }
    
    Serial.print("Direction: ");
    Serial.print(measuredDirection);
    Serial.print(" degrees\tVoltage: ");
    Serial.print(voltage, 2);
    Serial.print("V\tResistance: ");
    Serial.print(resistances[index]);
    Serial.println(" Ohms");
  } else {
    Serial.println("Direction not found.");
  }

  delay(2000);  // Esperar  segundo antes de la siguiente lectura
}
