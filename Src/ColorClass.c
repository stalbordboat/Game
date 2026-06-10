// MIT LICENSE - Copyright (c) Ralph Desir 2025
#include "Internal.h"

PRIVATE
void color_dispose(mrb_state *mrb, Buffer *color) {
    mrb_free(mrb, color);
}

PRIVATE struct mrb_data_type color_data = { "Color", color_dispose };

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = NULL;
    mrb_int    r     = 255;
    mrb_int    g     = 255;
    mrb_int    b     = 255;
    mrb_int    a     = 255;

    IGNORE_RETURN mrb_get_args(mrb, "|iiii", &r, &g, &b, &a);

    color = mrb_calloc(mrb, 1, sizeof(SDL_Color));

    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;

    DATA_PTR(self)  = color;
    DATA_TYPE(self) = &color_data;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    mrb_value  orig = {0};
    SDL_Color *src  = NULL;
    SDL_Color *dest = NULL;

    IGNORE_RETURN mrb_get_args(mrb, "o", &orig);

    src   = DATA_PTR(orig);
    dest  = mrb_calloc(mrb, 1, sizeof(SDL_Color));
    *dest = *src;

    DATA_PTR(copy)  = dest;
    DATA_TYPE(copy) = DATA_TYPE(orig);

    return copy;
}

PRIVATE
mrb_value get_r(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = DATA_PTR(self);

    return mrb_int_value(mrb, color->r);
}

PRIVATE
mrb_value get_g(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = DATA_PTR(self);

    return mrb_int_value(mrb, color->g);
}

PRIVATE
mrb_value get_b(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = DATA_PTR(self);

    return mrb_int_value(mrb, color->b);
}

PRIVATE
mrb_value get_a(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = DATA_PTR(self);

    return mrb_int_value(mrb, color->a);
}

PRIVATE
mrb_value set_r(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = DATA_PTR(self);
    mrb_int    r     = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &r);

    color->r = r;

    return mrb_int_value(mrb, color->r);
}

PRIVATE
mrb_value set_g(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = DATA_PTR(self);
    mrb_int    g     = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &g);

    color->g = g;

    return mrb_int_value(mrb, color->g);
}

PRIVATE
mrb_value set_b(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = DATA_PTR(self);
    mrb_int    b     = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &b);

    color->b = b;

    return mrb_int_value(mrb, color->b);
}

PRIVATE
mrb_value set_a(mrb_state *mrb, mrb_value self) {
    SDL_Color *color = DATA_PTR(self);
    mrb_int    a     = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &a);

    color->a = a;

    return mrb_int_value(mrb, color->a);
}

PUBLIC
void DefineColorClass(mrb_state *mrb) {
    struct RClass *color = NULL;

    SAVE_ARENA(mrb);

    color = mrb_define_class(mrb, "Color", mrb->object_class);
    SET_INSTANCE_TYPE(color);

    mrb_define_method(mrb, color, "initialize",      initialize,      MRB_ARGS_OPT(4));
    mrb_define_method(mrb, color, "initialize_copy", initialize_copy, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, color, "red",             get_r,           MRB_ARGS_NONE());
    mrb_define_method(mrb, color, "green",           get_g,           MRB_ARGS_NONE());
    mrb_define_method(mrb, color, "blue",            get_b,           MRB_ARGS_NONE());
    mrb_define_method(mrb, color, "alpha",           get_a,           MRB_ARGS_NONE());
    mrb_define_method(mrb, color, "red=",            set_r,           MRB_ARGS_REQ(1));
    mrb_define_method(mrb, color, "green=",          set_g,           MRB_ARGS_REQ(1));
    mrb_define_method(mrb, color, "blue=",           set_b,           MRB_ARGS_REQ(1));
    mrb_define_method(mrb, color, "alpha=",          set_a,           MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}
