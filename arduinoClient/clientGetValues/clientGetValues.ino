/*
 modified from 'Repeating Web Client' example by Tom Igoe
 */

#include <SPI.h>
#include <Ethernet.h>
#include <JsonParser.h>

using namespace ArduinoJson::Parser;

// assign a MAC address for the ethernet controller.
//02 AA BB CC 00 35
byte mac[] = { 
  0x02, 0xAA, 0xBB, 0xCC, 0x00, 0x35 };
IPAddress ip(128,122,151,123);
char server[] = "http://isthefloorfeeding.herokuapp.com";

// initialize the library instance:
EthernetClient client;

//create timing variables
unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 5*1000;  // delay between updates, in milliseconds

//create pin assignments
int statePin = 3;
int sweetPin = 2;
int savoryPin = 4;
int amount1Pin = 5;
int amount2Pin = 6;
int amount3Pin = 7;
int amount4Pin = 8;
int netStatusLEDG = 0;
int netStatusLEDR = 1;

//create data holders
int state = 0;
int type = 0;
int amount = 0;


String response = "";
bool begin = false;

void setup() {
  for(int i = 0; i <= 9; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW); 
  }

  // start serial port:
  // Serial.begin(9600);

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    // Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);

    digitalWrite(netStatusLEDR, HIGH);
    digitalWrite(netStatusLEDG, LOW);
  } 
  else {
    digitalWrite(netStatusLEDR, LOW);
    digitalWrite(netStatusLEDG, HIGH);
  }
  delay(1000); //wait for shield to initialize
  // Serial.println("connecting...");
}

void loop() {
  setState(state);
  setType(type);
  setAmount(amount);

  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  /*
  if (client.available()) {
   char c = client.read();
   Serial.print(c);
   }
   */
  if(client.available() || !begin) {
    char in = client.read();
    if (in == '{') {
      digitalWrite(netStatusLEDG, HIGH);
      begin = true;
    }
    if (begin) response += (in);
    if (in == '}') {
      begin = false;
      parseJSON(response);
      // Serial.print(response); 
      response = "";
      digitalWrite(netStatusLEDG, LOW);
    }

  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    // Serial.println();
    // Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    httpRequest();
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  String GETrequest = "GET /";
  String HTTPtype = " HTTP/1.1\r\n"; 
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    //  Serial.println("connecting...");
    //send the data to the server using GET requests. 
    //heroku didn't like println's so I'm using just .print commands
    //send three GET requests, then close connection
    client.print(GETrequest+"status" + HTTPtype);
    client.print("Host: isthefloorfeeding.herokuapp.com\r\n");
    client.print("\r\n");
    client.println("Connection: close");
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    //  Serial.println("connection failed");
    // Serial.println("disconnecting.");
    client.stop();

    digitalWrite(netStatusLEDG, LOW);
    digitalWrite(netStatusLEDR, HIGH);
  }
}

void parseJSON(String json) {
  char charBuf[json.length()+1];
  json.toCharArray(charBuf, json.length()+1);

  JsonParser<16> parser;
  JsonObject root = parser.parse(charBuf); 

  if (!root.success())
  {
    //  Serial.println("JsonParser.parse() failed");
    return;
    digitalWrite(netStatusLEDR, HIGH);
  }

  long _state  = root["state"];
  long _type = root["type"];
  long _amount = root["amount"];
  state = _state;
  type = _type;
  amount = _amount;
  // Serial.println(_state);
  // Serial.println(_type);
  // Serial.println(_amount);
}


void setState(int input) {
  digitalWrite(statePin, input);
}

void setType(int input) {
  switch(input) {
  case 1:
    digitalWrite(savoryPin, HIGH);
    digitalWrite(sweetPin, LOW);
    break;
  case 2:
    digitalWrite(savoryPin, LOW);
    digitalWrite(sweetPin, HIGH);
    break;
  default:
    digitalWrite(savoryPin, LOW);
    digitalWrite(sweetPin, LOW);
  }
}

void setAmount(int input) {
  for(int i = amount1Pin; i <= amount4Pin; i++){
    if(input > (i-amount1Pin)) {
      digitalWrite(i, HIGH);
    } 
    else {
      digitalWrite(i, LOW);
    }
  } 
}




































