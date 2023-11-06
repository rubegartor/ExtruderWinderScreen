#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <lvgl.h>
#include <components/general.h>

void init_connection();

String getMac();

void send(const char* key, String data);