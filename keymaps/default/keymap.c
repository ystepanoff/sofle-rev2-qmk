#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#include "oled_driver.h"
#include "pet/pet.h"
#endif

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _BASE,
    _UPPER,
    _LOWER,
    _ADJUST,
};

enum custom_keycodes {
    KC_PRVWD = QK_USER,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND
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
                    KC_LCTL, KC_LALT, KC_LGUI,  TL_LOWR, KC_SPC,             KC_ENT, TL_UPPR, KC_RGUI, KC_RALT, KC_RCTL
    ),

    /* UPPER
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |  `   |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  | F12  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | TAB  |   =  |   -  |   +  |   {  |   }  |-------.    ,-------|   ;  |   :  |   _  |   [  |   ]  |   |  |
    * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
    * |LSHIFT|      |      |      |      |      |-------|    |-------|      |      |      |      |      |RSHIFT|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *            | LCTRL| LALT | LGUI |LOWER | / SPACE /       \ENTER \  |RAISE | RGUI | RALT |RCTRL |
    *            |      |      |      |      |/       /         \      \ |      |      |      |      |
    *            `-----------------------------------'           '------''---------------------------'
    */
    [_UPPER] = LAYOUT(
        _______,  KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_GRV,   KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F12,
        KC_TAB,   KC_EQL,  KC_MINS, KC_PLUS,  KC_LCBR,  KC_RCBR,                        KC_SCLN, KC_COLN, KC_UNDS, KC_LBRC, KC_RBRC, KC_PIPE,
        KC_LSFT,  _______, _______, _______,  _______,  _______, KC_MUTE,      XXXXXXX, _______, _______, _______, _______, _______, KC_RSFT,
                         KC_LCTL, KC_LALT, KC_LGUI,  TL_LOWR, KC_SPC,           KC_ENT, TL_UPPR,  KC_RGUI, KC_RALT, KC_RCTL
    ),

    /* LOWER
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      | INS  |PRSCR | MENU |      |      |                    | PGUP | PWRD |  UP  | NWRD |      | BSPC |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | CAPS |      |      |      |      |      |--------.   ,-------| PGDN | LEFT | DOWN |RIGHT | DEL  |      |
    * |------+------+------+------+------+------|  MUTE  |   |       |------+------+------+------+------+------|
    * |LSHIFT| UNDO |  CUT | COPY | PASTE|      |--------|   |-------|      | LSTR |      | LEND |      |RSHIFT|
    * `-----------------------------------------/       /     \       \-----------------------------------------'
    *            |LCTRL | LALT | LGUI |LOWER | / SPACE /       \ ENTER \  |RAISE | RGUI | RALT |RCTRL |
    *            |      |      |      |      |/       /         \       \ |      |      |      |      |
    *            `-----------------------------------'           '-------''---------------------------'
    */
    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                        _______, _______,  _______, _______,   _______,    _______,
        XXXXXXX, KC_INS,  KC_PSCR, KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, KC_PRVWD, KC_UP,   KC_NXTWD,  C(KC_BSPC), KC_BSPC,
        KC_CAPS, _______, _______, _______, XXXXXXX, XXXXXXX,                        KC_PGDN, KC_LEFT,  KC_DOWN, KC_RGHT,   KC_DEL,     _______,
        _______, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,    _______,  XXXXXXX, KC_LSTRT, XXXXXXX, KC_LEND,   XXXXXXX,    _______,
                        _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
    ),

    /* ADJUST
    * ,------------------------------------------.                    ,-----------------------------------------.
    * |      |      |      |      |      |       |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+-------|                    |------+------+------+------+------+------|
    * | BOOT |      |      |      |      |       |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+-------|                    |------+------+------+------+------+------|
    * |      |      |MACWIN|      |      |       |-------.    ,-------|      | VOLD | MUTE | VOLU |      |      |
    * |------+------+------+------+------+-------|  MUTE |    |       |------+------+------+------+------+------|
    * |      |      |      |      |      |       |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
    * `------------------------------------------/       /     \      \-----------------------------------------'
    *            | LCTRL | LALT | LGUI |LOWER | / ENTER /       \Space \  |RAISE | RGUI | RALT | RCTRL |
    *            |       |      |      |      |/       /         \      \ |      |      |      |       |
    *            `------------------------------------'           '------''----------------------------'
    */
    [_ADJUST] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                           _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
                is_pet_sneaking = true;
            } else {
                is_pet_sneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                is_pet_jumping  = true;
                is_jump_done = false;
            } else {
                is_pet_jumping = false;
            }
            break;
    }
    return true;
}

const char PROGMEM image[] = {
    0,  0,  0,  0,  0,  192,192,128,0,  0,  128,192,192,0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  224,224,0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  224,224,0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  224,224,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  224,224,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  1,  7,  127,127,7,  1,  0,  62, 127,107,
    105,105,111,110,28, 127,119,99, 99, 255,255,0,  28, 127,119,99,
    99, 119,127,28, 0,  127,127,3,  1,  1,  0,  1,  1,  102,111,111,
    95, 123,123,48, 0,  0,  0,  0,  0,  0,  127,127,28, 62, 119,99,
    65, 28, 127,107,105,105,111,111,8,  3,  15, 254,248,252,63, 7,
    1,  0,  127,127,99, 99, 99, 127,30, 28, 127,119,99, 99, 119,127,
    28, 48, 121,73, 73, 75, 127,127,0,  0,  127,127,3,  1,  1,  28,
    127,119,99, 99, 127,127,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  3,  3,  3,  3,  3,  1,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  24, 120,
    240,192,192,248,56, 8,  0,  16, 248,248,0,  0,  0,  0,  0,  0,
    240,248,24, 24, 248,240,0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    3,  3,  3,  1,  0,  0,  0,  2,  3,  3,  2,  2,  0,  3,  3,  0,
    1,  3,  3,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

#ifdef OLED_ENABLE
static void print_status_narrow(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("-----ALPHA-----"), false);
            break;
        case _UPPER:
            oled_write_P(PSTR("-----UPPER-----"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("-----LOWER-----"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("-----ADJST-----"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n\n"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
    current_wpm   = get_current_wpm();
    render_pet(0, 12);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        oled_clear();
        oled_write_raw_P(image, sizeof(image));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        // For some bizzare reason need to swap here
        if (get_highest_layer(layer_state) == _UPPER) {
            tap_code(clockwise ? KC_VOLD : KC_VOLU);
        } else {
            tap_code(clockwise ? KC_LEFT : KC_RIGHT);
        }
    } else if (index == 1) {
        if (get_highest_layer(layer_state) == _UPPER) {
            tap_code(clockwise ? KC_PGDN : KC_PGUP);
        } else {
            tap_code(clockwise ? KC_UP : KC_DOWN);
        }
    }
    return true;
}
#endif
