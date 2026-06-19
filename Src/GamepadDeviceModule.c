// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Event Queue Gamepad Device Data Structure
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value self_get_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gdevice.timestamp);
}

PRIVATE
mrb_value self_get_which(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gdevice.which);
}

PUBLIC
void DefineGamepadDeviceModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *gamepaddev = NULL;
    struct RClass *ex_event   = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event   = mrb_module_get(mrb, "Event");
    gamepaddev = mrb_define_module_under(mrb, ex_event, "GamepadDevice");

    mrb_define_module_function(mrb, gamepaddev, "timestamp", self_get_timestamp, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepaddev, "which",     self_get_which,     MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}

