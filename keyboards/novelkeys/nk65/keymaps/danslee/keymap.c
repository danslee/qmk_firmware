// Copyright 2019 Yiancar
// SPDX-License-Identifier: GPL-2.0-or-later

// danslee variation
// CAPS -> lcontrol + tap for escape
// option and mac keys moved to default mac positions.
// Media volume and forward back controls on layer 1 at arrow keys
#include QMK_KEYBOARD_H

// ---- Custom RGB mode states ----
enum custom_rgb_mode {
    CRM_OFF,
    CRM_WHITE,
    CRM_RED,
    CRM_WHITE_REACTIVE,
};
static uint8_t current_rgb_mode = CRM_OFF;

// ---- Function to cycle lighting modes ----
void cycle_rgb_mode(void) {
    current_rgb_mode = (current_rgb_mode + 1) % 4;

    switch (current_rgb_mode) {
        case CRM_OFF:
            rgb_matrix_enable();
            rgb_matrix_sethsv_noeeprom(0, 0, 0);  // all LEDs off
            break;

        case CRM_WHITE:
            rgb_matrix_enable();
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(0, 0, 255);  // white
            break;

        case CRM_RED:
            rgb_matrix_enable();
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(0, 255, 255); // red
            break;

        case CRM_WHITE_REACTIVE:
            rgb_matrix_enable();
            rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
            // Base color white, reactive flashes blue
            rgb_matrix_sethsv_noeeprom(0, 0, 255);   // white base
            rgb_matrix_sethsv(170, 255, 255);        // blue reactive
            break;
    }
}

enum custom_keycodes {
    CRM_CYCLE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CRM_CYCLE:
            if (record->event.pressed) {
                cycle_rgb_mode();
            }
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi( /* Base */
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
 LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        MO(1), KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT_65_ansi( /* FN */
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_PWR,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, KC_EJCT,
        KC_CAPS, RM_TOGG, _______, _______, RM_SATD, RM_SATU, _______, _______, _______, _______, _______, _______,          _______, _______,
        KC_LSFT, _______, CRM_CYCLE, RM_HUED, RM_HUEU, _______, _______, RM_VALD, RM_VALU, RM_SPDD, RM_SPDU, KC_MUTE,          KC_VOLU, KC_MPLY,
        _______, _______, _______,                   _______,                            _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    )
};
