#include <lvgl.h>
#include <Arduino.h>

#define TFT_BL 2
#define GFX_BL DF_GFX_BL

extern float minRead, actRead, maxRead, weight;
extern uint16_t pSpeed, minPSpeed, maxPSpeed;
extern String eTime;

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

extern lv_obj_t *tabview, *tab1, *tab2, *tab3, *tab4;
extern lv_obj_t *minMeasureLabel, *actMeasureLabel, *maxMeasureLabel;
extern lv_obj_t *winderInfoPullerSpeedLabel, *winderInfoTimeLabel, *winderInfoWeightLabel;
extern lv_obj_t *activeTabIndex, *confirmationMenuAction;
extern lv_obj_t *minSpeedSpinbox, *maxSpeedSpinbox, *diameterSpinbox, *autostopSpinbox;
extern lv_obj_t *polymerDropdown;
extern lv_obj_t *controlParentContent, *positionBar, *positionBarMinLabel, *positionBarMaxLabel, *homePositionBtn, *startAlignerBtn;

extern uint8_t winderAddr[];

void setActiveTab(uint8_t index);

String getConfirmationMenuAction();

void setConfirmationMenuAction(String action);