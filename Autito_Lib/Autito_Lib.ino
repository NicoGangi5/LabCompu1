#include "Autito.h"


//#include <TimerOne.h>


int Motor1_Adelante = 10;
int Motor1_Atras = 9;

int Motor2_Adelante = 11;
int Motor2_Atras = 12;

int Speed = 0;
int Angulo = 0;

int Trigger = 22;
int Echo = 24;



Autito Car(Motor1_Atras, Motor1_Adelante, Motor2_Adelante, Motor2_Atras, Trigger, Echo);



void setup()
{

  pinMode(13,OUTPUT);

  pinMode(8,OUTPUT);

  digitalWrite(8,HIGH);
}


void loop()
{
  //Car.Adelante(Speed);
  for (int brightness = 0; brightness < 255; brightness++) {
      analogWrite(13, brightness);
      Car.Adelante(Speed);
      delay(100);
    }
    
  Car.Apagar();
  delay(500);
	
}
