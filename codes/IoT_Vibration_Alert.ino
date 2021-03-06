#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);

const char* ssid = "ssid";
const char* password = "password";
String  data =""; 

int motor = D1;
int buzzer_pin = D2;

struct MusicStruct {
  int A = 550;
  int As = 582;
  int B = 617;
  int C = 654;
  int Cs = 693;
  int D = 734;
  int Ds = 777;
  int E = 824;
  int F = 873;
  int Fs = 925;
  int G = 980;
  int Gs = 1003;
  int A2 = 1100;
  int A2s = 1165;
  int B2 = 1234;
  int C3 = 1308;
  int C3s = 1385;
  int D3 = 1555;
}Music;

struct LengthStruct {
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
}Length;

int tempo = 1000;


void setup()
{
  pinMode(motor, OUTPUT);
  server.begin();
  Serial.begin(115200);
  connectWiFi();
  digitalWrite(motor,LOW);
}

void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
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
    setTone(buzzer_pin, Music.B, tempo * Length.one);
  setTone(buzzer_pin, Music.E, tempo * Length.one_half);
  setTone(buzzer_pin, Music.G, tempo * Length.half);
  setTone(buzzer_pin, Music.F, tempo * Length.one);
  setTone(buzzer_pin, Music.E, tempo * Length.two);
  setTone(buzzer_pin, Music.B2, tempo * Length.one);
  setTone(buzzer_pin, Music.A2, tempo * Length.two_half);
  setTone(buzzer_pin, Music.Fs, tempo * Length.two_half);

  
}

void motorOff(void)   
{
  digitalWrite(motor,LOW);
  Serial.println("off");
  delay(1000);
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
