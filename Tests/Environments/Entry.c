// MIT LICENSE - Copyright (c) 2025 Ralph St.Albord
// Description: Native Entry Point
#include "Native/Native.h"

PRIVATE SDL_Window   *private_window   = NULL;
PRIVATE SDL_Renderer *private_renderer = NULL;
PRIVATE SDL_Event    *private_event    = NULL;

PRIVATE
mrb_value is_native_test(mrb_state *mrb, mrb_value self) {
    if(!private_window) {
        return mrb_false_value();
    }

    if(!private_renderer) {
        return mrb_false_value();
    }

    if(!private_event) {
        return mrb_false_value();
    }

    return mrb_true_value();
}

PUBLIC
bool NativeEntryPoint(mrb_state *mrb, SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event) {
    private_window   = window;
    private_renderer = renderer;
    private_event    = event;

    mrb_define_method(mrb, mrb->kernel_module, "native_test?", is_native_test, MRB_ARGS_NONE());

    return true;
}

PUBLIC
void NativeExitPoint(mrb_state *mrb) {
}
