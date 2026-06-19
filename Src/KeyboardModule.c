// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Represents Keyboard Devices
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value get_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->key.timestamp);
}

PRIVATE
mrb_value is_down(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(private_event->key.down);
}

PRIVATE
mrb_value is_repeat(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(private_event->key.repeat);
}

PRIVATE
mrb_value get_key(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->key.scancode);
}

PUBLIC
void DefineKeyboardModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *keyboard = NULL;
    struct RClass *ex_event = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event = mrb_module_get(mrb, "Event");
    keyboard = mrb_define_module_under(mrb, ex_event, "Keyboard");

    mrb_define_const(mrb, keyboard, "KEY_Z",         mrb_int_value(mrb, SDL_SCANCODE_Z));
    mrb_define_const(mrb, keyboard, "KEY_X",         mrb_int_value(mrb, SDL_SCANCODE_X));
    mrb_define_const(mrb, keyboard, "KEY_I",         mrb_int_value(mrb, SDL_SCANCODE_I));
    mrb_define_const(mrb, keyboard, "KEY_J",         mrb_int_value(mrb, SDL_SCANCODE_J));
    mrb_define_const(mrb, keyboard, "KEY_K",         mrb_int_value(mrb, SDL_SCANCODE_K));
    mrb_define_const(mrb, keyboard, "KEY_L",         mrb_int_value(mrb, SDL_SCANCODE_L));
    mrb_define_const(mrb, keyboard, "KEY_W",         mrb_int_value(mrb, SDL_SCANCODE_W));
    mrb_define_const(mrb, keyboard, "KEY_S",         mrb_int_value(mrb, SDL_SCANCODE_S));
    mrb_define_const(mrb, keyboard, "KEY_A",         mrb_int_value(mrb, SDL_SCANCODE_A));
    mrb_define_const(mrb, keyboard, "KEY_D",         mrb_int_value(mrb, SDL_SCANCODE_D));
    mrb_define_const(mrb, keyboard, "KEY_UP",        mrb_int_value(mrb, SDL_SCANCODE_UP));
    mrb_define_const(mrb, keyboard, "KEY_DOWN",      mrb_int_value(mrb, SDL_SCANCODE_DOWN));
    mrb_define_const(mrb, keyboard, "KEY_LEFT",      mrb_int_value(mrb, SDL_SCANCODE_LEFT));
    mrb_define_const(mrb, keyboard, "KEY_RIGHT",     mrb_int_value(mrb, SDL_SCANCODE_RIGHT));
    mrb_define_const(mrb, keyboard, "KEY_C",         mrb_int_value(mrb, SDL_SCANCODE_C));
    mrb_define_const(mrb, keyboard, "KEY_V",         mrb_int_value(mrb, SDL_SCANCODE_V));
    mrb_define_const(mrb, keyboard, "KEY_SPACE",     mrb_int_value(mrb, SDL_SCANCODE_SPACE));
    mrb_define_const(mrb, keyboard, "KEY_ENTER",     mrb_int_value(mrb, SDL_SCANCODE_RETURN));
    mrb_define_const(mrb, keyboard, "KEY_E",         mrb_int_value(mrb, SDL_SCANCODE_E));
    mrb_define_const(mrb, keyboard, "KEY_F",         mrb_int_value(mrb, SDL_SCANCODE_F));
    mrb_define_const(mrb, keyboard, "KEY_Q",         mrb_int_value(mrb, SDL_SCANCODE_Q));
    mrb_define_const(mrb, keyboard, "KEY_R",         mrb_int_value(mrb, SDL_SCANCODE_R));
    mrb_define_const(mrb, keyboard, "KEY_LCTRL",     mrb_int_value(mrb, SDL_SCANCODE_LCTRL));
    mrb_define_const(mrb, keyboard, "KEY_RCTRL",     mrb_int_value(mrb, SDL_SCANCODE_RCTRL));
    mrb_define_const(mrb, keyboard, "KEY_LSHIFT",    mrb_int_value(mrb, SDL_SCANCODE_LSHIFT));
    mrb_define_const(mrb, keyboard, "KEY_RSHIFT",    mrb_int_value(mrb, SDL_SCANCODE_RSHIFT));
    mrb_define_const(mrb, keyboard, "KEY_LALT",      mrb_int_value(mrb, SDL_SCANCODE_LALT));
    mrb_define_const(mrb, keyboard, "KEY_RALT",      mrb_int_value(mrb, SDL_SCANCODE_RALT));
    mrb_define_const(mrb, keyboard, "KEY_PAD_7",     mrb_int_value(mrb, SDL_SCANCODE_KP_7));
    mrb_define_const(mrb, keyboard, "KEY_PAD_8",     mrb_int_value(mrb, SDL_SCANCODE_KP_8));
    mrb_define_const(mrb, keyboard, "KEY_PAD_9",     mrb_int_value(mrb, SDL_SCANCODE_KP_9));
    mrb_define_const(mrb, keyboard, "KEY_PAD_4",     mrb_int_value(mrb, SDL_SCANCODE_KP_4));
    mrb_define_const(mrb, keyboard, "KEY_PAD_6",     mrb_int_value(mrb, SDL_SCANCODE_KP_6));
    mrb_define_const(mrb, keyboard, "KEY_PAD_1",     mrb_int_value(mrb, SDL_SCANCODE_KP_1));
    mrb_define_const(mrb, keyboard, "KEY_PAD_2",     mrb_int_value(mrb, SDL_SCANCODE_KP_2));
    mrb_define_const(mrb, keyboard, "KEY_PAD_3",     mrb_int_value(mrb, SDL_SCANCODE_KP_3));
    mrb_define_const(mrb, keyboard, "KEY_ESC",       mrb_int_value(mrb, SDL_SCANCODE_ESCAPE));
    mrb_define_const(mrb, keyboard, "KEY_BACKSPACE", mrb_int_value(mrb, SDL_SCANCODE_BACKSPACE));

    mrb_define_module_function(mrb, keyboard, "timestamp", get_timestamp, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, keyboard, "down?",     is_down,       MRB_ARGS_NONE());
    mrb_define_module_function(mrb, keyboard, "repeat?",   is_repeat,     MRB_ARGS_NONE());
    mrb_define_module_function(mrb, keyboard, "key",       get_key,       MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
