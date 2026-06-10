// MIT LICENSE - Copyright (c) Ralph Desir 2025
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value get_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gbutton.timestamp);
}

PRIVATE
mrb_value get_which(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gbutton.which);
}

PRIVATE
mrb_value get_button(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gbutton.button);
}

PRIVATE
mrb_value is_down(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(private_event->gbutton.down);
}

PUBLIC
void DefineGamepadButtonModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *gamepadbutton = NULL;
    struct RClass *ex_event      = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event      = mrb_module_get(mrb, "Event");
    gamepadbutton = mrb_define_module_under(mrb, ex_event, "GamepadButton");

    mrb_define_const(mrb, gamepadbutton, "S",           mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_SOUTH));
    mrb_define_const(mrb, gamepadbutton, "E",           mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_EAST));
    mrb_define_const(mrb, gamepadbutton, "W",           mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_WEST));
    mrb_define_const(mrb, gamepadbutton, "N",           mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_NORTH));
    mrb_define_const(mrb, gamepadbutton, "BACK",        mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_BACK));
    mrb_define_const(mrb, gamepadbutton, "GUIDE",       mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_GUIDE));
    mrb_define_const(mrb, gamepadbutton, "START",       mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_START));
    mrb_define_const(mrb, gamepadbutton, "LEFT_STICK",  mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_LEFT_STICK));
    mrb_define_const(mrb, gamepadbutton, "RIGHT_STICK", mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_RIGHT_STICK));
    mrb_define_const(mrb, gamepadbutton, "L1",          mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER));
    mrb_define_const(mrb, gamepadbutton, "R1",          mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER));
    mrb_define_const(mrb, gamepadbutton, "UP",          mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_DPAD_UP));
    mrb_define_const(mrb, gamepadbutton, "DOWN",        mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_DPAD_DOWN));
    mrb_define_const(mrb, gamepadbutton, "LEFT",        mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_DPAD_LEFT));
    mrb_define_const(mrb, gamepadbutton, "RIGHT",       mrb_int_value(mrb, SDL_GAMEPAD_BUTTON_DPAD_RIGHT));

    mrb_define_module_function(mrb, gamepadbutton, "timestamp", get_timestamp, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadbutton, "which",     get_which,     MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadbutton, "button",    get_button,    MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadbutton, "down?",     is_down,       MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
