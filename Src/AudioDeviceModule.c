// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Event Queue Audio Device Data Structure
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value self_get_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->adevice.timestamp);
}

PRIVATE
mrb_value self_get_which(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->adevice.which);
}

PRIVATE
mrb_value self_is_recording(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(private_event->adevice.recording);
}

PUBLIC
void DefineAudioDeviceModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *audio_dev = NULL;
    struct RClass *ex_event  = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event  = mrb_module_get(mrb, "Event");
    audio_dev = mrb_define_module_under(mrb, ex_event, "AudioDevice");

    mrb_define_module_function(mrb, audio_dev, "timestamp",  self_get_timestamp, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, audio_dev, "which",      self_get_which,     MRB_ARGS_NONE());
    mrb_define_module_function(mrb, audio_dev, "recording?", self_is_recording,  MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
