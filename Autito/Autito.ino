#include <Servo.h>
#include <TimerOne.h>


//--------------------------VARIABLES--------------------------
int Cont = 0;                             //Contador
int Pos = 0;                              //Posición del servo
int Speed = 0;                            //Velocidad de los motores                   
int Flag1 = 0;                             //Bandera 1
int Flag2 = 0;
long distancia = 0;                       //Distancia al objeto
long tiempo;                              //Tiempo usado para calcular la distancia al objeto
float Angulo = 0;                         //Ángulo de giro del auto 

Servo myservo;                            //Creo el objeto Servo


//--------------------------SETUP--------------------------
void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);              //Enable motor izquierdo  
  pinMode(3,OUTPUT);              //Atras motor izquierdo              
  pinMode(4,OUTPUT);              //Adelante motor izquierdo

  pinMode(5,OUTPUT);              //Adelante motor derecho
  pinMode(6,OUTPUT);              //Atras motor derecho
  pinMode(7,OUTPUT);              //Enable motor derecho

  pinMode(13,OUTPUT);             //LED que indica cuando esta midiendo

  myservo.attach(8);              //Objeto servo pin 8
  
  Timer1.initialize(30000);       //Inicializo el timer
  Timer1.attachInterrupt(Timer);  //Adjunto el timer a una función

  pinMode(9, OUTPUT);             //Envio de pulso para ultrasonido
  pinMode(10, INPUT);             //Recepción de pulso para ultrasonido
}


//--------------------------CÓDICO--------------------------
void loop() {
  if(Flag2==0){                                                       //Inicio que permite la Intro, solo se ejecuta una vez.
    Servito(0);                                                       //Pone el servo una posición conocida en el caso de que se salga el sensor y haya que ponerlo de nuevo
    delay(10000);
    Intro();                                                          //Función Intro
    Flag2=1;
  }
  
  else{       
      Servito(45);                                                    //Servo en el medio
      if((distancia>=10)&(Flag1==0)){                                 
        
         Adelante(255);                                               //Para distancias mayores a 10cm velocidad máxima
      }
    
      if((distancia<10)&(Flag1==0)){    
        
        Adelante(128);                                                //Para distancias entre 7 y 9cm velocidad media
      }
    
      if(distancia<=7){                                               //Para distancias menores a 7cm
         
         Flag1=1;
         Apagar();                                                    //Se para por 100 ms
         delay(100);
         Atras(150);                                                  //Va hacia atrás
         delay(600);
         Servito(0);                                                 //Mueve el servo hacia la derecha 45º
         if(distancia>9){

            Derecha(80);                                             //En el caso de no haber nada a menos de 9cm gira hacia a la derecha y pone Flag1=0 para que
            delay(200);                                              //pueda volver a la condicion inicial de velocidad máxima y media.
            Servito(45);                                             //Vuelve el servo a la posición inicial
            Flag1=0;        
         }
    
         if(distancia<9){                                            //Este caso se da si al mirar hacia la izquierda tiene otro obstáculo por ende tiene que ir a la derecha
    
            Servito(90);                                             //Mueve el servo hacia la izquierda 45º
            if(distancia>9){
    
            Izquierda(80);                                           //En el caso de no haber nada a menos de 9cm gira hacia a la izquierda y pone Flag1=0 para que
            delay(200);                                              //pueda volver a la condicion inicial de velocidad máxima y media.
            Servito(45);                                             //Vuelve el servo a la posición inicial
            Flag1=0;        
            }
         }
    
      }
  }  
}   






//--------------------------TIMER--------------------------
void Timer(){ 
  Distancia();                                                      //Cada 30 ms mide la distancia 
}


//--------------------------SERVO--------------------------
void Servito(int Pos){
    myservo.write(Pos);                                             //Pone el servo en la posición solicitada
}


//--------------------------ADELANTE--------------------------
void Adelante(int Speed){                                          //Activa ambos motores a la velocidad solicitada hacia adelante
  digitalWrite(3, LOW);
  analogWrite(4, Speed);

  analogWrite(5, Speed);
  digitalWrite(6, LOW);
}


//--------------------------ATRAS--------------------------
void Atras(int Speed){                                             //Activa ambos motores a la velocidad solicitada hacia atrás
  analogWrite(3, Speed);
  digitalWrite(4, LOW);

  digitalWrite(5, LOW);
  analogWrite(6, Speed);
}

//--------------------------APAGAR--------------------------
void Apagar(){                                                     //Desactiva ambos motores
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

//--------------------------DERECHA--------------------------
void Derecha(int Angulo){
  float Tiempo=0;                                                  //Calcula el tiempo necesario de giro a una velocidad máxima para el ángulo solicidato
  Tiempo=(Angulo*4.1666);
  
  digitalWrite(3, LOW);
  analogWrite(4, 255);  
                                                                   //Gira hacia la derecha durante el tiempo calculado y luego apaga los motores
  digitalWrite(5, LOW);
  analogWrite(6, 255);

  delay(Tiempo);                                               

  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

//--------------------------IZQUIERDA--------------------------
void Izquierda(int Angulo){
  float Tiempo=0;                                                  //Calcula el tiempo necesario de giro a una velocidad máxima para el ángulo solicidato                                             
  Tiempo=(Angulo*4.1666);
  
  analogWrite(3, 255);
  digitalWrite(4, LOW);
                                                                   //Gira hacia la izquierda durante el tiempo calculado y luego apaga los motores
  analogWrite(5, 255);
  digitalWrite(6, LOW);

  delay(Tiempo);

  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

//--------------------------Distancia--------------------------
void Distancia(){

  digitalWrite(13,HIGH);                                           //Prende el led durante el proceso de medición 
  
  digitalWrite(9,LOW);                                             // Por cuestión de estabilización del sensor
  delayMicroseconds(2);
  
  digitalWrite(9, HIGH);                                           //Envío del pulso ultrasónico de 10us
  delayMicroseconds(10);
  
  tiempo=pulseIn(10, HIGH);                                        //Calculo el tiempo que tarda en volver el pulso 
  distancia= int(0.017*tiempo);                                    //Sabiendo la velocidad a la que viaja calculo la distancia 
  
  Serial.print("Distancia ");                                      //Envío el valor de distancia UART 0 (Se lee en la terminal de Arduino)
  Serial.print(distancia);
  Serial.println(" cm"); 

  digitalWrite(13,LOW);

}


//--------------------------Intro--------------------------
void Intro(){
  
  Servito(0);
  delay(250);
  Servito(180);
  delay(250);
  Servito(90);
  delay(250);
  Izquierda(360);
  delay(100);
  Derecha(360);
  delay(100);
  Apagar();
  
}
