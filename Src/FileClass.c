// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Represent Files On A Filesystem
#include "Internal.h"
#include "File.c"

PRIVATE
mrb_value self_is_archive(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(IsPhysfsMounted());
}

PRIVATE
mrb_value self_set_write_dir(mrb_state *mrb, mrb_value self) {
    mrb_value   ex_path = {0};
    const char *in_path = NULL;
    int         status  = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = PHYSFS_setWriteDir(in_path);
    if(!status) {
        SetErrorPhysfs();
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    File      *file    = NULL;
    char      *in_path = NULL;
    mrb_value  ex_path = {0};
    mrb_int    mode    = 0;

    IGNORE_RETURN mrb_get_args(mrb, "Si", &ex_path, &mode);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    file    = OpenFile(in_path, mode);
    if(!file) {
        RaiseRuntimeError(mrb);
    }

    DATA_PTR(self) = file;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT copy;

    IGNORE_RETURN SDL_SetError("File cannot be copied");
    RaiseRuntimeError(mrb);

    return copy;
}

PRIVATE
mrb_value close(mrb_state *mrb, mrb_value self) {
    File *file   = DATA_PTR(self);
    bool  status = false;

    status = CloseFile(file);
    if(!status) {
        RaiseRuntimeError(mrb);
    }
    DATA_PTR(self) = NULL;

    return mrb_nil_value();
}

PRIVATE
mrb_value size(mrb_state *mrb, mrb_value self) {
    File *file = DATA_PTR(self);

    return mrb_int_value(mrb, GetFileSize(file));
}

PRIVATE
mrb_value read(mrb_state *mrb, mrb_value self) {
    File      *file = DATA_PTR(self);
    char      *buf  = NULL;
    mrb_int    size = 0;
    mrb_value  str  = {0};

    IGNORE_RETURN mrb_get_args(mrb, "|i", &size);

    if(size == 0) {
        size = GetFileSize(file);
        if(size == -1) {
            RaiseRuntimeError(mrb);
        }
    }

    buf  = mrb_calloc(mrb, size, sizeof(char));
    size = ReadFile(file, buf, size);
    if(size == -1) {
        RaiseRuntimeError(mrb);
    }

    str = mrb_str_new(mrb, buf, size);
    mrb_free(mrb, buf);

    return str;
}

PRIVATE
mrb_value write(mrb_state *mrb, mrb_value self) {
    File      *file = DATA_PTR(self);
    char      *buf  = NULL;
    mrb_int    size = -1;
    mrb_value  str  = {0};

    IGNORE_RETURN mrb_get_args(mrb, "S|i", &str, &size);

    buf = RSTRING_PTR(str);
    if(size == -1) {
        size = RSTRING_LEN(str);
    }

    size = WriteFile(file, buf, size);
    if(size == -1) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, size);
}

PRIVATE
mrb_value flush(mrb_state *mrb, mrb_value self) {
    File *file   = DATA_PTR(self);
    bool  status = FALSE;

    status = FlushFile(file);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value move_to(mrb_state *mrb, mrb_value self) {
    File    *file   = DATA_PTR(self);
    mrb_int  offset = 0;
    mrb_int  from   = 0;
    bool     status = false;

    IGNORE_RETURN mrb_get_args(mrb, "ii", &offset, &from);

    status = SeekFile(file, offset, from);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value position(mrb_state *mrb, mrb_value self) {
    File   *file   = DATA_PTR(self);
    Sint64  offset = 0;

    offset = TellFile(file);
    if(offset == -1) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, offset);
}

PRIVATE
mrb_value read_8(mrb_state *mrb, mrb_value self) {
    File  *file   = DATA_PTR(self);
    Sint8  val    = 0;
    bool   status = false;

    status = ReadFileS8(file, &val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, val);
}

PRIVATE
mrb_value read_16_be(mrb_state *mrb, mrb_value self) {
    File  *file   = DATA_PTR(self);
    Sint16 val    = 0;
    bool   status = false;

    status = ReadFileS16BE(file, &val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, val);
}

PRIVATE
mrb_value read_16_le(mrb_state *mrb, mrb_value self) {
    File  *file   = DATA_PTR(self);
    Sint16 val    = 0;
    bool   status = false;

    status = ReadFileS16LE(file, &val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, val);
}

PRIVATE
mrb_value read_32_be(mrb_state *mrb, mrb_value self) {
    File  *file   = DATA_PTR(self);
    Sint32 val    = 0;
    bool   status = false;

    status = ReadFileS32BE(file, &val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, val);
}

PRIVATE
mrb_value read_32_le(mrb_state *mrb, mrb_value self) {
    File  *file   = DATA_PTR(self);
    Sint32 val    = 0;
    bool   status = false;

    status = ReadFileS32LE(file, &val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, val);
}

PRIVATE
mrb_value read_64_be(mrb_state *mrb, mrb_value self) {
    File  *file   = DATA_PTR(self);
    Sint64 val    = 0;
    bool   status = false;

    status = ReadFileS64BE(file, &val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, val);
}

PRIVATE
mrb_value read_64_le(mrb_state *mrb, mrb_value self) {
    File  *file   = DATA_PTR(self);
    Sint64 val    = 0;
    bool   status = false;

    status = ReadFileS64LE(file, &val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, val);
}

PRIVATE
mrb_value write_8(mrb_state *mrb, mrb_value self) {
    File   *file   = DATA_PTR(self);
    mrb_int val    = 0;
    bool    status = false;

    IGNORE_RETURN mrb_get_args(mrb, "i", &val);

    status = WriteFileS8(file, (Sint8)val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value write_16_be(mrb_state *mrb, mrb_value self) {
    File   *file   = DATA_PTR(self);
    mrb_int val    = 0;
    bool    status = false;

    IGNORE_RETURN mrb_get_args(mrb, "i", &val);

    status = WriteFileS16BE(file, (Sint16)val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value write_16_le(mrb_state *mrb, mrb_value self) {
    File   *file   = DATA_PTR(self);
    mrb_int val    = 0;
    bool    status = false;

    IGNORE_RETURN mrb_get_args(mrb, "i", &val);

    status = WriteFileS16LE(file, (Sint16)val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value write_32_be(mrb_state *mrb, mrb_value self) {
    File   *file   = DATA_PTR(self);
    mrb_int val    = 0;
    bool    status = false;

    IGNORE_RETURN mrb_get_args(mrb, "i", &val);

    status = WriteFileS32BE(file, (Sint32)val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value write_32_le(mrb_state *mrb, mrb_value self) {
    File   *file   = DATA_PTR(self);
    mrb_int val    = 0;
    bool    status = false;

    IGNORE_RETURN mrb_get_args(mrb, "i", &val);

    status = WriteFileS32LE(file, (Sint32)val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value write_64_be(mrb_state *mrb, mrb_value self) {
    File   *file   = DATA_PTR(self);
    mrb_int val    = 0;
    bool    status = false;

    IGNORE_RETURN mrb_get_args(mrb, "i", &val);

    status = WriteFileS64LE(file, (Sint64)val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value write_64_le(mrb_state *mrb, mrb_value self) {
    File   *file   = DATA_PTR(self);
    mrb_int val    = 0;
    bool    status = false;

    IGNORE_RETURN mrb_get_args(mrb, "i", &val);

    status = WriteFileS64LE(file, (Sint64)val);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PUBLIC
void DefineFileClass(mrb_state *mrb) {
    struct RClass *file = NULL;

    SAVE_ARENA(mrb);

    file = mrb_define_class(mrb, "File", mrb->object_class);

    mrb_define_const(mrb, file, "MODE_READ",    mrb_int_value(mrb, FILE_MODE_READ));
    mrb_define_const(mrb, file, "MODE_WRITE",   mrb_int_value(mrb, FILE_MODE_WRITE));
    mrb_define_const(mrb, file, "MODE_APPEND",  mrb_int_value(mrb, FILE_MODE_APPEND));
    mrb_define_const(mrb, file, "FROM_START",   mrb_int_value(mrb, SDL_IO_SEEK_SET));
    mrb_define_const(mrb, file, "FROM_CURRENT", mrb_int_value(mrb, SDL_IO_SEEK_CUR));
    mrb_define_const(mrb, file, "FROM_END",     mrb_int_value(mrb, SDL_IO_SEEK_END));

    mrb_define_class_method(mrb, file, "is_archive?",   self_is_archive,    MRB_ARGS_NONE());
    mrb_define_class_method(mrb, file, "set_write_dir", self_set_write_dir, MRB_ARGS_REQ(1));

    mrb_define_method(mrb, file, "initialize",      initialize,      MRB_ARGS_REQ(2));
    mrb_define_method(mrb, file, "initialize_copy", initialize_copy, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, file, "close",           close,           MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "size",            size,            MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "read",            read,            MRB_ARGS_OPT(1));
    mrb_define_method(mrb, file, "write",           write,           MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
    mrb_define_method(mrb, file, "flush",           flush,           MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "move_to",         move_to,         MRB_ARGS_REQ(2));
    mrb_define_method(mrb, file, "position",        position,        MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "read_8",          read_8,          MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "read_16_be",      read_16_be,      MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "read_16_le",      read_16_le,      MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "read_32_be",      read_32_be,      MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "read_32_le",      read_32_le,      MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "read_64_be",      read_64_be,      MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "read_64_le",      read_64_le,      MRB_ARGS_NONE());
    mrb_define_method(mrb, file, "write_8",         write_8,         MRB_ARGS_REQ(1));
    mrb_define_method(mrb, file, "write_16_be",     write_16_be,     MRB_ARGS_REQ(1));
    mrb_define_method(mrb, file, "write_16_le",     write_16_le,     MRB_ARGS_REQ(1));
    mrb_define_method(mrb, file, "write_32_be",     write_32_be,     MRB_ARGS_REQ(1));
    mrb_define_method(mrb, file, "write_32_le",     write_32_le,     MRB_ARGS_REQ(1));
    mrb_define_method(mrb, file, "write_64_be",     write_64_be,     MRB_ARGS_REQ(1));
    mrb_define_method(mrb, file, "write_64_le",     write_64_le,     MRB_ARGS_REQ(1));

    mrb_define_alias(mrb, file, "length", "size");

    IGNORE_RETURN mrb_load_irep(mrb, File_symbol);

    RESTORE_ARENA(mrb);
}
