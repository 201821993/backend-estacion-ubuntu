#define WIND_DIR_PIN A0
const int vane = 34;
int vin=0; 
String windDir = "";
        


void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
Serial.println("imprime algo ");


}

void loop() {
 
  Serial.print("Esto vale vin");
  vin = analogRead(vane);
  Serial.print("esto manda la veleta ");
  Serial.println(vin);
  Serial.println("Esto vale el sensor: ");
 float voltage = (3.3 / 4095) * vin;  //
 //
 Serial.print("este es el voltaje  ---> ");
   Serial.println(voltage);
  Serial.println("");
    if      (vin < 150) windDir="202.5";
  else if (vin < 300) windDir = "180";
  else if (vin < 400) windDir = "247.5";
  else if (vin < 600) windDir = "225";
  else if (vin < 900) windDir = "292.5";
  else if (vin < 1100) windDir = "270";
  else if (vin < 1500) windDir = "112.5";
  else if (vin < 1700) windDir = "135";
  else if (vin < 2250) windDir = "337.5";
  else if (vin < 2350) windDir = "315";
  else if (vin < 2700) windDir = "67.5";
  else if (vin < 3000) windDir = "90";
  else if (vin < 3200) windDir = "22.5";
  else if (vin < 3400) windDir = "45";
  else if (vin < 4000) windDir = "0";
  else windDir = "0"; 
  Serial.println(windDir);
delay(2000);
//  // put your main code here, to run repeatedly:
//veleta = analogRead(sensorPing);
//
//
//Serial.print("Dirección de la veta");
//  if( 745<veleta && veleta < 824  ){
//  Serial.println("N o 0"); //0°
//  }
//  else if(384<velta && velta < 425){
//      Serial.println("NNE o 22.5");
//    }
//      else if(384<velta && velta < 425){
//      Serial.println("NNE o 22.5");
//    }
//      else if(437<velta && velta < 483){
//      Serial.println("NNE o 22.5");
//    }
//      else if(78<velta && velta < 87){
//      Serial.println("NNE o 22.5");
//    }
//      else if(88<velta && velta < 97){
//      Serial.println("NNE o 22.5");
//    }
//      else if(384<velta && velta < 425){
//      Serial.println("NNE o 22.5");
//    }
//      else if(384<velta && velta < 425){
//      Serial.println("NNE o 22.5");
//    }  else if(384<velta && velta < 425){
//      Serial.println("NNE o 22.5");
//    }
//      else if(384<velta && velta < 425){
//      Serial.println("NNE o 22.5");
//    }
}
