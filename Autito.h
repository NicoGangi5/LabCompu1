/*
  Autito.h - Library for use in Laboratorio de Computación 1 - Universidad Católica de Cordoba - Argentina 
  Created by Nicolás Gangi & Martín Marcucci, August 12, 2018.
  Released into the public domain.
*/

#ifndef Autito_h
#define Autito_h

#include <Arduino.h>

class Autito
{
public:
	Autito(int Pin1, int Pin2, int Pin3, int Pin4, int Trigger, int Echo);
	void Adelante (int Speed);
	void Atras (int Speed);
	void Apagar ();
	void Derecha (int Angulo);
	void Izquierda (int Angulo);
	void Distancia (); 

private:
	int _Speed;
	int _Angulo;

	int _Pin1;
	int _Pin2;
	int _Pin3;
	int _Pin4;

	int _Trigger;
	int _Echo;
};

#endif