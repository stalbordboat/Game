// MIT LICENSE - Copyright (c) Ralph Desir 2026
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value get_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gsensor.timestamp);
}

PRIVATE
mrb_value get_which(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gsensor.which);
}

PRIVATE
mrb_value get_sensor(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gsensor.sensor);
}

PRIVATE
mrb_value get_data(mrb_state *mrb, mrb_value self) {
    mrb_value ary = {0};
    mrb_value val = {0};

    UNUSED_ARGUMENT self;

    ary = mrb_ary_new_capa(mrb, 3);

    for(int i = 0;i < 3;++i) {
        val = mrb_float_value(mrb, private_event->gsensor.data[i]);
        mrb_ary_set(mrb, ary, i, val);
    }

    return ary;
}

PRIVATE
mrb_value get_sensor_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->gsensor.sensor_timestamp);
}

PUBLIC
void DefineGamepadSensorModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *gamepad_sensor = NULL;
    struct RClass *ex_event       = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event       = mrb_module_get(mrb, "Event");
    gamepad_sensor = mrb_define_module_under(mrb, ex_event, "GamepadSensor");

    mrb_define_module_function(mrb, gamepad_sensor, "timestamp",        get_timestamp,        MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepad_sensor, "which",            get_which,            MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepad_sensor, "sensor",           get_sensor,           MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepad_sensor, "data",             get_data,             MRB_ARGS_NONE());
    mrb_define_module_function(mrb, gamepad_sensor, "sensor_timestamp", get_sensor_timestamp, MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
