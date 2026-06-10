// MIT LICENSE - Copyright (c) Ralph Desir 2025
#include "Internal.h"
#include "Timer.c"

PRIVATE
mrb_value self_delay(mrb_state *mrb, mrb_value self) {
    mrb_int ms = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i", &ms);

    SDL_Delay(ms);

    return mrb_nil_value();
}

PRIVATE
mrb_value self_ticks(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, SDL_GetTicks());
}

PRIVATE
mrb_value self_counter(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, SDL_GetPerformanceCounter());
}

PRIVATE
mrb_value self_frequency(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, SDL_GetPerformanceFrequency());
}

PUBLIC
void DefineTimerClass(mrb_state *mrb) {
    struct RClass *timer = NULL;

    SAVE_ARENA(mrb);

    timer = mrb_define_class(mrb, "Timer", mrb->object_class);

    mrb_define_class_method(mrb, timer, "wait",      self_delay,     MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, timer, "ticks",     self_ticks,     MRB_ARGS_NONE());
    mrb_define_class_method(mrb, timer, "counter",   self_counter,   MRB_ARGS_NONE());
    mrb_define_class_method(mrb, timer, "frequency", self_frequency, MRB_ARGS_NONE());

    IGNORE_RETURN mrb_load_irep(mrb, Timer_symbol);

    RESTORE_ARENA(mrb);
}
