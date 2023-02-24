
// - Lien vidéo: https://youtu.be/bQL0pm41uJY

#ifndef Effects_H
#define Effects_H


  

class Effects {
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
  
 void drawCanva(int xx0, int yy0, int xx1, int yy1, int xx2, int yy2) {
  dx = (int)(sin(xps) * 32);
  dy  = (int)(cos(xps) * 16);
  for(int x=xx0; x < xx1; x++) {
    for(int y=yy0; y < yy1; y++) {
  int c0 = canvasM.getPixel(x, y);
  if (c0 != 0) {
  value = valhue
  + (uint8_t)((dx * dx + dy * dy) << 2);
    vga.dotFast(x+xx2, y+yy2, ColorHue(value)); 
    }
    dy--;
    }
    dx--;
   valhue-=3;
  }
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
  if (Temp != NewTemp || Humi != NewHumi) {
  Temp = NewTemp;
  Humi = NewHumi;
  wirttemphu();
  if      (Humi<20) { cc = 4; }
  else if (Humi<30) { cc = 3; }
  else if (Humi<60) { cc = 2; }
  else if (Humi<70) { cc = 1; }
  else              { cc = 0; }
  
  if      (Temp<15) { ac = 0; }
  else if (Temp<20) { ac = 1; }
  else if (Temp<30) { ac = 2; }
  else if (Temp<36) { ac = 3; }
  else              { ac = 4; }
  }
}
void wirttemphu() {
    ddate = "/Temhumi/";
    ddate += rtc.getTime("%F");
    ddate += ".txt";
    text = rtc.getTime();
    text += " ";
    text += "Temperature: ";
    text += Temp;
    text += " *C ";
    text += "Humidity: ";
    text += Humi;
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
String printTextMesg(String source) {
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
void getmesg()
{
    switch(msg)
    {
    case 0 :
        textmsg = Message;
        msg++;
        break;
    case 1 :
        redtemphumi();
        textmsg = "Temperature: ";
        textmsg += Temp;
        textmsg += (char)(1);
        msg++;
        break;
    case 2 :
        textmsg = "Humidity: ";
        textmsg += Humi;
        textmsg += " %";
        msg++;
        break;
    case 3 :
        textmsg = rtc.getDate(true);
        msg = 0;
        break;
    case 4 :
        textmsg = textip;
        msg = 0;
        break;
    }
}
void writeTime()
{
  configTime(0, 0, "", ""); 
  rtc.DSsetdatime(); 
  configTime(Tz * 3600, 0, "", "");
}
};

#endif
