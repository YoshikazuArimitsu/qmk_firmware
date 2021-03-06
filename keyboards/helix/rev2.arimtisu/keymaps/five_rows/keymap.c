#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif
#ifdef CONSOLE_ENABLE
#include <print.h>
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number
{
  _QWERTY = 0,
  //_COLEMAK,
  _ARIEUCALYN,
  //_EUCALYN,
  _KEYPAD,
  _AUX,
  _KAUX,
  _LOWER,
  _RAISE,
  _PADFUNC,
  _ADJUST,
};

enum custom_keycodes
{
  QWERTY = SAFE_RANGE,
  //COLEMAK,
  ARIEUCALYN,
  //EUCALYN,
  KEYPAD,
  EISU,
  KANA,
  ZERO2,
  RGBRST
};

enum macro_keycodes
{
  KC_SAMPLEMACRO,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  BS  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   `  |   '  |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Lower| Caps |  Alt |  GUI | Space|  BS  | Enter| Space| GUI  | Alt  | Menu |Lower |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_QWERTY] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_RCTL,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_GRV, KC_QUOT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        MO(_LOWER), MO(_LOWER), KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, LT(_RAISE, KC_BSPC),
        LT(_RAISE, KC_ENT), KC_SPC, KC_RGUI, KC_RALT, KC_APP, MO(_LOWER), MO(_LOWER)),

    /* AriEucalyn (http://eucalyn.hatenadiary.jp/entry/about-eucalyn-layout)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   ,  |   .  |   ;  |             |   M  |   R  |   D  |   Y  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   I  |   U  |             |   G  |   T  |   K  |   S  |   N  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   F  |   `  |   '  |   B  |   H  |   J  |   L  |   /  |  =   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Lower | Raise|  GUI |  Alt |  GUI | Space|  BS  | Enter| Space|   (  |   [  |   {  |Raise |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_ARIEUCALYN] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_COMM, KC_DOT, KC_SCLN, KC_M, KC_R, KC_D, KC_Y, KC_P, KC_BSLS,
        KC_LCTL, KC_A, KC_O, KC_E, KC_I, KC_U, KC_G, KC_T, KC_K, KC_S, KC_N, KC_MINS,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_F, KC_GRV, KC_QUOT, KC_B, KC_H, KC_J, KC_L, KC_SLSH, KC_EQL,
        MO(_LOWER), MO(_RAISE), KC_APP, KC_LALT, KC_LGUI, KC_SPC, KC_BSPC, KC_ENT, KC_SPC, LSFT(KC_9), KC_LBRC, LSFT(KC_LBRC), MO(_RAISE), MO(_LOWER)),

    /* Keypad
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   /  |   *  | Del  |  F1  |  F6  |             |  F1  |  F6  | Del  | Tab  |   /  |   *  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   7  |   8  |   9  | BS   |  F2  |  F7  |             |  F2  |  F7  | BS   |   7  |   8  |   9  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   4  |   5  |   6  |  -   |  F3  |  F8  |             |  F3  |  F8  |  -   |   4  |   5  |   6  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   1  |   2  |   3  |  +   |  F4  |  F9  |  F11 |  F11 |  F4  |  F9  |  +   |   1  |   2  |   3  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   0  |   ,  |   .  | Enter|  F5  |  F10 |  F12 |  F12 |  F5  |  F10 | Enter|   0  |  ,   |   .  |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_KEYPAD] = LAYOUT(
        KC_TAB, KC_PSLS, KC_PAST, KC_DEL, KC_F1, KC_F6, KC_F1, KC_F6, KC_DEL, KC_TAB, KC_PSLS, KC_PAST,
        KC_KP_7, KC_KP_8, KC_KP_9, KC_BSPC, KC_F2, KC_F7, KC_F2, KC_F7, KC_BSPC, KC_KP_7, KC_KP_8, KC_KP_9,
        KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS, KC_F3, KC_F8, KC_F3, KC_F8, KC_PMNS, KC_KP_4, KC_KP_5, KC_KP_6,
        KC_KP_1, KC_KP_2, KC_KP_3, KC_PPLS, KC_F4, KC_F9, KC_F11, KC_F11, KC_F4, KC_F9, KC_PPLS, KC_KP_1, KC_KP_2, KC_KP_3,
        KC_KP_0, KC_COMM, KC_PDOT, KC_PENT, KC_F5, KC_F10, LT(_PADFUNC, KC_F12),
        LT(_PADFUNC, KC_F12), KC_F5, KC_F10, KC_PENT, KC_KP_0, KC_COMM, KC_PDOT),

    /*  AUX modifier key layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  00  |      |      |      |      |      |      |      |      |      |      |  00  |      |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_KAUX] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, ZERO2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ZERO2, _______),

    /*  Keypad function layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      | Pause| ScrLk| PtrSc|             | PtrSc| ScrLk| Pause|      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      | Home |  Up  | PgUp |             | PgUp |  Up  | Home |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |Delete|Insert| Left | Down | Right|             | Left | Down | Right|Insert|Delete|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      | End  |      | PgDn |Adjust|Adjust| PgDn |      | End  |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_PADFUNC] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS, KC_SLCK, KC_PSCR, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_UP, KC_PGUP, KC_PGUP, KC_UP, KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_DEL, KC_INS, KC_LEFT, KC_DOWN, KC_RGHT, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS, KC_DEL, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_END, XXXXXXX, KC_PGDN, MO(_ADJUST),
        MO(_ADJUST), KC_PGDN, XXXXXXX, KC_END, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |Pause | ScrLk| Ins  |      |             |      | Ins  | ScrLk|Pause |      | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | PgUp |      | Up   |Delete| Home |             | Home |Delete| Up   |      | PgUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | PgDn | Left | Down | Right| End  |Adjust|Adjust| End  | Left | Down | Right| PgDn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | PrtSc|      |      |      |      |      |      |      |      | PrtSc|      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_LOWER] = LAYOUT(
        XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        XXXXXXX, XXXXXXX, KC_PAUS, KC_SLCK, KC_INS, XXXXXXX, XXXXXXX, KC_INS, KC_SLCK, KC_PAUS, XXXXXXX, KC_F12,
        _______, KC_HOME, XXXXXXX, KC_UP, KC_DEL, KC_PGUP, KC_PGUP, KC_DEL, KC_UP, XXXXXXX, KC_HOME, _______,
        _______, KC_END, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, _______,
        _______, _______, KC_PSCR, _______, _______, _______, MO(_ADJUST),
        MO(_ADJUST), _______, _______, _______, KC_PSCR, _______, _______),

    /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  _   |  -   |             |  =   |  +   |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  {   |  [   |             |  ]   |  }   |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      | EISU | EISU | KANA | KANA | Next | Vol- | Vol+ | Play |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |  )   |  ]   |  }   |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_RAISE] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LSFT(KC_MINS), KC_MINS, KC_EQL, LSFT(KC_EQL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, LSFT(KC_LBRC), KC_LBRC, KC_RBRC, LSFT(KC_RBRC), XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EISU, EISU, KANA, KANA, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______,
        MO(_ADJUST), MO(_ADJUST), KC_CAPS, _______, _______, XXXXXXX, _______,
        _______, XXXXXXX, LSFT(KC_0), KC_RBRC, LSFT(KC_RBRC), MO(_ADJUST), MO(_ADJUST)),

    /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |Keypad|AriEuc|AriEuc|Qwerty|Qwerty|             |Qwerty|Qwerty|AriEuc|AriEuc|Keypad|      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|RGB ON|Aud on| Win  |             | Win  |Aud on|RGB ON|RGBRST|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| Mac  |             | Mac  |Audoff|RGB md| VAL+ | SAT+ | HUE+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |      |      |      |      |      |      |      |      | VAL- | SAT- | HUE- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_ADJUST] = LAYOUT(
        XXXXXXX, KEYPAD, ARIEUCALYN, ARIEUCALYN, QWERTY, QWERTY, QWERTY, QWERTY, ARIEUCALYN, ARIEUCALYN, KEYPAD, XXXXXXX,
        XXXXXXX, RESET, RGBRST, RGB_TOG, AU_ON, AG_SWAP, AG_SWAP, AU_ON, RGB_TOG, RGBRST, XXXXXXX, XXXXXXX,
        RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, AU_OFF, AG_NORM, AG_NORM, AU_OFF, RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI,
        RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD,
        _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______),

    /*  AUX modifier key layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |  BS  | Enter|      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_AUX] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_BSPC, LT(_RAISE, KC_ENT),
        _______, _______, _______, _______, _______, _______, _______)};

#else
#error "undefined keymaps"
#endif

#ifdef AUDIO_ENABLE

float tone_qwerty[][2] = SONG(QWERTY_SOUND);
float tone_dvorak[][2] = SONG(DVORAK_SOUND);
float tone_colemak[][2] = SONG(COLEMAK_SOUND);
float tone_plover[][2] = SONG(PLOVER_SOUND);
float tone_plover_gb[][2] = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);
#endif

static int current_default_layer;

uint32_t default_layer_state_set_kb(uint32_t state)
{
  // 1<<_QWERTY  - 1 == 1 - 1 == _QWERTY (=0)
  // 1<<_COLEMAK - 1 == 2 - 1 == _COLEMAK (=1)
  current_default_layer = state - 1;
  // 1<<_ARIEUCALYN  - 2 == 4 - 2 == _ARIEUCALYN (=2)
  if (current_default_layer == 3)
    current_default_layer -= 1;
  // 1<<_EUCALYN - 5 == 8 - 5 == _EUCALYN (=3)
  if (current_default_layer == 7)
    current_default_layer -= 4;
  // 1<<_KEYPAD  - 12 == 16 - 12 == _KEYPAD (=4)
  if (current_default_layer == 15)
    current_default_layer -= 11;
  return state;
}

void update_base_layer(int base)
{
  if (current_default_layer != base)
  {
    eeconfig_update_default_layer(1UL << base);
    default_layer_set(1UL << base);
    layer_off(_AUX);
    layer_off(_KAUX);
  }
  else
  {
    if (base < _KEYPAD)
      layer_invert(_AUX);
    else
      layer_invert(_KAUX);
  }
}

struct keybuf
{
  char col, row;
  char frame;
};
struct keybuf keybufs[256];
unsigned char keybuf_begin, keybuf_end;

unsigned char modifier_status = 0;
#define MOD_SHIFT 0x01
#define MOD_CTRL 0x02
#define MOD_ALT 0x04
#define MOD_APP 0x08
#define MOD_GUI 0x10

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  int col, row;
  col = record->event.key.col;
  row = record->event.key.row;
  if (record->event.pressed && ((row < 5 && is_master) || (row >= 5 && !is_master)))
  {
    int end = keybuf_end;
    keybufs[end].col = col;
    keybufs[end].row = row % 5;
    keybufs[end].frame = 0;
    keybuf_end++;
  }

  switch (keycode)
  {
  case QWERTY:
    if (record->event.pressed)
    {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_qwerty);
#endif
      update_base_layer(_QWERTY);
    }
    return false;
    break;
/*  case COLEMAK:
    if (record->event.pressed)
    {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_colemak);
#endif
      update_base_layer(_COLEMAK);
    }
    return false;
    break; */
  case ARIEUCALYN:
    if (record->event.pressed)
    {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_dvorak);
#endif
      update_base_layer(_ARIEUCALYN);
    }
    return false;
    break;
/*  case EUCALYN:
    if (record->event.pressed)
    {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_dvorak);
#endif
      update_base_layer(_EUCALYN);
    }
    return false;
    break; */
  case KEYPAD:
    if (record->event.pressed)
    {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_dvorak);
#endif
      update_base_layer(_KEYPAD);
    }
    return false;
    break;
  case ZERO2:
    if (record->event.pressed)
    {
      SEND_STRING("00");
    }
    return false;
    break;
  case EISU:
    if (record->event.pressed)
    {
      if (keymap_config.swap_lalt_lgui == false)
      {
        register_code(KC_LANG2);
      }
      else
      {
        SEND_STRING(SS_LALT("`"));
      }
    }
    else
    {
      unregister_code(KC_LANG2);
    }
    return false;
    break;
  case KANA:
    if (record->event.pressed)
    {
      if (keymap_config.swap_lalt_lgui == false)
      {
        register_code(KC_LANG1);
      }
      else
      {
        SEND_STRING(SS_LALT("`"));
      }
    }
    else
    {
      unregister_code(KC_LANG1);
    }
    return false;
    break;
  case RGBRST:
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed)
    {
      eeconfig_update_rgblight_default();
      rgblight_enable();
    }
#endif
    break;

  case KC_LSFT:
  case KC_RSFT:
    if (record->event.pressed) {
      modifier_status |= MOD_SHIFT;
    } else {
      modifier_status &= ~MOD_SHIFT;
    }
    break;
  case KC_LCTL:
  case KC_RCTL:
    if (record->event.pressed) {
      modifier_status |= MOD_CTRL;
    } else {
      modifier_status &= ~MOD_CTRL;
    }
    break;
  case KC_LALT:
  case KC_RALT:
    if (record->event.pressed) {
      modifier_status |= MOD_ALT;
    } else {
      modifier_status &= ~MOD_ALT;
    }
    break;
  case KC_APP:
    if (record->event.pressed) {
      modifier_status |= MOD_APP;
    } else {
      modifier_status &= ~MOD_APP;
    }
    break;
  case KC_RGUI:
  case KC_LGUI:
    if (record->event.pressed) {
      modifier_status |= MOD_GUI;
    } else {
      modifier_status &= ~MOD_GUI;
    }
    break;
  }
  return true;
}

void matrix_init_user(void)
{
#ifdef AUDIO_ENABLE
  startup_user();
#endif
//SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
  iota_gfx_init(!has_usb()); // turns on the display
#endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
  _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}

#endif

unsigned char rgb[7][5][3];
unsigned char rgbZ[7][5][3];

void led_my_init(void)
{
  static int scan_count = -10;
  static int keys[] = {6, 6, 6, 7, 7};
  static int keys_sum[] = {0, 6, 12, 18, 25};
  static int steps = 0;
  static int rgblight_restore_wait = 0;

  //
  if(steps > 0) {
    steps--;
    return;
  } else {
    steps = 3;
  }

  if (scan_count == -1)
  {
    memset(rgbZ, 0, sizeof(rgbZ));
    rgblight_enable_noeeprom();
  }
  else if (scan_count >= 0 && scan_count < 5)
  {
    for (unsigned char c = keybuf_begin; c != keybuf_end; c++)
    {
      int i = c;
      // FIXME:
      int color = (keybufs[i].row * 3 + keybufs[i].col) % 7 + 1;
      char r = (color & 0x4) >> 2;
      char g = (color & 0x2) >> 1;
      char b = (color & 0x1);

      int y = scan_count;
      int dist_y = abs(y - keybufs[i].row);
      for (int x = 0; x < keys[y]; x++)
      {
        int dist = abs(x - keybufs[i].col) + dist_y;
        if (dist <= keybufs[i].frame)
        {
          int elevation = MAX(0, (8 + dist - keybufs[i].frame)) << 2;
          if (elevation)
          {
            if ((rgb[x][y][0] != 255) && r)
            {
              rgb[x][y][0] = MIN(255, elevation + rgb[x][y][0]);
            }
            if ((rgb[x][y][1] != 255) && g)
            {
              rgb[x][y][1] = MIN(255, elevation + rgb[x][y][1]);
            }
            if ((rgb[x][y][2] != 255) && b)
            {
              rgb[x][y][2] = MIN(255, elevation + rgb[x][y][2]);
            }
          }
        }
      }
    }
  }
  else if (scan_count == 5)
  {
    for (unsigned char c = keybuf_begin; c != keybuf_end; c++)
    {
      int i = c;
      if (keybufs[i].frame < 18)
      {
        keybufs[i].frame++;
      }
      else
      {
        keybuf_begin++;
      }
    }
  }
  else if (scan_count >= 6 && scan_count <= 10)
  {
    int y = scan_count - 6;

    if(memcmp(rgb, rgbZ, sizeof(rgb)) == 0) {
      if(rgblight_restore_wait) {
        rgblight_restore_wait--;
      } else {
        rgblight_timer_enable();
      }
    } else {
        rgblight_timer_disable();
        for (int x = 0; x < keys[y]; x++)
        {
          int at = keys_sum[y] + ((y & 1) ? x : (keys[y] - x - 1));
          led[at].r = rgb[x][y][0];
          led[at].g = rgb[x][y][1];
          led[at].b = rgb[x][y][2];
        }
        rgblight_restore_wait = 100;
    }

    rgblight_set();
  }
  else if (scan_count == 11)
  {
    memset(rgb, 0, sizeof(rgb));
  }

  scan_count++;
  if (scan_count >= 12)
  {
    scan_count = 0;
  }
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void)
{
  led_my_init();
  iota_gfx_task(); // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                   const struct CharacterMatrix *source)
{
  if (memcmp(dest->display, source->display, sizeof(dest->display)))
  {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

static void render_logo(struct CharacterMatrix *matrix)
{

  static char logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};
  matrix_write(matrix, logo);
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_ANIMATIONS)
  char buf[30];
  if (rgblight_config.enable)
  {
    snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
             rgblight_config.mode,
             rgblight_config.hue / RGBLIGHT_HUE_STEP,
             rgblight_config.sat / RGBLIGHT_SAT_STEP,
             rgblight_config.val / RGBLIGHT_VAL_STEP);
    matrix_write(matrix, buf);
  }
#endif
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static const char Qwerty_name[] PROGMEM = " Qwerty";
//static const char Colemak_name[] PROGMEM = " Colemak";
static const char AriEucalyn_name[] PROGMEM = " AriEucalyn";
//static const char Eucalyn_name[] PROGMEM = " Eucalyn";
static const char Keypad_name[] PROGMEM = " Keypad";

static const char AUX_name[] PROGMEM = ":AUX";
static const char KAUX_name[] PROGMEM = ":00";
static const char Padfunc_name[] PROGMEM = ":PadFunc";
static const char Lower_name[] PROGMEM = ":Func";
static const char Raise_name[] PROGMEM = ":Extra";
static const char Adjust_name[] PROGMEM = ":Adjust";

static const char *layer_names[] = {
    [_QWERTY] = Qwerty_name,
//    [_COLEMAK] = Colemak_name,
    [_ARIEUCALYN] = AriEucalyn_name,
//    [_EUCALYN] = Eucalyn_name,
    [_KEYPAD] = Keypad_name,
    [_AUX] = AUX_name,
    [_KAUX] = KAUX_name,
    [_LOWER] = Lower_name,
    [_RAISE] = Raise_name,
    [_PADFUNC] = Padfunc_name,
    [_ADJUST] = Adjust_name};

void render_status(struct CharacterMatrix *matrix)
{

  // Render to mode icon
  static char logo[][2][3] = {{{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}};
  if (keymap_config.swap_lalt_lgui == false)
  {
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }
  else
  {
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  int name_num;
  uint32_t lstate;
  matrix_write_P(matrix, layer_names[current_default_layer]);
  matrix_write_P(matrix, PSTR("\n"));
  for (lstate = layer_state, name_num = 0;
       lstate && name_num < sizeof(layer_names) / sizeof(char *);
       lstate >>= 1, name_num++)
  {
    if ((lstate & 1) != 0)
    {
      if (layer_names[name_num])
      {
        matrix_write_P(matrix, layer_names[name_num]);
      }
    }
  }

  // Host Keyboard LED Status
  char led[40];
  /*
  snprintf(led, sizeof(led), "\n%s  %s  %s",
           (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
           (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
           (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  */
  snprintf(led, sizeof(led), "\n%s%s%s%s%s",
           (modifier_status & MOD_CTRL) ? ":Ctrl " : "",
           (modifier_status & MOD_SHIFT) ? ":Shift " : "",
           (modifier_status & MOD_ALT) ? ":Alt " : "",
           (modifier_status & MOD_APP) ? ":App " : "",
           (modifier_status & MOD_GUI) ? ":Gui " : "");
  matrix_write(matrix, led);
}

void iota_gfx_task_user(void)
{
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable)
  {
    return;
  }
#endif

  matrix_clear(&matrix);
  if (is_master)
  {
    render_status(&matrix);
  }
  else
  {
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
