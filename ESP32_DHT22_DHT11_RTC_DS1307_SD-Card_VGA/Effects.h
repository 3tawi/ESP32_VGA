
// - Lien vidéo: https://youtu.be/bQL0pm41uJY

#ifndef Effects_H
#define Effects_H


  

class Effects {

private:
const String MonthtostrFullEN[12] ={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November" , "December"};
const String MonthtostrEN[12]     ={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const String daytostrFullEN[7]    ={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const String daytostrEN[7]        ={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

const String MonthtostrFullFR[12] ={"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"};
const String MonthtostrFR[12]     ={"Jan", "Fév", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Déc"};
const String daytostrFullFR[7]    ={"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const String daytostrFR[7]        ={"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"} ; 

const String MonthtostrFullGR[12] ={"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
const String MonthtostrGR[12]     ={"Jan", "Feb", "März", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"};
const String daytostrFullGR[7]    ={"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
const String daytostrGR[7]        ={"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"}; 

const String MonthtostrFullES[12] ={"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
const String MonthtostrES[12]     ={"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
const String daytostrFullES[7]    ={"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
const String daytostrES[7]        ={"Dom", "Lun", "Mar", "Mié", "Jue", "Vie", "Sáb"}; 

public:
  

void Displaysegment(int segm, int xs, int ys, int hs, int ws, long cs) {
  switch(segm) {
    case 0 :
        vga.fillEllipse(xs+hs, ys, hs, ws, ColorHue(cs));
        vga.ellipse(xs+hs, ys, hs, ws, ColorHue(cs*2));
        break;
    case 1 :
        vga.fillEllipse(xs+(hs*2), ys+hs, ws, hs, ColorHue(cs+(segm*60)));
        vga.ellipse(xs+(hs*2), ys+hs, ws, hs, ColorHue(cs*2));
        break;
    case 2 :
        vga.fillEllipse(xs+(hs*2), ys+(hs*3), ws, hs, ColorHue(cs+(segm*60)));
        vga.ellipse(xs+(hs*2), ys+(hs*3), ws, hs, ColorHue(cs*2));
        break;
    case 3 :
        vga.fillEllipse(xs+hs, ys+(hs*4), hs, ws, ColorHue(cs+(segm*60)));
        vga.ellipse(xs+hs, ys+(hs*4), hs, ws, ColorHue(cs*2));
        break;
    case 4 :
        vga.fillEllipse(xs, ys+(hs*3), ws, hs, ColorHue(cs+(segm*60)));
        vga.ellipse(xs, ys+(hs*3), ws, hs, ColorHue(cs*2));
        break;
    case 5 :
        vga.fillEllipse(xs, ys+hs, ws, hs, ColorHue(cs+(segm*60)));
        vga.ellipse(xs, ys+hs, ws, hs, ColorHue(cs*2));
        break;
    case 6 :
        vga.fillEllipse(xs+hs, ys+(hs*2), hs, ws, ColorHue(cs+(segm*60)));
        vga.ellipse(xs+hs, ys+(hs*2), hs, ws, ColorHue(cs*2));
        break;
    }
}
void DisplayNumber(int xval, int xs, int ys, int hs, int ws, long cs) {
  if(xval != 1 && xval != 4)                           { Displaysegment(0, xs, ys, hs, ws, cs+(xval*200)); }         // a
  if(xval != 5 && xval != 6)                           { Displaysegment(1, xs, ys, hs, ws, cs+(xval*200)); }         // b
  if(xval != 2)                                        { Displaysegment(2, xs, ys, hs, ws, cs+(xval*200)); }         // c
  if(xval != 1 && xval != 4 && xval != 7)              { Displaysegment(3, xs, ys, hs, ws, cs+(xval*200)); }         // d
  if(xval == 0 || xval == 2 || xval == 6 || xval == 8) { Displaysegment(4, xs, ys, hs, ws, cs+(xval*200)); }         // e
  if(xval != 1 && xval != 2 && xval != 3 && xval != 7) { Displaysegment(5, xs, ys, hs, ws, cs+(xval*200)); }         // f
  if(xval != 0 && xval != 1 && xval != 7)              { Displaysegment(6, xs, ys, hs, ws, cs+(xval*200)); }         // g
}
  
 void printCanva(int xx0, int yy0, int xx1, int yy1, int xx2, int yy2) {
  dx = (int)(sin(xps) * 32);
  dy  = (int)(cos(xps) * 16);
  for(int x=xx0; x < xx1; x++) {
    for(int y=yy0; y < yy1; y++) {
  int c0 = canvasM.getPixel(x, y);
  if (c0 != 0) {
  value = valhue
  + (uint8_t)((dx * dx + dy * dy) << 2);
    vga.dotFast(x+xx2, y+yy2, ColorHue(value)); 
    } else {
     vga.dotFast(x+xx2, y+yy2, myBLACK);
   }
    dy--;
    }
    dx--;
   valhue-=3;
  }
  }

  void ClearFrame()
  {
      vga.clear(0);
  }
    
  void redtemphumi() {
  sensor.read();
  if (NewTemp != Temp || NewHumi != Humi) {
    if      (NewHumi<20) { cc = 4; }
    else if (NewHumi<30) { cc = 3; }
    else if (NewHumi<60) { cc = 2; }
    else if (NewHumi<70) { cc = 1; }
    else              { cc = 0; }
    if      (NewTemp<15) { ac = 0; }
    else if (NewTemp<20) { ac = 1; }
    else if (NewTemp<30) { ac = 2; }
    else if (NewTemp<36) { ac = 3; }
    else              { ac = 4; }
    wirttemphu();
    Temp = NewTemp;
    Humi = NewHumi;
    NewRTCm = 60;
  }
}
void wirttemphu() {
    ddate = "/Temhumi/";
    ddate += rtc.getTime("%F");
    ddate += ".txt";
    text = rtc.getTime();
    text += " ";
    text += strtemp;
    text += NewTemp;
    text += " *C ";
    text += strhumi;
    text += NewHumi;
    text += " %RH";
    text = text;
    writeFileSD(ddate, text);
}
void writeFileSD(const String path, const String mesg){
    File fileth = SD.open(path, FILE_APPEND);
     if(fileth){ fileth.println(mesg); } 
    fileth.close();
}

  VGA3BitI::Color ColorHue(long hue) {
  uint8_t lo;
  // Hue
  hue %= 1791; // -1791 to +1791
  if (hue < 0)
    hue += 1791;      //     0 to +1791
  lo = hue & 255;     // Low byte  = primary/secondary color mix
  switch (hue >> 8) { // High byte = sextant of colorwheel
  case 0:
    r = 255;
    g = 255 - lo;
    b = 255 - lo;
    break; // W to R
  case 1:
    r = 255;
    g = lo;
    b = 0;
    break; // R to Y
  case 2:
    r = 255 - lo;
    g = 255;
    b = 0;
    break; // Y to G
  case 3:
    r = 0;
    g = 255;
    b = lo;
    break; // G to C
  case 4:
    r = 0;
    g = 255 - lo;
    b = 255;
    break; // C to B
  case 5:
    r = lo;
    g = 0;
    b = 255;
    break; // B to M
  default:
    r = 255;
    g = lo;
    b = 255;
    break; // M to W
  }
    return vga.RGB(r,g,b);
} 
int codchar(char source1) {
  int so1 = source1;
    switch(so1) {
    case 169 :
        so1 = 232;
        break;
    case 168 :
        so1 = 233;
        break;
    case 187 :
        so1 = 251;
        break;
    case 164 :
        so1 = 228;
        break;
    case 161 :
        so1 = 225;
        break;
    default :
        so1 = 195;
        break;
    }
    return (so1);
}
int gtchar(char source1) {
  int so1 = source1;
    return (so1);
}
String TraTextMesg(String source) {
  int so;
  String sour="";
  int k = source.length();
  for(int j=0; j<k; j++) {
    so = gtchar(source[j]);
    if (so == 195) {
      so = codchar(source[j+1]);
    if (so != 195) { j++; }
      so = codchar(source[j]);
    }
    sour += char(so);
    }
    return (sour);
  }
  
String getfullDateMesg(int fo, bool mod = false) {
  char s[51];
  switch(fo) {
    case 0 :
      if (mod) {
        sprintf(s, "%s, %s, %02d %s %04d", rtc.getAmPm(), daytostrFullEN[rtc.getDayofWeek()], rtc.getDay(), MonthtostrFullEN[rtc.getMonth()], rtc.getYear()); }
      else {
        sprintf(s, "%s, %02d %s %04d", daytostrEN[rtc.getDayofWeek()], rtc.getDay(), MonthtostrEN[rtc.getMonth()], rtc.getYear()); }
      break;
    case 1 :
      if (mod) {
        sprintf(s, "%s, %s, %02d %s %04d", rtc.getAmPm(), daytostrFullFR[rtc.getDayofWeek()], rtc.getDay(), MonthtostrFullFR[rtc.getMonth()], rtc.getYear()); }
      else {
        sprintf(s, "%s, %02d %s %04d", daytostrFR[rtc.getDayofWeek()], rtc.getDay(), MonthtostrFR[rtc.getMonth()], rtc.getYear()); }
      break;
    case 2 :
      if (mod) {
        sprintf(s, "%s, %s, %02d %s %04d", rtc.getAmPm(), daytostrFullGR[rtc.getDayofWeek()], rtc.getDay(), MonthtostrFullGR[rtc.getMonth()], rtc.getYear()); }
      else {
        sprintf(s, "%s, %02d %s %04d", daytostrGR[rtc.getDayofWeek()], rtc.getDay(), MonthtostrGR[rtc.getMonth()], rtc.getYear()); }
      break;
    case 3 :
      if (mod) {
        sprintf(s, "%s, %s, %02d %s %04d", rtc.getAmPm(), daytostrFullES[rtc.getDayofWeek()], rtc.getDay(), MonthtostrFullES[rtc.getMonth()], rtc.getYear()); }
      else {
        sprintf(s, "%s, %02d %s %04d", daytostrES[rtc.getDayofWeek()], rtc.getDay(), MonthtostrES[rtc.getMonth()], rtc.getYear()); }
      break;
    }
  if (fo == 0) return String(s);
  return TraTextMesg(String(s));
}
  
void getmesg()
{
  xps = 490;
  switch(msg) {
    case 0 :
        textmsg = Message;
        msg++;
        break;
    case 1 :
        redtemphumi();
        textmsg = strtemp;
        textmsg += NewTemp;
        textmsg += (char)(1);
        msg++;
        break;
    case 2 :
        textmsg = strhumi;
        textmsg += NewHumi;
        textmsg += " %";
        msg++;
        break;
    case 3 :
        textmsg = getfullDateMesg(fon, true);
        msg = 0;
        break;
    case 4 :
        textmsg = "Hello!";
        msg = 5;
        break;
    case 5 :
        textmsg = textip;
        msg = 0;
        break;
    }
}

void readSttWifi() {
  File file = SPIFFS.open("/Stt-wifi.txt");
  if(file) {
    String textwifi = "";
    while (file.available()) {
      int savednum = file.read();
      textwifi += (char)savednum;
     }
    file.close();
    readsource(textwifi);
  }
}

void readSttspeed() {
  File file = SPIFFS.open("/Sttingsp.txt");
  if(file) {
    String text = "";
    while (file.available()) {
      int savednum = file.read();
      text += (char)savednum;
     }
    file.close();
    readsource(text);
  } else {
    Ci  = 0;
    Tz  = 1;
    sp0 = 12;
    sp1 = 10;
    maxTime = 60000;
    ModeAuto  = true;
    Mode24h = true;
  }
}

void readsource(String source) {
  String line = "";
  int k = source.length();
  for(int j=0; j<k; j++) {
    if (source[j] == '\n') {
      readLine(line);
      line = "";
      } else
    line += source[j];
  }
}
void readLine(String Line) {
        Serial.println(Line);
      if (Line.startsWith("speed0=")) {
        Line = Line.substring(7);
        if (Line.length() > 0) {
          sp0 = Line.toInt();
        }
        Serial.println(sp0);
      }
      else if (Line.startsWith("speed1=")) {
        Line = Line.substring(7);
        if (Line.length() > 0) {
          sp1 = Line.toInt();
        }
        Serial.println(sp1);
      }
      else if (Line.startsWith("Cindex=")) {
        Line = Line.substring(7);
        if (Line.length() > 0) {
          Ci = Line.toInt();
        }
        Serial.println(Ci);
      }
      else if (Line.startsWith("mAuto=")) {
        Line = Line.substring(6);
        if (Line.length() > 0) {
          ModeAuto = Line.toInt();
        }
        Serial.println(ModeAuto);
      }
      else if (Line.startsWith("m24h=")) {
        Line = Line.substring(5);
        if (Line.length() > 0) {
          Mode24h = Line.toInt();
        }
        Serial.println(ModeAuto);
      }
      else if (Line.startsWith("mymsge=")) {
        Line = Line.substring(7);
        if (Line.length() > 0) {
          Message = Line;
        }
        Serial.println(Message);
      }
      else if (Line.startsWith("Ssid=")) {
        Line = Line.substring(5);
        if (Line.length() > 0) {
          Ssid = Line;
        }
        Serial.println(Ssid);
      }
      else if (Line.startsWith("Pass=")) {
        Line = Line.substring(5);
        if (Line.length() > 0) {
          Pass = Line;
        }
        Serial.println(Pass);
      }
      else if (Line.startsWith("Wifis=")) {
        Line = Line.substring(6);
        if (Line.length() > 0) {
          wifiok = Line.toInt();
        }
        Serial.println(wifiok);
      }
      else if (Line.startsWith("Lang=")) {
        Line = Line.substring(5);
        if (Line.length() > 0) {
          fon = Line.toInt();
        }
        Serial.println(fon);
      }
  }

void handleSave() {
   Savewifi();
   SaveStting();
   writeTime();
}
  
void Savewifi() {
    File file = SPIFFS.open("/Stt-wifi.txt", FILE_WRITE);
    if (file) {
      String textw =  "\n";
             textw += "Ssid=";
             textw += Ssid;
             textw += "\nPass=";
             textw += Pass;
             textw += "\nWifis=";
             textw += wifiok;
             textw += "\n";
      file.print(textw);
      file.close();
      Serial.println(textw);
    }
}
  
void SaveStting() {
    File file = SPIFFS.open("/Sttingsp.txt", FILE_WRITE);
    if (file) {
      String text =  "speed0=";
             text += sp0;
             text += "\nspeed1=";
             text += sp1;
             text += "\nCindex=";
             text += Ci;
             text += "\nmAuto=";
             text += ModeAuto;
             text += "\nm24h=";
             text += Mode24h;
             text += "\nmymsge=";
             text += Message;
             text += "\nLang=";
             text += fon;
             text += "\n";
      file.print(text);
      file.close();
      Serial.println(text);
    }
}

void prepacard() { 
    File root = SD.open("/Temhumi");
    if(!root.isDirectory()){
        SD.mkdir("/Temhumi");
    }
}

void updateTime()
{
  rtc.DSgetdatime(); 
  configTime(Tz * 3600, 0, "", "");
} 
  
void writeTime()
{
  configTime(0, 0, "", ""); 
  rtc.DSsetdatime(); 
  configTime(Tz * 3600, 0, "", "");
}
};

#endif
