/*
- Lien vidéo: https://youtu.be/bQL0pm41uJY

MIT License

Copyright (c) 2022 3tawi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef DigitalClock_H
class DigitalClock : public Play {
private:
long hueColor;

public:
    DigitalClock() {
        name = (char *)"DigitalClock";
    }

    void start() {
    }

    unsigned int playframe() {
    drawMesg();
    effects.printCanva(0, 0, 505, 77, 0, 0);
    if ( (millis() - currentTime) > 1000 ) { 
      drawTime();
      flasher = !flasher;
      hueColor++;
      currentTime = millis();
    }
    if (modewi) server.handleClient();
    return 0;
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
     if (xps < -text_length) { effects.getmesg(); }
  }
       
void drawTime() {
  drawTimese();
  if (NewRTCm != rtc.getMinute()) {
  drawTimehm();
  drawTemphu();
  drawDate();
  effects.printCanva(0, 0, 510, 55, 30, 260);
  NewRTCm = rtc.getMinute();
      }
}
    
void drawTimese() {
  if (flasher) {
    vga.fillEllipse(230, 145, 8, 10, effects.ColorHue(hueColor*2));
    vga.fillEllipse(230, 205, 8, 10, effects.ColorHue(hueColor*2));
   } else {
     vga.fillEllipse(230, 145, 8, 10, vga.RGB(0));
     vga.fillEllipse(230, 205, 8, 10, vga.RGB(0));
   }
  gfx.setFont(&atawi19x11c);
  gfx.setTextSize(3);
  gfx.setTextColor(myCOLOR[rtc.getSecond()%7]);
  gfx.setCursor(480,200);
  vga.fillRect(480, 200, 80, 65, vga.RGB(0));
  gfx.print(rtc.getTime("%S"));
}
    
void drawTimehm() {
  gfx.setFont(&atawi19x11c);
  gfx.setTextSize(9);
  text = Mode24h ? rtc.getTime("%H") : rtc.getTime("%I");
  gfx.setTextColor(myCOLOR[rtc.getMinute()%7]);
  vga.fillRect(0, 85, 470, 175, vga.RGB(0));
  gfx.setCursor(0,90);
  gfx.print(text);
  text = rtc.getTime("%M");
  gfx.setCursor(260, 90);
  gfx.print(text);
  gfx.setFont();
}
    
void drawTemphu() {
   vga.fillRect(0, 320, 560, 80, vga.RGB(0));
   gfx.setFont(&atawi19x11c);
   gfx.setTextSize(4);
   gfx.setTextColor(myCOLOR[ac]);
   gfx.setCursor(5,320);
   gfx.print(NewTemp);
   gfx.setTextSize(2);
   gfx.setTextColor(myCOLOR[4]);
   gfx.print(" *");
   gfx.setTextSize(4);
   gfx.setTextColor(myCOLOR[cc]);
   gfx.setCursor(290,320);
   gfx.print(NewHumi);
   gfx.setTextColor(myCOLOR[0]);
   gfx.print(" %");
   getSyTemp();
  }
   
void drawDate() {
  canvasM.fillScreen(0);
  canvasM.setFont(&atawi11x7g);
  canvasM.setTextSize(5);
  canvasM.setCursor(0, 0);
  text = effects.getfullDateMesg(fon);
  canvasM.print(text);
  canvasM.setFont();
  }
  
void getSyTemp() {
  vga.fillRect(490, 0, 70, 180, vga.RGB(0));
  int xs=490, ys=30;
  for(int y=ys; y<ys+111; y+=2) {
    vga.fillRect(xs+34, y, 3, 1, vga.RGB(0xffffff));
    }
  vga.setTextColor(vga.RGB(0xffff00));
  vga.setFont(Font8x8);
  for(int y=ys; y<ys+101; y+=20) {
    vga.fillRect(xs+34, y, 6, 1, vga.RGB(0xff00ff));
    vga.setCursor(xs+45, y-3);
    vga.print((ys+100-y)/2);
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
  int tec = map(NewTemp, 0, 50, ys+100, ys);
  int yec = ys+136-tec;
  vga.fillRect(xs+21, ys, 9, 130, vga.RGB(0));
  vga.fillRect(xs+21, tec, 9, yec, vga.RGB(0x0000ff));
}
};

#endif
