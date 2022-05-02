#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
//Pines conección pulsador
const int LED=13;
const int BOTON1=7;
const int BOTON2=6;
const int BOTON3=5;
const int BOTON4=4;
int va1;
int va2;
int va3;
int va4;
//Pines de conexión del driver
int Pin_Motor_Der_A = 8;
int Pin_Motor_Der_B = 9;
int Pin_Motor_Izq_A = 10;
int Pin_Motor_Izq_B = 11;

void setup() {
  //Configuración sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  //Configuración pulsadores
  pinMode(LED,OUTPUT);
  pinMode(BOTON1,INPUT);
  pinMode(BOTON2,INPUT);
  pinMode(BOTON3,INPUT);
  pinMode(BOTON4,INPUT);
  // inicializar la comunicación serial a 9600 bits por segundo:
  Serial.begin(9600);
  // configuramos los pines como salida
  pinMode(Pin_Motor_Der_A, OUTPUT);
  pinMode(Pin_Motor_Der_B, OUTPUT);
  pinMode(Pin_Motor_Izq_A, OUTPUT);
  pinMode(Pin_Motor_Izq_B, OUTPUT);
}

void loop() {
    // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  //Mover el robot
  va1=digitalRead(BOTON1);
  va2=digitalRead(BOTON2);
  va3=digitalRead(BOTON3);
  va4=digitalRead(BOTON4);
  if(distance>10){
      Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if  (va1==HIGH){
    digitalWrite(LED,HIGH);
    Mover_Adelante();
    delay(2000);
    }
  if  (va2==HIGH){
    digitalWrite(LED,HIGH);
    Mover_Retroceso();
    delay(2000);
    }
  if  (va3==HIGH){
    digitalWrite(LED,HIGH);
    Mover_Derecha();
    delay(2000);
    }
   if  (va4==HIGH){
    digitalWrite(LED,HIGH);
    Mover_Izquierda();
    delay(2000);
    }
   else{
    Mover_Stop();
    }
  }
  else{
    Mover_Stop();
      Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
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
