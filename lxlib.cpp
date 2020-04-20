#include <Ticker.h>
#include "lxlib.h"
#include "wifi.h"
#include "ota.h"

ADC_MODE(ADC_VCC);

void goToSleep() {
  // TODO Check MCU before
  ESP.deepSleep(0);
}

Ticker sleepMon(goToSleep, 60000);

LxLib::LxLib()
{
}

LxLib::~LxLib()
{
}

void LxLib::begin() {
  initWiFi();
  initOTA();
}

void LxLib::update() {
  loopWiFi();
  loopOTA();
  sleepMon.update();
}

void LxLib::enableDeepSleep(bool enable)
{
  if (enable) {
    sleepMon.start();
  } else {
    sleepMon.stop();
  }
}

void LxLib::resetSleepCounter() {
  sleepMon.stop();
  sleepMon.start();
}