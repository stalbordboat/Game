// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Utility Methods For Power Stats
#include "Internal.h"

PRIVATE
int GetPowerStatus(mrb_state *mrb) {
    mrb_int status = SDL_POWERSTATE_ERROR;

    status = SDL_GetPowerInfo(NULL, NULL);
    if(status == SDL_POWERSTATE_ERROR) {
        RaiseRuntimeError(mrb);
    }

    return status;
}

PRIVATE
mrb_value self_is_unknown(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_bool_value((GetPowerStatus(mrb) == SDL_POWERSTATE_UNKNOWN));
}

PRIVATE
mrb_value self_is_on_battery(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_bool_value((GetPowerStatus(mrb) == SDL_POWERSTATE_ON_BATTERY));
}

PRIVATE
mrb_value self_is_no_battery(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_bool_value((GetPowerStatus(mrb) == SDL_POWERSTATE_NO_BATTERY));
}

PRIVATE
mrb_value self_is_charging(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_bool_value((GetPowerStatus(mrb) == SDL_POWERSTATE_CHARGING));
}

PRIVATE
mrb_value self_is_charged(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_bool_value((GetPowerStatus(mrb) == SDL_POWERSTATE_CHARGED));
}

PRIVATE
mrb_value self_seconds(mrb_state *mrb, mrb_value self) {
    mrb_int status = SDL_POWERSTATE_ERROR;
    int     sec    = 0;

    UNUSED_ARGUMENT self;

    status = SDL_GetPowerInfo(&sec, NULL);
    if(status == SDL_POWERSTATE_ERROR) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, sec);
}

PRIVATE
mrb_value self_percent(mrb_state *mrb, mrb_value self) {
    mrb_int status = SDL_POWERSTATE_ERROR;
    int     per    = 0;

    UNUSED_ARGUMENT self;

    status = SDL_GetPowerInfo(NULL, &per);
    if(status == SDL_POWERSTATE_ERROR) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, per);
}

PUBLIC
void DefinePowerModule(mrb_state *mrb) {
    struct RClass *power = NULL;

    SAVE_ARENA(mrb);

    power = mrb_define_module(mrb, "Power");

    mrb_define_module_function(mrb, power, "unknown?",    self_is_unknown,    MRB_ARGS_NONE());
    mrb_define_module_function(mrb, power, "on_battery?", self_is_on_battery, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, power, "no_battery?", self_is_no_battery, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, power, "charging?",   self_is_charging,   MRB_ARGS_NONE());
    mrb_define_module_function(mrb, power, "charged?",    self_is_charged,    MRB_ARGS_NONE());
    mrb_define_module_function(mrb, power, "seconds",     self_seconds,       MRB_ARGS_NONE());
    mrb_define_module_function(mrb, power, "percent",     self_percent,       MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
