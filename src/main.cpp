#include <lvgl.h>
#include <BlockNot.h>
#include <Arduino_GFX_Library.h>

#include <connection/connection.h>
#include <components/sidebar.h>
#include <components/homeTab.h>
#include <components/controlTab.h>
#include <components/settingsTab.h>
#include <components/popupTab.h>

BlockNot updateLVGL(10);

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */,
    0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 8 /* hsync_back_porch */,
    0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 8 /* vsync_back_porch */,
    0 /* pclk_active_neg */, 16000000 /* prefer_speed */);

Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    800 /* width */, 480 /* height */, rgbpanel);

#include "touch.h"

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  if (touch_has_signal()) {
    if (touch_touched()) {
      data->state = LV_INDEV_STATE_PR;

      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    } else if (touch_released()) {
      data->state = LV_INDEV_STATE_REL;
    }
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

void my_log_cb(const char *buf) {
  Serial2.printf(buf, strlen(buf));
}

void update_widgets_timer(lv_timer_t *timer) {
  lv_label_set_text(actMeasureLabel, String(actRead).c_str());
  lv_label_set_text(minMeasureLabel, String(minRead).c_str());
  lv_label_set_text(maxMeasureLabel, String(maxRead).c_str());
  lv_label_set_text(winderInfoPullerSpeedLabel, (LV_SYMBOL_LOOP + String(' ') + String(pSpeed)).c_str());
  lv_label_set_text(winderInfoWeightLabel, (String(weight) + String("g")).c_str());
  lv_label_set_text(winderInfoTimeLabel, eTime.c_str());
}

void setup() {
  Serial2.begin(115200, SERIAL_8N1, 18, 17);
  Serial2.setDebugOutput(true);

  gfx->begin();

  lv_init();
  delay(10);
  touch_init();

  lv_log_register_print_cb(my_log_cb);

  screenWidth = gfx->width();
  screenHeight = gfx->height();

  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  if (disp_draw_buf) {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 4);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Initialize the (dummy) input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    build_sidebar();
    build_homeTab(tab1);
    build_controlTab(tab2);
    build_settingsTab(tab3);
    build_popupTab(tab4);

    delay(500);

    init_connection();

    // Startup config requests
    do {
      Serial2.println("Requesting reqDiameter");
      send("reqDiameter", "");
      delay(100);
    } while (!reqDiameterSetted);

    do {
      Serial2.println("Requesting reqDiameter");
      send("reqMinPSpeed", "");
      delay(100);
    } while (!reqMinPSpeedSetted);

    do {
      Serial2.println("Requesting reqMaxPSpeed");
      send("reqMaxPSpeed", "");
      delay(100);
    } while (!reqMaxPSpeedSetted);
    
    do {
      Serial2.println("Requesting reqPolymer");
      send("reqPolymer", "");
      delay(100);
    } while(!reqPolymerSetted);

    do {
      Serial2.println("Requesting reqMinRead");
      send("reqMinRead", "");
      delay(100);
    } while(!reqMinReadSetted);

    do {
      Serial2.println("Requesting reqMaxRead");
      send("reqMaxRead", "");
      delay(100);
    } while(!reqMaxReadSetted);

    do {
      Serial2.println("Requesting reqAutostop");
      send("reqAutostop", "");
      delay(100);
    } while (!reqAutoStopSetted);

    do {
      Serial2.println("Requesting reqMaxPosition");
      send("reqMaxPosition", "");
      delay(100);
    } while (!reqMaxPositionSetted);

    do {
      Serial2.println("Requesting reqMinPosition");
      send("reqMinPosition", "");
      delay(100);
    } while(!reqMinPositionSetted);

    do {
      Serial2.println("Requesting reqPositioned");
      send("reqPositioned", "");
      delay(100);
    } while(!reqPositionedSetted);


    #ifdef TFT_BL
      pinMode(TFT_BL, OUTPUT);
      digitalWrite(TFT_BL, HIGH);
    #endif

    lv_timer_create(update_widgets_timer, 100, NULL);
  }
}

void loop() {
  if (updateLVGL.TRIGGERED) {
    lv_timer_handler();
  }
}
