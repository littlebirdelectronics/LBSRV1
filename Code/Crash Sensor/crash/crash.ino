int pin = 13;
volatile int state = LOW;

void setup()
{
  pinMode(pin, OUTPUT);
  attachInterrupt(0, crash, HIGH);
    Serial.begin(9600);

}

void loop()
{
  if (state==HIGH){
  digitalWrite(pin, state);
  }
}

void crash()
{
  state = HIGH;
  Serial.println("trig");
}
