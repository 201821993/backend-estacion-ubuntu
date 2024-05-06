#define WIND_DIR_PIN A0
const int vane = 35;
int vin=0; 
String windDir = "";
        
int veleta = 0;

void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
Serial.println("imprime algo ");


}

void loop() {
 
  Serial.print("Esto vale vin");
  veleta = analogRead(WIND_DIR_PIN);
  Serial.println("Esto vale el sensor: "+veleta);
   Serial.println("--- ");
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
