#include <Servo.h>

#define DIODE1 0
#define DIODE2 1
#define DIODE3 2

double diode1 = 0;
double diode2 = 0;
double diode3 = 0;

Servo topServo;
Servo bottomServo;

int topServoAngle = 0;
int bottomServoAngle = 0;

enum States {START, DOWN, UP, ERROR};

void setup()
{
	topServo.attach(9);
	bottomServo.attach(10);
	Serial.begin(9600);
}

void loop()
{
 // topServo.write(69);
	updateDiodeValues();

	if (getDirectionPolar(2) == 1)
	{
		if (topServoAngle > 68.0 && topServoAngle < 70.0)
		{
			bottomServo.write(180);
			delay(800);
			bottomServo.write(96);
		}
		
		// Serial.println("UP");
		Serial.println(topServoAngle);
		if (topServoAngle != 180)
		{
			topServoAngle += 1;
		}
		topServo.write(topServoAngle);
	}
	else if (getDirectionPolar(2) == -1)
	{
		if (topServoAngle > 68.0 && topServoAngle < 70.0)
		{
			bottomServo.write(0);
			delay(800);
			bottomServo.write(96);
			// delay(100000);
		}		
		
		// Serial.println("DOWN");
		Serial.println(topServoAngle);
		if (topServoAngle != 0)
		{
			topServoAngle -= 1;
		}

		topServo.write(topServoAngle);

	}else if (getDirectionPolar(2) == 0){

		topServo.write(topServoAngle);		
		// Serial.println("NO MOVEMENT");
						
	}else{

		Serial.println("EMERGENCY");
		
	}
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
	else if (diode1 > diode2)
	{
		return 1;
	}
	else if (diode1 < diode2)
	{
		return -1;
	}
	else 
	{
		return -2;
	}
}


// int goUpTopServo(int currentAngle){      
//     topServo.write(currentAngle + 1);              	 //command to rotate the servo to the specified angle    
// }

// int goDownTopServo(int currentAngle){
//     topServo.write(currentAngle-1);    
// }

// int goUpSecServo(int currentAngle){      
//     secServo.write(currentAngle + 1);              	 //command to rotate the servo to the specified angle    
// }

// int goDownSecServo(int currentAngle){
//     secServo.write(currentAngle-1);    
// }
