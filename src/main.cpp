#include "Arduino_H7_Video.h"
#include "Arduino_GigaDisplayTouch.h"
#include <Arduino_GigaDisplay.h>
#include "lvgl.h"
#include <Wire.h>

Arduino_H7_Video          Display(800, 480, GigaDisplayShield);
Arduino_GigaDisplayTouch  TouchDetector;
GigaDisplayRGB rgb;

#define SLAVE_ADDRESS 0x60

#include <components/general.h>
#include <components/sidebar.h>
#include <components/homeTab.h>
#include <components/controlTab.h>
#include <components/settingsTab.h>
#include <components/popupTab.h>

void setup() {
  Serial.begin(115200);

  Display.begin();
  TouchDetector.begin();

  build_sidebar();
  build_homeTab(tab1);
  build_controlTab(tab2);
  build_settingsTab(tab3);
  build_popupTab(tab4);

  communication.init();

  delay(100);
  communication.sendEvent("reqDiameter", "");
  delay(100);
  communication.sendEvent("reqMinPSpeed", "");
  delay(100);
  communication.sendEvent("reqMaxPSpeed", "");
  delay(100);
  communication.sendEvent("reqPolymer", "");
  delay(100);
  communication.sendEvent("reqMinRead", "");
  delay(100);
  communication.sendEvent("reqMaxRead", "");
  delay(100);
  communication.sendEvent("reqAutostop", "");
  delay(100);
  communication.sendEvent("reqMaxPosition", "");
  delay(100);
  communication.sendEvent("reqMinPosition", "");
  delay(100);
  communication.sendEvent("reqPositioned", "");
  delay(100);
  communication.sendEvent("reqStAutoStop", "");
  delay(100);
  communication.sendEvent("reqTemp", "");
}

void loop() {
  lv_timer_handler();
}