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

double diff12;
double diff13;
double diff23;
double precision;

void setup()
{
	loopCounter = 0;
	precision = 5;

    topServo.attach(9);
	bottomServo.attach(10);

  	topServoAngle = 180;
	bottomServoAngle = 170;

	topServo.write(topServoAngle);
	bottomServo.write(bottomServoAngle);

	delay(2000);

//	topServo.write(69);
//	bottomServo.write(0);
//	delay(2000);
//
//	topServo.write(180);
//	delay(2000);

// Servo test sequence
	// if (topServoAngle > 69.0) {
	// 	topServoAngle -= 10;
	// 	topServo.write(topServoAngle);
	// 	bottomServo.write(180);
	// 	delay(1000);
	// 	bottomServo.write(0);
	// 	delay(1000);
	// }

	Serial.begin(9600);
}

void loop()
{
	updateDiodeValues();
    updateServoAngles();
	
	// loopCounter += 1;

	// if (loopCounter % 1 == 0) {
	// 	Serial.print(diode1);
	// 	Serial.print(" "); 
	// 	Serial.print(diode2); 
	// 	Serial.print(" "); 
	// 	Serial.print(diode3); 
	// 	Serial.println(" ");
	// 	Serial.print(topServo.read());
	// 	Serial.println(" ");
	// 	Serial.print(bottomServo.read());
	// }
	
	diff12 = diode1 - diode2;
	diff13 = diode1 - diode3;
	diff23 = diode2 - diode3;

	if (abs(diff13) < precision && abs(diff23) < precision)
	{
		topServo.write(topServoAngle);
	}
	else if (diff13 > precision || diff23 > precision)
	{
		if(topServoAngle == 69)
		{
			if (bottomServoAngle < 90)
			{
				bottomServoAngle = 170;
				bottomServo.write(bottomServoAngle);
			}
			else if (bottomServoAngle > 90)
			{
				bottomServoAngle = 10;
				bottomServo.write(bottomServoAngle);
			}
			
			delay(1000);
		}
		else if (topServoAngle > 69)
		{
			topServoAngle -= 1;
			topServo.write(topServoAngle);	
		}        
	}
	else if (diff13 < -precision || diff23 < -precision)
	{
		if (topServoAngle < 180)
		{
			topServoAngle += 1;
			topServo.write(topServoAngle);
		}        
	}
	
    // TURN //

    updateServoAngles();

	if (abs(diff12) < precision)
	{
		bottomServo.write(bottomServoAngle);
	}
	else if (diff12 > precision) 
	{
		if(bottomServoAngle < 180)
		{
			bottomServoAngle += 1;
   		    bottomServo.write(bottomServoAngle);  
		}
	}
	else if (diff12 < -precision)
	{
		if (bottomServoAngle > 0)
		{
			bottomServoAngle -= 1;
			bottomServo.write(bottomServoAngle);
		}
	}
  
	delay(25);
}

void updateDiodeValues()
{
	diode1 = analogRead(DIODE1);
	diode2 = analogRead(DIODE2);
	diode3 = analogRead(DIODE3);
}

void updateServoAngles()
{
    topServoAngle = topServo.read();
    bottomServoAngle = bottomServo.read();
}
// int compareDiodeTheta(double precision)
// { 
// 	if (abs(diode1 - diode2) < precision) 
// 	{
// 		return 0;
// 	} 
// 	else if (diode1 - diode2 > precision)
// 	{
// 		return 1;
// 	}
// 	else if (diode2 - diode1 > precision)
// 	{
// 		return -1;
// 	}
// }

// int compareDiodePhi(double precision)
// {
// 	if (abs(diode2 - diode3) < precision) 
// 	{
// 		return 0;
// 	} 
// 	else if (diode2 - diode3 > precision)
// 	{
// 		return 1;
// 	}
// 	else if (diode3 - diode2 > precision)
// 	{
// 		return -1;
// 	}
// }
