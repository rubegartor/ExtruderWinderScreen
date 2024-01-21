#include <communication/communication.h>
#include <components/general.h>

typedef struct struct_message {
  String key;
  String data;
} struct_message;

struct_message sendingData;
struct_message incomingData;

String sendOutBuffer[QUEUE_BUFFER_SIZE];
uint8_t sendOutBufferIndex = 0;

void _emptyBuffer() {
  memset(sendOutBuffer, 0, sizeof(sendOutBuffer) / sizeof(String));
  sendOutBufferIndex = 0;
}

String _fillBuffer(String data) {
  String whiteSpaces = "";

  for (uint16_t i = 0; i < (QUEUE_BUFFER_SIZE - data.length()); i++) {
    whiteSpaces += " ";
  }
  
  return whiteSpaces;
}

void _requestEvent() {
  if (sendOutBufferIndex > 0) {
    for (String toSend : sendOutBuffer) {
      if (toSend.isEmpty()) continue;
      Wire.write(toSend.c_str());
    }

    _emptyBuffer();
  } else {
    Wire.write(_fillBuffer("").c_str());
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
    for (uint8_t i = 0; i < bytes; i++) {
      byte x = Wire.read();
      line += (char)x;
    }
  }

  _convertToStruct(line, ';');

  if (incomingData.key == "resetScr") {
    NVIC_SystemReset();
  }

  if (incomingData.key == "lastRead") {
    lv_label_set_text(actMeasureLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "minRead") {
    lv_label_set_text(minMeasureLabel, incomingData.data.c_str());
  }

  if (incomingData.key == "maxRead") {
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
    lv_spinbox_set_value(waterTempSpinbox, incomingData.data.toInt());
  }

  if (incomingData.key == "minPSpeed") {
    lv_spinbox_set_value(minSpeedSpinbox, incomingData.data.toInt());
  }

  if (incomingData.key == "maxPSpeed") {
    lv_spinbox_set_value(maxSpeedSpinbox, incomingData.data.toInt());
  }

  if (incomingData.key == "polymer") {
    lv_dropdown_set_selected(polymerDropdown, incomingData.data.toInt());
  }

  if (incomingData.key == "diameter") {
    lv_spinbox_set_value(diameterSpinbox, incomingData.data.toFloat() * 100);
    lv_obj_invalidate(diameterSpinbox);
  }

  if (incomingData.key == "autostop") {
    lv_spinbox_set_value(autostopSpinbox, incomingData.data.toFloat() * 100);
    lv_obj_invalidate(autostopSpinbox);
  }

  if (incomingData.key == "maxPosition") {
    uint16_t maxPosition = incomingData.data.toInt();
    lv_bar_set_range(positionBar, lv_bar_get_min_value(positionBar), maxPosition);
    lv_label_set_text(positionBarMaxLabel, String(maxPosition).c_str());

    lv_obj_invalidate(positionBar);
  }

  if (incomingData.key == "minPosition") {
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
    if ((bool)incomingData.data.toInt()) {
      lv_obj_set_style_pad_top(controlParentContent, 80, 0);
      lv_obj_del(startAlignerBtn);
    }  
  }

  if (incomingData.key == "stAutoStop") {
    rgb.off();

    switch (incomingData.data.toInt()){
      case 0:
        rgb.on(0, 255, 0);
        break;
      case 2:
        rgb.on(255, 0, 0);
        break;
    }
  }
}

void Communication::sendEvent(String eventName, String eventData) {
  sendingData.key = eventName;
  sendingData.data = eventData;

  String builtData = sendingData.key + ";" + sendingData.data;
  builtData = builtData + _fillBuffer(builtData);

  if (builtData.length() != QUEUE_BUFFER_SIZE) return;
  if (sendOutBufferIndex > QUEUE_BUFFER_SIZE - 1) return;
  
  sendOutBuffer[sendOutBufferIndex] = builtData;
  sendOutBufferIndex++;
}

void Communication::handleRequests() {
  if (this->requestCompletedIndex == sizeof(requests) / sizeof(String)) return;

  if (!requestsCompleted && millis() - this->lastMillisRequests > REQUESTS_DELAY) {
    communication.sendEvent(requests[this->requestCompletedIndex], "");
    this->requestCompletedIndex++;
    this->lastMillisRequests = millis();
  }
}

void Communication::init() {
  Wire.onReceive(_receiveEvent);
  Wire.onRequest(_requestEvent);

  Wire.begin(SLAVE_ADDRESS);
}