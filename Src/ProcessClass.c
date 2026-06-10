// MIT LICENSE - Copyright (c) Ralph Desir 2025
#include "Internal.h"

PRIVATE
mrb_value self_open(mrb_state *mrb, mrb_value self) {
    struct RClass *process = NULL;
    mrb_value      argv[2] = {0};
    mrb_value      args    = {0};
    mrb_bool       pipe    = FALSE;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "A|b", &args, &pipe);

    process = mrb_class_get(mrb, "Process");
    argv[0] = args;
    argv[1] = mrb_bool_value(pipe);

    return mrb_obj_new(mrb, process, 2, argv);
}

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    char       **in_args     = NULL;
    SDL_Process *process     = NULL;
    mrb_value    ex_args     = {0};
    mrb_bool     ex_pipe     = FALSE;
    mrb_int      ex_ary_size = 0;
    mrb_value    val         = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "A|b", &ex_args, &ex_pipe);

    ex_ary_size = RARRAY_LEN(ex_args);
    in_args     = mrb_calloc(mrb, ex_ary_size + 1, sizeof(char *));

    for(int i = 0;i < ex_ary_size;++i) {
        val        = mrb_ary_entry(ex_args, i);
        in_args[i] = mrb_str_to_cstr(mrb, val);
    }

    process = SDL_CreateProcess((const char **)in_args, ex_pipe);
    if(!process) {
        RaiseRuntimeError(mrb);
    }

    mrb_free(mrb, in_args);

    DATA_PTR(self) = process;

    return self;
}

PRIVATE
mrb_value close(mrb_state *mrb, mrb_value self) {
    SDL_Process *process = DATA_PTR(self);

    UNUSED_ARGUMENT mrb;

    SDL_DestroyProcess(process);
    DATA_PTR(self) = NULL;

    return mrb_nil_value();
}

PRIVATE
mrb_value end(mrb_state *mrb, mrb_value self) {
    SDL_Process *process = DATA_PTR(self);
    mrb_bool    force    = TRUE;
    bool        status   = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "|b", &force);

    status = SDL_KillProcess(process, force);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value read(mrb_state *mrb, mrb_value self) {
    SDL_Process *process  = DATA_PTR(self);
    size_t       datasize = 0;
    int          exitcode = 0;
    Buffer      *out      = NULL;
    mrb_sym      sym      = 0;
    mrb_value    val      = {0};

    out = SDL_ReadProcess(process, &datasize, &exitcode);
    if(!out) {
        RaiseRuntimeError(mrb);
    }

    sym = mrb_intern_lit(mrb, "@exit_code");
    val = mrb_int_value(mrb, exitcode);
    mrb_iv_set(mrb, self, sym, val);

    return mrb_str_new(mrb, (const char *)out, (mrb_int)datasize);
}

PRIVATE
mrb_value exit_code(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@exit_code"));
}

PRIVATE
mrb_value wait(mrb_state *mrb, mrb_value self) {
    SDL_Process *process = DATA_PTR(self);
    mrb_bool    block    = TRUE;
    mrb_bool    status   = TRUE;
    int         exitcode = 0;
    mrb_sym     sym      = 0;
    mrb_value   val      = {0};

    IGNORE_RETURN mrb_get_args(mrb, "|b", &block);

    status = SDL_WaitProcess(process, block, &exitcode);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    sym = mrb_intern_lit(mrb, "@exit_code");
    val = mrb_int_value(mrb, exitcode);
    mrb_iv_set(mrb, self, sym, val);

    return mrb_nil_value();
}

PUBLIC
void DefineProcessClass(mrb_state *mrb) {
    struct RClass *process = NULL;

    SAVE_ARENA(mrb);

    process = mrb_define_class(mrb, "Process", mrb->object_class);

    mrb_define_class_method(mrb, process, "open", self_open, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));

    mrb_define_method(mrb, process, "initialize", initialize, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
    mrb_define_method(mrb, process, "close",      close,      MRB_ARGS_NONE());
    mrb_define_method(mrb, process, "end",        end,        MRB_ARGS_OPT(1));
    mrb_define_method(mrb, process, "read",       read,       MRB_ARGS_NONE());
    mrb_define_method(mrb, process, "exit_code",  exit_code,  MRB_ARGS_NONE());
    mrb_define_method(mrb, process, "wait",       wait,       MRB_ARGS_OPT(1));

    RESTORE_ARENA(mrb);
}
