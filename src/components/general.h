#pragma once

#include <lvgl.h>
#include <Arduino.h>
#include <communication/communication.h>

//0xf3fd, 0xf0b2, 0xf2c9, 0xf017, 0xf5cd
LV_FONT_DECLARE(testfont);
#define SPEED_SYMBOL "\xEF\x8F\xBD"
#define MOVE_SYMBOL "\xEF\x82\xB2"
#define TEMP_SYMBOL "\xEF\x8B\x89"
#define CLOCK_SYMBOL "\xEF\x80\x97"
#define WEIGHT_SYMBOL "\xEF\x97\x8D"

extern float minRead, actRead, maxRead, weight, temp;
extern uint16_t pSpeed, minPSpeed, maxPSpeed;
extern String eTime;

extern Communication communication;

extern bool reqDiameterSetted;
extern bool reqMinPSpeedSetted;
extern bool reqMaxPSpeedSetted;
extern bool reqPolymerSetted;
extern bool reqMinReadSetted;
extern bool reqMaxReadSetted;
extern bool reqAutoStopSetted;
extern bool reqMaxPositionSetted;
extern bool reqMinPositionSetted;
extern bool reqPositionedSetted;
extern bool reqStAutoStopSetted;
extern bool reqTempSetted;

extern lv_obj_t *tabview, *tab1, *tab2, *tab3, *tab4;
extern lv_obj_t *minMeasureLabel, *actMeasureLabel, *maxMeasureLabel;
extern lv_obj_t *winderInfoPullerSpeedLabel, *winderInfoTimeLabel, *winderInfoWeightLabel, *waterTempInfoLabel;
extern lv_obj_t *activeTabIndex, *confirmationMenuAction;
extern lv_obj_t *minSpeedSpinbox, *maxSpeedSpinbox, *waterTempSpinbox, *diameterSpinbox, *autostopSpinbox, *autostopSpinboxLabel;
extern lv_obj_t *polymerDropdown;
extern lv_obj_t *controlParentContent, *positionBar, *positionBarMinLabel, *positionBarMaxLabel, *homePositionBtn, *startAlignerBtn;

void setActiveTab(uint8_t index);

String getConfirmationMenuAction();

void setConfirmationMenuAction(String action);