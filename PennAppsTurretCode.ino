#include <Servo.h>

Servo servoX;         // Create a servo object for the X-axis
Servo servoY;         // Create a servo object for the Y-axis

void setup() {
  Serial.begin(4800);
  servoX.attach(9);
  servoY.attach(10);
  servoX.write(90);
  servoY.write(65); 
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

        int servoXAngle = map(reversedX, 0, 640, 45, 135); // Adjust the mapping for left and right

        // Constrain the servo angle to a reasonable range
        servoXAngle = constrain(servoXAngle, 20, 110);

        // Map the Y-coordinate to servo angle for Y-axis
        int servoYAngle = map(y, 0, 480, 20, 110); // Adjust the mapping for up and down

        // Constrain the servo angle to a reasonable range
        servoYAngle = constrain(servoYAngle, 20, 110);

        // Set the servo positions
        servoX.write(servoXAngle);
        servoY.write(servoYAngle);
      }
    }
  }
}