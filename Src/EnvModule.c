// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Getter/Setter Environment Variable Interface
#include "Internal.h"

PRIVATE SDL_Environment *private_env = NULL;

PRIVATE
mrb_value self_get(mrb_state *mrb, mrb_value self) {
    mrb_value   ex_name   = {0};
    mrb_value   ex_result = {0};
    char       *in_name   = NULL;
    const char *in_result = NULL;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_name);

    in_name   = mrb_str_to_cstr(mrb, ex_name);
    in_result = SDL_GetEnvironmentVariable(private_env, in_name);
    if(!in_result) {
        return mrb_nil_value();
    }

    ex_result = mrb_str_new_cstr(mrb, in_result);

    return ex_result;
}

PRIVATE
mrb_value self_set(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_name   = {0};
    mrb_value  ex_value  = {0};
    char      *in_name   = NULL;
    char      *in_value  = NULL;
    int        overwrite = 0;
    int        status    = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "SS", &ex_name, &ex_value);

    in_name  = mrb_str_to_cstr(mrb, ex_name);
    in_value = mrb_str_to_cstr(mrb, ex_value);

    status = SDL_SetEnvironmentVariable(private_env, in_name, in_value, overwrite);
    if(status == -1) {
        IGNORE_RETURN SDL_SetError("Failed to set evironment variable %s", in_name);
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        IGNORE_RETURN SDL_ClearError();
        return mrb_nil_value();
    }

    return ex_value;
}

PUBLIC
void DefineEnvModule(mrb_state *mrb, SDL_Environment *env) {
    struct RClass *ex_env = NULL;

    private_env = env;

    SAVE_ARENA(mrb);

    ex_env = mrb_define_module(mrb, "Env");

    mrb_define_module_function(mrb, ex_env, "[]",  self_get, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, ex_env, "[]=", self_set, MRB_ARGS_REQ(2));

    RESTORE_ARENA(mrb);
}
