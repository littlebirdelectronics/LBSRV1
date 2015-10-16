// Thumb Joystick example
// Mike Grusin, SparkFun Electronics 3/11
// This code is free, baby. Use it however you like.

//Modified By Nick Owen 10/15

// This sketch shows the basic operation of the Thumb Joystick Adafruit Analog Thumb Stick, Littlbird Part No. 
// The joystick outputs two analog voltages (VERT and HORIZ), and one digital signal (SEL) for the pushbutton.

// Connections to joystick (change if you use different pins):

const int VERT = 0; // analog
const int HORIZ = 1; // analog
const int SEL = 7; // digital

// Also connect the joystick VCC to Arduino 5V, and joystick GND to Arduino GND.

// This sketch outputs serial data at 9600 baud (open Serial Monitor to view).

void setup()
{
  // make the SEL line an input
  pinMode(SEL, INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(SEL, HIGH);

  // set up serial port for output
  Serial.begin(9600);
}

void loop()
{
  int vertical, horizontal, select;

  // read all values from the joystick

  vertical = analogRead(VERT); // will be 0-1023
  horizontal = analogRead(HORIZ); // will be 0-1023
  select = digitalRead(SEL); // will be HIGH (1) if not pressed, and LOW (0) if pressed

  // print out the values

  if ((vertical < 5 && 10 > horizontal < 510)) {
    Serial.println(" UP");
  }

  if ((vertical > 568 && 10 > horizontal < 310)) {
    Serial.println(" DOWN");
  }

  if ((horizontal > 600 && 10 > vertical < 510)) {
    Serial.println(" LEFT");
  }
  if ((horizontal < 5 && 10 > vertical < 510)) {
    Serial.println(" RIGHT");
  }

  if ((horizontal > 300) && (horizontal < 320) && (vertical > 300) && (vertical < 320)) {
    Serial.println("Centre");
  }

  if (select == HIGH) {
    Serial.print(" not pressed");
  }
  else {
    Serial.print(" PRESSED!");
  }
  
  Serial.println(" ");
  /*
  Serial.print("vertical: ");
  Serial.print(vertical, DEC);
  Serial.print(" horizontal: ");
  Serial.print(horizontal, DEC);
  Serial.print(" select: ");
  */

}
