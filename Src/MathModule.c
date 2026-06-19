// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: General Mathematical Functions
#include "Internal.h"

#define PI 3.14159265358979323846264338327950288
#define E  2.718281828459045

PRIVATE
mrb_value math_acos(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_acos(val));
}

PRIVATE
mrb_value math_asin(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_asin(val));
}

PRIVATE
mrb_value math_atan(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_atan(val));
}

PRIVATE
mrb_value math_atan2(mrb_state *mrb, mrb_value self) {
    mrb_float val1 = 0.0;
    mrb_float val2 = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "ff", &val1, &val2);

    return mrb_float_value(mrb, SDL_atan2(val1, val2));
}

PRIVATE
mrb_value math_ceil(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_ceil(val));
}

PRIVATE
mrb_value math_cos(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_cos(val));
}

PRIVATE
mrb_value math_exp(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_exp(val));
}

PRIVATE
mrb_value math_fabs(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_fabs(val));
}

PRIVATE
mrb_value math_floor(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_floor(val));
}

PRIVATE
mrb_value math_trunc(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_trunc(val));
}

PRIVATE
mrb_value math_fmod(mrb_state *mrb, mrb_value self) {
    mrb_float x = 0;
    mrb_float y = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "ff", &x, &y);

    return mrb_float_value(mrb, SDL_fmod(x, y));
}

PRIVATE
mrb_value math_log(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_log(val));
}

PRIVATE
mrb_value math_log10(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_log10(val));
}

PRIVATE
mrb_value math_pow(mrb_state *mrb, mrb_value self) {
    mrb_float x = 0;
    mrb_float y = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "ff", &x, &y);

    return mrb_float_value(mrb, SDL_pow(x, y));
}

PRIVATE
mrb_value math_round(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_round(val));
}

PRIVATE
mrb_value math_lround(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_int_value(mrb, SDL_lround(val));
}

PRIVATE
mrb_value math_sin(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_sin(val));
}

PRIVATE
mrb_value math_sqrt(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_sqrt(val));
}

PRIVATE
mrb_value math_tan(mrb_state *mrb, mrb_value self) {
    mrb_float val = 0.0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "f", &val);

    return mrb_float_value(mrb, SDL_tan(val));
}

PRIVATE
mrb_value math_abs(mrb_state *mrb, mrb_value self) {
    mrb_int val = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i", &val);

    val = SDL_abs(val);

    return mrb_int_value(mrb, val);
}

PUBLIC
void DefineMathModule(mrb_state *mrb) {
    struct RClass *math = NULL;

    SAVE_ARENA(mrb);

    math = mrb_define_module(mrb, "Math");

    mrb_define_const(mrb, math, "PI", mrb_float_value(mrb, PI));
    mrb_define_const(mrb, math, "E",  mrb_float_value(mrb, E));

    mrb_define_module_function(mrb, math, "acos",   math_acos,   MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "asin",   math_asin,   MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "atan",   math_atan,   MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "atan2",  math_atan2,  MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, math, "ceil",   math_ceil,   MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "cos",    math_cos,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "exp",    math_exp,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "fabs",   math_fabs,   MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "floor",  math_floor,  MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "trunc",  math_trunc,  MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "fmod",   math_fmod,   MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, math, "log",    math_log,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "log10",  math_log10,  MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "pow",    math_pow,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "round",  math_round,  MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "lround", math_lround, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "sin",    math_sin,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "sqrt",   math_sqrt,   MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "tan",    math_tan,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, math, "abs",    math_abs,    MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}
