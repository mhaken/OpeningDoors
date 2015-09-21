#include <SPI.h>
#include <Ethernet.h>

 byte mac[] = { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA }; //physical mac address
 byte ip[] = { 192, 168, 1, 200 }; // fixed IP addr in LAN
 byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
 byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
 EthernetServer server(80); //server port

 String readString;

 void setup(){
 pinMode(6, OUTPUT); //pin selected to control LED
 //start Ethernet
 Ethernet.begin(mac, ip, gateway, subnet);
 server.begin();
 //the pin for the servo co
 //enable serial data print
 Serial.begin(9600);
 }

 void loop(){
 // Create a client connection
   EthernetClient client = server.available();
   if (client) {
   while (client.connected()) {
    if (client.available()) {
    char c = client.read();

 //read char by char HTTP request
 if (readString.length() < 100) {

 //store characters to string
 readString += c;
 //Serial.print(c);
 }

 //if HTTP request has ended
 if (c == '\n') {

 ///////////////
 Serial.println(readString); //print to serial monitor for debuging
 client.println("HTTP/1.1 200 OK"); //send new page
 client.println("Content-Type: text/html");
 client.println(); 
 client.println("<HTML>");
 client.println("<HEAD> <STYLE>body{}</STYLE>");
 client.println("<TITLE>Home Automation</TITLE>");
 client.println("</HEAD>");
 client.println("<BODY'>");
 client.println("<H1>Home Automation</H1>");
 client.println("<hr />");
 client.println("<br />");

 client.println("<a href=\"/?lighton\"\"><div style='text-align:center;margin-left: auto;     margin-right: auto;    width: 60%;height:40%;background-color:red' ></div></a>");

 client.println("</BODY>");
 client.println("</HTML>");

 delay(1);
 //stopping client
 client.stop();

 ///////////////////// control arduino pin
 if(readString.indexOf("?lighton") >0)//checks for on
 {
 digitalWrite(6, HIGH); // set pin 6 high
 Serial.println("LED On");
 delay(2000);
 digitalWrite(6, LOW);
 }
 
 readString=""; //clearing string for next read

 }
 }
 }
 }
 } 
