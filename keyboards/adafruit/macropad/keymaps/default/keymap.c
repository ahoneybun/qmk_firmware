/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

enum layers{
  MAIN,
  FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [MAIN] = LAYOUT(
                    LT(1,KC_MUTE),
      KC_MPRV, KC_MPLY, KC_MNXT,
      KC_7,   KC_8, KC_9,
      KC_4,   KC_5, KC_6,
      MT(MOD_LCTL | MOD_LGUI, KC_1),   KC_2, MT(MOD_LSFT | MOD_LGUI, KC_3)
  ),
  [FUNC] = LAYOUT(
                        _______,
      CK_TOGG, AU_TOGG, MU_TOGG,
      _______, MU_NEXT, _______,
      _______, _______, _______,
      _______, _______, _______
  ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [MAIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [FUNC] = { ENCODER_CCW_CW(_______, _______) },
};
#endif


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case MAIN:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case FUNC:
            oled_write_P(PSTR("Functions"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    return false;
}

#endif
