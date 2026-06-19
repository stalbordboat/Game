// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: File Status Utility Methods
#include "Internal.h"

PRIVATE
mrb_value does_exist(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    mrb_bool   status  = FALSE;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = DoesExistFileUtils(in_path);
    if(!status) {
        // We don't need to report an error here, we just need the status
        // of the file's existence.
        IGNORE_RETURN SDL_ClearError();
    }

    return mrb_bool_value(status);
}

PRIVATE
mrb_value is_file(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    mrb_bool   status  = FALSE;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = IsNormalFileUtils(in_path);

    return mrb_bool_value(status);
}

PRIVATE
mrb_value is_dir(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    mrb_bool   status  = FALSE;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = IsDirFileUtils(in_path);

    return mrb_bool_value(status);
}

PRIVATE
mrb_value is_other(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    mrb_bool   status  = FALSE;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = IsOtherFileUtils(in_path);

    return mrb_bool_value(status);
}

PRIVATE
mrb_value get_size(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    mrb_int    result  = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    result  = GetSizeFileUtils(in_path);

    return mrb_int_value(mrb, result);
}

PRIVATE
mrb_value create_time(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    mrb_int    result  = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    result  = CreateTimeFileUtils(in_path);

    return mrb_int_value(mrb, result);
}

PRIVATE
mrb_value modify_time(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    mrb_int    result  = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    result  = ModifyTimeFileUtils(in_path);

    return mrb_int_value(mrb, result);
}

PRIVATE
mrb_value access_time(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    mrb_int    result  = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    result  = AccessTimeFileUtils(in_path);

    return mrb_int_value(mrb, result);
}

PUBLIC
void DefineFileUtilsStatModule(mrb_state *mrb) {
    struct RClass *fileutils = NULL;
    struct RClass *stat      = NULL;

    SAVE_ARENA(mrb);

    fileutils = mrb_module_get(mrb, "FileUtils");
    stat      = mrb_define_module_under(mrb, fileutils, "Stat");

    mrb_define_module_function(mrb, stat, "exist?",      does_exist,  MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, stat, "file?",       is_file,     MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, stat, "dir?",        is_dir,      MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, stat, "other?",      is_other,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, stat, "size",        get_size,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, stat, "length",      get_size,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, stat, "create_time", create_time, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, stat, "modify_time", modify_time, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, stat, "access_time", access_time, MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}
