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
	bottomServo.write(180);
	delay(1000);
	topServo.write(69);
	bottomServo.write(0);
	delay(1000);
	topServo.write(180);
	delay(1000);

	Serial.begin(9600);
}

void loop()
{
	updateDiodeValues();
	
	loopCounter += 1;
	if (loopCounter % 60 == 0) {
		Serial.print(diode1);
		Serial.print(" "); 
		Serial.print(diode2); 
		Serial.print(" "); 
		Serial.println(diode3); 
	}

	if (compareDiode(diode2, diode1, 15) == 1)
	{
		if(topServoAngle == 69)
		{
			if (bottomServoAngle < 90)
			{
				bottomServoAngle = 180;
				bottomServo.write(bottomServoAngle);
			}
			else if (bottomServoAngle > 90)
			{
				bottomServoAngle = 0;
				bottomServo.write(bottomServoAngle);
			}
			
			delay(1000);
		}
        else if (topServoAngle != 69)
		{
            topServoAngle -= 1;
        }        
		topServo.write(topServoAngle);
    }
	else if (compareDiode(diode2, diode1, 15) == -1)
	{
        if (topServoAngle != 180)
		{
            topServoAngle += 1;
        }        
		topServo.write(topServoAngle);
    }
	
	if (compareDiode(diode1, diode3, 15) == 1)
	{
        if (bottomServoAngle != 180)
		{
            bottomServoAngle += 1;
        }        
		bottomServo.write(bottomServoAngle);
    }
	else if (compareDiode(diode1, diode3, 15) == -1)
	{
        if (bottomServoAngle != 0)
		{
            bottomServoAngle -= 1;
        }        
		bottomServo.write(bottomServoAngle);
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

int compareDiode(double firstDiode, double secondDiode, double precision)
{ 
	if (abs(firstDiode - secondDiode) < precision) 
	{
		return 0;
	} 
	else if (firstDiode > secondDiode)
	{
		return 1;
	}
	else if (firstDiode < secondDiode)
	{
		return -1;
	}
}