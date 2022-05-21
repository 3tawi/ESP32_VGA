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

public:
    DigitalClock() {
        name = (char *)"DigitalClock";
    }

    void start() {
    }

    unsigned int playframe() {
    vga.clear(0);
    drawTime();
    drawDate();
    effects.drawCanva(0, 0, 500, 55, 15, 260);
    drawMesg();
    effects.drawCanva(0, 0, 480, 77, 0, 0);
    drawTemphu();
    if ( (millis() - currentTime) > 1000 ) { 
      rtc.DSread();
      flasher = !flasher;
      currentTime = millis();
    }
    vga.show();
    return 0;
    }
    
void drawTime() {
  gfx.setFont(&atawi19x11c);
  gfx.setTextSize(9);
  gfx.setTextColor(myCOLOR[rtc.minute%7]);
  gfx.setCursor(0,90);
  gfx.print(rtc.getMahmin(flasher));
  gfx.setTextSize(3);
  gfx.setTextColor(myCOLOR[rtc.second%7]);
  gfx.setCursor(455,200);
  gfx.print(rtc.getSecond());
}
  
void drawTemphu() {
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
     { xps = 480;
     effects.getmesg(); }
  }
void getSyTemp()
{
  int xs=465, ys=40;
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
