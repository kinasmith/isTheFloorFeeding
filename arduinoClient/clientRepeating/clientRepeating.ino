 /*
 modified from 'Repeating Web Client' example by Tom Igoe
*/

#include <SPI.h>
#include <Ethernet.h>

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
int statePin = 7;
int amountPin = A0;
int typePin = A1;
int networkStatusLedPin = 8;

//create data holders
int state = 0;
int type = 0;
int amount = 0;

void setup() {
  pinMode(statePin, INPUT_PULLUP); //set switch input to pullup
  pinMode(networkStatusLedPin, OUTPUT); //set status led (no implemented yet) to output
  // start serial port:
  Serial.begin(9600);

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  delay(1000); //wait for shield to initialize
  Serial.println("connecting...");
}

void loop() {
  state = !digitalRead(statePin); //invert switch reading to 0==off
  amount = map(analogRead(amountPin), 0, 1023, 0, 4); //map analog input
  type = map(analogRead(typePin), 0, 1023, 0, 3);

  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    httpRequest(state, type, amount);
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}

// this method makes a HTTP connection to the server:
void httpRequest(int _state, int _type, int _amount) {
  String GETrequest = "GET /";
  String HTTPtype = " HTTP/1.1\r\n"; 
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    //send the data to the server using GET requests. 
    //heroku didn't like println's so I'm using just .print commands
    //send three GET requests, then close connection
    client.print(GETrequest+"food/" + _state + HTTPtype);
    client.print("Host: isthefloorfeeding.herokuapp.com\r\n");
    client.print("\r\n");

    client.print(GETrequest+"type/" + _type + HTTPtype);
    client.print("Host: isthefloorfeeding.herokuapp.com\r\n");
    client.print("\r\n");

    client.print(GETrequest+"amount/" + _amount + HTTPtype);
    client.print("Host: isthefloorfeeding.herokuapp.com\r\n");
    client.print("\r\n");

    client.println("Connection: close");
    // client.println();
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}






















