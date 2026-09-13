#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ 1 │ 2 │ 3 │ ─── [Encoder Click: KC_MUTE]
     * ├───┼───┼───┤
     * │ 4 │ 5 │ 6 │
     * └───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_MPRV, KC_MNXT, KC_MPLY,
        KC_1,    KC_2,    KC_3
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
void matrix_init_user(void) {
    gpio_set_pin_input_high(GP3);
}

void matrix_scan_user(void) {
    static bool stable_state = false;
    static bool raw_state = false;
    static uint16_t change_time = 0;

    bool pressed = !gpio_read_pin(GP3);

    if (pressed != raw_state) {
        raw_state = pressed;
        change_time = timer_read();
    }

    if (pressed != stable_state && timer_elapsed(change_time) > 20) {
        stable_state = pressed;

        if (stable_state) {
            tap_code(KC_MUTE);
        }
    }
}
