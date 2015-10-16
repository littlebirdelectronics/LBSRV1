/*
  RedBeaat WiFi Web Server for Littlebird Space Rover 1 LBSRV1
 
 A simple web server that shows that maps html buttons to digital output.
 using a WiFi shield.
 
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 Originally created 13 July 2010 by dlf (Metodo2 srl)
 modified 31 May 2012 by Tom Igoe
 
 Further adapted and additional coding for LBSRV1 by Nick Owen 10/15
 
 
 */

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

// Pins to for Arduion commuincations via level 3.3v to 5vdc level shifter
int LV1=9;
int LV2=8;
int LV3=7;

// your network name also called SSID
char ssid[] = "INSERT YOUR SSID";

// your network password
char password[] = "password";


// your network key Index number (needed only for WEP)
int keyIndex = 0;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);      // initialize serial communication
  pinMode(RED_LED, OUTPUT);      // set the LED pin mode
 
  pinMode(LV1, OUTPUT);      // set the LED pin mode
  pinMode(LV2, OUTPUT);      // set the LED pin mode
  pinMode(LV3, OUTPUT);      // set the LED pin mode

  digitalWrite(LV1, LOW);
  digitalWrite(LV2, LOW);
 digitalWrite(LV3, LOW);
 
 
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  // you're connected now, so print out the status  
  printWifiStatus();

  Serial.println("Starting webserver on port 80");
  server.begin();                           // start the web server on port 80
  Serial.println("Webserver started!");  

}


void loop() {
  // listen for incoming clients

  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        IncomingChar(c);

        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply

        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          client.println("<input type=button value='Forward' onmousedown=location.href='/?FWD'><br/><br/>");
          client.println( "<input type=button value='Reverse' onmousedown=location.href='/?REV'><br/><br/>");
          client.println("<input type=button value='Left' onmousedown=location.href='/?LFT'><br/><br/>");
          client.println( "<input type=button value='Right' onmousedown=location.href='/?RHT'><br/><br/>");
          client.println( "<input type=button value='CLAW OPEN' onmousedown=location.href='/?COP'><br/><br/>");
          client.println( "<input type=button value='CLAW SHUT' onmousedown=location.href='/?CSH'><br/><br/>");



          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 3; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}






//***** Group up characters until end of line ****
void IncomingChar (const byte InChar)
{
  static char InLine [500];    //Hope we don't get more than that in one line
  static unsigned int Position = 0;

  switch (InChar)
  {
  case '\r':   // Don't care about carriage return so throw away.
    break;

  case '\n':   
    InLine [Position] = 0;  
    ProcessCommand(String(InLine));
    Position = 0;  
    break;

  default:
    InLine [Position++] = InChar;
  }  
} 






void ProcessCommand(String InLine){
  Serial.println("Recieved: " + InLine);


  if (InLine.startsWith("GET /?FWD")){
    Serial.println(" motor FWD request nick !!! ");
    //Serial1.println(" motor FWD request nick !!! ");
    digitalWrite(LV1, HIGH);
    digitalWrite(LV2, HIGH);
    digitalWrite(LV3, LOW);
  }

  if (InLine.startsWith("GET /?REV")){
    Serial.println(" motor REV request nick !!! ");
    // Serial1.println(" motor REV request nick !!! ");
    digitalWrite(LV1, LOW);
    digitalWrite(LV2, LOW);
    digitalWrite(LV3, LOW);
  }

  if (InLine.startsWith("GET /?LFT")){
    Serial.println(" motor LEFT request nick !!! ");
    //Serial1.println(" motor Left request nick !!! ");
    digitalWrite(LV1, LOW);
    digitalWrite(LV2, HIGH);
    digitalWrite(LV3, LOW);
  }

  if (InLine.startsWith("GET /?RHT")){
    Serial.println(" motor Right request nick !!! ");
    // Serial1.println(" motor Right request nick !!! ");
    digitalWrite(LV1, HIGH);
    digitalWrite(LV2, LOW);
    digitalWrite(LV3, LOW);
  }

 if (InLine.startsWith("GET /?COP")){
    Serial.println(" motor Right request nick !!! ");
    // Serial1.println(" motor Right request nick !!! ");
    digitalWrite(LV1, LOW);
    digitalWrite(LV2, HIGH);
    digitalWrite(LV3, HIGH);
  }

 if (InLine.startsWith("GET /?CSH")){
    Serial.println(" motor Right request nick !!! ");
    // Serial1.println(" motor Right request nick !!! ");
    digitalWrite(LV1, HIGH;
    digitalWrite(LV2, HIGH);
    digitalWrite(LV3, HIGH);
  }


}





