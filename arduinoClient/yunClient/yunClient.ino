/*
  Yún HTTP Client

 This example for the Arduino Yún shows how create a basic
 HTTP client that connects to the internet and downloads
 content. In this case, you'll connect to the Arduino
 website and download a version of the logo as ASCII text.

 created by Tom igoe
 May 2013

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/HttpClient

 */

#include <Bridge.h>
#include <HttpClient.h>

int statePin = 7;
int amountPin = A0;
int typePin = A1;
int networkStatusLedPin = 8;

//create data holders
int state = 0;
int type = 0;
int amount = 0;

int randomValue = 5;
String stateURL = "";
String typeURL = "";
String amountURL = "";

void setup() {
  pinMode(statePin, INPUT_PULLUP); //set switch input to pullup
  pinMode(networkStatusLedPin, OUTPUT); //set status led (no implemented yet) to output

  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Serial.begin(9600);

  while (!Serial); // wait for a serial connection

}

void loop() {
  state = !digitalRead(statePin); //invert switch reading to 0==off
  amount = map(analogRead(amountPin), 0, 1023, 0, 4); //map analog input
  type = map(analogRead(typePin), 0, 1023, 0, 3);
  // Initialize the client library
  HttpClient client;
  stateURL = "http://isthefloorfeeding.herokuapp.com/state/";
  stateURL += state;
  typeURL = "http://isthefloorfeeding.herokuapp.com/type/";
  typeURL += type;
  amountURL = "http://isthefloorfeeding.herokuapp.com/amount/";
  amountURL += amount;
  // Make a HTTP request:
  client.get(stateURL);
  client.get(typeURL);
  client.get(amountURL);

/*
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  Serial.flush();
*/
  delay(1000);
}


