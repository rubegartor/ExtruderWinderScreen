#include <components/settingsTab.h>

static void lv_min_spinbox_increment_event_cb(lv_event_t *event)
{
  lv_event_code_t code = lv_event_get_code(event);
  if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
    lv_spinbox_increment(minSpeedSpinbox);

    send("setMinSpeed", (String)lv_spinbox_get_value(minSpeedSpinbox));
  }
}

static void lv_min_spinbox_decrement_event_cb(lv_event_t *event)
{
  lv_event_code_t code = lv_event_get_code(event);
  if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
    lv_spinbox_decrement(minSpeedSpinbox);

    send("setMinSpeed", (String)lv_spinbox_get_value(minSpeedSpinbox));
  }
}

static void lv_max_spinbox_increment_event_cb(lv_event_t *event)
{
  lv_event_code_t code = lv_event_get_code(event);
  if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT) {
    lv_spinbox_increment(maxSpeedSpinbox);

    send("setMaxSpeed", (String)lv_spinbox_get_value(maxSpeedSpinbox));
  }
}

static void lv_max_spinbox_decrement_event_cb(lv_event_t *event)
{
  lv_event_code_t code = lv_event_get_code(event);
  if(code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
    lv_spinbox_decrement(maxSpeedSpinbox);

    send("setMaxSpeed", (String)lv_spinbox_get_value(maxSpeedSpinbox));
  }
}

static void event_handler(lv_event_t *event)
{
  lv_event_code_t code = lv_event_get_code(event);
  lv_obj_t * obj = lv_event_get_target(event);
  if(code == LV_EVENT_VALUE_CHANGED) {
    char buf[12];
    lv_dropdown_get_selected_str(obj, buf, sizeof(buf));

    send("setPolymer", String(buf));
  }

  if (code == LV_EVENT_READY) {
    lv_obj_set_style_text_font(lv_dropdown_get_list(lv_event_get_target(event)), &lv_font_montserrat_20, 0);
  }
}

static void restar_system_cb(lv_event_t *event) {
  digitalWrite(TFT_BL, LOW);
  send("reboot", "");

  delay(1500);
}

void build_settingsTab(lv_obj_t *parent) {
  lv_obj_t *settingsParent = lv_obj_create(parent);
  lv_obj_align(settingsParent, LV_ALIGN_TOP_LEFT, 10, 10);
  lv_obj_set_size(settingsParent, lv_obj_get_width(parent) - 20, lv_obj_get_height(parent) - 20);
  lv_obj_set_style_bg_color(settingsParent, lv_palette_darken(LV_PALETTE_GREY, 2), 0);
  lv_obj_set_style_border_width(settingsParent, 0, 0);

  lv_obj_t *minSpeedSpinboxLabel = lv_label_create(settingsParent);
  lv_obj_set_style_text_color(minSpeedSpinboxLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(minSpeedSpinboxLabel, LV_ALIGN_TOP_LEFT, 0, 20);
  lv_label_set_text(minSpeedSpinboxLabel, "Min Speed");

  minSpeedSpinbox = lv_spinbox_create(settingsParent);
  lv_spinbox_set_range(minSpeedSpinbox, 0, 13000);
  lv_spinbox_set_digit_format(minSpeedSpinbox, 5, 0);
  lv_spinbox_set_step(minSpeedSpinbox, 1000);
  lv_spinbox_step_prev(minSpeedSpinbox);
  lv_obj_set_width(minSpeedSpinbox, 150);
  lv_obj_align_to(minSpeedSpinbox, minSpeedSpinboxLabel, LV_ALIGN_OUT_RIGHT_MID, lv_obj_get_height(minSpeedSpinbox) + 165, 0);

  lv_obj_t *minSpeedSpinboxPlusBtn = lv_btn_create(settingsParent);
  lv_obj_set_size(minSpeedSpinboxPlusBtn, lv_obj_get_height(minSpeedSpinbox), lv_obj_get_height(minSpeedSpinbox));
  lv_obj_align_to(minSpeedSpinboxPlusBtn, minSpeedSpinbox, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
  lv_obj_set_style_bg_img_src(minSpeedSpinboxPlusBtn, LV_SYMBOL_PLUS, 0);
  lv_obj_set_style_bg_color(minSpeedSpinboxPlusBtn, lv_palette_main(LV_PALETTE_ORANGE), 0);
  lv_obj_add_event_cb(minSpeedSpinboxPlusBtn, lv_min_spinbox_increment_event_cb, LV_EVENT_ALL,  NULL);

  lv_obj_t *minSpeedSpinboxMinusBtn = lv_btn_create(settingsParent);
  lv_obj_set_size(minSpeedSpinboxMinusBtn, lv_obj_get_height(minSpeedSpinbox), lv_obj_get_height(minSpeedSpinbox));
  lv_obj_align_to(minSpeedSpinboxMinusBtn, minSpeedSpinbox, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  lv_obj_set_style_bg_img_src(minSpeedSpinboxMinusBtn, LV_SYMBOL_MINUS, 0);
  lv_obj_set_style_bg_color(minSpeedSpinboxMinusBtn, lv_palette_main(LV_PALETTE_ORANGE), 0);
  lv_obj_add_event_cb(minSpeedSpinboxMinusBtn, lv_min_spinbox_decrement_event_cb, LV_EVENT_ALL, NULL);

  


  lv_obj_t *maxSpeedSpinboxLabel = lv_label_create(settingsParent);
  lv_obj_set_style_text_color(maxSpeedSpinboxLabel, lv_color_hex(0xFFFFFF), 0);
  lv_label_set_text(maxSpeedSpinboxLabel, "Max Speed");
  lv_obj_align(maxSpeedSpinboxLabel, LV_ALIGN_TOP_LEFT, 0, 100);

  maxSpeedSpinbox = lv_spinbox_create(settingsParent);
  lv_spinbox_set_range(maxSpeedSpinbox, 0, 13000);
  lv_spinbox_set_digit_format(maxSpeedSpinbox, 5, 0);
  lv_spinbox_step_prev(maxSpeedSpinbox);
  lv_spinbox_set_step(maxSpeedSpinbox, 1000);
  lv_obj_set_width(maxSpeedSpinbox, 150);
  lv_obj_align_to(maxSpeedSpinbox, minSpeedSpinbox, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

  lv_obj_t *maxSpeedSpinboxPlusBtn = lv_btn_create(settingsParent);
  lv_obj_set_size(maxSpeedSpinboxPlusBtn, lv_obj_get_height(maxSpeedSpinbox), lv_obj_get_height(maxSpeedSpinbox));
  lv_obj_align_to(maxSpeedSpinboxPlusBtn, maxSpeedSpinbox, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
  lv_obj_set_style_bg_img_src(maxSpeedSpinboxPlusBtn, LV_SYMBOL_PLUS, 0);
  lv_obj_set_style_bg_color(maxSpeedSpinboxPlusBtn, lv_palette_main(LV_PALETTE_ORANGE), 0);
  lv_obj_add_event_cb(maxSpeedSpinboxPlusBtn, lv_max_spinbox_increment_event_cb, LV_EVENT_ALL,  NULL);

  lv_obj_t *maxSpeedSpinboxMinusBtn = lv_btn_create(settingsParent);
  lv_obj_set_size(maxSpeedSpinboxMinusBtn, lv_obj_get_height(maxSpeedSpinbox), lv_obj_get_height(maxSpeedSpinbox));
  lv_obj_align_to(maxSpeedSpinboxMinusBtn, maxSpeedSpinbox, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  lv_obj_set_style_bg_img_src(maxSpeedSpinboxMinusBtn, LV_SYMBOL_MINUS, 0);
  lv_obj_set_style_bg_color(maxSpeedSpinboxMinusBtn, lv_palette_main(LV_PALETTE_ORANGE), 0);
  lv_obj_add_event_cb(maxSpeedSpinboxMinusBtn, lv_max_spinbox_decrement_event_cb, LV_EVENT_ALL, NULL);

  polymerDropdown = lv_dropdown_create(settingsParent);
  lv_dropdown_set_options(polymerDropdown, "PLA\nABS\nTPU (80A)\nTPU (85A)\nTPU (90A)\nPETG\nPC/ABS\nOtro");
  lv_obj_align(polymerDropdown, LV_ALIGN_TOP_MID, 0, 20);
  lv_obj_add_event_cb(polymerDropdown, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align_to(polymerDropdown, maxSpeedSpinboxMinusBtn, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
  lv_obj_set_style_text_font(polymerDropdown, &lv_font_montserrat_28, 0);
  lv_obj_set_width(polymerDropdown, 280);

  lv_obj_t *polymerDropdownLabel = lv_label_create(settingsParent);
  lv_label_set_text(polymerDropdownLabel, "Polimero");
  lv_obj_set_style_text_color(polymerDropdownLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align_to(polymerDropdownLabel, maxSpeedSpinboxLabel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, lv_obj_get_height(polymerDropdown) - 20);

  lv_obj_t *restartSystemBtn = lv_btn_create(settingsParent);
  lv_obj_align(restartSystemBtn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_obj_set_style_bg_color(restartSystemBtn, lv_palette_main(LV_PALETTE_ORANGE), 0);
  lv_obj_add_event_cb(restartSystemBtn, restar_system_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_t *restartSystemBtnLabel = lv_label_create(restartSystemBtn);
  lv_obj_set_style_text_color(restartSystemBtnLabel, lv_color_hex(0xFFFFFF), 0);
  lv_label_set_text(restartSystemBtnLabel, LV_SYMBOL_REFRESH " Reiniciar");
}