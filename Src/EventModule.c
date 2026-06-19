// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: The Event Queue
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value self_is_fetching(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(SDL_PollEvent(private_event));
}

PRIVATE
mrb_value self_get_type(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->type);
}

PUBLIC
void DefineEventModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *ex_event = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event = mrb_define_module(mrb, "Event");

    mrb_define_const(mrb, ex_event, "QUIT",                        mrb_int_value(mrb, SDL_EVENT_QUIT));
    mrb_define_const(mrb, ex_event, "KEY_DOWN",                    mrb_int_value(mrb, SDL_EVENT_KEY_DOWN));
    mrb_define_const(mrb, ex_event, "KEY_UP",                      mrb_int_value(mrb, SDL_EVENT_KEY_UP));
    mrb_define_const(mrb, ex_event, "STATE_PRESSED",               mrb_bool_value(TRUE));
    mrb_define_const(mrb, ex_event, "STATE_RELEASED",              mrb_bool_value(FALSE));
    mrb_define_const(mrb, ex_event, "GAMEPAD_BUTTON_DOWN",         mrb_int_value(mrb, SDL_EVENT_GAMEPAD_BUTTON_DOWN));
    mrb_define_const(mrb, ex_event, "GAMEPAD_BUTTON_UP",           mrb_int_value(mrb, SDL_EVENT_GAMEPAD_BUTTON_UP));
    mrb_define_const(mrb, ex_event, "GAMEPAD_AXIS_MOTION",         mrb_int_value(mrb, SDL_EVENT_GAMEPAD_AXIS_MOTION));
    mrb_define_const(mrb, ex_event, "GAMEPAD_REMOVED",             mrb_int_value(mrb, SDL_EVENT_GAMEPAD_REMOVED));
    mrb_define_const(mrb, ex_event, "GAMEPAD_ADDED",               mrb_int_value(mrb, SDL_EVENT_GAMEPAD_ADDED));
    mrb_define_const(mrb, ex_event, "GAMEPAD_TOUCHPAD_DOWN",       mrb_int_value(mrb, SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN));
    mrb_define_const(mrb, ex_event, "GAMEPAD_TOUCHPAD_MOTION",     mrb_int_value(mrb, SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION));
    mrb_define_const(mrb, ex_event, "GAMEPAD_TOUCHPAD_UP",         mrb_int_value(mrb, SDL_EVENT_GAMEPAD_TOUCHPAD_UP));
    mrb_define_const(mrb, ex_event, "GAMEPAD_SENSOR_UPDATE",       mrb_int_value(mrb, SDL_EVENT_GAMEPAD_SENSOR_UPDATE));
    mrb_define_const(mrb, ex_event, "KEYBOARD_ADDED",              mrb_int_value(mrb, SDL_EVENT_KEYBOARD_ADDED));
    mrb_define_const(mrb, ex_event, "KEYBOARD_REMOVED",            mrb_int_value(mrb, SDL_EVENT_KEYBOARD_REMOVED));
    mrb_define_const(mrb, ex_event, "AUDIO_DEVICE_ADDED",          mrb_int_value(mrb, SDL_EVENT_AUDIO_DEVICE_ADDED));
    mrb_define_const(mrb, ex_event, "AUDIO_DEVICE_REMOVED",        mrb_int_value(mrb, SDL_EVENT_AUDIO_DEVICE_REMOVED));
    mrb_define_const(mrb, ex_event, "AUDIO_DEVICE_FORMAT_CHANGED", mrb_int_value(mrb, SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED));
    mrb_define_const(mrb, ex_event, "CAMERA_DEVICE_ADDED",         mrb_int_value(mrb, SDL_EVENT_CAMERA_DEVICE_ADDED));
    mrb_define_const(mrb, ex_event, "CAMERA_DEVICE_REMOVED",       mrb_int_value(mrb, SDL_EVENT_CAMERA_DEVICE_REMOVED));
    mrb_define_const(mrb, ex_event, "CAMERA_DEVICE_APPROVED",      mrb_int_value(mrb, SDL_EVENT_CAMERA_DEVICE_APPROVED));
    mrb_define_const(mrb, ex_event, "CAMERA_DEVICE_DENIED",        mrb_int_value(mrb, SDL_EVENT_CAMERA_DEVICE_DENIED));
    mrb_define_const(mrb, ex_event, "SENSOR_UPDATE",               mrb_int_value(mrb, SDL_EVENT_SENSOR_UPDATE));

    mrb_define_module_function(mrb, ex_event, "fetching?", self_is_fetching, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, ex_event, "type",      self_get_type,    MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
