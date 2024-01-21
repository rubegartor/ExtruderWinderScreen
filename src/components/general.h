#pragma once

#include <lvgl.h>
#include <Arduino.h>
#include <Arduino_H7_Video.h>
#include <Arduino_GigaDisplayTouch.h>
#include <Arduino_GigaDisplay.h>
#include <communication/communication.h>

extern Arduino_H7_Video Display;
extern Arduino_GigaDisplayTouch TouchDetector;
extern GigaDisplayRGB rgb;

//0xf3fd, 0xf0b2, 0xf2c9, 0xf017, 0xf5cd
LV_FONT_DECLARE(icons);
#define SPEED_SYMBOL "\xEF\x8F\xBD"
#define MOVE_SYMBOL "\xEF\x82\xB2"
#define TEMP_SYMBOL "\xEF\x8B\x89"
#define CLOCK_SYMBOL "\xEF\x80\x97"
#define WEIGHT_SYMBOL "\xEF\x97\x8D"

extern Communication communication;

extern float minRead, actRead, maxRead, weight, temp;
extern uint16_t pSpeed, minPSpeed, maxPSpeed;
extern String eTime;

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