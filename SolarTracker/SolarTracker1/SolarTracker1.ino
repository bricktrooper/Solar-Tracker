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
	topServo.write(180);
	bottomServo.attach(10);
	bottomServo.write(0);
	Serial.begin(9600);
}

void loop()
{
	updateDiodeValues();

	Serial.println(getDirectionPolar(2));

	if (getDirectionPolar(2) == 1)
	{
		if (topServoAngle = 69.0)
		{
			bottomServo.write(180);
		}

		if (topServoAngle != 180)
		{
			topServoAngle -= 1;
		}	

		// Serial.println("UP");
		Serial.println(topServoAngle);
		
		topServo.write(topServoAngle);
	}
	else if (getDirectionPolar(2) == -1)
	{		
		if (topServoAngle != 69.0)
		{
			topServoAngle += 1;
		}
		
		// Serial.println("DOWN");
		Serial.println(topServoAngle);
		
		topServo.write(topServoAngle);
	} 
	else if (getDirectionPolar(2) == 0)
	{
		// Serial.println("NO MOVEMENT");
		topServo.write(topServoAngle);					
	}
	else
	{
		Serial.println("WTF");
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


int didWeSpin = 0;

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

	int moveUpDown = getDirectionPolar(15);

	if(didWeSpin == 1){
		if(moveUpDown == 1){
			moveUpDown = -1;
		}else if(moveUpDown == -1){
			moveUpDown = 1;
		}
		
	}
	
	if (getDirectionPolar(15) == 1) 
	{
        
		if(topServoAngle == 69){
			if(didWeSpin == 0){
			didWeSpin = 1;
			}else if(didWeSpin == 1){
				didWeSpin = 0;
			}
			bottomServoAngle.write(180);
		}

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

	delay(50);


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
