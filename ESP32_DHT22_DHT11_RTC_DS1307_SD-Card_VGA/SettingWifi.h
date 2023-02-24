/*
 * Adapted by 3tawi
 * Aurora: https://github.com/pixelmatix/aurora
 * Copyright (c) 2014 Jason Coon
 *
 */

#ifndef SettingWifi_H
#define SettingWifi_H

#include <WiFi.h>
#include <WebServer.h>
#include "index.h"

WebServer server(80);
IPAddress ip(192,168,1,31); // 30 to 250
IPAddress gateway(192, 168,1,1);
IPAddress gatewayap(192,168,4,1);
IPAddress subnet(255, 255, 255, 0);

class SettingWifi {
  private:
const char* Apssid = "Esp32-P3";
const char* Appassword = "GPxMatrix";
  
  public:
    
  void Setup() {
    effects.readSttWifi();
    if (wifiok) getWifi();
    else getAPWifi();
  }
  
void getWifi() {
  int lengthSsid = Ssid.length() + 1;
  int lengthPass = Pass.length() + 1;
  char user[lengthSsid], pasw[lengthPass];
  Ssid.toCharArray(user, lengthSsid);
  Pass.toCharArray(pasw, lengthPass);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(user, pasw);
  int xc = 0;
    Serial.println(" ");
  while (WiFi.status() != WL_CONNECTED && xc < 15) {
    delay(1000);
    Serial.print(".");
    xc++;
  }
    Serial.println(" ");
  if (WiFi.status() == WL_CONNECTED) { 
    textip = "CONNECTED To: ";
    textip += Ssid;
    textip += " IP Address: http://";
    textip += WiFi.localIP().toString().c_str();
    wifiok = true;
    msg = 4, effects.getmesg();
    } else { 
    wifiok = false;
    } 
  Serial.println("");
  Serial.println(textip);
}
    
void getAPWifi() {
  if (wifiapok) WiFi.softAPdisconnect(true);
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(Apssid, Appassword);
  textip = "Local Wifi : ";
  textip += Apssid;
  textip += " Password: ";
  textip += Appassword;
  textip += " IP Address: http://";
  textip += WiFi.softAPIP().toString().c_str();
  msg = 4, effects.getmesg(); 
  wifiapok = true;
  wifiok = false;
  Serial.println("");
  Serial.println(textip);
}
  
void handleRoot() {
 server.send(200, "text/html", MAIN_page); //Send web page
}
void handlesendate() { 
    handleRoot();
    datetxt = server.arg("bday");
    datee = "/Temhumi/";
    datee += datetxt;
    datee += ".txt";
}
void sendatetxt() {
    datetxt = rtc.getTime("%F");
    datee = "/Temhumi/";
    datee += datetxt;
    datee += ".txt";
}
void handletxt() {
  if (datetxt == "") { sendatetxt(); }
  File fdate = SD.open(datee);
  if (fdate) {
    size_t sent = server.streamFile(fdate, "text/plain");
  } else {
    server.send(200, "text/plain", "file not fond");
  }
    fdate.close();
}
void handleWifi() { 
  handleRoot(); 
  Ssid = server.arg("usname");
  Pass = server.arg("pssw");
  getWifi();
  if (!wifiok) getAPWifi();
}
void handleSpe0() {
    handleRoot();
    sp0 = server.arg("Speed0").toInt();
}
void handleSpe1() {
    handleRoot();
    sp1 = server.arg("Speed1").toInt();
}
void handleMode24h() {
    handleRoot(); 
    Mode24h = !Mode24h;
    NewRTCm = 60;
}
void handleModeAuto() {
    handleRoot();
    ModeAuto = !ModeAuto;
    NewRTCm = 60;
}
void handlezoneTime() {
    handleRoot();
    Tz = server.arg("locatz").toInt(); 
    configTime(Tz * 3600, 0, "", "");
    xps = 490, textmsg = "Zone Time Up"; 
    NewRTCm = 60;
}
void handlelocaltime() { 
    handleRoot();
    rtc.setTime(server.arg("locadt").toInt());
    xps = 490, textmsg = "Local Time Up"; 
    NewRTCm = 60;
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
    rtc.setTime(s, m, h, dd, mo, yr);
    xps = 490, textmsg = "Manual Time Up"; 
    NewRTCm = 60;
}
void handleChangefont() { 
    handleRoot();
    fon++;
    fon%=4;
    strtemp = effects.TraTextMesg(ftemp[fon]);
    strhumi = effects.TraTextMesg(fhumi[fon]);
    NewRTCm = 60;
}
void handleMesg() { 
    handleRoot();
    Message = server.arg("Message");
    Message = effects.TraTextMesg(Message);
    msg = 0, effects.getmesg(); 
}
void handlestate() {
  String content = "<?xml version = \"1.0\" ?>";
  content += "<inputs><analog>";
  content += NewTemp;
  content += "</analog><analog>";
  content += NewHumi;
  content += "</analog><analog>";
  content += Tz;
  content += "</analog><analog>";
  content += Ci+1;
  content += "</analog><analog>";
  content += ModeAuto;
  content += "</analog><analog>";
  content += Mode24h;
  content += "</analog><analog>";
  content += sp0;
  content += "</analog><analog>";
  content += sp1;
  content += "</analog><analog>";
  content += fon;
  content += "</analog></inputs>";
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/xml", content); //Send web page
}
void handledata() {
  String content = "<?xml version = \"1.0\" ?>";
  content += "<inputs><analog>";
  content += datetxt;
  content += "</analog></inputs>";
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/xml", content); //Send web page
}

};

#endif
