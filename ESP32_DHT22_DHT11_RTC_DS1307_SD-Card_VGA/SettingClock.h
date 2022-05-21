
// - Lien vidéo: https://youtu.be/bQL0pm41uJY

#ifndef SettingClock_H
class SettingClock : public Play {
private:
long hueColor;

public:
    SettingClock() {
        name = (char *)"SettingClock";
    }

    unsigned int playframe() {
    drawMesg();
    effects.printCanva(0, 0, 480, 77, 0, 0);
    if ( (millis() - currentTime) > 1000 ) { 
      rtc.DSread();
      drawTime();
      flasher = !flasher;
      hueColor++;
      currentTime = millis();
    }
        return 0;
    }
       
void drawTime() {
  drawTimese();
  if (NewRTCm != rtc.minute) {
  drawTemphu();
  drawDate();
  effects.printCanva(0, 0, 510, 55, 15, 260);
  drawTimehm();
  NewRTCm = rtc.minute;
      }
}
    
void drawTimese() {
  if (flasher) {
    vga.fillEllipse(220, 145, 6, 8, effects.ColorHue(hueColor*2));
    vga.fillEllipse(220, 200, 6, 8, effects.ColorHue(hueColor*2));
   } else {
     vga.fillEllipse(220, 145, 6, 8, vga.RGB(0));
     vga.fillEllipse(220, 200, 6, 8, vga.RGB(0));
   }
   vga.fillRect(450, 190, 80, 65, vga.RGB(0));
   int Vals = rtc.second;
   int dig1 = Vals / 10;
   int dig2 = Vals - (dig1 * 10);
   effects.DisplayNumber(dig1, 455, 200, 12, 5, hueColor+256);
   effects.DisplayNumber(dig2, 495, 200, 12, 5, hueColor+256);
}
    
void drawTimehm() {
   int Valh = rtc.hour;
   int Valm = rtc.minute;
   int dig1 = Valh / 10;
   int dig2 = Valh - (dig1 * 10);
   vga.fillRect(0, 85, 450, 175, vga.RGB(0));
   effects.DisplayNumber(dig1, 15, 96, 38, 11, hueColor);
   effects.DisplayNumber(dig2, 120, 96, 38, 11, hueColor);
   dig1 = Valm / 10;
   dig2 = Valm - (dig1 * 10);
   effects.DisplayNumber(dig1, 245, 96, 38, 11, hueColor+127);
   effects.DisplayNumber(dig2, 350, 96, 38, 11, hueColor+127);
  }
    
void drawTemphu() {
   vga.fillRect(0, 320, 530, 80, vga.RGB(0));
   gfx.setFont(&atawi19x11c);
   gfx.setTextSize(4);
   gfx.setTextColor(myCOLOR[ac]);
   gfx.setCursor(0,320);
   gfx.print(Temp);
   gfx.setTextSize(2);
   gfx.setTextColor(myCOLOR[4]);
   gfx.print(" *");
   gfx.setTextSize(4);
   gfx.setTextColor(myCOLOR[cc]);
   gfx.setCursor(270,320);
   gfx.print(Humi);
   gfx.setTextColor(myCOLOR[0]);
   gfx.print(" %");
   getSyTemp();
  }
  
void drawDate()
{
    canvasM.fillScreen(0);
    canvasM.setFont(&atawi11x7g);
    canvasM.setTextSize(5);
    canvasM.setCursor(0, 0);
    canvasM.print(effects.printTextMesg(rtc.getDate()));
    canvasM.setFont();
  }
  
void drawMesg()
{
    uint16_t text_length = textmsg.length() * 49; 
    canvasM.fillScreen(0);
    canvasM.setFont(&atawi11x7g);
    canvasM.setTextSize(7);
    canvasM.setCursor(xps, 0);
    canvasM.print(textmsg);
    canvasM.setFont();
     xps-=sp0;
     if (xps < -text_length) 
     { xps = 450;
     effects.getmesg(); }
  }
void getSyTemp() {
  vga.fillRect(450, 0, 80, 180, vga.RGB(0));
  int xs=465, ys=20;
  for(int x=ys; x<ys+111; x+=2) {
  vga.fillRect(xs+34, x, 3, 1, vga.RGB(0xffffff));
  }
  vga.setTextColor(vga.RGB(0xffff00));
  vga.setFont(Font8x8);
  for(int x=ys; x<ys+101; x+=20) {
  vga.fillRect(xs+34, x, 6, 1, vga.RGB(0xff00ff));
  vga.setCursor(xs+45, x-3);
  vga.print((ys+100-x)/2);
  }
  vga.circle(xs+25, ys, 8, vga.RGB(0xff00ff));
  vga.circle(xs+25, ys, 7, vga.RGB(0xff00ff));
  vga.circle(xs+25, ys, 6, vga.RGB(0xffffff));
  vga.circle(xs+25, ys, 5, vga.RGB(0xffffff));
  vga.fillCircle(xs+25, ys+136, 20, vga.RGB(0xff00ff));
  vga.fillCircle(xs+25, ys+136, 18, vga.RGB(0xffffff));
  vga.fillCircle(xs+25, ys+136, 16, vga.RGB(0x00ff00));
  vga.fillCircle(xs+25, ys+136, 12, vga.RGB(0x0000ff));
  vga.fillRect(xs+17, ys, 2, 118, vga.RGB(0xff00ff));
  vga.fillRect(xs+19, ys, 2, 120, vga.RGB(0xffffff));
  vga.fillRect(xs+30, ys, 2, 120, vga.RGB(0xffffff));
  vga.fillRect(xs+32, ys, 2, 118, vga.RGB(0xff00ff));
  int tec = map(Temp, 0, 50, ys+100, ys);
  int yec = ys+136-tec;
  vga.fillRect(xs+21, ys, 9, 130, vga.RGB(0));
  vga.fillRect(xs+21, tec, 9, yec, vga.RGB(0x0000ff));
}
};

#endif
