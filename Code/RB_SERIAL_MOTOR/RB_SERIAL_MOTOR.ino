

// Hbridge Connections
const int M2 = 10;   //PWM control for motor outputs 1 and 2 is on digital pin 3
const int E2 = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
const int M1 = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
const int E1 = 13;  //direction control for motor outputs 3 and 4 is on digital pin 13

const int HV1 = 5;
const int HV2 = 6;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Stop();

  Serial.println("Keyboard Commands");
  Serial.println("1-FWD 2-BACK 3-Left 4_Right 5-Stop");

}

void loop() {
  // put your main code here, to run repeatedly:
  if ((digitalRead(HV1)== HIGH) && (digitalRead(HV2)==HIGH)) {forw();}
  if ((digitalRead(HV2)== LOW) && (digitalRead(HV2)==LOW)) {back();}

  
}

void forw() // no pwm defined
{

  // Left Motors FWD
  digitalWrite(M1, HIGH);
  digitalWrite(E1, HIGH);

  //Right Motors FWD
  digitalWrite(M2, HIGH);
  digitalWrite(E2, HIGH);



}

void back() // no pwm defined
{
  // Left Motors REVERSE
  digitalWrite(M1, LOW);
  digitalWrite(E1, HIGH);

  //Right Motors REVERSE
  digitalWrite(M2, LOW);
  digitalWrite(E2, HIGH);

}


void left() // turn left
{
  // Left Motors FWD
  digitalWrite(M1, HIGH);
  digitalWrite(E1, HIGH);

  //Right Motors STOP
  digitalWrite(M2, LOW);
  digitalWrite(E2, LOW);

}

void right() // turn left
{
  // Left Motors STOP
  digitalWrite(M1, LOW);
  digitalWrite(E1, LOW);

  //Right Motors FWD
  digitalWrite(M2, HIGH);
  digitalWrite(E2, HIGH);
}

void Stop() //stop
{
  // Left Motors STOP
  digitalWrite(M1, LOW);
  digitalWrite(E1, LOW);

  //Right Motors STOP
  digitalWrite(M2, LOW);
  digitalWrite(E2, LOW);

}



