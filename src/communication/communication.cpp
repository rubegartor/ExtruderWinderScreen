#include <communication/communication.h>
#include <components/general.h>

typedef struct struct_message {
  String key;
  String data;
} struct_message;

struct_message sendingData;
struct_message incomingData;

String sendOutBuffer[QEUE_BUFFER_SIZE];
uint16_t sendOutBufferIndex = 0;

void _emptyBuffer() {
  memset(sendOutBuffer, 0, QEUE_BUFFER_SIZE);
  sendOutBufferIndex = 0;
}

void _requestEvent() {
  if (sendOutBufferIndex > 0) {
    for (uint8_t i = 0; i < 32; i++) {
      Wire.write(sendOutBuffer[i].c_str());
    }

    _emptyBuffer();
  } else {
    Wire.write("                                ");
  }
}

void _convertToStruct(const String &input, char delimiter) {
  int delimiterPos = input.indexOf(delimiter);

  incomingData.key = input.substring(0, delimiterPos);
  incomingData.data = input.substring(delimiterPos + 1);
}

void _receiveEvent(int bytes) {
  String line = "";
  while (Wire.available()) {
    for (int i = 0; i < bytes; i++) {
      byte x = Wire.read();
      line += (char)x;
    }
  }

  _convertToStruct(line, ';');

  if (incomingData.key == "resetScr") {
  }

  if (incomingData.key == "lastRead") {
    lv_label_set_text(actMeasureLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "minRead") {
    reqMinReadSetted = true;
    lv_label_set_text(minMeasureLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "maxRead") {
    reqMaxReadSetted = true;
    lv_label_set_text(maxMeasureLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "pSpeed") {
    lv_label_set_text(winderInfoPullerSpeedLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "eWeight") {
    lv_label_set_text(winderInfoWeightLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "temp") {
    lv_label_set_text(waterTempInfoLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "eTime") {
    lv_label_set_text(winderInfoTimeLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "stTemp") {
    reqTempSetted = true;
    lv_spinbox_set_value(waterTempSpinbox, incomingData.data.toInt());
  }

  if (incomingData.key == "minPSpeed") {
    reqMinPSpeedSetted = true;
    lv_spinbox_set_value(minSpeedSpinbox, incomingData.data.toInt());
  }

  if (incomingData.key == "maxPSpeed") {
    reqMaxPSpeedSetted = true;
    lv_spinbox_set_value(maxSpeedSpinbox, incomingData.data.toInt());
  }

  if (incomingData.key == "polymer") {
    reqPolymerSetted = true;
    lv_dropdown_set_selected(polymerDropdown, incomingData.data.toInt());
  }

  if (incomingData.key == "diameter") {
    reqDiameterSetted = true;
    lv_spinbox_set_value(diameterSpinbox, incomingData.data.toFloat() * 100);
    delay(100);
    lv_obj_invalidate(diameterSpinbox);
  }

  if (incomingData.key == "autostop") {
    reqAutoStopSetted = true;

    lv_spinbox_set_value(autostopSpinbox, incomingData.data.toFloat() * 100);
    delay(100);
    lv_obj_invalidate(autostopSpinbox);
  }

  if (incomingData.key == "maxPosition") {
    reqMaxPositionSetted = true;

    uint16_t maxPosition = incomingData.data.toInt();
    lv_bar_set_range(positionBar, lv_bar_get_min_value(positionBar), maxPosition);
    lv_label_set_text(positionBarMaxLabel, String(maxPosition).c_str());

    lv_obj_invalidate(positionBar);
  }

  if (incomingData.key == "minPosition") {
    reqMinPositionSetted = true;

    int16_t minPosition = incomingData.data.toInt();
    lv_bar_set_range(positionBar, minPosition, lv_bar_get_max_value(positionBar));
    lv_label_set_text(positionBarMinLabel, String(minPosition).c_str());

    lv_obj_invalidate(positionBar);
  }

  if (incomingData.key == "position") {
    lv_bar_set_value(positionBar, incomingData.data.toInt(), LV_ANIM_ON);
    lv_obj_invalidate(positionBar);
  }

  if (incomingData.key == "positioned") {
    reqPositionedSetted = true;

    if (incomingData.data.toInt() == true) {
      lv_obj_set_style_pad_top(controlParentContent, 80, 0);
      lv_obj_del(startAlignerBtn);
    }  
  }

  if (incomingData.key == "stAutoStop") {
    reqStAutoStopSetted = true;
    String labelText;

    if (incomingData.data.toInt() == 0) {
      labelText = "Auto Stop  " LV_SYMBOL_OK;
    } else if (incomingData.data.toInt() == 2) {
      labelText = "Auto Stop  " LV_SYMBOL_CLOSE;
    } else {
      labelText = "Auto Stop";
    }

    lv_label_set_text(autostopSpinboxLabel, labelText.c_str());
  }
}

void Communication::sendEvent(String eventName, String eventData) {
  String builtData = eventName + ";" + eventData;
  String whiteSpaces = "";

  for (uint16_t i = 0; i < (QEUE_BUFFER_SIZE - builtData.length()); i++) {
    whiteSpaces += " ";
  }

  builtData = builtData + whiteSpaces;
  sendOutBuffer[sendOutBufferIndex] = builtData;
  sendOutBufferIndex++;
}

void Communication::init() {
  Wire.onReceive(_receiveEvent);
  Wire.onRequest(_requestEvent);

  Wire.begin(SLAVE_ADDRESS);
}