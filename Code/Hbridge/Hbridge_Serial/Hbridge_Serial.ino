

// Hbridge Connections
const int M2 = 10;   //PWM control for motor outputs 1 and 2 is on digital pin 3
const int E2 = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
const int M1 = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
const int E1 = 13;  //direction control for motor outputs 3 and 4 is on digital pin 13

int inByte = 0;         // incoming serial byte


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Stop();

  Serial.println("Keyboard Commands");
  Serial.println("1-FWD 2-BACK 3-Left 4_Right 5-Stop");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {

    inByte = Serial.read();
    switch (inByte) {

      case 49: // kyb 1 // Forward
        forw();
        Serial.println("Forward");
        break;

      case 50: // kyb 2 // Back
        back();
        Serial.println("Back");
        break;

      case 51: // kyb 3 // Left
        left();
        Serial.println("left");
        break;

      case 52: // kyb 4 // Right
        right();
        Serial.println("Right");
        break;

      case 53: // kyb 5 //Stop
        Stop();
        Serial.println("Stop");
        break;



    }
  }

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
  digitalWrite(E1, LOW1);

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



