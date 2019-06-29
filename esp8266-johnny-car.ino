/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "d764372adca1478db1b6bf027707484b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jurassic world";
char pass[] = "rex061321";

/* define os pinos de controle do motor L298N ou L293D */
int leftMotorForward = 2;       /* GPIO2(D4) -> IN3   */
int rightMotorForward = 15;     /* GPIO15(D8) -> IN1  */
int leftMotorBackward = 0;      /* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;    /* GPIO13(D7) -> IN2  */

/* define os pinos de habilitação L298N ou L293D */
int rightMotorENB = 14;         /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12;          /* GPIO12(D6) -> Motor-B Enable */

bool isFrente;
bool isRe;
bool isEsquerda;
bool isDireita;

void setup()
{
  // Debug console
  Serial.begin(9600);

  /* inicializa os pinos de controle do motor como saída */
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  /* inicializar os pinos de habilitação do motor como saída */
  pinMode(rightMotorENB, OUTPUT);
  pinMode(leftMotorENB, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();

  if (isFrente || isRe || isEsquerda || isDireita) {
    if (isFrente) {
      Serial.println("FRENTE");
      TurnLeft();
    } 
  
    if (isRe) {
      Serial.println("RÉ");
      TurnRight();
    }
  
    if (isEsquerda) {
      Serial.println("ESQUERDA");
      MotorBackward();
    }
  
    if (isDireita) {
      Serial.println("DIREITA");
      MotorForward();
    }
  } else {
    MotorStop();
  }
}

// Frente
BLYNK_WRITE(V1) {
  Serial.print("Frente: ");
  Serial.println(param.asInt());

  if (param.asInt()) {
    isFrente = param.asInt();
  } else {
    isFrente = param.asInt();
  }
}

// Ré
BLYNK_WRITE(V2) {
  Serial.print("Ré: ");
  Serial.println(param.asInt());

  if (param.asInt()) {
    isRe = param.asInt();
  } else {
    isRe = param.asInt();
  }
}

// Esquerda
BLYNK_WRITE(V3) {
  Serial.print("Esquerda: ");
  Serial.println(param.asInt());

  if (param.asInt()) {
    isEsquerda = param.asInt();
  } else {
    isEsquerda = param.asInt();
  }
}

// Direita
BLYNK_WRITE(V4) {
  Serial.print("Direita: ");
  Serial.println(param.asInt());

  if (param.asInt()) {
    isDireita = param.asInt();
  } else {
    isDireita = param.asInt();
  }
}

// Stop
BLYNK_WRITE(V5) {
  Serial.print("Stop: ");
  Serial.println(param.asInt());

  MotorStop();
}

void MotorForward(void) {
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorBackward, LOW);
}

void MotorBackward(void) {
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
}

void TurnLeft(void) {
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
}

void TurnRight(void) {
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
}

void MotorStop(void)   
{
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);

  Serial.println("STOPPPP");
}



  
