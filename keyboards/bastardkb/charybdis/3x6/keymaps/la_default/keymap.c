/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
    LAYER_GAME,
    LAYER_GAME_STATIC,
};


enum custom_keycodes {
    LAYER_SWITCH = SAFE_RANGE,
};

#define KC_COMBO_1 KC_U
#define KC_COMBO_2 KC_I
#define KC_COMBO_3 KC_P

#define KC_COMBO_2_3 KC_O

bool combo_keys_pressed[4] = { false, false, false, false };
bool is_game_layer_on = false;
bool is_game_layer_on_2 = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COMBO_1:
            combo_keys_pressed[0] = record->event.pressed;
            break;
        case KC_COMBO_2:
            combo_keys_pressed[1] = record->event.pressed;
            break;
        case KC_COMBO_2_3:
            combo_keys_pressed[2] = record->event.pressed;
            break;
        case KC_COMBO_3:
            combo_keys_pressed[3] = record->event.pressed;
            break;
        default:
            break;
    }

    bool all_keys_pressed = combo_keys_pressed[0] && combo_keys_pressed[1] && combo_keys_pressed[3];
    bool all_keys_pressed_2 = combo_keys_pressed[0] && combo_keys_pressed[1] && combo_keys_pressed[2];
    
    if (all_keys_pressed && record->event.pressed) {
      // Toggle the layer state
      if (is_game_layer_on) {
	layer_off(LAYER_GAME);
	is_game_layer_on = false;
      } else {
	layer_on(LAYER_GAME);
	is_game_layer_on = true;
      }
      return false; // Custom processing for this keycode, quit further processing
    }

    if (all_keys_pressed_2 && record->event.pressed) {
      // Toggle the layer state
      if (is_game_layer_on_2) {
	layer_off(LAYER_GAME_STATIC);
	is_game_layer_on_2 = false;
      } else {
	layer_on(LAYER_GAME_STATIC);
	is_game_layer_on_2 = true;
      }
      return false; // Custom processing for this keycode, quit further processing
    }

    
    return true; // Process all other keycodes normally
}


#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)


// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                     \
    KC_P, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_Q, \
	KC_SCLN,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,          KC_K,          KC_L,    KC_SCLN, KC_A, \
	KC_SLSH,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,          KC_COMM,       KC_DOT,  KC_SLSH, KC_Z, \
                      ESC_MED, SPC_NAV, TAB_FUN, ENT_SYM, BSP_NUM

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_RALT
#define ______________HOME_ROW_GACS_R______________ KC_RALT, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX


#define LAYOUT_LAYER_GAME                                                                     \
    KC_P, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_COMBO_1,    KC_COMBO_2,    KC_O,    KC_COMBO_3, KC_Q, \
	KC_SCLN,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_A,	\
	KC_SLSH, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_Z, \
	 LALT_T(KC_ESC), LSFT_T(KC_SPC), LCTL_T(KC_TAB), ENT_SYM, BSP_NUM

#define LAYOUT_LAYER_GAME_STATIC                                                                     \
    KC_P, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_COMBO_1,    KC_COMBO_2,    KC_O,    KC_COMBO_3, KC_Q, \
	KC_SCLN, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_A, \
	KC_SLSH, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_Z, \
	 KC_ESC, KC_SPC, KC_TAB, ENT_SYM, BSP_NUM


/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYOUT_LAYER_FUNCTION                                                                 \
    _______________DEAD_HALF_ROW_______________, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12, XXXXXXX,  \
    ______________HOME_ROW_GACS_L______________, KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11, XXXXXXX, \
    _______________DEAD_HALF_ROW_______________, KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10, XXXXXXX, \
                      XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
#define LAYOUT_LAYER_MEDIA                                                                    \
     XXXXXXX, XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX,  XXXXXXX, \
     XXXXXXX, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,  XXXXXXX, \
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT, QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                  \
    XXXXXXX, DRGSCRL, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, DRAGSCROLL_MODE_TOGGLE, DRGSCRL, DRGSCRL, XXXXXXX, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
    XXXXXXX, _______, DRGSCRL, _______, EE_CLR,  QK_BOOT, QK_BOOT, EE_CLR,  SNIPING, DRGSCRL, _______, XXXXXXX, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
  * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
#define LAYOUT_LAYER_NAVIGATION                                                               \
    _______________DEAD_HALF_ROW_______________, _______________DEAD_HALF_ROW_______________, \
    ______________HOME_ROW_GACS_L______________, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,  \
    _______________DEAD_HALF_ROW_______________,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_DEL,  XXXXXXX, \
                      XXXXXXX, _______, XXXXXXX,  KC_ENT, KC_BSPC

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL                                                                  \
     XXXXXXX, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, _______________DEAD_HALF_ROW_______________, \
     XXXXXXX, KC_QUOT,    KC_4,    KC_5,    KC_6,  KC_EQL, ______________HOME_ROW_GACS_R______________, \
      XXXXXXX, KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS, _______________DEAD_HALF_ROW_______________, \
                       KC_DOT,    KC_0, KC_MINS, XXXXXXX, _______

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                  \
     XXXXXXX, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, _______________DEAD_HALF_ROW_______________, \
     XXXXXXX, LSFT(KC_QUOT),  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ______________HOME_ROW_GACS_R______________, \
     XXXXXXX, KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, _______________DEAD_HALF_ROW_______________, \
                      KC_LPRN, KC_RPRN, KC_UNDS, _______, XXXXXXX

/** \brief QWERTY layout (3 rows, 10 columns). */



/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 */
#define _HOME_ROW_MOD_GACS(                                            \
    E0,L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,E1,	       \
    E2,L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,	       \
    ...)                                                               \
    E0, L00,         L01,         L02,         L03,         L04,	       \
	R05,         R06,         R07,         R08,         R09, E1,	\
	E2, LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),RALT_T(L14), \
	       RALT_T(R15),  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define _POINTER_MOD(                                                  \
    E0, L00, L01, L02, L03, L04, R05, R06, R07, R08, R09, E1,	       \
    E2, L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,E3,		\
    E4, L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,E5,		\
    ...)                                                               \
    E0, L00,         L01,         L02,         L03,         L04,       \
        R05,         R06,         R07,         R08,         R09, E1,	\
	E2, L10,         L11,         L12,         L13,         L14,	\
	R15,         R16,         R17,         R18,         R19, E3,	\
	E4, _L_PTR(L20),        L21,  _L_PTR(L22),         L23,         L24, \
	R25,         R26,         R27,         R28,  _L_PTR(R29), E5,	\
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)


#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_GAME] = LAYOUT_wrapper(LAYOUT_LAYER_GAME),
  [LAYER_GAME_STATIC] = LAYOUT_wrapper(LAYOUT_LAYER_GAME_STATIC),
};
// clang-format on
