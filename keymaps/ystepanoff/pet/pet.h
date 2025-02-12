#define WPM_SPEED_1 10
#define WPM_SPEED_2 40

#define ANIM_FRAME_DURATION 200

#include "neko.h"

uint32_t anim_timer = 0;
uint8_t current_frame = 0;
int current_wpm = 0;

bool is_ctrl_pressed = false;
bool is_pet_jumping  = false;
bool is_pet_jump_done = true;

void animate_pet(int x, int y) {
    if (!is_ctrl_pressed) {
        if (is_pet_jumping || !is_pet_jump_done) {
            oled_set_cursor(x, y);
            oled_write_raw_P(blank, sizeof(blank));
            oled_set_cursor(x, y - 1);
            is_pet_jump_done = true;
        } else {
            oled_set_cursor(x, y - 1);
            oled_write_raw_P(blank, sizeof(blank));
            oled_set_cursor(x, y);
        }
    } else {
        oled_set_cursor(x, y);
    }

    current_frame = (current_frame + 1) % 2;
    led_t led_usb_state = host_keyboard_led_state();
    if (led_usb_state.caps_lock) {
        oled_write_raw_P(caps[current_frame], ANIM_SIZE);
    } else if (is_ctrl_pressed) {
        oled_write_raw_P(ctrl[current_frame], ANIM_SIZE);
    } else if (current_wpm <= WPM_SPEED_1) {
        oled_write_raw_P(low[current_frame], ANIM_SIZE);
    } else if (current_wpm <= WPM_SPEED_2) {
        oled_write_raw_P(mid[current_frame], ANIM_SIZE);
    } else {
        oled_write_raw_P(high[current_frame], ANIM_SIZE);
    }
}


static void render_pet(int x, int y) {
#if OLED_TIMEOUT > 0
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }
#endif

    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_pet(x, y);
    }
}


