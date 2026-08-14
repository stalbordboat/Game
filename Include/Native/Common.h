// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Common.h - A header for frequently used identifiers.
#ifndef COMMON_H
#define COMMON_H

#include "Platform.h"
#include <SDL3/SDL.h>
#include <physfs.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/irep.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/hash.h>

#define GAME_MAJOR_VERSION "0"
#define GAME_MINOR_VERSION "3"
#define GAME_PATCH_VERSION "0"
#define GAME_RELEASE_TYPE  ""
#define GAME_COPYRIGHT     "MIT LICENSE - Copyright (c) 2026 Ralph St.Albord"

#define PRIVATE static
#define PUBLIC  extern

#define UNUSED_ARGUMENT (void)
#define IGNORE_RETURN   (void)

#define SAVE_ARENA(mrb)    int arena_idx = mrb_gc_arena_save(mrb)
#define RESTORE_ARENA(mrb) mrb_gc_arena_restore(mrb, arena_idx)

#define SET_INSTANCE_TYPE(klass) MRB_SET_INSTANCE_TT(klass, MRB_TT_CDATA)

#define DEFAULT_WINDOW_WIDTH  1280
#define DEFAULT_WINDOW_HEIGHT 720

#endif /*COMMON_H*/
