const int Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int Echo = 3;   //Pin digital 3 para el Echo del sensor
#define led_pin 12 //rojo
#define led_pin2 13  //verde
int analogvoltage; 
float voltage;


// defines variables
char input; //variable del celular
long duracion;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
//Pines conección pulsador
const int LED=13;
const int BOTON1=7;
const int BOTON2=6;
const int BOTON3=5;
const int BOTON4=4;


Arriba pin 7
Abajo pin 6
Derecha pin 5
Izquierda pin 4
int va1; //mover adelante
int va2; // retroceso
int va3; //derecha
int va4; //izquierda

//Pines de conexión del driver
int Pin_Motor_Der_A = 8;
int Pin_Motor_Der_B = 9;
int Pin_Motor_Izq_A = 10;
int Pin_Motor_Izq_B = 11;

void setup() {
  // inicializar la comunicación serial a 9600 bits por segundo:
  Serial.begin(9600);
  
  //Medidor de batería
  pinMode(led_pin, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(led_pin, LOW);
  digitalWrite(led_pin2, LOW);
  
  //Configuración sensor
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  
  //Configuración pulsadores
  pinMode(LED,OUTPUT);
  pinMode(BOTON1,INPUT);
  pinMode(BOTON2,INPUT);
  pinMode(BOTON3,INPUT);
  pinMode(BOTON4,INPUT);
  
  // configuramos los pines como salida
  pinMode(Pin_Motor_Der_A, OUTPUT);
  pinMode(Pin_Motor_Der_B, OUTPUT);
  pinMode(Pin_Motor_Izq_A, OUTPUT);
  pinMode(Pin_Motor_Izq_B, OUTPUT);
}

void loop() {

  //Medidor de batería
  voltage = analogRead(A0); 
  Nivel_bateria(voltage);

//Sensor ultrasonido
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

    input=0;
  
  //Mover el robot
  va1=digitalRead(BOTON1);
  va2=digitalRead(BOTON2);
  va3=digitalRead(BOTON3);
  va4=digitalRead(BOTON4);
  
  if(d > 5){
    if(Serial.available()>0){ //bluetooth
    input=Serial.read();
  }
  if  (va1==HIGH || input=='1'){
    Mover_Adelante();
    Serial.println("1");
    delay(500);
    }
  else if  (va2==HIGH || input=='2'){
    Serial.println("2");
    Mover_Retroceso();
    delay(500);
    }
  else if  (va3==HIGH  || input=='3'){
    Mover_Derecha();
    Serial.println("3");
    delay(500);
    }
  else  if  (va4==HIGH || input=='4'){
    Mover_Izquierda();
    Serial.println("4");
    delay(500);
    }
   else{
    Mover_Stop();
    }
  }
else{
    Mover_Stop();

    }
    

}

void Nivel_bateria (float voltaje){
  if (voltage < 627) 
  {
    digitalWrite(led_pin, HIGH);
    digitalWrite(led_pin2, LOW);
    Serial.print("Batería baja:  ");
    Serial.println(voltage);

  }
  else if(627<voltage<700){
        digitalWrite(led_pin, HIGH);
    digitalWrite(led_pin2, HIGH);
    Serial.print("Batería media:  ");
    Serial.println(voltage);

    }
    
  else
  {
    digitalWrite(led_pin, LOW);
    digitalWrite(led_pin2, HIGH);
    Serial.print("Batería bien:  ");
    Serial.println(voltage);

  }
  }

void Mover_Adelante()
{
  digitalWrite (Pin_Motor_Der_A, HIGH);
  digitalWrite (Pin_Motor_Der_B, LOW);
  digitalWrite (Pin_Motor_Izq_A, HIGH);
  digitalWrite (Pin_Motor_Izq_B, LOW);
}
void Mover_Retroceso()
{
  digitalWrite (Pin_Motor_Der_A,LOW );
  digitalWrite (Pin_Motor_Der_B,HIGH );
  digitalWrite (Pin_Motor_Izq_A,LOW );
  digitalWrite (Pin_Motor_Izq_B,HIGH );
}
void Mover_Derecha()
{
  digitalWrite (Pin_Motor_Der_A,LOW );
  digitalWrite (Pin_Motor_Der_B,HIGH );
  digitalWrite (Pin_Motor_Izq_A,HIGH);
  digitalWrite (Pin_Motor_Izq_B,LOW);
}
void Mover_Izquierda()
{
  digitalWrite (Pin_Motor_Der_A,HIGH);
  digitalWrite (Pin_Motor_Der_B,LOW);
  digitalWrite (Pin_Motor_Izq_A,LOW );
  digitalWrite (Pin_Motor_Izq_B,HIGH );
}
void Mover_Stop()
{
  digitalWrite (Pin_Motor_Der_A, LOW);
  digitalWrite (Pin_Motor_Der_B, LOW);
  digitalWrite (Pin_Motor_Izq_A, LOW);
  digitalWrite (Pin_Motor_Izq_B, LOW);
}
