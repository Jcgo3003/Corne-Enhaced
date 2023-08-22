/* Copyright 2022 Jcgo3003

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

// Hand Configuration
#define MASTER_LEFT
// #define MASTER_RIGHT

#define USE_SERIAL_PD2

// -- Encoders --
#define ENCODERS_PAD_A { B2 } 
#define ENCODERS_PAD_B { B6 } 
#define ENCODER_RESOLUTIONS { 2 }

// -- Scroll Config --
#define MK_UNMOD_SPEED
#define MK_2_SPEED
#define MK_MOMENTARY_ACCEL

#define MK_W_OFFSET_UNMOD 2     
#define MK_W_INTERVAL_UNMOD 40   
#define MK_W_OFFSET_2 15 
#define MK_W_INTERVAL_2 40 

// #define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#define RETRO_TAPPING

// -- Oled --
#ifdef OLED_ENABLE
#   define SPLIT_LAYER_STATE_ENABLE
#   define SPLIT_LED_STATE_ENABLE
#   define SPLIT_MODS_ENABLE
#   define SPLIT_OLED_ENABLE
#   define OLED_FONT_H "keyboards/crkbd/keymaps/soundmonster/glcdfont.c"
#   define OLED_TIMEOUT 30000
#endif

// -- Id's -- 
// #undef PRODUCT
// #undef VENDOR_ID
// #undef PRODUCT_ID
// #undef DEVICE_VER
// #undef MANUFACTURER
// #define PRODUCT         Corne_JCGO
// #define VENDOR_ID       0x3141 // pi
// #define PRODUCT_ID      0x4242 // 42 keys
// #define DEVICE_VER      0x0007 // v3.1
// #define MANUFACTURER    Corne

// Save space
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
//#define NO_ACTION_TAPPING
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION