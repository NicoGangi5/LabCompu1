/*
  Autito.h - Library for use in Laboratorio de Computación 1 - Universidad Católica de Cordoba - Argentina 
  Created by Nicolás Gangi & Martín Marcucci, August 12, 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Autito.h"




//--------------------------CONSTRUCTOR--------------------------

Autito::Autito(int Pin1, int Pin2, int Pin3, int Pin4, int Trigger, int Echo)
{
  pinMode(Pin1, OUTPUT);
  _Pin1 = Pin1;

  pinMode(Pin2, OUTPUT);
  _Pin2 = Pin2;

  pinMode(Pin3, OUTPUT);
  _Pin3 = Pin3;

  pinMode(Pin4, OUTPUT);
  _Pin4 = Pin4;

  pinMode(Trigger, OUTPUT);
  _Trigger = Trigger;

  pinMode(Echo, INPUT);
  _Echo = Echo;
}


//--------------------------ADELANTE--------------------------
void Autito::Adelante(int Speed){                                          //Activa ambos motores a la velocidad solicitada hacia adelante
  digitalWrite(_Pin1, LOW);
  analogWrite(_Pin2, Speed);

  analogWrite(_Pin3, Speed);
  digitalWrite(_Pin4, LOW);

  return 0;
}


//--------------------------ATRAS--------------------------
void Autito::Atras(int Speed){                                             //Activa ambos motores a la velocidad solicitada hacia atrás
  analogWrite(_Pin1, Speed);
  digitalWrite(_Pin2, LOW);

  digitalWrite(_Pin3, LOW);
  analogWrite(_Pin4, Speed);

  return 0;
}

//--------------------------APAGAR--------------------------
void Autito::Apagar(){                                                     //Desactiva ambos motores
  digitalWrite(_Pin1, LOW);
  digitalWrite(_Pin2, LOW);

  digitalWrite(_Pin3, LOW);
  digitalWrite(_Pin4, LOW);

  return 0;
}

//--------------------------DERECHA--------------------------
void Autito::Derecha(int Angulo){
  float Tiempo=0;                                                  //Calcula el tiempo necesario de giro a una velocidad máxima para el ángulo solicidato
  Tiempo=(Angulo*4.1666);
  
  digitalWrite(_Pin1, LOW);
  analogWrite(_Pin2, 255);  
                                                                   //Gira hacia la derecha durante el tiempo calculado y luego apaga los motores
  digitalWrite(_Pin3, LOW);
  analogWrite(_Pin4, 255);

  delay(Tiempo);                                               

  digitalWrite(_Pin1, LOW);
  digitalWrite(_Pin2, LOW);

  digitalWrite(_Pin3, LOW);
  digitalWrite(_Pin4, LOW);

  return 0;
}

//--------------------------IZQUIERDA--------------------------
void Autito::Izquierda(int Angulo){
  float Tiempo=0;                                                  //Calcula el tiempo necesario de giro a una velocidad máxima para el ángulo solicidato                                             
  Tiempo=(Angulo*4.1666);
  
  analogWrite(_Pin1, 255);
  digitalWrite(_Pin2, LOW);
                                                                   //Gira hacia la izquierda durante el tiempo calculado y luego apaga los motores
  analogWrite(_Pin3, 255);
  digitalWrite(_Pin4, LOW);

  delay(Tiempo);

  digitalWrite(_Pin1, LOW);
  digitalWrite(_Pin2, LOW);

  digitalWrite(_Pin3, LOW);
  digitalWrite(_Pin4, LOW);

  return 0;
}

//--------------------------Distancia--------------------------
float Autito::Distancia(){
  long tiempo = 0;
  long distancia = 0;

  digitalWrite(_Trigger,LOW);                                             // Por cuestión de estabilización del sensor
  delayMicroseconds(2);
  
  digitalWrite(_Trigger, HIGH);                                           //Envío del pulso ultrasónico de 10us
  delayMicroseconds(10);
  
  tiempo=pulseIn(_Echo, HIGH);                                        //Calculo el tiempo que tarda en volver el pulso 
  distancia= int(0.017*tiempo);                                    //Sabiendo la velocidad a la que viaja calculo la distancia 

  return distancia;
  
  /*
  Serial.print("Distancia ");                                      //Envío el valor de distancia UART 0 (Se lee en la terminal de Arduino)
  Serial.print(distancia);
  Serial.println(" cm"); 
  */

}
