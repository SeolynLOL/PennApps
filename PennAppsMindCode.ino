#include <Brain.h>
#include <Servo.h>

Brain brain(Serial);
Servo waterServo;

void setup() {
  Serial.begin(9600);

  waterServo.attach(11);

  waterServo.write(0); 
}

int timer = 0;
int stage = 0;

void loop() {
  
  if(brain.update()){
    if(brain.readMeditation() > 85 && timer > 4){
      timer = 0;
      
      if(stage==0){
        Serial.print("1");
      }
      else if(stage == 1){
        Serial.print("2");
      }
      else if(stage==2){
        waterServo.write(90);
        delay(400);         
        waterServo.write(0); 
        stage = -1;
        Serial.print("3");
      }

      stage++;
    
    } else{
      timer++;
      Serial.print("0");
    }
    Serial.print(",");
    Serial.print(brain.readMeditation());
    //Serial.print(brain.readMeditation());
    Serial.print(",");
    Serial.println(brain.readSignalQuality());


  }




}