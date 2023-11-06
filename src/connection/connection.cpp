#include <connection/connection.h>

esp_now_peer_info_t peerInfo;

typedef struct struct_message {
  String key;
  String data;
} struct_message;

struct_message dataStruct;

struct_message incomingData;

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incoming, int len) {
  memcpy(&incomingData, incoming, sizeof(incomingData));

  if (incomingData.key == "resetScr") {
    digitalWrite(TFT_BL, LOW);
    delay(1500);
    ESP.restart();
  }

  if (incomingData.key == "lastRead") {
    actRead = incomingData.data.toFloat();
  }

  if (incomingData.key == "minRead") {
    reqMinReadSetted = true;
    minRead = incomingData.data.toFloat();
  }

  if (incomingData.key == "maxRead") {
    reqMaxReadSetted = true;
    maxRead = incomingData.data.toFloat();
  }

  if (incomingData.key == "pSpeed") {
    pSpeed = incomingData.data.toInt();
  }

  if (incomingData.key == "eWeight") {
    weight = incomingData.data.toFloat();
  }

  if (incomingData.key == "eTime") {
    eTime = incomingData.data;
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
    }  }
}

void init_connection() {
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    return;
  }
  
  // Register peer
  memcpy(peerInfo.peer_addr, winderAddr, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    return;
  }

  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

void send(const char* key, String data) {
  dataStruct.key = key;
  dataStruct.data = data;

  esp_now_send(winderAddr, (uint8_t *)&dataStruct, sizeof(dataStruct));
}