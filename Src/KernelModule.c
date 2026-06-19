// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Kernel Namespace Methods
#include "Internal.h"
#include "Kernel.c"

PRIVATE
mrb_value assert_true(mrb_state *mrb, mrb_value self) {
    mrb_value label   = {0};
    mrb_value value_a = {0};
    mrb_value value_b = {0};
    mrb_value value_c = {0};
    mrb_bool  cond    = FALSE;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "Soo", &label, &value_a, &value_b);

    value_c = mrb_funcall(mrb, value_a, "eql?", 1, value_b);
    cond    = mrb_bool(value_c);
    if(!cond) {
        IGNORE_RETURN SDL_SetError("FAILED TEST: %s", mrb_str_to_cstr(mrb, label));
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value kernel_absolute_path(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path        = {0};
    char      *in_path        = NULL;
    char      *status         = NULL;
    char       resv[PATH_MAX] = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = AbsolutePath(in_path, resv);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_str_new_cstr(mrb, resv);
}

PRIVATE
mrb_value mrb_load(mrb_state *mrb, mrb_value self) {
    mrb_value   ex_path = {0};
    char       *in_path = NULL;
    char       *script  = NULL;
    BufferSize  size    = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    script  = GetFileBuffer(in_path, &size);
    if(!script) {
        RaiseRuntimeError(mrb);
    }

    if(HasExtname(in_path, ".rb")) {
        IGNORE_RETURN mrb_load_string(mrb, script);
    }
    else {
        IGNORE_RETURN mrb_load_irep_buf(mrb, script, size);
    }

    FreeBuffer(script);

    return mrb_nil_value();
}

PRIVATE
mrb_value native_load_basic(mrb_state *mrb, mrb_value self) {
    bool       status  = false;
    mrb_value  ex_path = {0};
    char      *in_path = NULL;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = NativeLoadBasic(mrb, in_path);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value open_url(mrb_state *mrb, mrb_value self) {
    mrb_value   ex_url = {0};
    const char *in_url = NULL;
    bool        status = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_url);

    in_url = mrb_str_to_cstr(mrb, ex_url);
    status = SDL_OpenURL(in_url);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value get_argv_ary(mrb_state *mrb, int argc, char **argv) {
    mrb_value ary = {0};
    mrb_value val = {0};

    ary = mrb_ary_new_capa(mrb, argc);

    for(int i = 1;i < argc;++i) {
        val = mrb_str_new_cstr(mrb, argv[i]);
        mrb_ary_push(mrb, ary, val);
    }

    return ary;
}

PUBLIC
void ExtendKernelModule(mrb_state *mrb, int argc, char *argv[]) {
    struct RClass *kernel = mrb->kernel_module;

    SAVE_ARENA(mrb);

    mrb_define_const(mrb, kernel, "EXECUTABLE_NAME",       mrb_str_new_cstr(mrb, *argv));
    mrb_define_const(mrb, kernel, "ARGV",                  get_argv_ary    (mrb, argc, argv));
    mrb_define_const(mrb, kernel, "MAJOR",                 mrb_str_new_cstr(mrb, GAME_MAJOR_VERSION));
    mrb_define_const(mrb, kernel, "MINOR",                 mrb_str_new_cstr(mrb, GAME_MINOR_VERSION));
    mrb_define_const(mrb, kernel, "PATCH",                 mrb_str_new_cstr(mrb, GAME_PATCH_VERSION));
    mrb_define_const(mrb, kernel, "RELEASE_TYPE",          mrb_str_new_cstr(mrb, GAME_RELEASE_TYPE));
    mrb_define_const(mrb, kernel, "COPYRIGHT",             mrb_str_new_cstr(mrb, GAME_COPYRIGHT));
    mrb_define_const(mrb, kernel, "PLATFORM",              mrb_str_new_cstr(mrb, GAME_PLATFORM));
    mrb_define_const(mrb, kernel, "DEFAULT_WINDOW_WIDTH",  mrb_int_value   (mrb, DEFAULT_WINDOW_WIDTH));
    mrb_define_const(mrb, kernel, "DEFAULT_WINDOW_HEIGHT", mrb_int_value   (mrb, DEFAULT_WINDOW_HEIGHT));
    mrb_define_const(mrb, kernel, "NATIVE_LOAD_COUNT_MAX", mrb_int_value   (mrb, NATIVE_LOAD_COUNT_MAX));

    mrb_define_method(mrb, kernel, "assert_true",       assert_true,          MRB_ARGS_REQ(3));
    mrb_define_method(mrb, kernel, "absolute_path",     kernel_absolute_path, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, kernel, "mrb_load",          mrb_load,             MRB_ARGS_REQ(1));
    mrb_define_method(mrb, kernel, "native_load_basic", native_load_basic,    MRB_ARGS_REQ(1));
    mrb_define_method(mrb, kernel, "open_url",          open_url,             MRB_ARGS_REQ(1));

    IGNORE_RETURN mrb_load_irep(mrb, Kernel_symbol);

    RESTORE_ARENA(mrb);
}
