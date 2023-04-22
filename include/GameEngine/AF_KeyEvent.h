#pragma once
#include <stdint.h>
struct AF_KeyEvent {
    int32_t keyCode;
    bool keyDown;

    AF_KeyEvent(int32_t code, bool down): keyCode(code), keyDown(down) {}
};