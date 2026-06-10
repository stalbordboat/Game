// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Entry Point
#include "Internal.h"
#include "Array.c"
#include "Integer.c"

#define WINDOW_ENABLED(env) !SDL_GetEnvironmentVariable(env, GAME_NO_WINDOW_NAME)
#define EVENTS_ENABLED(env) !SDL_GetEnvironmentVariable(env, GAME_NO_EVENTS_NAME)
#define AUDIO_ENABLED(env)  !SDL_GetEnvironmentVariable(env, GAME_NO_AUDIO_NAME)

PRIVATE SDL_INLINE
void ExtendArrayClass(mrb_state *mrb) {
    IGNORE_RETURN mrb_load_irep(mrb, Array_symbol);
}

PRIVATE SDL_INLINE
void ExtendIntegerClass(mrb_state *mrb) {
    IGNORE_RETURN mrb_load_irep(mrb, Integer_symbol);
}

int main(int argc, char *argv[]) {
    bool             initialized  = false;
    bool             status_error = false;
    int              status_exit  = GAME_EXIT_SUCCESS;
    SDL_Environment *env          = NULL;
    SDL_Window      *window       = NULL;
    SDL_Renderer    *renderer     = NULL;
    MIX_Mixer       *mixer        = NULL;
    MIX_Track       **tracks      = NULL;
    SDL_Event       *event        = NULL;
    mrb_state       *mrb          = NULL;

    initialized = InitInternal(argc, argv);
    if(initialized) {
        env      = Environment();
        mrb      = MrbState();
        window   = Window();
        renderer = Renderer();
        mixer    = Mixer();
        tracks   = Tracks();
        event    = Event();

        ExtendArrayClass         (mrb);
        ExtendIntegerClass       (mrb);
        ExtendKernelModule       (mrb, argc, argv);
        DefineMathModule         (mrb);
        DefineFileClass          (mrb);
        DefineFileUtilsModule    (mrb);
        DefineFileUtilsStatModule(mrb);
        DefineEnvModule          (mrb, env);
        DefineLogModule          (mrb);
        DefineTimerClass         (mrb);
        DefineTimeModule         (mrb);
        DefineProcessClass       (mrb);
        DefinePowerModule        (mrb);

        if(WINDOW_ENABLED(env)) {
            DefineGraphicsModule(mrb, window, renderer);
            DefinePointClass    (mrb);
            DefineRectClass     (mrb);
            DefineColorClass    (mrb);
            DefineImageClass    (mrb, renderer);
            DefineSpriteClass   (mrb, renderer);
            DefineCameraClass   (mrb, renderer);
        }

        if(AUDIO_ENABLED(env)) {
            DefineAudioRecorderClass(mrb);
            DefineMixerModule       (mrb);
            DefineSoundClass        (mrb, mixer, tracks);
            DefineLocationClass     (mrb);
        }

        if(EVENTS_ENABLED(env)) {
            DefineEventModule          (mrb, event);
            DefineKeyboardModule       (mrb, event);
            DefineKeyboardDeviceModule (mrb, event);
            DefineGamepadDeviceModule  (mrb, event);
            DefineGamepadButtonModule  (mrb, event);
            DefineGamepadAxisModule    (mrb, event);
            DefineGamepadTouchpadModule(mrb, event);
            DefineGamepadSensorModule  (mrb, event);
            DefineAudioDeviceModule    (mrb, event);
            DefineCameraDeviceModule   (mrb, event);
            DefineGamepadClass         (mrb);
        }

        IGNORE_RETURN RunGame();
    }

    status_error = IsErrorSet();
    if(status_error) {
        HandleError();
        status_exit = GAME_EXIT_FAILURE;
    }

    NativeUnLoad(mrb);
    QuitInternal();

    return status_exit;
}
