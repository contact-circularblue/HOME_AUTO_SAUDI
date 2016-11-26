#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// wifi connection variables
const char* ssid = "Circular Blue";
const char* password = "mightycartoon";
boolean wifiConnected = false;
int counter=1;

// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged"; // a string to send back

void setup() {
// Initialise Serial connection
Serial.begin(115200);

// Initialise wifi connection
wifiConnected = connectWifi();

// only proceed if wifi connection successful
if(wifiConnected){
udpConnected = connectUDP();
if (udpConnected){
// initialise pins
Serial.println("UDP connected");
}
}
}

void loop() {
// check if the WiFi and UDP connections were successful
if(wifiConnected){
if(udpConnected){

// if there’s data available, read a packet


// send a reply, to the IP address and port that sent us the packet we received
UDP.beginPacket("192.168.1.255", 80);
Request_Case(counter);
counter++;
if(counter>8)
{
counter=1;
}
/*UDP.write("jackhammer,1,1");
delay(3000);
UDP.write("jackhammer,1,0");
delay(3000);
UDP.write("jackhammer,2,1");
delay(3000);
UDP.write("jackhammer,2,0");
delay(3000);
UDP.write("jackhammer,3,1");
delay(3000);
UDP.write("jackhammer,3,0");
delay(3000);
UDP.write("jackhammer,4,1");
delay(3000);
UDP.write("jackhammer,4,0");
delay(3000);
UDP.endPacket();
*/
// turn LED on or off depending on value recieved

}
delay(10);

int packetSize = UDP.parsePacket();
if(packetSize)
{
Serial.println("");
Serial.print("Received packet of size ");
Serial.println(packetSize);
Serial.print("From ");
IPAddress remote = UDP.remoteIP();
for (int i =0; i < 4; i++)
{
Serial.print(remote[i], DEC);
if (i < 3)
{
Serial.print(".");
}
}
Serial.print(", port ");
Serial.println(UDP.remotePort());

// read the packet into packetBufffer
UDP.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
Serial.println("Contents:");
//int value = packetBuffer[0]*256 + packetBuffer[1];
for(int i=0;i<packetSize;i++)
Serial.print(char(packetBuffer[i]));

}

}

}


// connect to UDP – returns true if successful or false if not
boolean connectUDP(){
boolean state = false;

Serial.println("");
Serial.println("Connecting to UDP");

if(UDP.begin(localPort) == 1){
Serial.println("Connection successful");
state = true;
}
else{
Serial.println("Connection failed");
}

return state;
}
// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
boolean state = true;
int i = 0;
WiFi.begin(ssid, password);
Serial.println("");
Serial.println("Connecting to WiFi");

// Wait for connection
Serial.print("Connecting");
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
if (i > 10){
state = false;
break;
}
i++;
}
if (state){
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
}
else {
Serial.println("");
Serial.println("Connection failed.");
}
return state;
}
