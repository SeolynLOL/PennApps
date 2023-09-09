#include <Servo.h>

Servo servoX;         // Create a servo object for the X-axis
Servo servoY;         // Create a servo object for the Y-axis
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

        int servoXAngle = map(reversedX, 0, 640, 45, 135); // Adjust the mapping for left and right

        // Constrain the servo angle to a reasonable range
        servoXAngle = constrain(servoXAngle, 45, 135);

        // Map the Y-coordinate to servo angle for Y-axis
        int servoYAngle = map(y, 0, 480, 45, 135); // Adjust the mapping for up and down

        // Constrain the servo angle to a reasonable range
        servoYAngle = constrain(servoYAngle, 45, 135);

        // Set the servo positions
        servoX.write(servoXAngle);
        servoY.write(servoYAngle);

        // Check if it's time to trigger the water servo
        unsigned long currentTime = millis();
        if (currentTime - lastTriggerTime >= 1000) { // Trigger every 1 second
          waterServo.write(0); // Spin to 0 degrees (trigger)
          delay(100);          // Wait briefly
          waterServo.write(90); // Spin back to 90 degrees (reset)
          lastTriggerTime = currentTime;
        }
      }
    }
  }
}
