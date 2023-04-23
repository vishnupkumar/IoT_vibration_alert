#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);

const char* ssid = "ssid";
const char* password = "password";
String  data =""; 

int motor = D1;

void setup()
{
  pinMode(motor, OUTPUT);
  server.begin();
  Serial.begin(115200);
  connectWiFi();
  digitalWrite(motor,LOW);
}

void loop()
{
    client = server.available();
    if (!client) return; 
    data = checkClient ();
    
    Serial.println(data);
    
    if (data == "on") motorOn();
    else if (data == "off") motorOff();
    else motorOff();
   

} 

void motorOn(void)   
{
  digitalWrite(motor,HIGH);
  Serial.println("on");  
}

void motorOff(void)   
{
  digitalWrite(motor,LOW);
  Serial.println("off");
}

String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}
