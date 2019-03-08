#include <Servo.h>

#define DIODE1 0
#define DIODE2 1
#define DIODE3 2

double diode1 = 0;
double diode2 = 0;
double diode3 = 0;

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
	topServo.write(180);
	bottomServo.write(0);

	delay(1000);
	Serial.begin(9600);
}

void loop()
{
	updateDiodeValues();
	
	loopCounter += 1;
	if (loopCounter % 60 == 0) {
		Serial.println(getDirectionPolar(2));
		Serial.print(diode1);
		Serial.print(" "); 
		Serial.print(diode2); 
		Serial.print(" "); 
		Serial.println(diode3); 
	}
	
	if (getDirectionPolar(15) == 1)
	{
        if (topServoAngle != 69)
		{
            topServoAngle -= 1;
        }        
		topServo.write(topServoAngle);
    }
	else if (getDirectionPolar(15) == -1)
	{
        if (topServoAngle != 180)
		{
            topServoAngle += 1;
        }        
		topServo.write(topServoAngle);
    }

	delay(10);


// Servo test sequence
	// if (topServoAngle > 69.0) {
	// 	topServoAngle -= 10;
	// 	topServo.write(topServoAngle);
	// 	bottomServo.write(180);
	// 	delay(1000);
	// 	bottomServo.write(0);
	// 	delay(1000);
	// }
}

void updateDiodeValues()
{
	diode1 = analogRead(DIODE1);
	diode2 = analogRead(DIODE2);
	diode3 = analogRead(DIODE3);
}

int getDirectionPolar(double precision)
{ 
	if (abs(diode1 - diode2) < precision) 
	{
		return 0;
	} 
	else if (diode1 < diode2)
	{
		return 1;
	}
	else if (diode1 > diode2)
	{
		return -1;
	}
	else 
	{
		return -2;
	}
}