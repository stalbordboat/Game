// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Utility Methods For Logging 
#include "Internal.h"

PRIVATE
char *get_log_msg(mrb_state *mrb, mrb_value self) {
    mrb_int    argc = 0;
    mrb_value *argv = NULL;
    mrb_value  ary  = {0};
    mrb_value  val  = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "*", &argv, &argc);

    ary = mrb_ary_new_capa(mrb, argc);

    for(int i = 0;i < argc;++i) {
        val = mrb_obj_as_string(mrb, argv[i]);
        mrb_ary_push(mrb, ary, val);
    }

    val = mrb_str_new_lit(mrb, " ");
    val = mrb_ary_join(mrb, ary, val);

    return RSTRING_PTR(val);
}

PRIVATE
mrb_value self_info(mrb_state *mrb, mrb_value self) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", get_log_msg(mrb, self));

    return mrb_nil_value();
}

PRIVATE
mrb_value self_warn(mrb_state *mrb, mrb_value self) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", get_log_msg(mrb, self));

    return mrb_nil_value();
}

PRIVATE
mrb_value self_error(mrb_state *mrb, mrb_value self) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", get_log_msg(mrb, self));

    return mrb_nil_value();
}

PUBLIC
void DefineLogModule(mrb_state *mrb) {
    struct RClass *log = NULL;

    SAVE_ARENA(mrb);

    log = mrb_define_module(mrb, "Log");

    mrb_define_module_function(mrb, log, "info",  self_info,  MRB_ARGS_REST());
    mrb_define_module_function(mrb, log, "warn",  self_warn,  MRB_ARGS_REST());
    mrb_define_module_function(mrb, log, "error", self_error, MRB_ARGS_REST());

    RESTORE_ARENA(mrb);
}
