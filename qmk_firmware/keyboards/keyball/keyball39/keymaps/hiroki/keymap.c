/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

static const char LFSTR_ON[] PROGMEM = "\xB2\xB3";
static const char LFSTR_OFF[] PROGMEM = "\xB4\xB5";

// 文字入力中のトラックボール無効化用の変数
static uint32_t last_key_time = 0;
#define TRACKBALL_DISABLE_TIME 200 // キー入力後200ms間トラックボールを無効にする

//　特定のレイヤーでスクロールモードにする
layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 4
    keyball_set_scroll_mode(get_highest_layer(state) == 4);
    return state;
}

// OLEDの表示を変更する
#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"
void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// オートマウスを有効にする
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // 文字キーが押された場合、タイムスタンプを記録
    if (record->event.pressed && 
        ((keycode >= KC_A && keycode <= KC_Z) ||
         (keycode >= KC_1 && keycode <= KC_0) ||
         keycode == KC_SPC || keycode == KC_ENT || keycode == KC_TAB ||
         keycode == KC_BSPC || keycode == KC_DEL || keycode == KC_DOT ||
         keycode == KC_COMM || keycode == KC_SCLN || keycode == KC_QUOT ||
         keycode == KC_SLSH || keycode == KC_MINS || keycode == KC_EQL)) {
        last_key_time = timer_read32();
    }

    switch (keycode) {
        // case KC_BTN1:
        //     if (record->event.pressed) {
        //         // マウス左クリックが押された時にレイヤー6を有効にする
        //         layer_on(6);
        //     } else {
        //         // マウス左クリックが離された時にレイヤー6を無効にする
        //         layer_off(6);
        //     }
            break;
        case SCRL_MO:
            if (record->event.pressed) {
                set_auto_mouse_enable(false); // 押している間はオートマウス無効
            } else {
                set_auto_mouse_enable(true);  // 離したら有効
            }
            break;
        case SSNP_HOR_MO:
            if (record->event.pressed) {
                // キーを押した時：水平モードに切り替え
                keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_HORIZONTAL);
            } else {
                // キーを離した時：垂直モードに戻す
                keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
            }
            return false; // process_record_kbでの処理をスキップ
            break;
        default:
            break;
    }
    return true;
}

// 文字入力直後はトラックボールの動きを無効にする
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    uint32_t current_time = timer_read32();
    
    // 最後の文字キー入力から50ms以内の場合、カーソル移動を無効にする
    if (TIMER_DIFF_32(current_time, last_key_time) < TRACKBALL_DISABLE_TIME) {
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    
    return mouse_report;
}
#endif

// コンボの設定
#ifdef COMBO_ENABLE
const uint16_t PROGMEM ds_combo[]     = {KC_D, KC_S, COMBO_END}; // D,Sコンボ
const uint16_t PROGMEM cv_combo[]     = {KC_C, KC_V, COMBO_END}; // C,Vコンボ
const uint16_t PROGMEM mcomm_combo[]  = {KC_M, KC_COMM, COMBO_END}; // M,コンマコンボ
const uint16_t PROGMEM qwer_combo[]   = {KC_Q, KC_W, KC_E, KC_R, COMBO_END}; // Q,W,E,Rコンボ
const uint16_t PROGMEM fd_combo[]     = {KC_F, KC_D, COMBO_END}; // F,Dコンボ
const uint16_t PROGMEM fs_combo[]     = {KC_F, KC_S, COMBO_END}; // F,Sコンボ
const uint16_t PROGMEM kl_combo[]     = {KC_K, KC_L, COMBO_END}; // K,Lコンボ
const uint16_t PROGMEM kj_combo[]     = {KC_K, KC_J, COMBO_END}; // K,Jコンボ
const uint16_t PROGMEM ui_combo[]     = {KC_U, KC_I, COMBO_END}; // U,Iコンボ

combo_t key_combos[] = {
COMBO(fd_combo, KC_BTN1)      // F,Dコンボで左クリック
,COMBO(fs_combo, KC_BTN2)     // F,Sコンボで右クリック
,COMBO(ds_combo, KC_LNG2)     // D,Sコンボで言語2を選択
,COMBO(kl_combo, KC_LNG1)     // K,Lコンボで言語1を選択
,COMBO(cv_combo, KC_LSFT)     // C,Vコンボで左シフト
,COMBO(mcomm_combo, KC_RSFT)  // M,コンマコンボで右シフト
,COMBO(kj_combo, KC_Z)        // K,JコンボでZキー
,COMBO(ui_combo, KC_Z)        // U,IコンボでZキー
,COMBO(qwer_combo, TG(3))     // Q,W,E,Rコンボでレイヤー3に切替
};
#endif