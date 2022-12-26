// REQUIRES the following Arduino libraries:
// - Lien vidéo: https://youtu.be/bQL0pm41uJY
// - Diagram: https://youtu.be/Ezd5nrAYFwA
// - VGA Library: https://github.com/bitluni/ESP32Lib
// - DS1307ESP Library: https://github.com/3tawi/DS1307ESPTime
// - DHT Sensor Library: https://github.com/3tawi/esp32DHT
// - Adafruit_GFX Library: https://github.com/adafruit/Adafruit-GFX-Library
// - Getting Started ESP32 / ESP32S : https://www.youtube.com/watch?v=9b0Txt-yF7E
// Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects

#include <SD.h>
#include "SPIFFS.h"
#include <ESP32Lib.h>
#include <GfxWrapper.h>
#include <DS1307ESPTime.h>
#include <esp32DHT.h>
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
//DHT11 sensor;
DHT22 sensor;


String strtemp, strhumi;
String ftemp[4] = {"Temperature : ", "Température : ", "Temperatur : ", "Temperatura : "}; 
String fhumi[4] = {"Humidity : ", "Humidité : ", "Feuchtigkeit : ", "Humedad : "}; 
String  Ssid, Pass;
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
bool modewi;
bool wifiok = false;
bool wifiapok = false;
bool ModeAuto;
bool Mode24h = true;
int xps=490;
int dx, dy;
const int buttonPin = 35;
int buttonState;
int Tz = 1; // Time Zone
int fon = 3; // language 0 = EN  |  1 = FR  |  2 = GR | 3 = ES

long frameTime = 0;
long currentTime  = 0;
long lastTime = 0;
long maxTime = 45000; // 45 seconds
long prevTime = 0;

#include "Effects.h"
Effects effects;
#include "Play.h"
#include "SettingWifi.h"
SettingWifi wifi;
#include "Modeclock.h"
Modeclock Mode;

void(* resetFunc) (void) = 0;//declare reset function at address 0

  
void getstting() { 
  rtc.DSbegin();
  effects.readSttspeed();
  strtemp = effects.TraTextMesg(ftemp[fon]);
  strhumi = effects.TraTextMesg(fhumi[fon]);
  effects.updateTime();
  effects.prepacard();
}

void RedButton() { 
  delay(200); 
  buttonState = analogRead(buttonPin);
  Serial.println(buttonState);
  if (buttonState <= 500)
    modewi = true;
  else
    modewi = false;
    msg = 0, effects.getmesg(); 
}
void setup() {
  Serial.begin(115200);
  RedButton();
  SPIFFS.begin();
  getstting();
  if (modewi) wifisetup();
  vga.init(vga.MODE720x400.custom(560, 400), redPin, greenPin, bluePin, hsyncPin, vsyncPin);
  gfx.setTextWrap(false);
  canvasM.setTextWrap(false);
  delay(1000);
  sensor.setup(13);  // pin 13 is DATA
  SD.begin(3);
  sensor.onData([](float humidity, float temperature) {
  NewHumi = humidity;
  NewTemp = temperature;
  });
  Mode.setModeclock(Ci);
  Mode.start();
}

void loop() {
    Mode.playframe();
    if (ModeAuto  &&  (millis() - lastTime > (sp1*maxTime))) { 
      vga.clear(0);
      Mode.stop(); 
      Mode.setModeclock(Ci);
      Mode.start();  
      NewRTCm = 60;
      lastTime = millis();
    }
}

void wifisetup(){ 
  wifi.Setup();
  server.on("/", hanRoot);
  server.on("/readstat", hanstate);
  server.on("/mytimezon", hanzoneTime); 
  server.on("/mode24h", hanMode24h);
  server.on("/localdatime", hanlocaltime);
  server.on("/restime", hanMyTime);
  server.on("/sendate", hansendate);
  server.on("/readtext", hantxt);
  server.on("/mySpeed0", hanSpe0);
  server.on("/mySpeed1", hanSpe1);
  server.on("/myMesg", hanMesg); 
  server.on("/modepre", handleModePre);
  server.on("/modenex", handleModeNex);
  server.on("/modeauto", hanModeAuto);
  server.on("/Mywifi", hanWifi);
  server.on("/readdata", handata);
  server.on("/modepat", handleModePat);
  server.on("/langue", hanChangefont);
  server.on("/modesave", hanSave);
  server.on("/restesp", resetFunc);
  server.begin();
  }

void hanRoot(){ wifi.handleRoot(); }
void hansendate(){ wifi.handlesendate(); }
void hantxt(){ wifi.handletxt(); }
void hanstate(){ wifi.handlestate(); }
void hanMode24h(){ wifi.handleMode24h(); }
void hanzoneTime(){ wifi.handlezoneTime(); }
void hanlocaltime(){ wifi.handlelocaltime(); }
void hanMyTime(){ wifi.handleMyTime(); }
void hanSpe0(){ wifi.handleSpe0(); }
void hanSpe1(){ wifi.handleSpe1(); }
void hanMesg(){ wifi.handleMesg(); }
void hanWifi(){ wifi.handleWifi(); }
void handata(){ wifi.handledata(); }
void hanChangefont(){ wifi.handleChangefont(); }
void hanModeAuto(){ wifi.handleModeAuto(); }
void hanSave(){ effects.handleSave(); }

void handleModePat() {
  wifi.handleRoot();
  Ci = server.arg("Pattern").toInt();
  Ci -= 1;
  lastTime = 0; 
}
void handleModeNex() {
  wifi.handleRoot();
  Mode.move(1);
  Ci = Mode.getModeIndex(); 
  lastTime = 0; 
}
void handleModePre() {
  wifi.handleRoot();
  Mode.move(-1);
  Ci = Mode.getModeIndex();
  lastTime = 0; 
}
