

const int RecordTime = 3;// definir el tiempo de medición (segundos)
const int SensorPin = 3;

int InterruptCounter;
float WindSpeed;
void setup() {
  // put your setup code here, to run once:
  pinMode(SensorPin,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  meassure();
  Serial.println("Wind Speed");
  Serial.print(WindSpeed); // velocidad en km/h
  Serial.print(" km/h "); 
  Serial.println(WindSpeed / 3.6); // velocidad en m/s
  Serial.print(" m/s ");
} 
void meassure(){
  InterruptCounter = 0;
  attachInterrupt(digitalPinToInterrupt(SensorPin),countup,RISING);
  delay(1000 * RecordTime);
  detachInterrupt(digitalPinToInterrupt(SensorPin));
  WindSpeed = (float)InterruptCounter / ( (float)RecordTime*2.4);
  
  }
  void countup(){
    InterruptCounter++;
    }
