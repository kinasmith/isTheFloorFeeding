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


//Pin Declarations
int amountLED1Pin = 2;
int amountLED2Pin = 3;
int amountLED3Pin = 4;
int amountLED4Pin = 5;

int sweetLEDPin = 6;
int savoryLEDPin = 7;
int stateLEDPin = 8;

int stateReadPin = 9;

int amountReadPin = A0;
int typeReadPin = A1;

//int networkStatusLedPin = 8;

//create data holders
int state = 0;
int type = 0;
int typeIN = 0;
int amount = 0;

//String stateURL = "http://isthefloorfeeding.herokuapp.com/state/";
String stateURL = "";
//String amountURL = "http://isthefloorfeeding.herokuapp.com/amount/";
String typeURL = "";
//String typeURL = "http://isthefloorfeeding.herokuapp.com/type/";
String amountURL = "";

//create timing variables
unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 1000; // delay between updates, in milliseconds


void setup() {
  for (int i = amountLED1Pin; i <= stateLEDPin; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(stateReadPin, INPUT_PULLUP);

  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Serial.begin(9600);

  // while (!Serial); // wait for a serial connection

}

void loop() {
  state = !digitalRead(stateReadPin);
  typeIN = map(analogRead(typeReadPin), 0, 1000, -256, 255);
  amount = map(analogRead(amountReadPin), 0, 1000, 0, 5);

  if (state == 1) {
    setState(state);
    setType(typeIN);
    setAmount(amount);
  } else {
    setState(0);
    setType(0);
    setAmount(0);
  }

  // Initialize the client library
  HttpClient client;
  stateURL = "http://isthefloorfeeding.herokuapp.com/state/";
  stateURL += state;
  typeURL = "http://isthefloorfeeding.herokuapp.com/type/";
  typeURL += type;
  amountURL = "http://isthefloorfeeding.herokuapp.com/amount/";
  amountURL += amount;
  // Make a HTTP request:
  if (millis() - lastConnectionTime > postingInterval) {
    digitalWrite(13, HIGH);
    client.get(stateURL);
    client.get(typeURL);
    client.get(amountURL);
    digitalWrite(13, LOW);
    Serial.println();
    Serial.println(state);
    Serial.println(amount);
    Serial.println(type);
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    Serial.flush();
    lastConnectionTime = millis();
  }

  //  delay(1000);
}

void setState(int input) {
  digitalWrite(stateLEDPin, input);
}

void setAmount(int input) {
  for (int i = amountLED1Pin; i <= amountLED4Pin; i++) {
    if (input > (i - amountLED1Pin)) {
      digitalWrite(i, HIGH);
    }
    else {
      digitalWrite(i, LOW);
    }
  }
}

void setType(int input) {
  if (input > 100) {
    digitalWrite(sweetLEDPin, LOW);
    digitalWrite(savoryLEDPin, HIGH);
    type = 1;
  } else if (input < -100) {
    digitalWrite(sweetLEDPin, HIGH);
    digitalWrite(savoryLEDPin, LOW);
    type = 2;
  } else {
    digitalWrite(sweetLEDPin, LOW);
    digitalWrite(savoryLEDPin, LOW);
    type = 0;
  }
}


