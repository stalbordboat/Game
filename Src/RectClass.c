// MIT LICENSE - Copyright (c) Ralph Desir 2025
#include "Internal.h"

PRIVATE
void rect_dispose(mrb_state *mrb, Buffer *rect) {
    mrb_free(mrb, rect);
}

PRIVATE struct mrb_data_type rect_data = { "Rect", rect_dispose };

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = NULL;
    mrb_float  x    = 0.0;
    mrb_float  y    = 0.0;
    mrb_float  w    = 0.0;
    mrb_float  h    = 0.0;

    IGNORE_RETURN mrb_get_args(mrb, "|f|f|f|f", &x, &y, &w, &h);

    rect = mrb_calloc(mrb, 1, sizeof(SDL_FRect));

    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    DATA_PTR(self)  = rect;
    DATA_TYPE(self) = &rect_data;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    mrb_value  orig = {0};
    SDL_FRect *src  = NULL;
    SDL_FRect *dest = NULL;

    IGNORE_RETURN mrb_get_args(mrb, "o", &orig);

    src   = DATA_PTR(orig);
    dest  = mrb_calloc(mrb, 1, sizeof(SDL_FRect));
    *dest = *src;

    DATA_PTR(copy)  = dest;
    DATA_TYPE(copy) = DATA_TYPE(orig);

    return copy;
}

PRIVATE
mrb_value get_x(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = DATA_PTR(self);

    return mrb_float_value(mrb, rect->x);
}

PRIVATE
mrb_value get_y(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = DATA_PTR(self);

    return mrb_float_value(mrb, rect->y);
}

PRIVATE
mrb_value get_w(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = DATA_PTR(self);

    return mrb_float_value(mrb, rect->w);
}

PRIVATE
mrb_value get_h(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = DATA_PTR(self);

    return mrb_float_value(mrb, rect->h);
}

PRIVATE
mrb_value set_x(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = DATA_PTR(self);
    mrb_float  x    = 0.0;

    IGNORE_RETURN mrb_get_args(mrb, "f", &x);

    rect->x = x;

    return mrb_float_value(mrb, rect->x);
}

PRIVATE
mrb_value set_y(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = DATA_PTR(self);
    mrb_float  y    = 0.0;

    IGNORE_RETURN mrb_get_args(mrb, "f", &y);

    rect->y = y;

    return mrb_float_value(mrb, rect->y);
}

PRIVATE
mrb_value set_w(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = DATA_PTR(self);
    mrb_float  w    = 0.0;

    IGNORE_RETURN mrb_get_args(mrb, "f", &w);

    rect->w = w;

    return mrb_float_value(mrb, rect->w);
}


PRIVATE
mrb_value set_h(mrb_state *mrb, mrb_value self) {
    SDL_FRect *rect = DATA_PTR(self);
    mrb_float  h    = 0.0;

    IGNORE_RETURN mrb_get_args(mrb, "f", &h);

    rect->h = h;

    return mrb_float_value(mrb, rect->h);
}

PUBLIC
void DefineRectClass(mrb_state *mrb) {
    struct RClass *rect = NULL;

    SAVE_ARENA(mrb);

    rect = mrb_define_class(mrb, "Rect", mrb->object_class);
    SET_INSTANCE_TYPE(rect);

    mrb_define_method(mrb, rect, "initialize",      initialize,      MRB_ARGS_OPT(4));
    mrb_define_method(mrb, rect, "initialize_copy", initialize_copy, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rect, "x",               get_x,           MRB_ARGS_NONE());
    mrb_define_method(mrb, rect, "y",               get_y,           MRB_ARGS_NONE());
    mrb_define_method(mrb, rect, "width",           get_w,           MRB_ARGS_NONE());
    mrb_define_method(mrb, rect, "height",          get_h,           MRB_ARGS_NONE());
    mrb_define_method(mrb, rect, "x=",              set_x,           MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rect, "y=",              set_y,           MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rect, "width=",          set_w,           MRB_ARGS_REQ(1));
    mrb_define_method(mrb, rect, "height=",         set_h,           MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}
