#include <pebble.h>
#include "watchface.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static GFont s_res_bitham_42_bold;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_18;
static TextLayer *time_label;
static TextLayer *element_code_label;
static TextLayer *atomic_number_label;
static TextLayer *atomic_weight_label;
static TextLayer *element_name_label;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  // time_label
  time_label = text_layer_create(GRect(0, 0, 144, 37));
  text_layer_set_text(time_label, "--:--");
  text_layer_set_text_alignment(time_label, GTextAlignmentCenter);
  text_layer_set_font(time_label, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)time_label);
  
  // element_code_label
  element_code_label = text_layer_create(GRect(5, 67, 134, 55));
  text_layer_set_background_color(element_code_label, GColorBlack);
  text_layer_set_text_color(element_code_label, GColorWhite);
  text_layer_set_text(element_code_label, "Hg");
  text_layer_set_text_alignment(element_code_label, GTextAlignmentCenter);
  text_layer_set_font(element_code_label, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)element_code_label);
  
  // atomic_number_label
  atomic_number_label = text_layer_create(GRect(5, 40, 45, 24));
  text_layer_set_background_color(atomic_number_label, GColorBlack);
  text_layer_set_text_color(atomic_number_label, GColorWhite);
  text_layer_set_text(atomic_number_label, "80");
  text_layer_set_font(atomic_number_label, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)atomic_number_label);
  
  // atomic_weight_label
  atomic_weight_label = text_layer_create(GRect(5, 140, 134, 24));
  text_layer_set_background_color(atomic_weight_label, GColorBlack);
  text_layer_set_text_color(atomic_weight_label, GColorWhite);
  text_layer_set_text(atomic_weight_label, "200.5900");
  text_layer_set_text_alignment(atomic_weight_label, GTextAlignmentRight);
  text_layer_set_font(atomic_weight_label, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)atomic_weight_label);
  
  // element_name_label
  element_name_label = text_layer_create(GRect(5, 113, 134, 23));
  text_layer_set_background_color(element_name_label, GColorClear);
  text_layer_set_text_color(element_name_label, GColorWhite);
  text_layer_set_text(element_name_label, "Mercury");
  text_layer_set_text_alignment(element_name_label, GTextAlignmentCenter);
  text_layer_set_font(element_name_label, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)element_name_label);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(time_label);
  text_layer_destroy(element_code_label);
  text_layer_destroy(atomic_number_label);
  text_layer_destroy(atomic_weight_label);
  text_layer_destroy(element_name_label);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_watchface(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_watchface(void) {
  window_stack_remove(s_window, true);
}

void set_element(const struct element *element) {
    text_layer_set_text(element_code_label, element->code);
    text_layer_set_text(element_name_label, element->name);
    text_layer_set_text(atomic_number_label, element->number);
    text_layer_set_text(atomic_weight_label, element->mass);
}

void set_time_label(const char *time) {
    text_layer_set_text(time_label, time);
}
