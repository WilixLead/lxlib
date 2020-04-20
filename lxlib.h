#ifndef __LXLIB__
#define __LXLIB__

#include <Arduino.h>

class LxLib
{
private:
  
public:
  LxLib();
  ~LxLib();

  void begin();
  void update();
  void enableDeepSleep(bool enable);
  void goToSleep();
  void resetSleepCounter();
};

#endif