#include <Servo.h>

Servo servoX;
Servo servoY;
Servo waterServo;

unsigned long lastTriggerTime = 0;

void setup() {
  Serial.begin(9600);
  servoX.attach(9);
  servoY.attach(10);
  waterServo.attach(11);
  servoX.write(90);
  servoY.write(90); 
  waterServo.write(0); 
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); 
    int commaIndex = data.indexOf(',');
    if (commaIndex != -1) {
      int x = data.substring(0, commaIndex).toInt();
      data = data.substring(commaIndex + 1);
      commaIndex = data.indexOf(',');
      if (commaIndex != -1) {
        int y = data.substring(0, commaIndex).toInt();

        int reversedX = 640 - x;

        int servoXAngle = map(reversedX, 0, 640, 45, 135);

        servoXAngle = constrain(servoXAngle, 45, 135);

        int servoYAngle = map(y, 0, 480, 45, 135);

        servoYAngle = constrain(servoYAngle, 45, 135);

        servoX.write(servoXAngle);
        servoY.write(servoYAngle);

        unsigned long currentTime = millis();
        if (currentTime - lastTriggerTime >= 1000) { 
          waterServo.write(90);
          delay(400);         
          waterServo.write(0); 
          lastTriggerTime = currentTime;
        }
      }
    }
  }
}
