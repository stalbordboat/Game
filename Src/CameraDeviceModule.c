// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Event Queue Camera Device Data Structure
#include "Internal.h"

PRIVATE SDL_Event *private_event = NULL;

PRIVATE
mrb_value get_timestamp(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->cdevice.timestamp);
}

PRIVATE
mrb_value get_which(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, private_event->cdevice.which);
}

PUBLIC
void DefineCameraDeviceModule(mrb_state *mrb, SDL_Event *event) {
    struct RClass *camera_dev = NULL;
    struct RClass *ex_event   = NULL;

    private_event = event;

    SAVE_ARENA(mrb);

    ex_event   = mrb_module_get(mrb, "Event");
    camera_dev = mrb_define_module_under(mrb, ex_event, "CameraDevice");

    mrb_define_module_function(mrb, camera_dev, "timestamp", get_timestamp, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, camera_dev, "which",     get_which,     MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
