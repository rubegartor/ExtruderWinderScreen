#include <components/general.h>

float minRead, actRead, maxRead, weight;
uint16_t pSpeed, minPSpeed, maxPSpeed;
String eTime;

bool reqDiameterSetted;
bool reqMinPSpeedSetted;
bool reqMaxPSpeedSetted;
bool reqPolymerSetted;
bool reqMinReadSetted;
bool reqMaxReadSetted;
bool reqAutoStopSetted;
bool reqMaxPositionSetted;
bool reqMinPositionSetted;
bool reqPositionedSetted;

lv_obj_t *tabview, *tab1, *tab2, *tab3, *tab4;
lv_obj_t *minMeasureLabel, *actMeasureLabel, *maxMeasureLabel;
lv_obj_t *winderInfoPullerSpeedLabel, *winderInfoTimeLabel, *winderInfoWeightLabel;
lv_obj_t *activeTabIndex, *confirmationMenuAction;
lv_obj_t *minSpeedSpinbox, *maxSpeedSpinbox, *diameterSpinbox, *autostopSpinbox;
lv_obj_t *polymerDropdown;
lv_obj_t *controlParentContent, *positionBar, *positionBarMinLabel, *positionBarMaxLabel, *homePositionBtn, *startAlignerBtn;

uint8_t winderAddr[] = {0x34, 0x85, 0x18, 0x45, 0x23, 0x58};

void setActiveTab(uint8_t index) {
  lv_label_set_text(activeTabIndex, String(index).c_str());
}

String getConfirmationMenuAction() {
  return String(lv_label_get_text(confirmationMenuAction));
}

void setConfirmationMenuAction(String action) {
  lv_label_set_text(confirmationMenuAction, action.c_str());
}