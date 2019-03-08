#define PHOTODIODE_1 0
#define PHOTODIODE_2 1
#define PHOTODIODE_3 2

int diode[3];
 
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  diode[0] = analogRead(PHOTODIODE_1);  // Diode 1 reading 
  diode[1] = analogRead(PHOTODIODE_2);  // Diode 2 reading 
  diode[2] = analogRead(PHOTODIODE_3);  // Diode 3 reading 
Serial.println(diode[2]);
//  for (int i = 0; i < 3; i++)
//  {
////    Serial.print(i);
////    Serial.print(diode[i]);
////    Serial.println();
//  }
  
   delay(1000);
}
