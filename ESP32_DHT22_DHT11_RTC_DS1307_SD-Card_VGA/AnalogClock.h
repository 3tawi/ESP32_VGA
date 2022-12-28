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

#ifndef AnalogClock_H
#include <fontclock.h>
class AnalogClock : public Play {
private:
#define VGA_WIDTH 560
#define VGA_HEIGHT 400
const int CENTRE_X = 340;
const int CENTRE_Y = (VGA_HEIGHT / 2);
#define R_H1 70
#define R_H2 90
#define R_M1  110
#define R_M2  130
#define R_S1   130
#define R_S2   150
uint8_t Vals;
uint8_t Valm;
uint8_t Valh;
VGA3BitI::Color lineColor1;
VGA3BitI::Color lineColor2;
VGA3BitI::Color lineColor3;
int y0, y1, y2, y3;
long hueva;
float lasthour;
float lastminute;
float lastsecond;

public:
  AnalogClock() {
        name = (char *)"AnalogClock";
  }

  unsigned int playframe() {
    if ( (millis() - currentTime) > 1000 ) {
      drawTime();
      drawSed();
      flasher = !flasher;
      currentTime = millis();
    }
    if (NewRTCm != Valm) {
      effects.redtemphumi();
      drawTempHumi();
      getSyTemp();
      drawTime1();
      vga.fillRect(246, y0, 194, 76, vga.RGB(0));
      drawTime();
      NewRTCm = Valm;
    }
    if (modewi) server.handleClient();
    return 0;
    }

    void drawHMS(float angle, int r1, int r2, uint16_t c1, int z1, int z2) {
      int x[6];
      int y[6];
      float radians = radians(angle);
      x[0] = CENTRE_X + r2 * sin(radians);
      y[0] = CENTRE_Y + r2 * cos(radians);
      radians = radians(angle+z1);
      x[1] = CENTRE_X + r1 * sin(radians);
      y[1] = CENTRE_Y + r1 * cos(radians);
      radians = radians(angle-z1);
      x[2] = CENTRE_X + r1 * sin(radians);
      y[2] = CENTRE_Y + r1 * cos(radians);
      radians = radians(angle+z2);
      x[3] = CENTRE_X + 10 * sin(radians);
      y[3] = CENTRE_Y + 10 * cos(radians);
      radians = radians(angle-z2);
      x[4] = CENTRE_X + 10 * sin(radians);
      y[4] = CENTRE_Y + 10 * cos(radians);
      gfx.fillTriangle(x[0], y[0], x[1], y[1], x[2], y[2], c1);
      gfx.fillTriangle(x[0], y[0], x[3], y[3], x[4], y[4], c1);
    }

    void updatetime() {
      effects.redtemphumi();
      Valh = rtc.getHour();
      if (Valh < 3 || Valh > 8) { y0 = 250; }
      else { y0 = 90; }
      if (rtc.getHour(true) >= 12) {
        y1 = 10, y2 = 345;
      }  else {
        y1 = 350, y2 = 5;
      }
      drawTempHumi();
      getSyTemp();
      drawTime1();
      vga.fillRect(246, y0, 194, 78, vga.RGB(0));
    }

    void drawTime() {
      Vals = rtc.getSecond();
      Valm = rtc.getMinute();
      if (NewRTCm != Valm) {
        updatetime();
        NewRTCm = Valm;
      }
      if (lasthour != 180 - (30 * Valh) - (Valm / 2)) drawHMS(lasthour, R_H1, R_H2, 0x0, 4, 40);
      if (lastminute != 180 - (6 * Valm)) drawHMS(lastminute, R_M1, R_M2, 0x0, 4, 40);
      drawHMS(lastsecond, R_S1, R_S2, 0x0, 2, 30);
      drawdigi();
      float angle = 180 - (30 * Valh) - (Valm / 2);
      drawHMS(angle, R_H1, R_H2, 0xF800, 4, 40);
      lasthour = angle;
      angle = 180 - (6 * Valm);
      drawHMS(angle, R_M1, R_M2, 0x0F0F, 3, 30);
      lastminute = angle;
      angle =  180 - (Vals * 6);
      drawHMS(angle, R_S1, R_S2, myCOLOR[Vals%7], 2, 30);
      lastsecond = angle;
      float radians = radians(angle+90);
      int x = round(CENTRE_X + 210 * cos(radians));
      int y = round(CENTRE_Y - 191 * sin(radians));
      gfx.fillCircle(x,y, 3, myCOLOR[random(0, 6)]);
      gfx.fillCircle(CENTRE_X,CENTRE_Y, 10, myCOLOR[random(0, 6)]);
    }
    
void drawTime1() {
  double radians;
  int j = 0, x, y;
  vga.ellipse(CENTRE_X,CENTRE_Y, 220, 199, myCOLOR[Valm%7]);
  vga.ellipse(CENTRE_X,CENTRE_Y, 205, 184, myCOLOR[Valm%7]);
  for (int i = 0; i < 60; i+=5) {
    radians = (90.0F - (i * 6.0F)) * M_PI / 180.0;
    x = round(CENTRE_X + 210 * cos(radians));
    y = round(CENTRE_Y - 191 * sin(radians));
    gfx.fillCircle(x,y, 6, myCOLOR[Valm%7]);
    x = round(CENTRE_X + 190 * cos(radians));
    y = round(CENTRE_Y - 170 * sin(radians));
    gfx.setFont(&fontclock);
    gfx.setTextSize(4);
    gfx.setTextColor(myCOLOR[(Valm+(i/5))%7]);
    // gfx.setTextColor(myCOLOR[(i/5)%12]);
    gfx.setCursor(x,y);
    gfx.print(char(j));
    j++;
    if (j == 10) j = 11;
  }
  for (int i = 0; i < 60; i+=15) {
    radians = (90.0F - (i * 6.0F)) * M_PI / 180.0;
    x = round(CENTRE_X + 210 * cos(radians));
    y = round(CENTRE_Y - 191 * sin(radians));
    gfx.fillCircle(x,y, 8, myCOLOR[Valm%7]);
  }
  for (int i = 0; i < 60; i++) {
    radians = (90.0F - (i * 6.0F)) * M_PI / 180.0;
    x = round(CENTRE_X + 210 * cos(radians));
    y = round(CENTRE_Y - 191 * sin(radians));
    gfx.fillCircle(x,y, 3, myCOLOR[6-Valm%7]);
  }
}

void drawSed() {
  vga.fillRect(495, y1-5, 65, 52, vga.RGB(0));
  int dig1 = Vals / 10;
  int dig2 = Vals - (dig1 * 10);
  effects.DisplayNumber(dig1, 500, y1, 10, 5, hueva++);
  effects.DisplayNumber(dig2, 533, y1, 10, 5, hueva++);
}
void drawTempHumi() {
  gfx.setFont(&atawi11x7g);
  gfx.setTextSize(4);
  gfx.setTextColor(myCOLOR[random(0, 6)]);
  gfx.setCursor(500,y2);
  vga.fillRect(495, y2, 65, 52, vga.RGB(0));
  gfx.print(rtc.getAmPm());
  gfx.setFont();
  gfx.setFont(&atawi19x11c);
  gfx.setTextSize(3);
  gfx.setTextColor(myCOLOR[ac]);
  gfx.setCursor(0,5);
  vga.fillRect(0, 5, 200, 57, vga.RGB(0));
  gfx.print(Temp);
  gfx.setTextSize(2);
  gfx.setTextColor(myCOLOR[4]);
  gfx.print(" *");
  gfx.setTextSize(3);
  gfx.setTextColor(myCOLOR[cc]);
  gfx.setCursor(0,335);
  vga.fillRect(0, 335, 200, 57, vga.RGB(0));
  gfx.print(Humi);
  gfx.setTextColor(myCOLOR[0]);
  gfx.print(" %");
  gfx.setFont();
}
void drawdigi() {
  vga.fillRect(337, y0+15, 6, 27, vga.RGB(0));
  gfx.setFont(&atawi19x11c);
  gfx.setTextSize(3);
  gfx.setTextColor(myCOLOR[Valm%7]);
  gfx.setCursor(265,y0);
  text = Mode24h ? flasher ? rtc.getTime("%H:%M") : rtc.getTime("%H %M") : flasher ? rtc.getTime("%I:%M") : rtc.getTime("%I %M");
  gfx.print(text);
  gfx.setFont(&atawi11x7g);
  gfx.setTextSize(2);
  gfx.setCursor(246,y0+55);
  gfx.setTextColor(myCOLOR[(Valm+5)%7]);
  text = effects.getfullDateMesg(fon);
  gfx.print(text);
  gfx.setFont();
  }
void getSyTemp() {
  int xs=15, ys=90;
  vga.setTextColor(vga.RGB(0xffff00));
  vga.setFont(Font8x8);
  for(int y=ys+30; y<ys+171; y+=20) {
  vga.fillRect(xs+34, y, 6, 1, vga.RGB(0xff00ff));
  vga.setCursor(xs+45, y-3);
  vga.print((ys+130-y)/2);
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
