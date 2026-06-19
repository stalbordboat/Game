// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Master Internal Subsystems Management
#include "Internal.h"

#define USE_RUNTIME_ENVIRONMENT true
#define USED_BY_EXTERNAL_LIB

PRIVATE SDL_Environment *env            = NULL;
PRIVATE const char      *physfs_archive = NULL;
PRIVATE const char      *start_path     = NULL;
PRIVATE const char      *no_window      = NULL;
PRIVATE const char      *no_events      = NULL;
PRIVATE const char      *no_audio       = NULL;
PRIVATE mrb_state       *mrb            = NULL;

PUBLIC
mrb_state *MrbState(void) {
    SDL_assert(mrb);

    return mrb;
}

PUBLIC
SDL_Environment *Environment(void) {
    SDL_assert(env);

    return env;
}

PUBLIC
bool IsErrorSet(void) {
    return (SDL_strcmp(SDL_GetError(), "") != 0);
}

PRIVATE
bool InitEnvironment(void) {
    env = SDL_CreateEnvironment(USE_RUNTIME_ENVIRONMENT);
    if(!env) {
        return false;
    }

    physfs_archive = SDL_GetEnvironmentVariable(env, GAME_PHYSFS_ARCHIVE_NAME);
    start_path     = SDL_GetEnvironmentVariable(env, GAME_START_PATH_NAME);
    no_window      = SDL_GetEnvironmentVariable(env, GAME_NO_WINDOW_NAME);
    no_events      = SDL_GetEnvironmentVariable(env, GAME_NO_EVENTS_NAME);
    no_audio       = SDL_GetEnvironmentVariable(env, GAME_NO_AUDIO_NAME);

    if(!start_path) {
        start_path = DEFAULT_START_PATH;
    }

    return true;
}

PRIVATE
void QuitEnvironment(void) {
    SDL_DestroyEnvironment(env);
}

USED_BY_EXTERNAL_LIB
Buffer *mrb_basic_alloc_func(Buffer *buf, BufferSize size) {
    if(size == 0) {
        FreeBuffer(buf);
        return NULL;
    }

    return ReallocBuffer(buf, size);
}

PRIVATE
bool InitMrbInstance(void) {
    mrb = mrb_open();
    if(!mrb) {
        IGNORE_RETURN SDL_SetError("mruby instance failed to initialize");
        return false;
    }

    return true;
}

PRIVATE
void QuitMrbInstance(void) {
    mrb_close(mrb);

    mrb = NULL;
}

PRIVATE
void ErrorWindow(SDL_Window *window) {
    bool                 status = true;
    const char          *msg    = 0;
    const char          *title  = 0;
    SDL_MessageBoxFlags  flags  = SDL_MESSAGEBOX_ERROR;

    title = SDL_GetWindowTitle(window);
    msg   = SDL_GetError();

    status = SDL_ShowSimpleMessageBox(flags, title, msg, window);
    if(!status) {
        msg = SDL_GetError();
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", msg);
        IGNORE_RETURN SDL_ClearError();
        return;
    }
}

PUBLIC
void HandleError(void) {
    SDL_Window *window = Window();

    if(window) {
        ErrorWindow(window);
    }
    else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
    }
}

PUBLIC
bool InitInternal(int argc, char **argv) {
    bool status = false;

    status = InitEnvironment();
    if(!status) {
        return false;
    }

    UNUSED_ARGUMENT argc;

    IGNORE_RETURN InitGeneralSubsystem(physfs_archive, argc, argv);

    status = InitWindowSubsystem(no_window);
    if(!status) {
        return false;
    }

    status = InitEventSubsystem(no_events);
    if(!status) {
        return false;
    }

    status = InitAudioSubsystem(no_audio);
    if(!status) {
        return false;
    }

    status = InitMrbInstance();
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
void QuitInternal(void) {
    QuitEnvironment();
    QuitMrbInstance();
    QuitEventSubsystem();
    QuitAudioSubsystem();
    QuitWindowSubsystem();
    QuitGeneralSubsystem();
}

PUBLIC
bool RunGame(void) {
    char      *script = NULL;
    BufferSize size   = 0;

    SDL_assert(start_path);
    SDL_assert(mrb);

    script = GetFileBuffer(start_path, &size);
    if(!script) {
        return false;
    }

    if(HasExtname(start_path, ".rb")) {
        IGNORE_RETURN mrb_load_string(mrb, script);
    }
    else {
        IGNORE_RETURN mrb_load_irep_buf(mrb, script, size);
    }

    FreeBuffer(script);

    if(mrb->exc) {
        SetErrorMrbState(mrb);
        return false;
    }

    return true;
}
