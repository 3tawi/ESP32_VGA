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
#include <WebServer.h>
#include <SD.h>
#include "SPIFFS.h"
#include <ESP32Lib.h>
#include <Adafruit_GFX.h>
#include <GfxWrapper.h>
#include <DS1307ESP.h>
#include <EspDHT.h>
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
GfxWrapper<VGA3BitI> gfx(vga, 530, 400);
GFXcanvas1 canvasM(530, 77);
DS1307ESP rtc;
EspDHT dht;
WebServer server(80);

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
int xps=530;
int   dx, dy;
const int buttonPin = 35;
int buttonState;
bool modeS = false;
int Tz = 1; // Time Zone
int fon; // language 0 = EN  |  1 = FR  |  2 = GR | 3 = ES
String langfont[4] = {"EN", "FR", "GR", "ES"}; 

long frameTime = 0;
long currentTime  = 0;
long lastTime = 0;
long maxTime = 45000; // 45 seconds
long prevTime = 0;

const char* Apssid = "Esp32-VGA";
const char* Appassword = "3tawi-GP";
  IPAddress ip(192,168,1,69);
  IPAddress gateway(192, 168,1,1);
  IPAddress gatewayap(192,168,4,1);
  IPAddress subnet(255, 255, 255, 0);


#include "Effects.h"
Effects effects;
#include "Play.h"
#include "Modeclock.h"
Modeclock Mode;

void(* resetFunc) (void) = 0;//declare reset function at address 0


  void handleRoot() {
  File file = SPIFFS.open("/index.html");
  if (file) {
    size_t sent = server.streamFile(file, "text/html"); //Send web page
  }
    file.close();
}
void handlesendate() {
    handleRoot();
    datetxt = server.arg("bday");
  if (datetxt == "") { datetxt = rtc.getDayDate(); }
    datee = "/Temhumi/";
    datee += datetxt;
    datee += ".txt";
}
void handletxt() {
  if (datetxt == "") { handlesendate(); }
  File TempHumi = SD.open(datee);
  if (TempHumi) {
    size_t sent = server.streamFile(TempHumi, "text/plain");
  } else {
    server.send(200, "text/plain", "file not fond");
  }
    TempHumi.close();
}
void handleSpe0() {
    handleRoot();
    sp0 = server.arg("Speed0").toInt();
    rtc.write(1, sp0);
  }
void handleSpe1() {
    handleRoot();
    sp1 = server.arg("Speed1").toInt();
    rtc.write(2, sp1);
    maxTime = sp1 * 60000;
  }
void handleModera() { 
    if (modeS) { handleRoot(); }
    vga.clear(0);
    Mode.stop();  
    Mode.move(1);
    Mode.start(); 
    Ci = Mode.getModeIndex();
    Ci %= 3;
    rtc.write(3, Ci);
}
void handleModeam() { 
    handleRoot();
    ModeAuto = !ModeAuto;
    rtc.write(4, ModeAuto);
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
void handleMesg() { 
    handleRoot();
    Message = server.arg("Message");
    Message = changeMesg(Message);
    writeFile("/Message.txt", Message);
    msg = 0, effects.getmesg(); 
  }
void handlezoneTime() {
    handleRoot();
    Tz = server.arg("locatz").toInt(); 
    rtc.write(5, Tz);
}
void handlelocaltime() { 
    handleRoot();
    rtc.DSadjust(server.arg("locadt").toInt() + (Tz * 3600));
    msg = 3, effects.getmesg(); 
}
void handleMyTime() { 
    handleRoot();
    String hbuf = server.arg("htmie"); 
    String dbuf = server.arg("ddate");
    text = hbuf[0];
    text += hbuf[1];
    int h = text.toInt(); 
    text = hbuf[3];
    text += hbuf[4];
    int m = text.toInt(); 
    text = hbuf[6];
    text += hbuf[7];
    int s = text.toInt();
    
    text = dbuf[0];
    text += dbuf[1];
    text += dbuf[2];
    text += dbuf[3];
    int yr = text.toInt(); 
    text = dbuf[5];
    text += dbuf[6];
    int mo = text.toInt();
    text = dbuf[8];
    text += dbuf[9];
    int dd = text.toInt();
    rtc.DSadjust(h, m, s, yr, mo, dd);
    msg = 3, effects.getmesg(); 
}
void handlestate() {
  String content = "<?xml version = \"1.0\" ?>";
  content += "<inputs><analog>";
  content += Temp;
  content += "</analog><analog>";
  content += Humi;
  content += "</analog><analog>";
  content += Tz;
  content += "</analog><analog>";
  content += fon;
  content += "</analog><analog>";
  content += Ci+1;
  content += "</analog><analog>";
  content += ModeAuto;
  content += "</analog></inputs>";
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/xml", content); //Send web page
}
void handleMesge()
{
  String content = "<?xml version = \"1.0\" ?>";
  content += "<inputs><analog>";
  content += datetxt;
  content += "</analog></inputs>";
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/xml", content); //Send web page
}
void handleChangefont() {  
    handleRoot();
    fon++;
    fon%=4;
    rtc.SetFont(fon);
    rtc.write(6, fon);
    effects.getmesg();
}
void handleRestesp() {  
    handleRoot();
    delay(4000);     
    resetFunc();
}
void handleWifi() { 
  String user = server.arg("usname");
  String pasw = server.arg("pssw");
  writeFile("/Ssid.txt", user);
  writeFile("/Password.txt", pasw);
  effects.getWifi(user, pasw);
}
void getstting() { 
    sp0 = rtc.read(1);
    sp1 = rtc.read(2);
    Ci  = rtc.read(3);
    ModeAuto  = rtc.read(4);
    Tz  = rtc.read(5);
    fon  = rtc.read(6);
    maxTime = sp1 * 60000;
    if (Tz > 12) { Tz = Tz - 256; }
    Message = readFile("/Message.txt");
    rtc.SetFont(fon);
  if (modeS) {
    String user = readFile("/Ssid.txt");
    String pasw = readFile("/Password.txt");
    effects.getWifi(user, pasw);
    Ci  = 3;
    } else {
    vga.setFrameBufferCount(2);
    msg = 0, effects.getmesg(); 
    }
}
void RedButton() { 
  delay(200); 
  buttonState = analogRead(buttonPin);
  if (buttonState <= 100) {
    modeS = true;
  } else {
    modeS = false;
  }
}
void setup() {
  RedButton();
  rtc.begin();
  SPIFFS.begin();
  getstting(); 
  vga.init(vga.MODE720x400.custom(530, 400), redPin, greenPin, bluePin, hsyncPin, vsyncPin);
  gfx.setTextWrap(false);
  canvasM.setTextWrap(false);
  delay(1000);
  if (modeS) {
    server.on("/", handleRoot); 
    server.on("/MesSpeed0", handleSpe0); 
    server.on("/MesSpeed1", handleSpe1);
    server.on("/myMesg", handleMesg);  
    server.on("/mytimezon", handlezoneTime); 
    server.on("/localdatime", handlelocaltime);
    server.on("/restime", handleMyTime);
    server.on("/readtemhu", handlestate);
    server.on("/modera", handleModera);
    server.on("/modema", handleModeam);
    server.on("/changefont", handleChangefont);
    server.on("/Mywifi", handleWifi);
    server.on("/sendate", handlesendate);
    server.on("/readtext", handletxt);
    server.on("/readMesge", handleMesge); 
    server.on("/restesp", handleRestesp);
    server.begin();
  }
  dht.setup(13, EspDHT::DHT22);
  Mode.setModeclock(Ci);
  Mode.start();
  SD.begin(5);
}

void loop() {
    server.handleClient();
    frameTime = millis();
    if (ModeAuto  &&  millis() - lastTime > maxTime) { 
    handleModera();
    lastTime = millis();
    }
    if ( prevTime < frameTime)
    {
      prevTime = Mode.playframe() + frameTime;
    }
    if (TempHumi) {
    effects.redtemphumi();
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
