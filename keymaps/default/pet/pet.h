#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

#define ANIM_FRAME_DURATION 200
#define ANIM_SIZE 96

#include "luna.h"

uint32_t anim_timer = 0;
uint8_t current_frame = 0;
int current_wpm = 0;

bool is_pet_sneaking = false;
bool is_pet_jumping  = false;
bool is_jump_done = true;

void animate_pet(int x, int y) {
    if (is_pet_jumping || !is_jump_done) {
        oled_set_cursor(x, y + 2);
        oled_write("     ", false);
        oled_set_cursor(x, y - 1);
        is_jump_done = true;
    } else {
        oled_set_cursor(x, y - 1);
        oled_write("     ", false);
        oled_set_cursor(x, y);
    }

    current_frame = (current_frame + 1) % 2;
    led_t led_usb_state = host_keyboard_led_state();
    if (led_usb_state.caps_lock) {
        oled_write_raw_P(bark[current_frame], ANIM_SIZE);
    } else if (is_pet_sneaking) {
        oled_write_raw_P(sneak[current_frame], ANIM_SIZE);
    } else if (current_wpm <= MIN_WALK_SPEED) {
        oled_write_raw_P(sit[current_frame], ANIM_SIZE);
    } else if (current_wpm <= MIN_RUN_SPEED) {
        oled_write_raw_P(walk[current_frame], ANIM_SIZE);
    } else {
        oled_write_raw_P(run[current_frame], ANIM_SIZE);
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


