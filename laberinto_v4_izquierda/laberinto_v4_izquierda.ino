// Definimos los ultrasonicos por cada lado
/*
  Todos las posiciones es en base al robot.
    Ej:
      Derecha -> Derecha del robot 
        (En nuestro caso sera izquierda)
    violeta -> gnd
    blanco -> positivo
*/
// Derecha
#define trig_der 8
#define echo_der 2

// Frente
#define trig_frente 5
#define echo_frente 4

// Izquierda 
#define trig_izq 6
#define echo_izq 7

// Definimos los motores
#define in1 3
#define in2 9
#define in3 10
#define in4 11

// Velocidad
#define velocidad 60
#define k 0.7

float error;

// Definimos una variable p/ valor anterior
int valor_anterior = 0;
int distancia_muro = 20;

int sensorFrente = 0;
int sensorDerecha = 0;
int sensorIzquierda = 0;

int velocidadIzquierda = 0;
int velocidadDerecha = 0;
  
void setup()
{
  // Definimos los componentes a ocupar
  /* 
      Ultrasonicos 
  */
  
  // DERECHA
  pinMode(trig_der, OUTPUT);
  pinMode(echo_der, INPUT);
  // FRENTE
  pinMode(trig_frente, OUTPUT);
  pinMode(echo_frente, INPUT);
  // IZQUIERDA
  pinMode(trig_izq, OUTPUT);
  pinMode(echo_izq, INPUT);
  
  /*
      Motores
  */
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  /*
      Monitor Serial
  */
  //Serial.begin(9600);
  pinMode(13, OUTPUT);
  avanzar();
  delay(250);
}

void loop()
{ 
  digitalWrite(13, HIGH);
  sensorDerecha = distanciaDerecha();
  sensorFrente = distanciaFrente();
  sensorIzquierda = distanciaIzquierda();

  
  //Serial.println(sensorDerecha);

  if(sensorIzquierda > distancia_muro){
    // Gira a la izquierda
      avanzar();
      girarIzquierda();
      avanzar();
      delay(320);  
  } 
  else if (sensorFrente > 7) {
    // Sigue recto
    //avanzar();
    
    error = sensorIzquierda - sensorDerecha;
    if(abs(error) < 2){
      error = 0;
    }else{
      if(abs(error) < 10){
        velocidadIzquierda = velocidad - (k * error);
        velocidadDerecha = velocidad + (k * error);
        avanzar(velocidadDerecha, velocidadIzquierda);
      }else{
        error = 0;
        velocidadIzquierda = velocidad - (k * error);
        velocidadDerecha = velocidad + (k * error);
        avanzar(velocidadDerecha, velocidadIzquierda); 
      }   
    }   
  }
  else if (sensorDerecha > distancia_muro) {
    // Gira a la derecha
      avanzar();
      girarDerecha();
      avanzar();
      delay(320);
    //}
    //delay(100);
  }
  else{
      reversa();
      girarDerecha();
      delay(100);  
  }
}

long u_distancia(int trigger_pin, int echo_pin) {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  long microseconds = pulseIn(echo_pin , HIGH);
  long u_distancia;
  u_distancia = microseconds / 29 / 2;
  /*
  if(u_distancia != 0){
   valor_anterior = u_distancia; 
  }
  if (u_distancia == 0) {
    u_distancia = valor_anterior;
  }*/
  return u_distancia;
}

long distanciaDerecha(){
  return u_distancia(trig_der, echo_der);
}

long distanciaFrente(){
  return u_distancia(trig_frente, echo_frente);
}

long distanciaIzquierda(){
  return u_distancia(trig_izq, echo_izq);
}

// Funciones de movimiento
void avanzar(){
  analogWrite(in1, velocidad);
  analogWrite(in2, 0);
  analogWrite(in3, velocidad); 
  analogWrite(in4, 0); 
  delay(200);
  //Serial.println("Avanzar ");  
}

void avanzar(int velocidadDerecha, int velocidadIzquierda){
  analogWrite(in1, velocidadIzquierda);
  analogWrite(in2, 0);
  analogWrite(in3, velocidadDerecha);  
  analogWrite(in4, 0);  
  delay(200);
}

void reversa(){
  analogWrite(in1, 0);
  analogWrite(in2, velocidad);
  analogWrite(in3, 0); 
  analogWrite(in4, velocidad); 
  delay(350);
  //Serial.print("Reversa ");
  //Serial.println(distanciaFrente());
}

void detener(){
  //Serial.println("Detener");
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0); 
  analogWrite(in4, 0); 
}

void girarIzquierda(){
  
  analogWrite(in1, 0);
  analogWrite(in2, 60);
  analogWrite(in3, 60 +15); 
  analogWrite(in4, 0);
  delay(300);
  
}

void girarDerecha(){
  analogWrite(in1, 60);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 60 +15); 
  delay(300);   
}
