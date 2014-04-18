#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "controller/controller.h"
#include <SDL2/SDL.h>

#define KEYBOARD_INPUT_BUFFER_SIZE 16

typedef struct keyboard_keys_t keyboard_keys;
typedef struct keyboard_t keyboard;

struct keyboard_keys_t {
    int up;
    int down;
    int left;
    int right;
    int punch;
    int kick;
    int escape;
};

struct keyboard_t {
    keyboard_keys *keys;
    uint16_t buffer[KEYBOARD_INPUT_BUFFER_SIZE];
    uint32_t tick;
    uint8_t delay;
    uint8_t queued;
};

void keyboard_create(controller *ctrl, keyboard_keys *keys, int delay);
void keyboard_free(controller *ctrl);
void keyboard_set_delay(controller *ctrl, int delay);
int keyboard_binds_key(controller *ctrl, SDL_Event *event);

#endif // _KEYBOARD_H
