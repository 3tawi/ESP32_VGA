
// - Lien vidéo: https://youtu.be/bQL0pm41uJY

#ifndef Modeclock_H
#define Modeclock_H


#include "AnalogClock.h"
#include "DigitalClock.h"
#include "SegmentClock.h"
#include "SettingClock.h"

class Modeclock : public list {
  private:
    AnalogClock analogClock;
    DigitalClock digitalClock;
    SegmentClock segmentClock;
    SettingClock settingClock;

    int currentIndex = 0;
    Play* currentItem;

    int getCurrentIndex() {
      return currentIndex;
    }

    static const int Modenm = 4;
    Play* items[Modenm] = {
      &digitalClock,
      &analogClock,
      &segmentClock,
      &settingClock
    };

  
  public:
    char* Play::name = (char *)"Modeclock";

    void stop() {
      if (currentItem)
        currentItem->stop();
    }

    void start() {
      if (currentItem)
        currentItem->start();
    }

    void move(int step) {
      currentIndex += step;
    if (modeS) {
      if (currentIndex >= Modenm) currentIndex = 0;
      else if (currentIndex < 0) currentIndex = Modenm - 1;
      } else {
      if (currentIndex >= Modenm -1) currentIndex = 0;
      else if (currentIndex < 0) currentIndex = Modenm - 2;
      }
      moveTo(currentIndex);
    }


    unsigned int playframe() {
      return currentItem->playframe();
    }

    void moveTo(int index) {
      if (currentItem)
        currentItem->stop();

      currentIndex = index;

      currentItem = items[currentIndex];

      if (currentItem)
        currentItem->start();
    }  


    bool setModeclock(int index) {
      if (index >= Modenm || index < 0)
        return false;

      moveTo(index);

      return true;
    }
    int getModeIndex() {
      return currentIndex;
    }
};

#endif
