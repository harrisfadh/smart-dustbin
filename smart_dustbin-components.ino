#include <ESP8266WiFi.h>         // Include ESP8266 library
#include <FirebaseArduino.h>     // Include Firebase Arduino library
#include <SoftwareSerial.h>      // Include software serial library
#include <LiquidCrystal.h>
#include <Servo.h>

#define FIREBASE_HOST "smart-dustbin-c16c2-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "tRMSqeoYxYgRIguv96tDjTivLH1FT6hSJV74Jf6b"

#define WIFI_SSID "harleyQuinn"  //wifi ssid
#define WIFI_PASSWORD "12345678"   //wifi password

#define angle_0 0
#define angle_90 90       //motor angle 90
#define angle_180 180     //motor angle 180

#define detector_echo D6
#define detector_trig D7
#define dustbin_echo D8
#define dustbin_trig D9
#define servo_motor D10
/*#define rs D12
#define en D11
#define d4 D5
#define d5 D4
#define d6 D3
#define d7 D2*/

long duration_dustbin;
int distance_dustbin;
long duration_detector;
int distance_detector;
//const int rs = D12, en = D11, d4 = D5, d5 = D4, d6 = D3, d7 = D2;

//LiquidCrystal lcd(D12, D11, D5, D4, D3, D2);
Servo servo;
SoftwareSerial mySerial(D14, D13); //Configure mySerial for GSM

void WiFiConnection(){
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  Serial.print("connecting");  
  
  while (WiFi.status() != WL_CONNECTED)
  {  
    Serial.print(".");  
    delay(500);  
  }

  Serial.println();  
  Serial.print("connected: ");  
  Serial.println(WiFi.localIP());  

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //firebase initialization
  }

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);   //begin gsm mySerial
pinMode(dustbin_echo, INPUT);
pinMode(dustbin_trig, OUTPUT);
pinMode(detector_echo, INPUT);
pinMode(detector_trig, OUTPUT);
servo.attach(servo_motor);
servo.write(angle_0);
//lcd.begin(16,2);
//lcd.setCursor(0,0);
//lcd.print("TEST");
WiFiConnection();
}

void loop() {
  // put your main code here, to run repeatedly:
  
digitalWrite(dustbin_trig, LOW);
delay(100);
digitalWrite(dustbin_trig, HIGH);
delay(100);
digitalWrite(dustbin_trig, LOW);
duration_dustbin = pulseIn(dustbin_echo, HIGH);
distance_dustbin = duration_dustbin * 0.034/2;
Serial.print("Dustbin distance: ");
Serial.print(distance_dustbin);
Serial.println(" cm");

digitalWrite(detector_trig, LOW);
delay(100);
digitalWrite(detector_trig, HIGH);
delay(100);
digitalWrite(detector_trig, LOW);
duration_detector = pulseIn(detector_echo, HIGH);
distance_detector = duration_detector * 0.034/2;
Serial.print("Hand detector distance: ");
Serial.print(distance_detector);
Serial.println(" cm");
Serial.println("");

if((distance_detector <= 15) && (distance_dustbin > 7)){
  servo.write(angle_90);
  delay(4000);
  servo.write(angle_0);
}

if(distance_dustbin <= 7){
  servo.write(angle_0);
}

else if((distance_dustbin >= 26) && (distance_dustbin <= 30)){
  Firebase.setInt("empty", 1);
  Firebase.setInt("btm_quarter", 0);
  Firebase.setInt("half", 0);
  Firebase.setInt("upper_quarter", 0);
  Firebase.setInt("full", 0);
}

else if((distance_dustbin <= 24) && (distance_dustbin >= 20)){
  Firebase.setInt("empty", 0);
  Firebase.setInt("btm_quarter", 1);
  Firebase.setInt("half", 0);
  Firebase.setInt("upper_quarter", 0);
  Firebase.setInt("full", 0);
}

else if((distance_dustbin <= 19) && (distance_dustbin >= 13)){
  Firebase.setInt("empty", 0);
  Firebase.setInt("btm_quarter", 0);
  Firebase.setInt("half", 1);
  Firebase.setInt("upper_quarter", 0);
  Firebase.setInt("full", 0);
}

else if((distance_dustbin <= 12) && (distance_dustbin >= 8)){
  Firebase.setInt("empty", 0);
  Firebase.setInt("btm_quarter", 0);
  Firebase.setInt("half", 0);
  Firebase.setInt("upper_quarter", 1);
  Firebase.setInt("full", 0);
}

else if((distance_dustbin <= 7)){
  send_message();
  Firebase.setInt("empty", 0);
  Firebase.setInt("btm_quarter", 0);
  Firebase.setInt("half", 0);
  Firebase.setInt("upper_quarter", 0);
  Firebase.setInt("full", 1);
}
}

void send_message() {
 mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+601xxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Dustbin is FULL!");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(10000);
}
