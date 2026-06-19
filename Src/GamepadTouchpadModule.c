// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Event Queue Gamepad Touchpad Data Structure
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value self_get_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gtouchpad.timestamp);
}

PRIVATE
mrb_value self_get_finger(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gtouchpad.finger);
}

PRIVATE
mrb_value self_get_touch_x(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_float_value(mrb, private_event->gtouchpad.x);
}

PRIVATE
mrb_value self_get_touch_y(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_float_value(mrb, private_event->gtouchpad.y);
}

PRIVATE
mrb_value self_get_pressure(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_float_value(mrb, private_event->gtouchpad.pressure);
}

PRIVATE
mrb_value self_get_which(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gtouchpad.which);
}

PUBLIC
void DefineGamepadTouchpadModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *gamepadtouch = NULL;
    struct RClass *ex_event     = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event     = mrb_module_get(mrb, "Event");
    gamepadtouch = mrb_define_module_under(mrb, ex_event, "GamepadTouchpad");

    mrb_define_module_function(mrb, gamepadtouch, "timestamp", self_get_timestamp, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadtouch, "finger",    self_get_finger,    MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadtouch, "x",         self_get_touch_x,   MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadtouch, "y",         self_get_touch_y,   MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadtouch, "pressure",  self_get_pressure,  MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepadtouch, "which",     self_get_which,     MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
