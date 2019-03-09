#include <Servo.h>

Servo topServo;
Servo bottomServo;

int topServoAngle;
int bottomServoAngle;
int loopCounter;

void setup()
{
  loopCounter = 0;
    topServoAngle = 180;
  
  bottomServoAngle = 0;
  topServo.attach(9);
  bottomServo.attach(10);

  // topServo.write(180);
  // bottomServo.write(180);
  // delay(1000);
  // topServo.write(69);
  // bottomServo.write(0);
  // delay(1000);
  // topServo.write(180);
  // delay(1000);

  for (topServoAngle = 180; topServoAngle > 69.0; topServoAngle -= 10) {
    topServo.write(topServoAngle);
    bottomServo.write(180);
    delay(1000);
    bottomServo.write(0);
    delay(1000);
  }

  Serial.begin(9600);
}

void loop()
{

}
