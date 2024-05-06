const int vane = 34;
int vin = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
vin = analogRead(vane);

int voltageR = ( 3.3 / 4095 ) * vin;
Serial.println("El voltage es ");
Serial.println("");


}
