#include <kernel/scancodes.h>
#include <kernel/keyboard.h>

#include <stdio.h>

#include <stdint.h>

uint8_t *scan_code_set1[] = {
  (uint8_t []) { 0x01, 0x00, KEY_CODE_ESCAPE }, // Escape
  (uint8_t []) { 0x02, 0x00, KEY_CODE_1 }, // 1
  (uint8_t []) { 0x03, 0x00, KEY_CODE_2 }, // 2
  (uint8_t []) { 0x04, 0x00, KEY_CODE_3 }, // 3
  (uint8_t []) { 0x05, 0x00, KEY_CODE_4 }, // 4
  (uint8_t []) { 0x06, 0x00, KEY_CODE_5 }, // 5
  (uint8_t []) { 0x07, 0x00, KEY_CODE_6 }, // 6
  (uint8_t []) { 0x08, 0x00, KEY_CODE_7 }, // 7
  (uint8_t []) { 0x09, 0x00, KEY_CODE_8 }, // 8
  (uint8_t []) { 0x0A, 0x00, KEY_CODE_9 }, // 9
  (uint8_t []) { 0x0B, 0x00, KEY_CODE_0 }, // 0
  (uint8_t []) { 0x0C, 0x00, KEY_CODE_MINUS }, // -
  (uint8_t []) { 0x0D, 0x00, KEY_CODE_EQUAL_SIGN }, // =
  (uint8_t []) { 0x0E, 0x00, KEY_CODE_BACKSPACE }, // Backspace
  (uint8_t []) { 0x0F, 0x00, KEY_CODE_TAB }, // Tab
  (uint8_t []) { 0x10, 0x00, KEY_CODE_Q }, // Q
  (uint8_t []) { 0x11, 0x00, KEY_CODE_W }, // W
  (uint8_t []) { 0x12, 0x00, KEY_CODE_E }, // E
  (uint8_t []) { 0x13, 0x00, KEY_CODE_R }, // R
  (uint8_t []) { 0x14, 0x00, KEY_CODE_T }, // T
  (uint8_t []) { 0x15, 0x00, KEY_CODE_Y }, // Y
  (uint8_t []) { 0x16, 0x00, KEY_CODE_U }, // U
  (uint8_t []) { 0x17, 0x00, KEY_CODE_I }, // I
  (uint8_t []) { 0x18, 0x00, KEY_CODE_O }, // O
  (uint8_t []) { 0x19, 0x00, KEY_CODE_P }, // P
  (uint8_t []) { 0x1A, 0x00, KEY_CODE_BRACKET_OPEN }, // [
  (uint8_t []) { 0x1B, 0x00, KEY_CODE_BRACKET_CLOSE }, // ]
  (uint8_t []) { 0x1C, 0x00, KEY_CODE_ENTER }, // Enter
  (uint8_t []) { 0x1D, 0x00, KEY_CODE_LEFT_CTRL }, // Left Ctrl
  (uint8_t []) { 0x1E, 0x00, KEY_CODE_A }, // A
  (uint8_t []) { 0x1F, 0x00, KEY_CODE_S }, // S
  (uint8_t []) { 0x20, 0x00, KEY_CODE_D }, // D
  (uint8_t []) { 0x21, 0x00, KEY_CODE_F }, // F
  (uint8_t []) { 0x22, 0x00, KEY_CODE_G }, // G
  (uint8_t []) { 0x23, 0x00, KEY_CODE_H }, // H
  (uint8_t []) { 0x24, 0x00, KEY_CODE_J }, // J
  (uint8_t []) { 0x25, 0x00, KEY_CODE_K }, // K
  (uint8_t []) { 0x26, 0x00, KEY_CODE_L }, // L
  (uint8_t []) { 0x27, 0x00, KEY_CODE_SEMICOLON }, // ;
  (uint8_t []) { 0x28, 0x00, KEY_CODE_SINGLE_QUOTE }, // '
  (uint8_t []) { 0x29, 0x00, KEY_CODE_BACK_TICK }, // `
  (uint8_t []) { 0x2A, 0x00, KEY_CODE_LEFT_SHIFT }, // Left Shift
  (uint8_t []) { 0x2B, 0x00, KEY_CODE_BACKSLASH }, // Backslash
  (uint8_t []) { 0x2C, 0x00, KEY_CODE_Z }, // Z
  (uint8_t []) { 0x2D, 0x00, KEY_CODE_X }, // X
  (uint8_t []) { 0x2E, 0x00, KEY_CODE_C }, // C
  (uint8_t []) { 0x2F, 0x00, KEY_CODE_V }, // V
  (uint8_t []) { 0x30, 0x00, KEY_CODE_B }, // B
  (uint8_t []) { 0x31, 0x00, KEY_CODE_N }, // N
  (uint8_t []) { 0x32, 0x00, KEY_CODE_M }, // M
  (uint8_t []) { 0x33, 0x00, KEY_CODE_COMMA }, // ,
  (uint8_t []) { 0x34, 0x00, KEY_CODE_DOT }, // .
  (uint8_t []) { 0x35, 0x00, KEY_CODE_FORWARD_SLASH }, // /
  (uint8_t []) { 0x36, 0x00, KEY_CODE_RIGHT_SHIFT }, // Right Shift
  (uint8_t []) { 0x37, 0x00, KEY_CODE_ASTERISK }, // (Keypad)*
  (uint8_t []) { 0x38, 0x00, KEY_CODE_LEFT_ALT }, // Left Alt
  (uint8_t []) { 0x39, 0x00, KEY_CODE_SPACE }, // Space
  (uint8_t []) { 0x3A, 0x00, KEY_CODE_CAPS_LOCK }, // CapsLock
  (uint8_t []) { 0x3B, 0x00, KEY_CODE_F1 }, // F1
  (uint8_t []) { 0x3C, 0x00, KEY_CODE_F2 }, // F2
  (uint8_t []) { 0x3D, 0x00, KEY_CODE_F3 }, // F3
  (uint8_t []) { 0x3E, 0x00, KEY_CODE_F4 }, // F4
  (uint8_t []) { 0x3F, 0x00, KEY_CODE_F5 }, // F5
  (uint8_t []) { 0x40, 0x00, KEY_CODE_F6 }, // F6
  (uint8_t []) { 0x41, 0x00, KEY_CODE_F7 }, // F7
  (uint8_t []) { 0x42, 0x00, KEY_CODE_F8 }, // F8
  (uint8_t []) { 0x43, 0x00, KEY_CODE_F9 }, // F9
  (uint8_t []) { 0x44, 0x00, KEY_CODE_F10 }, // F10
  (uint8_t []) { 0x45, 0x00, KEY_CODE_NUM_LOCK }, // NumLock
  (uint8_t []) { 0x46, 0x00, KEY_CODE_SCROLL_LOCK }, // ScrollLock
  (uint8_t []) { 0x47, 0x00, KEY_CODE_KEYPAD_7 }, // (Keypad) 7
  (uint8_t []) { 0x48, 0x00, KEY_CODE_KEYPAD_8 }, // (Keypad) 8
  (uint8_t []) { 0x49, 0x00, KEY_CODE_KEYPAD_9 }, // (Keypad) 9
  (uint8_t []) { 0x4A, 0x00, KEY_CODE_KEYPAD_MINUS }, // (Keypad) -
  (uint8_t []) { 0x4B, 0x00, KEY_CODE_KEYPAD_4 }, // (Keypad) 4
  (uint8_t []) { 0x4C, 0x00, KEY_CODE_KEYPAD_5 }, // (Keypad) 5
  (uint8_t []) { 0x4D, 0x00, KEY_CODE_KEYPAD_6 }, // (Keypad) 6
  (uint8_t []) { 0x4E, 0x00, KEY_CODE_KEYPAD_PLUS }, // (Keypad) +
  (uint8_t []) { 0x4F, 0x00, KEY_CODE_KEYPAD_1 }, // (Keypad) 1
  (uint8_t []) { 0x50, 0x00, KEY_CODE_KEYPAD_2 }, // (Keypad) 2
  (uint8_t []) { 0x51, 0x00, KEY_CODE_KEYPAD_3 }, // (Keypad) 3
  (uint8_t []) { 0x52, 0x00, KEY_CODE_KEYPAD_0 }, // (Keypad) 0
  (uint8_t []) { 0x53, 0x00, KEY_CODE_KEYPAD_DOT }, // (Keypad) .
  (uint8_t []) { 0x57, 0x00, KEY_CODE_F11 }, // F11
  (uint8_t []) { 0x58, 0x00, KEY_CODE_F12 }, // F12
  (uint8_t []) { 0x81, 0x00, KEY_CODE_ESCAPE | KEY_RELEASED_FLAG }, // R-Escape
  (uint8_t []) { 0x82, 0x00, KEY_CODE_1 | KEY_RELEASED_FLAG }, // R-1
  (uint8_t []) { 0x83, 0x00, KEY_CODE_2 | KEY_RELEASED_FLAG }, // R-2
  (uint8_t []) { 0x84, 0x00, KEY_CODE_3 | KEY_RELEASED_FLAG }, // R-3
  (uint8_t []) { 0x85, 0x00, KEY_CODE_4 | KEY_RELEASED_FLAG }, // R-4
  (uint8_t []) { 0x86, 0x00, KEY_CODE_5 | KEY_RELEASED_FLAG }, // R-5
  (uint8_t []) { 0x87, 0x00, KEY_CODE_6 | KEY_RELEASED_FLAG }, // R-6
  (uint8_t []) { 0x88, 0x00, KEY_CODE_7 | KEY_RELEASED_FLAG }, // R-7
  (uint8_t []) { 0x89, 0x00, KEY_CODE_8 | KEY_RELEASED_FLAG }, // R-8
  (uint8_t []) { 0x8A, 0x00, KEY_CODE_9 | KEY_RELEASED_FLAG }, // R-9
  (uint8_t []) { 0x8B, 0x00, KEY_CODE_0 | KEY_RELEASED_FLAG }, // R-0
  (uint8_t []) { 0x8C, 0x00, KEY_CODE_MINUS | KEY_RELEASED_FLAG }, // R--
  (uint8_t []) { 0x8D, 0x00, KEY_CODE_EQUAL_SIGN | KEY_RELEASED_FLAG }, // R-=
  (uint8_t []) { 0x8E, 0x00, KEY_CODE_BACKSPACE | KEY_RELEASED_FLAG }, // R-Backspace
  (uint8_t []) { 0x8F, 0x00, KEY_CODE_TAB | KEY_RELEASED_FLAG }, // R-Tab
  (uint8_t []) { 0x90, 0x00, KEY_CODE_Q | KEY_RELEASED_FLAG }, // R-Q
  (uint8_t []) { 0x91, 0x00, KEY_CODE_W | KEY_RELEASED_FLAG }, // R-W
  (uint8_t []) { 0x92, 0x00, KEY_CODE_E | KEY_RELEASED_FLAG }, // R-E
  (uint8_t []) { 0x93, 0x00, KEY_CODE_R | KEY_RELEASED_FLAG }, // R-R
  (uint8_t []) { 0x94, 0x00, KEY_CODE_T | KEY_RELEASED_FLAG }, // R-T
  (uint8_t []) { 0x95, 0x00, KEY_CODE_Y | KEY_RELEASED_FLAG }, // R-Y
  (uint8_t []) { 0x96, 0x00, KEY_CODE_U | KEY_RELEASED_FLAG }, // R-U
  (uint8_t []) { 0x97, 0x00, KEY_CODE_I | KEY_RELEASED_FLAG }, // R-I
  (uint8_t []) { 0x98, 0x00, KEY_CODE_O | KEY_RELEASED_FLAG }, // R-O
  (uint8_t []) { 0x99, 0x00, KEY_CODE_P | KEY_RELEASED_FLAG }, // R-P
  (uint8_t []) { 0x9A, 0x00, KEY_CODE_BRACKET_OPEN | KEY_RELEASED_FLAG }, // R-[
  (uint8_t []) { 0x9B, 0x00, KEY_CODE_BRACKET_CLOSE | KEY_RELEASED_FLAG }, // R-]
  (uint8_t []) { 0x9C, 0x00, KEY_CODE_ENTER | KEY_RELEASED_FLAG }, // R-Enter
  (uint8_t []) { 0x9D, 0x00, KEY_CODE_LEFT_CTRL | KEY_RELEASED_FLAG }, // R-Left Control
  (uint8_t []) { 0x9E, 0x00, KEY_CODE_A | KEY_RELEASED_FLAG }, // R-A
  (uint8_t []) { 0x9F, 0x00, KEY_CODE_S | KEY_RELEASED_FLAG }, // R-S
  (uint8_t []) { 0xA0, 0x00, KEY_CODE_D | KEY_RELEASED_FLAG }, // R-D
  (uint8_t []) { 0xA1, 0x00, KEY_CODE_F | KEY_RELEASED_FLAG }, // R-F
  (uint8_t []) { 0xA2, 0x00, KEY_CODE_G | KEY_RELEASED_FLAG }, // R-G
  (uint8_t []) { 0xA3, 0x00, KEY_CODE_H | KEY_RELEASED_FLAG }, // R-H
  (uint8_t []) { 0xA4, 0x00, KEY_CODE_J | KEY_RELEASED_FLAG }, // R-J
  (uint8_t []) { 0xA5, 0x00, KEY_CODE_K | KEY_RELEASED_FLAG }, // R-K
  (uint8_t []) { 0xA6, 0x00, KEY_CODE_L | KEY_RELEASED_FLAG }, // R-L
  (uint8_t []) { 0xA7, 0x00, KEY_CODE_SEMICOLON | KEY_RELEASED_FLAG }, // R-;
  (uint8_t []) { 0xA8, 0x00, KEY_CODE_SINGLE_QUOTE | KEY_RELEASED_FLAG }, // R-'
  (uint8_t []) { 0xA9, 0x00, KEY_CODE_BACK_TICK | KEY_RELEASED_FLAG }, // R-`
  (uint8_t []) { 0xAA, 0x00, KEY_CODE_LEFT_SHIFT | KEY_RELEASED_FLAG }, // R-Left Shift
  (uint8_t []) { 0xAB, 0x00, KEY_CODE_BACKSLASH | KEY_RELEASED_FLAG }, // R-Backslash
  (uint8_t []) { 0xAC, 0x00, KEY_CODE_Z | KEY_RELEASED_FLAG }, // R-Z
  (uint8_t []) { 0xAD, 0x00, KEY_CODE_X | KEY_RELEASED_FLAG }, // R-X
  (uint8_t []) { 0xAE, 0x00, KEY_CODE_C | KEY_RELEASED_FLAG }, // R-C
  (uint8_t []) { 0xAF, 0x00, KEY_CODE_V | KEY_RELEASED_FLAG }, // R-V
  (uint8_t []) { 0xB0, 0x00, KEY_CODE_B | KEY_RELEASED_FLAG }, // R-B
  (uint8_t []) { 0xB1, 0x00, KEY_CODE_N | KEY_RELEASED_FLAG }, // R-N
  (uint8_t []) { 0xB2, 0x00, KEY_CODE_M | KEY_RELEASED_FLAG }, // R-M
  (uint8_t []) { 0xB3, 0x00, KEY_CODE_COMMA | KEY_RELEASED_FLAG }, // R-,
  (uint8_t []) { 0xB4, 0x00, KEY_CODE_DOT | KEY_RELEASED_FLAG }, // R-.
  (uint8_t []) { 0xB5, 0x00, KEY_CODE_FORWARD_SLASH | KEY_RELEASED_FLAG }, // R-/
  (uint8_t []) { 0xB6, 0x00, KEY_CODE_RIGHT_SHIFT | KEY_RELEASED_FLAG }, // R-RightShift
  (uint8_t []) { 0xB7, 0x00, KEY_CODE_ASTERISK | KEY_RELEASED_FLAG }, // R-(Keypad) *
  (uint8_t []) { 0xB8, 0x00, KEY_CODE_LEFT_ALT | KEY_RELEASED_FLAG }, // R-Left Alt
  (uint8_t []) { 0xB9, 0x00, KEY_CODE_SPACE | KEY_RELEASED_FLAG }, // R-Space
  (uint8_t []) { 0xBA, 0x00, KEY_CODE_CAPS_LOCK | KEY_RELEASED_FLAG }, // R-CapsLock
  (uint8_t []) { 0xBB, 0x00, KEY_CODE_F1 | KEY_RELEASED_FLAG }, // R-F1
  (uint8_t []) { 0xBC, 0x00, KEY_CODE_F2 | KEY_RELEASED_FLAG }, // R-F2
  (uint8_t []) { 0xBD, 0x00, KEY_CODE_F3 | KEY_RELEASED_FLAG }, // R-F3
  (uint8_t []) { 0xBE, 0x00, KEY_CODE_F4 | KEY_RELEASED_FLAG }, // R-F4
  (uint8_t []) { 0xBF, 0x00, KEY_CODE_F5 | KEY_RELEASED_FLAG }, // R-F5
  (uint8_t []) { 0xC0, 0x00, KEY_CODE_F6 | KEY_RELEASED_FLAG }, // R-F6
  (uint8_t []) { 0xC1, 0x00, KEY_CODE_F7 | KEY_RELEASED_FLAG }, // R-F7
  (uint8_t []) { 0xC2, 0x00, KEY_CODE_F8 | KEY_RELEASED_FLAG }, // R-F8
  (uint8_t []) { 0xC3, 0x00, KEY_CODE_F9 | KEY_RELEASED_FLAG }, // R-F9
  (uint8_t []) { 0xC4, 0x00, KEY_CODE_F10 | KEY_RELEASED_FLAG }, // R-F10
  (uint8_t []) { 0xC5, 0x00, KEY_CODE_NUM_LOCK | KEY_RELEASED_FLAG }, // R-NumLock
  (uint8_t []) { 0xC6, 0x00, KEY_CODE_SCROLL_LOCK | KEY_RELEASED_FLAG }, // R-ScrollLock
  (uint8_t []) { 0xC7, 0x00, KEY_CODE_KEYPAD_7 | KEY_RELEASED_FLAG }, // R-(Keypad) 7
  (uint8_t []) { 0xC8, 0x00, KEY_CODE_KEYPAD_8 | KEY_RELEASED_FLAG }, // R-(Keypad) 8
  (uint8_t []) { 0xC9, 0x00, KEY_CODE_KEYPAD_9 | KEY_RELEASED_FLAG }, // R-(Keypad) 9
  (uint8_t []) { 0xCA, 0x00, KEY_CODE_KEYPAD_MINUS | KEY_RELEASED_FLAG }, // R-(Keypad) -
  (uint8_t []) { 0xCB, 0x00, KEY_CODE_KEYPAD_4 | KEY_RELEASED_FLAG }, // R-(Keypad) 4
  (uint8_t []) { 0xCC, 0x00, KEY_CODE_KEYPAD_5 | KEY_RELEASED_FLAG }, // R-(Keypad) 5
  (uint8_t []) { 0xCD, 0x00, KEY_CODE_KEYPAD_6 | KEY_RELEASED_FLAG }, // R-(Keypad) 6
  (uint8_t []) { 0xCE, 0x00, KEY_CODE_KEYPAD_PLUS | KEY_RELEASED_FLAG }, // R-(Keypad) +
  (uint8_t []) { 0xCF, 0x00, KEY_CODE_KEYPAD_1 | KEY_RELEASED_FLAG }, // R-(Keypad) 1
  (uint8_t []) { 0xD0, 0x00, KEY_CODE_KEYPAD_2 | KEY_RELEASED_FLAG }, // R-(Keypad) 2
  (uint8_t []) { 0xD1, 0x00, KEY_CODE_KEYPAD_3 | KEY_RELEASED_FLAG }, // R-(Keypad) 3
  (uint8_t []) { 0xD2, 0x00, KEY_CODE_KEYPAD_0 | KEY_RELEASED_FLAG }, // R-(Keypad) 0
  (uint8_t []) { 0xD3, 0x00, KEY_CODE_KEYPAD_DOT | KEY_RELEASED_FLAG }, // R-(Keypad) .
  (uint8_t []) { 0xD7, 0x00, KEY_CODE_F11 | KEY_RELEASED_FLAG }, // R-F11
  (uint8_t []) { 0xD8, 0x00, KEY_CODE_F12 | KEY_RELEASED_FLAG }, // R-F12
  (uint8_t []) { 0xE0, 0x1C, 0x00, KEY_CODE_KEYPAD_ENTER }, // (Keypad) Enter
  (uint8_t []) { 0xE0, 0x1D, 0x00, KEY_CODE_RIGHT_CONTROL }, // Right Control
  (uint8_t []) { 0xE0, 0x35, 0x00, KEY_CODE_KEYPAD_FORWARD_SLASH }, // (Keypad) /
  (uint8_t []) { 0xE0, 0x38, 0x00, KEY_CODE_RIGHT_ALT }, // Right Alt
  (uint8_t []) { 0xE0, 0x47, 0x00, KEY_CODE_HOME }, // Home
  (uint8_t []) { 0xE0, 0x48, 0x00, KEY_CODE_UP }, // Cursor Up
  (uint8_t []) { 0xE0, 0x49, 0x00, KEY_CODE_PAGE_UP }, // Page Up
  (uint8_t []) { 0xE0, 0x4B, 0x00, KEY_CODE_LEFT }, // Cursor Left
  (uint8_t []) { 0xE0, 0x4D, 0x00, KEY_CODE_RIGHT }, // Cursor Right
  (uint8_t []) { 0xE0, 0x4F, 0x00, KEY_CODE_END }, // End
  (uint8_t []) { 0xE0, 0x50, 0x00, KEY_CODE_DOWN }, // Cursor Down
  (uint8_t []) { 0xE0, 0x51, 0x00, KEY_CODE_PAGE_DOWN }, // Page Down
  (uint8_t []) { 0xE0, 0x52, 0x00, KEY_CODE_INSERT }, // Insert
  (uint8_t []) { 0xE0, 0x53, 0x00, KEY_CODE_DELETE }, // Delete
  (uint8_t []) { 0xE0, 0x5B, 0x00, KEY_CODE_LEFT_GUI }, // Left GUI
  (uint8_t []) { 0xE0, 0x5C, 0x00, KEY_CODE_RIGHT_GUI }, // Right GUI
  (uint8_t []) { 0xE0, 0x5D, 0x00, KEY_CODE_APPS }, // "apps"
  (uint8_t []) { 0xE0, 0x9C, 0x00, KEY_CODE_KEYPAD_ENTER | KEY_RELEASED_FLAG }, // R-(Keypad) Enter
  (uint8_t []) { 0xE0, 0x9D, 0x00, KEY_CODE_RIGHT_CONTROL | KEY_RELEASED_FLAG }, // R-Right Control
  (uint8_t []) { 0xE0, 0xB5, 0x00, KEY_CODE_KEYPAD_FORWARD_SLASH | KEY_RELEASED_FLAG }, // R-(Keypad) /
  (uint8_t []) { 0xE0, 0xB8, 0x00, KEY_CODE_RIGHT_ALT | KEY_RELEASED_FLAG }, // R-Right Alt
  (uint8_t []) { 0xE0, 0xC7, 0x00, KEY_CODE_HOME | KEY_RELEASED_FLAG }, // R-Home
  (uint8_t []) { 0xE0, 0xC8, 0x00, KEY_CODE_UP | KEY_RELEASED_FLAG }, // R-Cursor Up
  (uint8_t []) { 0xE0, 0xC9, 0x00, KEY_CODE_PAGE_UP | KEY_RELEASED_FLAG }, // R-Page Up
  (uint8_t []) { 0xE0, 0xCB, 0x00, KEY_CODE_LEFT | KEY_RELEASED_FLAG }, // R-Cursor Left
  (uint8_t []) { 0xE0, 0xCD, 0x00, KEY_CODE_RIGHT | KEY_RELEASED_FLAG }, // R-Cursor Right
  (uint8_t []) { 0xE0, 0xCF, 0x00, KEY_CODE_END | KEY_RELEASED_FLAG }, // R-End
  (uint8_t []) { 0xE0, 0xD0, 0x00, KEY_CODE_DOWN | KEY_RELEASED_FLAG }, // R-Cursor Down
  (uint8_t []) { 0xE0, 0xD1, 0x00, KEY_CODE_PAGE_DOWN | KEY_RELEASED_FLAG }, // R-Page Down
  (uint8_t []) { 0xE0, 0xD2, 0x00, KEY_CODE_INSERT | KEY_RELEASED_FLAG }, // R-Insert
  (uint8_t []) { 0xE0, 0xD3, 0x00, KEY_CODE_DELETE | KEY_RELEASED_FLAG }, // R-Delete
  (uint8_t []) { 0xE0, 0xDB, 0x00, KEY_CODE_LEFT_GUI | KEY_RELEASED_FLAG }, // R-Left GUI
  (uint8_t []) { 0xE0, 0xDC, 0x00, KEY_CODE_RIGHT_GUI | KEY_RELEASED_FLAG }, // R-Right GUI
  (uint8_t []) { 0xE0, 0xDD, 0x00, KEY_CODE_APPS | KEY_RELEASED_FLAG }, // R-"apps"
  (uint8_t []) { 0xE0, 0x2A, 0xE0, 0x37, 0x00, KEY_CODE_PRINT_SCREEN }, // Print screen
  (uint8_t []) { 0xE0, 0xB7, 0xE0, 0xAA, 0x00, KEY_CODE_PRINT_SCREEN | KEY_RELEASED_FLAG }, // R-Print screen
  (uint8_t []) { 0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5, 0x00, KEY_CODE_PAUSE } // Pause
};

char char_list_en[] = {
  0x00, 0x00, '1', '2', '3', '4', '5', '6', '7', '8',
  '9', '0', '-', '=', '\b', '\t', 'Q', 'W', 'E', 'R',
  'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0x00,
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
  '\'', '`', 0x00, '\\', 'Z', 'X', 'C', 'V', 'B', 'N',
  'M', ',', '.', '/', 0x00, '*', 0x00, ' ', 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, '7', '8', '9', '-', '4', '5', '6', '+', '1',
  '2', '3', '0', '.', 0x00, 0x00, '\n', 0x00, '/', 0x00,
  '\r', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t get_char() {
  uint8_t key_code = get_key_code();
  if(key_code & KEY_RELEASED_FLAG) {
    return 0x00;
  } else {
    return char_list_en[key_code & (~0x80)];
  }
}

uint8_t get_key_code() {
  uint8_t key_code = read_scan_code();
  uint8_t key_code_invalidated = 0;
  
  for (uint16_t i = 0; i < NR_SCAN_CODES_SET_1; i++) {
    uint8_t *current = scan_code_set1[i];
    uint8_t found = 1;
    while(*current != 0x00) {
      if(key_code_invalidated) {
        key_code = read_scan_code();
      }
      
      if(key_code != *current) {
        found = 0;
        break;
      }
      
      current++;
      key_code_invalidated = 1;
    }
    
    if(found) {
      return *(current + 1);
    }
  }
  return 0;
}
