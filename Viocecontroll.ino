#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FirebaseArduino.h>
#include <TridentTD_LineNotify.h>
#include <Time.h>
#define FIREBASE_HOST "---"
#define FIREBASE_AUTH "---"
#define WIFI_SSID "AAA"
#define WIFI_PASSWORD "123456789"
#define TOKENCOUNT  1
#define LINE_TOKEN {"---"}



const int relayPin1 = D1;
const int relayPin2 = D2;
const int relayPin3 = D3;
const int relayPin4 = D4;



const long utcOffsetInSeconds = 25200;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
String status;



void setup() {

  LINE.setToken(LINE_TOKEN);
  Serial.begin(115200);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  timeClient.begin(true);
}

void loop()
{

  //แสดงเวลาปัจจุบัน
  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());  
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

      status = Firebase.getString("onauto");
      String Auto = Firebase.getString("onauto");
      Serial.println("Auto"+(Auto));
       {
        if (Auto == "1"){
        }
        else if (timeClient.getHours() == 18 && timeClient.getMinutes() == 00 && timeClient.getSeconds() == 0 ){
                  LINE.notify("ใกล้มืดแล้วอย่าลืมเปิดไฟด้วยค่ะ");
        }
        else if (timeClient.getHours() == 18 && timeClient.getMinutes() == 00 && timeClient.getSeconds() == 1 ){
                  LINE.notify("ใกล้มืดแล้วอย่าลืมเปิดไฟด้วยค่ะ");
        }
        else if (timeClient.getHours() == 18 && timeClient.getMinutes() == 00 && timeClient.getSeconds() == 2 ){
                  LINE.notify("ใกล้มืดแล้วอย่าลืมเปิดไฟด้วยค่ะ");
        }
        else if (timeClient.getHours() == 18 && timeClient.getMinutes() == 00 && timeClient.getSeconds() == 3 ){
                  LINE.notify("ใกล้มืดแล้วอย่าลืมเปิดไฟด้วยค่ะ");
        }
        else if (timeClient.getHours() == 8 && timeClient.getMinutes() == 30 && timeClient.getSeconds() == 0 ){
                  LINE.notify("สายแล้วอย่าลืมเปิดไฟด้วยค่ะ");
        }
        else if (timeClient.getHours() == 8 && timeClient.getMinutes() == 30 && timeClient.getSeconds() == 1 ){
                  LINE.notify("สายแล้วอย่าลืมเปิดไฟด้วยค่ะ");
        }
        else if (timeClient.getHours() == 8 && timeClient.getMinutes() == 30 && timeClient.getSeconds() == 2 ){
                  LINE.notify("สายแล้วอย่าลืมเปิดไฟด้วยค่ะ");
        }
        else if (timeClient.getHours() == 8 && timeClient.getMinutes() == 30 && timeClient.getSeconds() == 3 ){
                  LINE.notify("สายแล้วอย่าลืมเปิดไฟด้วยค่ะ");
        }
  }

  //automode++++++++++++++++++++++++++++++
  status = Firebase.getString("onauto");
    if(status=="0")
    {
      }
      else if (timeClient.getHours() == 18 && timeClient.getMinutes() == 10 ) { //ถ้าชั่วโมงเท่ากับ 18 และนาทีเท่ากับ 0 จะสั่งให้เปิดไฟ 
        Firebase.set("onone", "1");
        Firebase.set("ontwo", "1");
        Firebase.set("onthree", "1");
      }

      else if (timeClient.getHours() == 6 && timeClient.getMinutes() ==  30 ) { //ถ้าชั่วโมงเท่ากับ 6 และนาทีเท่ากับ 0 จะสั่งให้เปิดไฟ 
        Firebase.set("onone", "");
        Firebase.set("ontwo", "");
        Firebase.set("onthree", "");

      }
 
    {
      status = Firebase.getString("onone");
      if (status == "1") {
        digitalWrite(relayPin1, LOW);
        Serial.println("LED ONE: ON");
      }
      else {
        Serial.println("LED ONE: OFF");
        digitalWrite(relayPin1, HIGH);
      }
    }
    {
      status = Firebase.getString("ontwo");
      if (status == "1") {
        digitalWrite(relayPin2, LOW);
        Serial.println("LED TWO : ON");
      }
      else {
        Serial.println("LED TWO : OFF");
        digitalWrite(relayPin2, HIGH);
      }
    }
    {
      status = Firebase.getString("onthree");
      if (status == "1") {
        digitalWrite(relayPin3, LOW);
        Serial.println("LED THREE : ON");
      }
      else {
        Serial.println("LED THREE : OFF");
        digitalWrite(relayPin3, HIGH);
      }
    }
      {
        status = Firebase.getString("onfan");
        if (status == "1") {
          digitalWrite(relayPin4, LOW);
          Serial.println("FAN : ON");
        }
        else {
          Serial.println("FAN : OFF");
          digitalWrite(relayPin4, HIGH);
        }
      }


  //STATUS LIGHTS ONE ++++++++++++++++++++++++++
{
status = Firebase.getString("onstatuslightsone");
  if(status=="1")
  {
  }
  else if (digitalRead(D1))  {
    LINE.notify("LIGHTS ONE : OFF");
    Firebase.set("onstatuslightsone", "1");
  }
  else {
    LINE.notify("LIGHTS ONE : ON");
    Firebase.set("onstatuslightsone", "1");
  }
 }
 //STATUS LIGHTS TWO +++++++++++++++++++++++++++++
 {
status = Firebase.getString("onstatuslightstwo");
  if(status=="1")
  {
  }
  else if (digitalRead(D2))  {
    LINE.notify("LIGHTS TWO : OFF");
    Firebase.set("onstatuslightstwo", "1");
  }
  else {
    LINE.notify("LIGHTS TWO : ON");
    Firebase.set("onstatuslightstwo", "1");
  }
 }
 //STATUS LIGHTS THREE ++++++++++++++++++++++++++++
 {
status = Firebase.getString("onstatuslightsthree");
  if(status=="1")
  {
  }
  else if (digitalRead(D3))  {
    LINE.notify("LIGHTS THREE : OFF");
    Firebase.set("onstatuslightsthree", "1");
  }
  else {
    LINE.notify("LIGHTS THREE : ON");
    Firebase.set("onstatuslightsthree", "1");
  }
 }
 //STATUS FAN ++++++++++++++++++++++++++++++++++++
 {
status = Firebase.getString("onstatuslightsfan");
  if(status=="1")
  {
  }
  else if (digitalRead(D4))  {
    LINE.notify("FAN : OFF");
    Firebase.set("onstatuslightsfan", "1");
  }
  else {
    LINE.notify("FAN : ON");
    Firebase.set("onstatuslightsfan", "1");
  }
 }
//onauto status   
 {
      status = Firebase.getString("onauto");
      String Auto = Firebase.getString("onauto");
      Serial.println("Auto"+(Auto));
      status = Firebase.getString("onstatusauto");{
      if(status=="1")
        {
         }
      else if (Auto == "0")  {
        LINE.notify("AUTO : OFF");
        Firebase.set("onstatusauto", "1");
  }
      else if (Auto == "1"){
        LINE.notify("AUTO : ON");
        Firebase.set("onstatusauto", "1");
  }
      }
 }   
}   
//}


  