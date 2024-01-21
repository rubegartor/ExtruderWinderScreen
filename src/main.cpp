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
  rgb.begin();

  build_sidebar();
  build_homeTab(tab1);
  build_controlTab(tab2);
  build_settingsTab(tab3);
  build_popupTab(tab4);

  communication.init();
}

void loop() {
  communication.handleRequests();

  lv_timer_handler();
}