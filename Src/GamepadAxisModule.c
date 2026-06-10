// MIT LICENSE - Copyright (c) Ralph Desir 2025
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value get_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gaxis.timestamp);
}

PRIVATE
mrb_value get_which(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gaxis.which);
}

PRIVATE
mrb_value get_axis(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gaxis.axis);
}

PRIVATE
mrb_value get_value(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gaxis.value);
}

PUBLIC
void DefineGamepadAxisModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *gamepadaxis = NULL;
    struct RClass *ex_event    = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event    = mrb_module_get(mrb, "Event");
    gamepadaxis = mrb_define_module_under(mrb, ex_event, "GamepadAxis");

    mrb_define_const(mrb, gamepadaxis, "DEFAULT_DEADZONE", mrb_int_value(mrb, 8000));
    mrb_define_const(mrb, gamepadaxis, "LEFTX",            mrb_int_value(mrb, SDL_GAMEPAD_AXIS_LEFTX));
    mrb_define_const(mrb, gamepadaxis, "LEFTY",            mrb_int_value(mrb, SDL_GAMEPAD_AXIS_LEFTY));
    mrb_define_const(mrb, gamepadaxis, "RIGHTX",           mrb_int_value(mrb, SDL_GAMEPAD_AXIS_RIGHTX));
    mrb_define_const(mrb, gamepadaxis, "RIGHTY",           mrb_int_value(mrb, SDL_GAMEPAD_AXIS_RIGHTY));
    mrb_define_const(mrb, gamepadaxis, "TRIGGER_LEFT",     mrb_int_value(mrb, SDL_GAMEPAD_AXIS_LEFT_TRIGGER));
    mrb_define_const(mrb, gamepadaxis, "TRIGGER_RIGHT",    mrb_int_value(mrb, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER));

    mrb_define_module_function(mrb, gamepadaxis, "timestamp", get_timestamp, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadaxis, "which",     get_which,     MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadaxis, "axis",      get_axis,      MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadaxis, "value",     get_value,     MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
