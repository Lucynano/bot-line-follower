#define IN1 3
#define IN2 2
#define ENA 9

#define IN3 4
#define IN4 5
#define ENB 10

#define IRD 6
int valD;

#define IRC 7
int valC;

#define IRG 8
int valG;

#define VITESSE 180

// === Nouvelle variable globale ===
int lastDir = 0; // -1 = gauche, 0 = centre, 1 = droite

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IRD,INPUT);
  pinMode(IRC,INPUT);
  pinMode(IRG,INPUT);

  Serial.begin(9600);
}

void loop()
{
   valD = digitalRead(IRD);
  valC = digitalRead(IRC);
  valG = digitalRead(IRG);

  Serial.print(valG);
  Serial.print("\t");
  Serial.print(valC);
  Serial.print("\t");
  Serial.print(valD);
  Serial.print("\t");
  Serial.println("");

  // 📌 Sauvegarder la dernière direction vue
  if (valG == 1 && valD == 0) lastDir = -1; // gauche
  else if (valD == 1 && valG == 0) lastDir = 1; // droite
  else if (valC == 1 && valG == 0 && valD == 0) lastDir = 0; // centre

  // Logique de suivi de ligne
  if(valG == 0 && valC == 0 && valD == 0) search();
  else if(valG == 0 && valC == 0 && valD == 1) left();
  else if(valG == 0 && valC == 1 && valD == 0) forward();
  else if(valG == 0 && valC == 1 && valD == 1) left();
  else if(valG == 1 && valC == 0 && valD == 0) right();
  else if(valG == 1 && valC == 1 && valD == 0) right();
  else if(valG == 1 && valC == 1 && valD == 1) forward();

  delay(50);
}

void forward()
{
  //motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 160);

  //motor B
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 160);
}

void backward()
{
  //motor A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, VITESSE);
  //motor B
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, VITESSE);
}

void right()
{
  //motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, VITESSE);
  //motor B
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 130);
}

void left()
{
  //motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 130);
  //motor B
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, VITESSE);
}

void search()
{
  if (lastDir == -1) { // droite
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 130);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, 130);
    delay(200);
  }
  else if (lastDir == 1) { // gauche
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, 130);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 130);
    delay(200);
  }
  else { // centre
    forward();
    delay(150);
  }
}


void motor_stop()
{
  analogWrite(ENA,0); 
  analogWrite(ENB,0); 
}