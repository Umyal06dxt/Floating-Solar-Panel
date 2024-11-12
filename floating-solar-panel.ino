#include <Servo.h>

// Servo and position setup
Servo upperServo;
Servo lowerServo;
int errorMargin = 5;
int upperServoPos = 90;
int lowerServoPos = 90;

void setup() {
  Serial.begin(9600);
  upperServo.attach(9);
  lowerServo.attach(11);
  upperServo.write(upperServoPos);
  lowerServo.write(lowerServoPos);
  delay(200);
}

void loop() {
  int sensorReading0 = analogRead(A0);
  int sensorReading1 = analogRead(A1);
  int sensorReading2 = analogRead(A2);
  int sensorReading3 = analogRead(A3);

  int diff1 = abs(sensorReading0 - sensorReading1);
  int diff2 = abs(sensorReading2 - sensorReading3);

  // Adjust upper servo
  if (diff1 > errorMargin) {
    if (sensorReading0 > sensorReading1 && upperServoPos > 0) {
      upperServoPos--;
      upperServo.write(upperServoPos);
    } else if (sensorReading0 < sensorReading1 && upperServoPos < 180) {
      upperServoPos++;
      upperServo.write(upperServoPos);
    }
  }

  // Adjust lower servo
  if (diff2 > errorMargin) {
    if (sensorReading2 > sensorReading3 && lowerServoPos < 180) {
      lowerServoPos++;
      lowerServo.write(lowerServoPos);
    } else if (sensorReading2 < sensorReading3 && lowerServoPos > 0) {
      lowerServoPos--;
      lowerServo.write(lowerServoPos);
    }
  }

  delay(200);
}
