/*
This is the c configuration file for the keymap

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

#pragma once

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
//#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#define OLED_TIMEOUT 200000 // OLEDの表示時間を3分に設定する
#define TAP_CODE_DELAY 5

// ホールドキーのタイミング設定（ミリ秒）
#define TAPPING_TERM 110 // 110msに設定

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE // オートマウスを有効にする
#define AUTO_MOUSE_DEFAULT_LAYER 2 // オートマウスのデフォルトレイヤーを指定する
#define AUTO_MOUSE_TIME 800 // オートマウスレイヤーが切り替わるまでの時間(ミリ秒)
#define COMBO_ONLY_FROM_LAYER 0 // コンボをレイヤー0からのみ有効にする

#define DYNAMIC_KEYMAP_LAYER_COUNT 7 // レイヤー数を指定する
#define SPLIT_LED_STATE_ENABLE       // CapsLockなどのLED点灯状態をサブ側に伝達