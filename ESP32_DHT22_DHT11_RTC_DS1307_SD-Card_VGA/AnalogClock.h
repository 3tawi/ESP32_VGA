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
/*

#ifndef AnalogClock_H
class AnalogClock : public Play {
private:
#define VGA_WIDTH 530
#define VGA_HEIGHT 400
const int CENTRE_X = 320;
const int CENTRE_Y = (VGA_HEIGHT / 2);
#define R_H1 80
#define R_H2 100
#define R_M1  110
#define R_M2  130
#define R_S1   130
#define R_S2   150
VGA3BitI::Color lineColor1;
VGA3BitI::Color lineColor2;
VGA3BitI::Color lineColor3;
int x, x1, x2, x4;
int y, y1, y2, y3, y4, y5, y6;
long hueva;

public:
    AnalogClock() {
        name = (char *)"AnalogClock";
    }

    unsigned int playframe() {
    vga.clear(0);
    drawTempHumi();
    getSyTemp();
    drawDate();
    drawTime();
    if ( (millis() - currentTime) > 1000 ) { 
      rtc.DSread();
    lineColor1 = effects.ColorHue(random(0, 1791));
    lineColor2 = effects.ColorHue(random(0, 1791));
    lineColor3 = effects.ColorHue(hueva);
    flasher = !flasher;
    currentTime = millis();
    hueva++;
    }
    vga.show();
    return 0;
    }
    
void drawTime()
{
            double radians;
            int j = 0;
            uint8_t hour = rtc.hour;
            if (hour > 12)
                hour -= 12;
            if (hour < 3 || hour > 8) { 
              y3 = 250;
              y4 = 10, x4 = 465;
              y6 = 120; }
            else { 
              y3 = 90;
              y4 = 350, x4 = 465;
              y6 = 240; }
            vga.circle(CENTRE_X,CENTRE_Y, 199, lineColor3);
            vga.circle(CENTRE_X,CENTRE_Y, 184, lineColor3);
            for (int i = 0; i < 60; i+=5) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0;
            x = round(CENTRE_X + 191 * cos(radians));
            y = round(CENTRE_Y - 191 * sin(radians));
            vga.fillCircle(x,y, 5, lineColor1);
            x = round(CENTRE_X + 170 * cos(radians));
            y = round(CENTRE_Y - 170 * sin(radians));
            gfx.setFont(&fontclock);
            gfx.setTextSize(4);
            gfx.setTextColor(myCOLOR[(rtc.minute+(i/5))%7]);
            // gfx.setTextColor(myCOLOR[(i/5)%12]);
            gfx.setCursor(x,y);
            gfx.print(char(j));
            j++;
            if (j == 10) { j = 11;}
            }
            for (int i = 0; i < 60; i+=15) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0;
            x = round(CENTRE_X + 191 * cos(radians));
            y = round(CENTRE_Y - 191 * sin(radians));
            vga.fillCircle(x,y, 6, lineColor2);
            }
            for (int i = 0; i < 60; i++) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0;
            x = round(CENTRE_X + 191 * cos(radians));
            y = round(CENTRE_Y - 191 * sin(radians));
            vga.fillCircle(x,y, 3, effects.ColorHue((rtc.second+i)*15));
            }

            gfx.setFont(&atawi19x11c);
            gfx.setTextSize(3);
            gfx.setTextColor(myCOLOR[rtc.minute%7]);
            gfx.setCursor(245,y3);
            gfx.print(rtc.getMahmin(flasher));
            gfx.setFont(&atawi11x7g);
            gfx.setTextSize(2);
            gfx.setCursor(226,y3+55);
            gfx.setTextColor(myCOLOR[(rtc.minute+5)%7]);
            gfx.print(effects.printTextMesg(rtc.getDate()));
            gfx.setFont();
            drawMesg();
            effects.drawCanva(0, 0, 300, 34, 170, y6);
            
            // hour
            radians = (90.0F - ((hour * 30.0F) + ((rtc.minute * 29.0F) / 60.0F))) * M_PI / 180.0F;
            x = round(CENTRE_X + R_H1 * cos(radians));
            y = round(CENTRE_Y - R_H1 * sin(radians));
            x2 = round(CENTRE_X + R_H2 * cos(radians));
            y2 = round(CENTRE_Y - R_H2 * sin(radians));
            for (float i = hour-2; i < hour+2; i+=0.2F) {
            radians = (90.0F - ((i * 30.0F) + ((rtc.minute * 29.0F) / 60.0F))) * M_PI / 180.0F;
            x1 = round(CENTRE_X + 5 * cos(radians));
            y1 = round(CENTRE_Y - 5 * sin(radians));
            vga.line(x1, y1, x2, y2, vga.RGB(255,0,0));
            }
            for (float i = hour-2; i < hour+2; i+=0.2F) {
            radians = (90.0F - ((i * 30.0F) + ((rtc.minute * 29.0F) / 60.0F))) * M_PI / 180.0F;
            x1 = round(x + 5 * cos(radians));
            y1 = round(y - 5 * sin(radians));
            vga.line(x1, y1, x2, y2, vga.RGB(255,0,0));
            }

            // minute
            radians = (90.0F - (rtc.minute * 6.0F)) * M_PI / 180.0;
            x = round(CENTRE_X + R_M1 * cos(radians));
            y = round(CENTRE_Y - R_M1 * sin(radians));
            x2 = round(CENTRE_X + R_M2 * cos(radians));
            y2 = round(CENTRE_Y - R_M2 * sin(radians));
            for (int i = rtc.minute-10; i < rtc.minute+10; i++) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0F;
            x1 = round(CENTRE_X + 5 * cos(radians));
            y1 = round(CENTRE_Y - 5 * sin(radians));
            vga.line(x1, y1, x2, y2, vga.RGB(0,255,0));
            }
            for (int i = rtc.minute-10; i < rtc.minute+10; i++) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0F;
            x1 = round(x + 5 * cos(radians));
            y1 = round(y - 5 * sin(radians));
            vga.line(x1, y1, x2, y2, vga.RGB(0,255,0));
            }

            // second
            radians = (90.0F - (rtc.second * 6.0F)) * M_PI / 180.0F;
            x = round(CENTRE_X + R_S1 * cos(radians));
            y = round(CENTRE_Y - R_S1 * sin(radians));
            x2 = round(CENTRE_X + R_S2 * cos(radians));
            y2 = round(CENTRE_Y - R_S2 * sin(radians));
            for (int i = rtc.second-10; i < rtc.second+10; i++) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0F;
            x1 = round(CENTRE_X + 5 * cos(radians));
            y1 = round(CENTRE_Y - 5 * sin(radians));
            vga.line(x1, y1, x2, y2, lineColor1);
            }
            for (int i = rtc.second-10; i < rtc.second+10; i++) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0F;
            x1 = round(x + 5 * cos(radians));
            y1 = round(y - 5 * sin(radians));
            vga.line(x1, y1, x2, y2, lineColor1);
            }
            vga.fillCircle(CENTRE_X,CENTRE_Y, 10, lineColor1);
}

void drawDate()
{
            int Vals = rtc.second;
            int dig1 = Vals / 10;
            int dig2 = Vals - (dig1 * 10);
            effects.DisplayNumber(dig1, x4, y4, 10, 5, hueva);
            effects.DisplayNumber(dig2, x4+35, y4, 10, 5, hueva);
}
void drawTempHumi()
{
            gfx.setFont(&atawi19x11c);
            gfx.setTextSize(3);
            gfx.setTextColor(myCOLOR[ac]);
            gfx.setCursor(0,5);
            gfx.print(Temp);
            gfx.setTextSize(2);
            gfx.setTextColor(myCOLOR[4]);
            gfx.print(" *");
            gfx.setTextSize(3);
            gfx.setTextColor(myCOLOR[cc]);
            gfx.setCursor(0,335);
            gfx.print(Humi);
            gfx.setTextColor(myCOLOR[0]);
            gfx.print(" %");
            gfx.setFont();
  }
void drawMesg()
{
    uint16_t text_length = textmsg.length() * 21; 
    canvasM.fillScreen(0);
    canvasM.setFont(&atawi11x7g);
    canvasM.setTextSize(3);
    canvasM.setCursor(xps, 0);
    canvasM.print(textmsg);
    canvasM.setFont();
     xps-=sp0;
     if (xps < -text_length) 
     { xps = 300;
     effects.getmesg(); }
  }
void getSyTemp()
{
  int xs=15, ys=90;
 vga.setTextColor(vga.RGB(0xffff00));
  vga.setFont(Font8x8);
  for(int x=ys+30; x<ys+171; x+=20) {
  vga.fillRect(xs+34, x, 6, 1, vga.RGB(0xff00ff));
  vga.setCursor(xs+45, x-3);
  vga.print((ys+130-x)/2);
  }
  vga.fillRect(xs+16, ys+10, 18, 180, vga.RGB(0xff00ff));
  vga.fillEllipse(xs+25, ys, 10, 20, vga.RGB(0xff00ff));
  vga.fillEllipse(xs+25, ys, 8, 16, vga.RGB(0xffffff));
  vga.fillEllipse(xs+25, ys, 7, 15, vga.RGB(0x000000));
  vga.fillCircle(xs+25, ys+200, 24, vga.RGB(0xff00ff));
  vga.fillRect(xs+20, ys+12, 10, 200, vga.RGB(0xffffff));
  vga.fillCircle(xs+25, ys+200, 20, vga.RGB(0xffffff));
  vga.fillCircle(xs+25, ys+200, 18, vga.RGB(0x00ff00));
  vga.fillCircle(xs+25, ys+200, 16, vga.RGB(0x0000ff));
  for(int x=ys+20; x<ys+171; x+=2) {
  vga.fillRect(xs+32, x, 3, 1, vga.RGB(0xffffff));
  }
  int tec = map(Temp, -20, 60, ys+170, ys+10);
  int yec = ys+200-tec;
  vga.fillRect(xs+21, ys, 8, 180, vga.RGB(0x000000));
  vga.fillRect(xs+22, tec, 6, yec, vga.RGB(0x0000ff));
}
};

#endif
