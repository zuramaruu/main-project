#include <Servo.h>
Servo myservo;

void setup() 
{
  myservo.attach(3);
}

void loop() 
{
  myservo.write(10);
  delay(1000);
  myservo.write(10);
   delay(1000);
}
