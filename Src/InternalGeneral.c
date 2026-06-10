// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Internal General Subsystem Implementation
#include "Internal.h"
#include <stdlib.h> // For realpath(). -D _GNU_SOURCE is passed for this.
#include <errno.h>

PRIVATE int    game_argc = 0;
PRIVATE char **game_argv = NULL;

typedef bool (*NativeEntryPointFunc)(mrb_state *, SDL_Window *, SDL_Renderer *, SDL_Event *);
typedef void (*NativeExitPointFunc) (mrb_state *);

PRIVATE Uint8                native_load_count                       = 0;
PRIVATE SDL_SharedObject    *ext_handle[NATIVE_LOAD_COUNT_MAX]       = {0};
PRIVATE NativeExitPointFunc  NativeExitPoints[NATIVE_LOAD_COUNT_MAX] = {0};

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitGeneralSubsystem(const char *path, int argc, char **argv) {
    game_argc = argc;
    game_argv = argv;

    IGNORE_RETURN InitFileInternal(path, *game_argv);

    return true;
}

PUBLIC
void QuitGeneralSubsystem(void) {
    QuitFileInternal();
}

// =================
// General Functions
// =================

PUBLIC
int Argc(void) {
    return game_argc;
}

PUBLIC
char **Argv(void) {
    return game_argv;
}

PUBLIC
char *AbsolutePath(const char *relative_path, char *resolved_path) {
    char *status = NULL;

    status = realpath(relative_path, resolved_path);
    if(!status) {
        IGNORE_RETURN SDL_SetError("%s: %s", relative_path, strerror(errno));
        return NULL;
    }

    return status;
}

PUBLIC
bool NativeLoadBasic(mrb_state *mrb, const char *path) {
    NativeEntryPointFunc  NativeEntryPoint = NULL;
    SDL_Window           *window           = Window();
    SDL_Renderer         *renderer         = Renderer();
    SDL_Event            *event            = Event();

    if(native_load_count > NATIVE_LOAD_COUNT_MAX) {
        IGNORE_RETURN SDL_SetError("You are limited to %d extensions", NATIVE_LOAD_COUNT_MAX);
        return false;
    }

    ext_handle[native_load_count] = SDL_LoadObject(path);
    if(!ext_handle[native_load_count]) {
        return false;
    }

    NativeEntryPoint = (NativeEntryPointFunc)SDL_LoadFunction(ext_handle[native_load_count], "NativeEntryPoint");
    if(!NativeEntryPoint) {
        return false;
    }

    NativeExitPoints[native_load_count] = (NativeExitPointFunc)SDL_LoadFunction(ext_handle[native_load_count], "NativeExitPoint");
    if(!NativeExitPoints[native_load_count]) {
        IGNORE_RETURN SDL_SetError("The exit procedure(%s) was not set for %s", "NativeExitPoint", path);
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        IGNORE_RETURN SDL_ClearError();
    }

    if(!NativeEntryPoint(mrb, window, renderer, event)) {
        return false;
    }

    ++native_load_count;

    return true;
}

PUBLIC
void NativeUnLoad(mrb_state *mrb) {
    for(int i = 0;i < native_load_count;++i) {
        NativeExitPoints[i](mrb);
    }
}
