#include <components/general.h>

Arduino_H7_Video Display(800, 480, GigaDisplayShield);
Arduino_GigaDisplayTouch TouchDetector;
GigaDisplayRGB rgb;

Communication communication;

float minRead, actRead, maxRead, weight, temp;
uint16_t pSpeed, minPSpeed, maxPSpeed;
String eTime;

lv_obj_t *tabview, *tab1, *tab2, *tab3, *tab4;
lv_obj_t *minMeasureLabel, *actMeasureLabel, *maxMeasureLabel;
lv_obj_t *winderInfoPullerSpeedLabel, *winderInfoTimeLabel, *winderInfoWeightLabel, *waterTempInfoLabel;
lv_obj_t *activeTabIndex, *confirmationMenuAction;
lv_obj_t *minSpeedSpinbox, *maxSpeedSpinbox, *waterTempSpinbox, *diameterSpinbox, *autostopSpinbox, *autostopSpinboxLabel;
lv_obj_t *polymerDropdown;
lv_obj_t *controlParentContent, *positionBar, *positionBarMinLabel, *positionBarMaxLabel, *homePositionBtn, *startAlignerBtn;

void setActiveTab(uint8_t index) {
  lv_label_set_text(activeTabIndex, String(index).c_str());
}

String getConfirmationMenuAction() {
  return String(lv_label_get_text(confirmationMenuAction));
}

void setConfirmationMenuAction(String action) {
  lv_label_set_text(confirmationMenuAction, action.c_str());
}