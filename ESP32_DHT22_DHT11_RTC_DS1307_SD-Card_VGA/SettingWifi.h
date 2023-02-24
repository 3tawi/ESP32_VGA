/*
 * Adapted by 3tawi
 * Aurora: https://github.com/pixelmatix/aurora
 * Copyright (c) 2014 Jason Coon
 *
 */

#ifndef SettingWifi_H
#define SettingWifi_H
#include <WebServer.h>

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
  getAPWifi();
  }
    
void getAPWifi() {
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP(Apssid, Appassword);
  textip = "Local Wifi : ";
  textip += Apssid;
  textip += " Password: ";
  textip += Appassword;
  textip += " IP Address: http://";
  textip += WiFi.softAPIP().toString().c_str();
  msg = 4, effects.getmesg(); 
  Serial.println("");
  Serial.println(textip);
}

void handleRoot() {
  File file = SPIFFS.open("/index.html");
  if (file) {
    size_t sent = server.streamFile(file, "text/html"); //Send web page
  }
    file.close();
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
void handleMode24h() {
    handleRoot(); 
    Mode24h = !Mode24h;
    NewRTCm = 60;
}
void handlelocaltime() { 
    handleRoot();
    rtc.setTime(server.arg("locadt").toInt());
    effects.writeTime();
    msg = 5, effects.getmesg();  
    NewRTCm = 60;
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
  content += "</analog></inputs>";
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200, "text/xml", content); //Send web page
}

};

#endif
