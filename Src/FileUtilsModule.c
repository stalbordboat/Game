// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: File Utility Methods
#include "Internal.h"

PRIVATE
mrb_value entries(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path     = {0};
    mrb_value  ex_pattern  = mrb_str_new_lit(mrb, "*");
    char      *in_path     = NULL;
    char      *in_pattern  = NULL;
    char      **in_entries = NULL;
    int         count      = 0;
    mrb_value   ex_entries = {0};
    mrb_value   val        = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S|S", &ex_path, &ex_pattern);

    in_path    = mrb_str_to_cstr(mrb, ex_path);
    in_pattern = mrb_str_to_cstr(mrb, ex_pattern);
    in_entries = EntriesFileUtils(in_path, in_pattern, &count);
    if(!in_entries) {
        RaiseRuntimeError(mrb);
    }

    SAVE_ARENA(mrb);

    ex_entries = mrb_ary_new_capa(mrb, count);

    for(int i = 0;i < count;++i) {
        SAVE_ARENA(mrb);
        val = mrb_str_new_cstr(mrb, in_entries[i]);
        mrb_ary_push(mrb, ex_entries, val);
        RESTORE_ARENA(mrb);
    }

    RESTORE_ARENA(mrb);

    FreeBuffer(in_entries);

    return ex_entries;
}

PRIVATE
mrb_value copy(mrb_state *mrb, mrb_value self) {
    bool       status  = false;
    mrb_value  ex_src  = {0};
    mrb_value  ex_dest = {0};
    char      *in_src  = NULL;
    char      *in_dest = NULL;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "SS", &ex_src, &ex_dest);

    in_src  = mrb_str_to_cstr(mrb, ex_src);
    in_dest = mrb_str_to_cstr(mrb, ex_dest);
    status  = SDL_CopyFile(in_src, in_dest);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value make_directory(mrb_state *mrb, mrb_value self) {
    bool       status  = false;
    mrb_value  ex_path = {0};
    char      *in_path = NULL;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = SDL_CreateDirectory(in_path);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value base_path(mrb_state *mrb, mrb_value self) {
    const char *path = NULL;
    size_t      len  = 0;

    UNUSED_ARGUMENT self;

    path = SDL_GetBasePath();
    len  = SDL_strlen(path);

    return mrb_str_new_static(mrb, path, len);
}

PRIVATE
mrb_value current_directory(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_cwd = {0};
    char      *in_cwd = NULL;

    UNUSED_ARGUMENT self;

    in_cwd = SDL_GetCurrentDirectory();
    if(!in_cwd) {
        RaiseRuntimeError(mrb);
    }
    ex_cwd = mrb_str_new_cstr(mrb, in_cwd);

    FreeBuffer(in_cwd);

    return ex_cwd;
}

PRIVATE
mrb_value pref_path(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_org  = {0};
    mrb_value  ex_app  = {0};
    char      *in_org  = NULL;
    char      *in_app  = NULL;
    char      *in_path = NULL;
    mrb_value  ex_path = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "SS", &ex_org, &ex_app);

    in_org  = mrb_str_to_cstr(mrb, ex_org);
    in_app  = mrb_str_to_cstr(mrb, ex_app);
    in_path = SDL_GetPrefPath(in_org, in_app);
    if(!in_path) {
        // I'm assuming SDL sets the error(because they usually do), although that's not
        // stated in the docs:
        // https://wiki.libsdl.org/SDL3/SDL_GetPrefPath.
        RaiseRuntimeError(mrb);
    }
    ex_path = mrb_str_new_cstr(mrb, in_path);

    FreeBuffer(in_path);

    return ex_path;
}

PRIVATE
mrb_value user_directory(mrb_state *mrb, mrb_value self) {
    mrb_int     dir  = 0;
    const char *path = NULL;
    size_t      len  = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i", &dir);

    path = SDL_GetUserFolder(dir);
    if(!path) {
        // I'm assuming SDL sets the error(because they usually do), although that's not
        // stated in the docs:
        // https://wiki.libsdl.org/SDL3/SDL_GetPrefPath.
        RaiseRuntimeError(mrb);
    }
    len  = SDL_strlen(path);

    return mrb_str_new_static(mrb, path, len);
}

PRIVATE
mrb_value remove_path(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    bool       status  = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = SDL_RemovePath(in_path);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value rename_path(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_src  = {0};
    mrb_value  ex_dest = {0};
    char      *in_src  = NULL;
    char      *in_dest = NULL;
    bool       status  = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "SS", &ex_src, &ex_dest);

    in_src  = mrb_str_to_cstr(mrb, ex_src);
    in_dest = mrb_str_to_cstr(mrb, ex_dest);
    status  = SDL_RenamePath(in_src, in_dest);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value touch(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_path = {0};
    char      *in_path = NULL;
    File      *file    = NULL;
    bool       status  = false;
    int        mode    = -1;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = DoesExistFileUtils(in_path);
    if(status) {
        mode = FILE_MODE_READ;
    }
    else {
        mode = FILE_MODE_WRITE;
        // We can disregard the error this time.
        IGNORE_RETURN SDL_ClearError();
    }

    file    = OpenFile(in_path, mode);
    if(!file) {
        RaiseRuntimeError(mrb);
    }

    status = CloseFile(file);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PUBLIC
void DefineFileUtilsModule(mrb_state *mrb) {
    struct RClass *fileutils = NULL;

    SAVE_ARENA(mrb);

    fileutils = mrb_define_module(mrb, "FileUtils");

    mrb_define_const(mrb, fileutils, "DIR_HOME",        mrb_int_value(mrb, SDL_FOLDER_HOME));
    mrb_define_const(mrb, fileutils, "DIR_DESKTOP",     mrb_int_value(mrb, SDL_FOLDER_DESKTOP));
    mrb_define_const(mrb, fileutils, "DIR_DOCUMENTS",   mrb_int_value(mrb, SDL_FOLDER_DOCUMENTS));
    mrb_define_const(mrb, fileutils, "DIR_DOWNLOADS",   mrb_int_value(mrb, SDL_FOLDER_DOWNLOADS));
    mrb_define_const(mrb, fileutils, "DIR_MUSIC",       mrb_int_value(mrb, SDL_FOLDER_MUSIC));
    mrb_define_const(mrb, fileutils, "DIR_PICTURES",    mrb_int_value(mrb, SDL_FOLDER_PICTURES));
    mrb_define_const(mrb, fileutils, "DIR_PUBLICSHARE", mrb_int_value(mrb, SDL_FOLDER_PUBLICSHARE));
    mrb_define_const(mrb, fileutils, "DIR_SAVEDGAMES",  mrb_int_value(mrb, SDL_FOLDER_SAVEDGAMES));
    mrb_define_const(mrb, fileutils, "DIR_SCREENSHOTS", mrb_int_value(mrb, SDL_FOLDER_SCREENSHOTS));
    mrb_define_const(mrb, fileutils, "DIR_TEMPLATES",   mrb_int_value(mrb, SDL_FOLDER_TEMPLATES));
    mrb_define_const(mrb, fileutils, "DIR_VIDEOS",      mrb_int_value(mrb, SDL_FOLDER_VIDEOS));

    mrb_define_module_function(mrb, fileutils, "entries",           entries,           MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, fileutils, "copy",              copy,              MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, fileutils, "make_directory",    make_directory,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, fileutils, "base_path",         base_path,         MRB_ARGS_NONE());
    mrb_define_module_function(mrb, fileutils, "current_directory", current_directory, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, fileutils, "pref_path",         pref_path,         MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, fileutils, "user_directory",    user_directory,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, fileutils, "remove",            remove_path,       MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, fileutils, "rename_path",       rename_path,       MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, fileutils, "move",              rename_path,       MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, fileutils, "touch",             touch,             MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}
