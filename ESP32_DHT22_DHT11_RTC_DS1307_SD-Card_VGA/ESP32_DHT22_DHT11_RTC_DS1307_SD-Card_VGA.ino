// REQUIRES the following Arduino libraries:
// - Lien vidéo: https://youtu.be/bQL0pm41uJY
// - Diagram: https://youtu.be/Ezd5nrAYFwA
// - VGA Library: https://github.com/bitluni/ESP32Lib
// - Adafruit_GFX Library: https://github.com/adafruit/Adafruit-GFX-Library
// - DS1307ESP Library: https://github.com/3tawi/DS1307ESP
// - DHT Sensor Library: https://github.com/3tawi/EspDHT
// - Getting Started ESP32 / ESP32S : https://www.youtube.com/watch?v=9b0Txt-yF7E
// Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects

#include <WiFi.h>
#include <SD.h>
#include "SPIFFS.h"
#include <ESP32Lib.h>
#include <GfxWrapper.h>
#include <DS1307ESPTime.h>
#include <esp32DHT.h>
#include <fontclock.h>
#include <atawi19x11c.h>
#include <atawi11x7g.h>
#include <Ressources/Font8x8.h>

//vga pin configuration
const int redPin = 27;
const int greenPin = 26;
const int bluePin = 25;
const int vsyncPin = 32;
const int hsyncPin = 33;


VGA3BitI vga;
GfxWrapper<VGA3BitI> gfx(vga, 560, 400);
GFXcanvas1 canvasM(560, 77);
DS1307ESPTime rtc;
DHT11 sensor;

String text, textmsg, textip;
String datee, datetxt, ddate;
String Message = "Great Projects wish you a very nice day. Hope you have a great time ahead.";
uint16_t myBLACK = vga.RGB(0,0,0);
uint16_t myCOLOR[7] = {0x00FF, 0x0FFF, 0x0F0F, 0xFF0F, 0xF00F, 0xF0FF, 0xFFFF};
int ac, cc, Ci;
uint8_t  r, g, b;
int sp0, sp1, sp2 = 15, msg = 4;
long valhue;
long value;
float Temp, Humi;
float NewTemp, NewHumi;
int NewRTCm = 60;
bool flasher;
bool TempHumi;
bool ModeAuto;
bool Mode24h = true;
int xps=530;
int   dx, dy;
const int buttonPin = 35;
int buttonState;
bool modeS = true;
int Tz = 1; // Time Zone

long frameTime = 0;
long currentTime  = 0;
long lastTime = 0;
long maxTime = 45000; // 45 seconds
long prevTime = 0;

#include "Effects.h"
Effects effects;
#include "Play.h"
#include "SettingWifi.h"
#include "Modeclock.h"
Modeclock Mode;
SettingWifi wifi;

void(* resetFunc) (void) = 0;//declare reset function at address 0

void handleModera() { 
    vga.clear(0);
    Mode.stop();  
    Mode.move(1);
    Mode.start(); 
    Ci = Mode.getModeIndex();
}
  
int changechar(int sou) {
    switch(sou) {
    case 7838 :
        sou = 223;
        break;
    }
    return (sou);
}
String changeMesg(String source) {
  int k = source.length();
  String sour = "";
  Message = "";
  for(int j=0; j<k; j++) {
    sour = "";
    char sox = source[j], soy = source[j+1];
    if (sox == '&' && soy == '#') {
      j+=2;
      while (source[j] != ';') {
        sour += source[j];
        j++;
      }
  Message += (char)(changechar(sour.toInt()));
    } else {
    Message += source[j];
    }
  }
    return (Message);
}
void getstting() { 
    sp0 = 12;
    sp1 = 1;
    Ci  = 0;
    ModeAuto  = true;
    Tz  = 1;
    maxTime = 60000;
    Message = readFile("/Message.txt");
    vga.setFrameBufferCount(2);
    //rtc.setTime(0, 5, 3, 17, 12, 2022); // 03:05:00 17-12-2022
    //rtc.DSsetdatime(); 
}
void getsttingwifi() {
    sp0 = 12;
    sp1 = 1;
    Ci  = 0;
    ModeAuto  = false;
    Tz  = 1;
    maxTime = 60000;
    configTime(Tz * 3600, 0, "", "");
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  rtc.DSbegin();
  rtc.DSgetdatime();
  if (modeS) {
    wifi.Setup();
    Serial.println("modeS == 1");
    server.on("/", hanRoot);
    server.on("/readstat", hanstate);
    server.on("/localdatime", hanlocaltime);
    server.on("/mode24h", hanMode24h);
    server.on("/readtext", hantxt);
    server.begin();
    getsttingwifi();
  } else {
    Serial.println("modeS == 0");
    getstting();
  }
  vga.init(vga.MODE720x400.custom(560, 400), redPin, greenPin, bluePin, hsyncPin, vsyncPin);
  gfx.setTextWrap(false);
  canvasM.setTextWrap(false);
  delay(1000);
  sensor.setup(2);  // pin 13 is DATA
  SD.begin(5);
  sensor.onData([](float humidity, float temperature) {
  NewHumi = humidity;
  NewTemp = temperature;
  });
  Mode.setModeclock(Ci);
  Mode.start();
}

void hanRoot(){
    wifi.handleRoot();
}
void hantxt(){
    wifi.handletxt();
}
void hanstate(){
    wifi.handlestate();
}
void hanMode24h(){
    wifi.handleMode24h();
}
void hanlocaltime(){
    wifi.handlelocaltime();
}

void loop() {
    frameTime = millis();
    if (ModeAuto  &&  (millis() - lastTime > maxTime)) { 
    handleModera();
    lastTime = millis();
    }
    if ( prevTime < frameTime)
    {
      prevTime = Mode.playframe() + frameTime;
    }
}

String readFile(const String path) {
    File file = SPIFFS.open(path);
    String Mesg = "";
     if(!file || file.isDirectory()){ return Mesg; } 
     else { 
    while (file.available()) {
      int savednum = file.read();
      Mesg += (char)savednum;
    }
    }
    file.close();
    return Mesg;
}

void writeFile(const String path, const String mesg){
    File file = SPIFFS.open(path, FILE_WRITE);
     if(!file){ return; } 
     else { file.print(mesg); }
    file.close();
}
