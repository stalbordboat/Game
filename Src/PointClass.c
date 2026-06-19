// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Represents 2D Positional Data
#include "Internal.h"

PRIVATE
void point_dispose(mrb_state *mrb, Buffer *point) {
    mrb_free(mrb, point);
}

PRIVATE struct mrb_data_type point_data = { "Point", point_dispose };

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    SDL_FPoint *point = NULL;
    mrb_float   x     = 0.0;
    mrb_float   y     = 0.0;

    IGNORE_RETURN mrb_get_args(mrb, "|ff", &x, &y);

    point = mrb_calloc(mrb, 1, sizeof(SDL_FPoint));

    point->x = x;
    point->y = y;

    DATA_PTR(self)  = point;
    DATA_TYPE(self) = &point_data;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    mrb_value   orig = {0};
    SDL_FPoint *src  = NULL;
    SDL_FPoint *dest = NULL;

    IGNORE_RETURN mrb_get_args(mrb, "o", &orig);

    src   = DATA_PTR(orig);
    dest  = mrb_calloc(mrb, 1, sizeof(SDL_FPoint));
    *dest = *src;

    DATA_PTR(copy)  = dest;
    DATA_TYPE(copy) = DATA_TYPE(orig);

    return copy;
}

PRIVATE
mrb_value get_x(mrb_state *mrb, mrb_value self) {
    SDL_FPoint *point = DATA_PTR(self);

    return mrb_float_value(mrb, point->x);
}

PRIVATE
mrb_value get_y(mrb_state *mrb, mrb_value self) {
    SDL_FPoint *point = DATA_PTR(self);

    return mrb_float_value(mrb, point->y);
}

PRIVATE
mrb_value set_x(mrb_state *mrb, mrb_value self) {
    SDL_FPoint *point = DATA_PTR(self);
    mrb_float   x     = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &x);

    point->x = x;

    return mrb_float_value(mrb, point->x);
}

PRIVATE
mrb_value set_y(mrb_state *mrb, mrb_value self) {
    SDL_FPoint *point = DATA_PTR(self);
    mrb_float   y     = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &y);

    point->y = y;

    return mrb_float_value(mrb, point->y);
}

PUBLIC
void DefinePointClass(mrb_state *mrb) {
    struct RClass *point = NULL;

    SAVE_ARENA(mrb);

    point = mrb_define_class(mrb, "Point", mrb->object_class);
    SET_INSTANCE_TYPE(point);

    mrb_define_method(mrb, point, "initialize",      initialize,      MRB_ARGS_OPT(2));
    mrb_define_method(mrb, point, "initialize_copy", initialize_copy, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, point, "x",               get_x,           MRB_ARGS_NONE());
    mrb_define_method(mrb, point, "y",               get_y,           MRB_ARGS_NONE());
    mrb_define_method(mrb, point, "x=",              set_x,           MRB_ARGS_REQ(1));
    mrb_define_method(mrb, point, "y=",              set_y,           MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}

