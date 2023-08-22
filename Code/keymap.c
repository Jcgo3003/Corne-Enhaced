#include QMK_KEYBOARD_H 
#include "jcgo.h"
#include "analog.h"
#include "math.h"

// -- Luna Animation vars --
bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _NUM,
  _ADJUST
};

// -- Macros vars -- 
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NUM,
  ADJUST,

  TAB, // CMD + Tab
};

// -- Tap Dance -- 
enum {
    TD_ALT, // alt | cmd
    TD_SEA, // cmd + spc | Keycaps
    TD_SAV, // cmd + s | cmd + +
    // TD_SAA,  // cmd + shift + s | cmd + - 
    TD_COP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_4x6(                            //     BASE
//|-----------------------------------------------------|                    |-----------------------------------------------------|
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                          KC_Y,    KC_U,    KC_I,     KC_O,    KC_P, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                          KC_H,    KC_J,    KC_K,     KC_L, KC_SCLN, KC_QUOT,
//---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,                          KC_N,    KC_M,    KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
//---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    KC_NO,KC_NO,KC_NO,  KC_LGUI,  LOWER,   KC_SPC,     KC_ENT,  RAISE,TD(TD_ALT), KC_MUTE, LCTL(KC_LEFT), LCTL(KC_RGHT) // Mute , Mission control left|right
//          Mouse scroll horizontal //|--------------------------|  |-----------------------------|// Volume - | +

                                            // Mouse Normal Speed | + shift min Speed 
  ),

  [_LOWER] = LAYOUT_split_4x6(                             //     LOWER
//|-----------------------------------------------------|                    |-----------------------------------------------------|
    KC_TAB,    KC_1,   KC_2,    KC_3,     KC_4,   KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_DEL, 
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ESC,                       KC_NUBS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, 
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+---- ----|
    KC_LCTL, LGUI(KC_UP),LGUI(KC_DOWN), KC_MPRV, KC_MPLY,KC_MNXT,              KC_GRV,SGUI(KC_NUBS),TAB,SGUI(KC_4),TG(ADJUST),KC_RSFT,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    KC_NO,KC_NO,KC_NO,  KC_LGUI, _______,  KC_SPC,     KC_ENT,  TG(3),  TD(TD_ALT), KC_MUTE, LAG(KC_LEFT), LAG(KC_RGHT) // Sleep, Tab nav left|right
//                 Brightness - | + //|--------------------------|  |-----------------------------|// Word scroll horizontal left | right
  ),                                                     

  [_RAISE] = LAYOUT_split_4x6(                             //     RAISE
//|-----------------------------------------------------|                    |-----------------------------------------------------|
    KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,TD(TD_COP),  KC_9,    KC_0, LGUI(KC_BSPC), 
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_ESC,                      KC_BTN3, KC_BTN1, KC_BTN2,LGUI(KC_LBRC),TD(TD_SAV),TD(TD_SEA),
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LCTL, KC_HOME,LCTL(KC_DOWN),LCTL(KC_UP),  KC_END,LGUI(KC_A),      LGUI(KC_LSFT), LGUI(KC_B),LGUI(KC_COMM),LGUI(KC_DOT),LGUI(KC_SLSH), KC_RSFT,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    KC_NO,KC_NO,KC_NO,   KC_LGUI, TG(3),   KC_SPC,    KC_ENT, _______, TD(TD_ALT), KC_SLEP, LCTL(KC_LEFT), LCTL(KC_RGHT) // Mission control left|right
//            Mouse scroll vertical //|--------------------------|  |-----------------------------|// history Redo | undo 
  ),                                           // Mouse Fast Speed | + shift Top Speed

  [_NUM] = LAYOUT_split_4x6(                               //     NUM
//|-----------------------------------------------------|                    |-----------------------------------------------------|
    KC_TAB,LGUI(KC_SLSH),KC_DELETE, KC_INS, KC_PGUP, KC_HOME,                      KC_PEQL,    KC_7,     KC_8,    KC_9,   KC_0,  KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_ESC,                      KC_PCMM,    KC_4,    KC_5,   KC_6, KC_PPLS, KC_PMNS,  
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LCTL,LGUI(KC_A),LGUI(KC_I), LGUI(KC_DOT), KC_PGDN, KC_END,              KC_PDOT,    KC_1,    KC_2,    KC_3, KC_PSLS, KC_PAST,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    KC_NO,KC_NO,KC_NO,  KC_LGUI,  TG(3),  KC_SPC,      KC_ENT, TG(3),  TD(TD_ALT), KC_NO, LGUI(KC_LEFT), LGUI(KC_RGHT) // nothing , Web History nav left|right
//                             Zoom in|out //|------- -----------|  |-----------------------------| // Word Scroll Vertical up / down
  ),
  [_ADJUST] = LAYOUT_split_4x6(                            //     ADJUST
//|-----------------------------------------------------|                    |-----------------------------------------------------|
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT,  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_ESC,                     QK_BOOT,RGB_RMOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, 
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LCTL,  CG_NORM, SGUI(KC_3), CG_SWAP,  KC_SLEP, KC_TAB,                   RGB_TOG, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, 
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    KC_NO,KC_NO,KC_NO,  KC_LGUI, TG(ADJUST),KC_SPC,   KC_ENT,TG(ADJUST),TD(TD_ALT), KC_NO, LCTL(KC_LEFT), LCTL(KC_RGHT) // nothing , ctrl + left | right 
// Mouse scroll horizontal //|--------------------------|  |-----------------------------| // vol down | up
  )
};

// -- Tap Dance definition --
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for ALT, twice for CMD
    [TD_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_RGUI),               // alt/cmd   
    [TD_SEA] = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_SPC), KC_CAPS),          // find/ Caps   
    [TD_SAV] = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_SCLN), SGUI(KC_SCLN)),   // cmd+s/cmd+shift+s
    // [TD_SAA] = ACTION_TAP_DANCE_DOUBLE(SGUI(KC_SCLN), LGUI(KC_QUOT)),   // To DELETE
    [TD_COP] = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_I), KC_8)               // cmd+c/ 8
    // Close/reopen
};

// -- Oled Stuff --
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// -- Luna Animation --
// settings
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

// advanced settings
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 96 // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

// timers
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

// current frame
uint8_t current_frame = 0;

// status variables
int current_wpm = 0;
led_t isBarking;

// logic
static void render_luna(int LUNA_X, int LUNA_Y) {
    // Sit
    static const char PROGMEM sit[2][ANIM_SIZE] = {
        // 'sit1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        // 'sit2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    // Walk
    static const char PROGMEM walk[2][ANIM_SIZE] = {
        // 'walk1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80,
            0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03,
            0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'walk2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e,
            0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // Run
    static const char PROGMEM run[2][ANIM_SIZE] = {
        // 'run1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01,
            0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'run2', 32x22px
        {
            0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
            0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37,
            0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // Bark
    static const char PROGMEM bark[2][ANIM_SIZE] = {
        // 'bark1', 32x22px
        {
            0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
            0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
            0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'bark2', 32x22px
        {
            0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
            0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
            0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // Sneak
    static const char PROGMEM sneak[2][ANIM_SIZE] = {
        // 'sneak1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04,
            0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06,
            0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
        },

        // 'sneak2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04,
            0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04,
            0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // animation
    void animation_phase(void) {
        // jump
        if (isJumping || !showedJump) {
            // clear
            oled_set_cursor(LUNA_X,LUNA_Y +2);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X,LUNA_Y -1);
            showedJump = true;
        } else {
            // clear
            oled_set_cursor(LUNA_X,LUNA_Y -1);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X,LUNA_Y);
        }

        // switch frame
        current_frame = (current_frame + 1) % 2;
        
        // Draw current status
        if(isBarking.caps_lock) {  // Caps lock on/off
            oled_write_raw_P(bark[abs(1 - current_frame)], ANIM_SIZE);

        } else if(isSneaking) {
            oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);

        } else if(current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);

        } else if(current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
        }
    }

    // animation timer
    if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
    }
    // this fixes the screen on and off bug
    // if (current_wpm > 0) {
    //     oled_on();
    //     anim_sleep = timer_read32();
    // } else if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
    //     oled_off();
    // }
}

// -- Corne Logo -- 
void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("     "), false);
}

// -- Title --
void render_title_r(void) {
    oled_write_P(PSTR("Jbst "), false);// <- Add any 5 character word for the right side oled
}

void render_title_l(void) {
    oled_write_P(PSTR(" Jbst"), false); // <- Add Any 5 character word for the right side oled
}

// -- Spacer --
void render_space(void) {
    oled_write_P(PSTR("     "), false); 
}

// -- Status Icons --
void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

// -- Modifier Status --
void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

// -- Layer status --
void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM num_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    if(layer_state_is(_NUM)) {
        oled_write_P(num_layer, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else if(layer_state_is(_ADJUST)){
        oled_write_P(adjust_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

    // Main OLED display
    void render_status_main(void) { 
    render_logo();
    render_title_l();
    render_space();
    render_space();
    render_layer_state();
    render_luna(0,13);
    }

    // Secondary OLED display 
    void render_status_secondary(void) { 
        render_logo();
        render_title_r();
        render_space();
        render_space();
        render_layer_state();
        render_space();
        render_space();
        render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());    
    }

    // Stating the screen
    bool oled_task_user(void) {  
        // Luna Variables
        current_wpm = get_current_wpm();  
        isBarking = host_keyboard_led_state(); // Caps Lock

        #ifndef SPLIT_KEYBOARD
            else { oled_on(); }
        #endif

        if (is_keyboard_master()) {            // Render the Main/Secondary display
            render_status_main();  
        } else {
            render_status_secondary();
        }
        return false;
    }
#endif

// -- Macros --
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return true;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        register_code(KC_ACL2);
      } else {
        layer_off(_RAISE);
        unregister_code(KC_ACL2);
      }
      return false;

    case NUM:
        if (record->event.pressed) {
          layer_on(_NUM);
        } else {
          layer_off(_NUM);
        }
        return false;

    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;

    case KC_LGUI:
          if (record->event.pressed) {
              isSneaking = true;
          } else {
              isSneaking = false;
          }
          break;
          return false;

    case KC_SPC:
          if (record->event.pressed) {
              isJumping = true;
              showedJump = false;
          } else {
              isJumping = false;
          }
          break;
          return false; 


    case TAB:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB)); 
            isJumping = true;
        } else {
            isJumping = false;
            clear_keyboard();
        }
        break;
        return true;

      break;
    }
  return true;
}

// -- Encoder stuff --
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder Mouse Scroll*/
    if(IS_LAYER_ON(_NUM)){         // Zoom in/out
            if (clockwise) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_QUOT) SS_UP(X_LGUI));
            } else { 
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_RBRC) SS_UP(X_LGUI)); 
            }
    }if(IS_LAYER_ON(_RAISE)){      // Scroll Left/Right 
            if (clockwise) {
                tap_code(KC_WH_R);
            } else {
                tap_code(KC_WH_L);
            }
    }else if(IS_LAYER_ON(_LOWER)){ // Brightness -/+
            if(clockwise) {         
                tap_code(KC_BRID);
            } else {
                tap_code(KC_BRIU);
            }
    }else{
        if (clockwise) {            // Scroll Down/Up
                SEND_STRING(SS_DOWN(X_ACL2) SS_TAP(X_WH_D)); 
                clear_keyboard();

                if(get_mods() & MOD_MASK_CTRL){
                    tap_code(KC_WH_D); // Scroll Down/Up slower
                }
            } else {
                SEND_STRING(SS_DOWN(X_ACL2) SS_TAP(X_WH_U));
                clear_keyboard();

                if(get_mods() & MOD_MASK_CTRL){
                    tap_code(KC_WH_U); // Scroll Down/Up slower
                }
            }

        }
    }else if (index == 1) { /* Second encoder Volumen/Brightness/Words encoder*/
    if(IS_LAYER_ON(_NUM)){         // Word Scrolling Vertical
            if (clockwise) {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_DOWN) SS_UP(X_LALT)); 
                } else {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_UP) SS_UP(X_LALT));
                }
    }else if(IS_LAYER_ON(_RAISE)){ // History Scrolling
            if (clockwise) {
                SEND_STRING(SS_DOWN(X_LSFT) SS_LGUI("/")); // CMD + Shift + Z
            } else {
                SEND_STRING(SS_LGUI("/")); // CMD + Z
            }
            clear_keyboard();
    }else if(IS_LAYER_ON(_LOWER)){ // Word Scrolling Horizontal
            if (clockwise) {    
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT)); 
            } else {
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
            }    
    }else{
            if(clockwise) {         // Volumen 
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }            
        }
  }
  return false;
}

// -- Joystick stuff -- 
// Set Parameters
#define ONES(x) (fmax(fmin(x, 1.0), -1.0))
#define SIGN(x) ((x > 0) - (x < 0))
const pin_t xPin = B4;
const pin_t yPin = B5;

uint16_t x_scale = 128;
uint16_t y_scale = 128;
uint16_t x_dead =   24;
uint16_t y_dead =   24;
int16_t xcen, ycen;

float minCursorSpeed = 0.05;
float norCursorSpeed = 0.1;
float fastCursorSpeed = 0.4;
float maxCursorSpeed = 0.9;

int8_t xPolarity = -1;
int8_t yPolarity = -1;

uint8_t cursorTimeout = 45;
uint16_t lastCursor = 0;

bool pointing_device_task(void) {
    if (timer_elapsed(lastCursor) < cursorTimeout) return false;
    lastCursor = timer_read();

    report_mouse_t currentReport = pointing_device_get_report();
    int16_t x = analogReadPin(xPin);
    int16_t y = analogReadPin(yPin);
    int16_t xd = x-xcen;
    int16_t yd = y-ycen;
    if ( abs(xd) > x_dead || abs(yd) > y_dead ) {
        float xperc = ONES( (float)xd / x_scale);
        float yperc = ONES( (float)yd / y_scale);
        int8_t xmove = (int8_t)(xperc * 127.0);
        int8_t ymove = (int8_t)(yperc * 127.0);

        if(IS_LAYER_ON(_RAISE)) {
            currentReport.x = xPolarity * xmove * fastCursorSpeed;
            currentReport.y = yPolarity * ymove * fastCursorSpeed;
            
            if(get_mods() & MOD_MASK_SHIFT){
                currentReport.x = xPolarity * xmove * maxCursorSpeed;
                currentReport.y = yPolarity * ymove * maxCursorSpeed;
                }
        }else if(get_mods() & MOD_MASK_SHIFT){
            currentReport.x = xPolarity * xmove * minCursorSpeed;
            currentReport.y = yPolarity * ymove * minCursorSpeed;
        }else{
            currentReport.x = xPolarity * xmove * norCursorSpeed;
            currentReport.y = yPolarity * ymove * norCursorSpeed;
        }

    }

    pointing_device_set_report(currentReport);
    pointing_device_send();
    return true;
}

void keyboard_post_init_user(void) {
    xcen = analogReadPin(xPin);
    ycen = analogReadPin(yPin);
}
