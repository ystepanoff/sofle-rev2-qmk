#include "config.h"
#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#include "oled_driver.h"
#include "pet/pet.c"
#include "dvd/dvd.c"
#endif

#include "gpio.h"

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{35+15, 5, hsv},\
	  {35+22, 3, hsv},\
	  {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {35+ 10, 2, hsv}, \
	  {35+ 20, 2, hsv}, \
	  {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {35+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {35+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {35+ 25, 2, hsv}


enum sofle_layers {
    _BASE,
    _UPPER,
    _LOWER,
    _ADJUST,
};

enum custom_keycodes {
    KC_PRVWD = QK_USER,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * BASE (COLEMAK-DH)
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BSPC |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |   `  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  |   \  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
    * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
    * |LSHIFT|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |RSHIFT|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LCTRL| LALT | LGUI |LOWER | / SPACE /       \ENTER \  |RAISE | RGUI | RALT | RCTRL|
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `-----------------------------------'           '------''---------------------------'
    */
    [_BASE] = LAYOUT(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC,
        KC_GRV,   KC_Q,   KC_W,    KC_F,    KC_P,     KC_B,                        KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_BSLS,
        KC_TAB,   KC_A,   KC_R,    KC_S,    KC_T,     KC_G,                        KC_M,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT,
        KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_D,     KC_V,  KC_MUTE,     XXXXXXX, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                    KC_LCTL, KC_LALT, KC_LGUI,  MO(_LOWER), KC_SPC,             KC_ENT, MO(_UPPER), KC_RGUI, KC_RALT, KC_RCTL
    ),

    /* UPPER
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | LLCK |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  `   |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   -  |   +  | F12  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   =  |   -  |   +  |   =  |   _  |-------.    ,-------| HOME |  END |  DEL | UNDO |  CUT |  |   |
    * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
    * |LSHIFT|   *  |   /  |   {  |   [  |   (  |-------|    |-------|   )  |   ]  |   }  | COPY | PASTE|RSHIFT|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LCTRL| LALT | LGUI |LOWER | / SPACE /       \ENTER \  |RAISE | RGUI | RALT |RCTRL |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `-----------------------------------'           '------''---------------------------'
    */
    [_UPPER] = LAYOUT(
        QK_LLCK,  KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,
        KC_GRV,   KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS,  KC_F12,
        KC_TAB,   KC_EQL,  KC_MINS, KC_PLUS,  KC_EQL,   KC_UNDS,                        KC_HOME, KC_END,  KC_DEL,  KC_UNDO, KC_CUT,   KC_PIPE,
        KC_LSFT,  XXXXXXX, XXXXXXX, KC_LCBR,  KC_LBRC,  KC_LPRN, KC_MUTE,      XXXXXXX, KC_RPRN, KC_RBRC, KC_RCBR, KC_COPY, KC_PASTE, KC_RSFT,
                         KC_LCTL, KC_LALT, KC_LGUI,  _______, KC_SPC,           KC_ENT, _______,  KC_RGUI, KC_RALT, KC_RCTL
    ),

    /* LOWER
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | LLCK |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      | INS  |PRSCR | MENU |      |      |                    | PGUP | PWRD |  UP  | NWRD |      | BSPC |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | CAPS |      |      |      |      |      |--------.   ,-------| PGDN | LEFT | DOWN |RIGHT | DEL  |      |
    * |------+------+------+------+------+------|  MUTE  |   |       |------+------+------+------+------+------|
    * |LSHIFT| UNDO |  CUT | COPY | PASTE|      |--------|   |-------|      | LSTR |      | LEND |      |RSHIFT|
    * `-----------------------------------------/       /     \       \----------------------------------------'
    *            |LCTRL | LALT | LGUI |LOWER | / SPACE /       \ ENTER \  |RAISE | RGUI | RALT |RCTRL |
    *            |      |      |      |      |/       /         \       \ |      |      |      |      |
    *            `-----------------------------------'           '-------''---------------------------'
    */
    [_LOWER] = LAYOUT(
        QK_LLCK, _______, _______, _______, _______, _______,                        _______, _______,  _______, _______,   _______,    _______,
        XXXXXXX, KC_INS,  KC_PSCR, KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, KC_PRVWD, KC_UP,   KC_NXTWD,  C(KC_BSPC), KC_BSPC,
        KC_CAPS, _______, _______, _______, XXXXXXX, XXXXXXX,                        KC_PGDN, KC_LEFT,  KC_DOWN, KC_RGHT,   KC_DEL,     _______,
        _______, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,    _______,  XXXXXXX, KC_LSTRT, XXXXXXX, KC_LEND,   XXXXXXX,    _______,
                        _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
    ),

    /* ADJUST
    * ,------------------------------------------.                    ,-----------------------------------------.
    * | LLCK |      |      |      |      |       |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+-------|                    |------+------+------+------+------+------|
    * | BOOT |      |      |      |      |       |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+-------|                    |------+------+------+------+------+------|
    * |      |      |MACWIN|      |      |       |-------.    ,-------|      | VOLD | MUTE | VOLU |      |      |
    * |------+------+------+------+------+-------|  MUTE |    |       |------+------+------+------+------+------|
    * |      |      |      |      |      |       |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
    * `------------------------------------------/       /     \       \----------------------------------------'
    *            | LCTRL | LALT | LGUI |LOWER | / SPACE /       \ ENTER \  |RAISE | RGUI | RALT | RCTRL |
    *            |       |      |      |      |/       /         \       \ |      |      |      |       |
    *            `------------------------------------'           '-------''----------------------------'
    */
    [_ADJUST] = LAYOUT(
        QK_LLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                           _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
    )
};

#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM layer_base_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    //SET_LAYER_ID(HSV_ORANGE)
    SET_INDICATORS(HSV_ORANGE),
    SET_UNDERGLOW(HSV_ORANGE)
);
const rgblight_segment_t PROGMEM layer_upper_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_INDICATORS(HSV_MAGENTA),
    SET_UNDERGLOW(HSV_MAGENTA),

    {11, 1, HSV_CORAL},

    {12, 1, HSV_BLUE},
    {21, 2, HSV_BLUE},
    {31, 2, HSV_BLUE},
    {35+10, 3, HSV_BLUE},
    {35+21, 2, HSV_BLUE},
    {35+31, 2, HSV_BLUE},

    {10, 1, HSV_PURPLE},
    {13, 3, HSV_PURPLE},
    {18, 3, HSV_PURPLE},
    {23, 2, HSV_PURPLE},
    {29, 2, HSV_PURPLE},
    {33, 2, HSV_PURPLE},
    {35+13, 1, HSV_PURPLE},
    {35+20, 1, HSV_PURPLE},
    {35+23, 1, HSV_PURPLE},
    {35+30, 1, HSV_PURPLE},
    {35+33, 1, HSV_PURPLE},
    {35+9, 1, HSV_PURPLE},

    {35+14, 2, HSV_CHARTREUSE},
    {35+18, 2, HSV_CHARTREUSE},
    {35+24, 1, HSV_CHARTREUSE},
    {35+29, 1, HSV_CHARTREUSE},
    {35+34, 1, HSV_CHARTREUSE},

    {25, 1, HSV_ORANGE},
    {28, 1, HSV_ORANGE},
    {35, 1, HSV_ORANGE},
    {35+25, 1, HSV_ORANGE},
    {35+28, 1, HSV_ORANGE},
    {35+35, 1, HSV_ORANGE},

    {7, 1, HSV_MAGENTA},
    {16, 2, HSV_MAGENTA},
    {26, 1, HSV_MAGENTA},
    {35+7, 1, HSV_MAGENTA},
    {35+16, 2, HSV_MAGENTA},
    {35+26, 1, HSV_MAGENTA},

    {27, 1, HSV_RED},
    {35+27, 1, HSV_RED}

    /*SET_NUMPAD(HSV_BLUE),
    {7, 2, HSV_ORANGE},
    {25, 2, HSV_ORANGE},
    {25, 2, HSV_ORANGE},
    {25, 2, HSV_ORANGE}*/
);
const rgblight_segment_t PROGMEM layer_lower_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_GREEN),
    SET_NUMROW(HSV_GREEN)
);
const rgblight_segment_t PROGMEM layer_adjust_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PURPLE)
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_base_lights,
    layer_upper_lights,
    layer_lower_lights,
    layer_adjust_lights
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;

	rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5);// haven't found a way to set this in a more useful way

}
#endif

static bool adjust_locked = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_LLCK:
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                if (current_layer == _ADJUST) {
                    adjust_locked = !adjust_locked;
                }
                layer_lock_invert(current_layer);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                is_ctrl_pressed = true;
            } else {
                is_ctrl_pressed = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed && current_wpm > WPM_SPEED_1) {
                is_pet_jumping  = true;
                is_pet_jump_done = false;
            } else {
                is_pet_jumping = false;
            }
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (adjust_locked) {
        state |= (1 << _ADJUST);
        return state;
    }
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
	rgblight_set_layer_state(1, layer_state_cmp(state, _UPPER));
	rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
	rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    return update_tri_layer_state(state, _LOWER, _UPPER, _ADJUST);
}

// OLED
#ifdef OLED_ENABLE
static void print_status_narrow(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("----------COLEMAK-DH----------"), false);
            break;
        case _UPPER:
            oled_write_P(PSTR("----------  UPPER   ----------"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("----------  LOWER   ----------"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("----------  ADJUST  ----------"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n\n"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    if (led_usb_state.caps_lock) {
        oled_write_ln_P(PSTR(" CAPSLOCK "), 1);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
        current_wpm = get_current_wpm();
        render_pet(64, 0);
    } else {
        render_dvd();
    }
    return false;
}
#endif

// Encoders
#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (get_highest_layer(layer_state) == _UPPER) {
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
        } else {
            tap_code(clockwise ? KC_RIGHT : KC_LEFT);
        }
        left_encoder_state = clockwise ? 1: -1;
        last_ctrl_direction = clockwise ? _CTRL_EAST : _CTRL_WEST;
        last_activity_left_encoder = timer_read32();
    } else if (index == 1) {
        if (get_highest_layer(layer_state) == _UPPER) {
            tap_code(clockwise ? KC_PGDN : KC_PGUP);
        } else {
            tap_code(clockwise ? KC_UP : KC_DOWN);
        }
        right_encoder_state = clockwise ? -1 : 1;
        last_ctrl_direction = clockwise ? _CTRL_NORTH : _CTRL_SOUTH;
        last_activity_right_encoder = timer_read32();
    }
    return true;
}

void matrix_scan_user(void) {
    uint32_t now = timer_read32();
    if ((now - last_activity_left_encoder) > ENCODER_STATE_TIMEOUT) {
        left_encoder_state = 0;
    }
    if ((now - last_activity_right_encoder) > ENCODER_STATE_TIMEOUT) {
        right_encoder_state = 0;
    }
}
#endif
