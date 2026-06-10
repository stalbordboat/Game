// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Master Header For Internal Subsystems
#ifndef INTERNAL_H
#define INTERNAL_H

#include "InternalGeneral.h"
#include "InternalWindow.h"
#include "InternalEvent.h"
#include "InternalAudio.h"

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitInternal(int argc, char **argv);

PUBLIC
void QuitInternal(void);

PUBLIC
void SendNativeExitPoints(mrb_state *mrb);

// =================
// General Functions
// =================

PUBLIC
void HandleError(void);

PUBLIC
bool RunGame(void);

PUBLIC
bool IsErrorSet(void);

PUBLIC
mrb_state *MrbState(void);

PUBLIC
SDL_Environment *Environment(void);

// ==================
// General Subsystem
// ==================

PUBLIC
void ExtendKernelModule(mrb_state *mrb, int argc, char *argv[]);

PUBLIC
void DefineMathModule(mrb_state *mrb);

PUBLIC
void DefineFileClass(mrb_state *mrb);

PUBLIC
void DefineFileUtilsModule(mrb_state *mrb);

PUBLIC
void DefineFileUtilsStatModule(mrb_state *mrb);

PUBLIC
void DefineEnvModule(mrb_state *mrb, SDL_Environment *env);

PUBLIC
void DefineLogModule(mrb_state *mrb);

PUBLIC
void DefineTimerClass(mrb_state *mrb);

PUBLIC
void DefineTimeModule(mrb_state *mrb);

PUBLIC
void DefineProcessClass(mrb_state *mrb);

PUBLIC
void DefinePowerModule(mrb_state *mrb);

// ================
// Window Subsystem
// ================

PUBLIC
void DefineGraphicsModule(mrb_state *mrb, SDL_Window *window, SDL_Renderer *renderer);

PUBLIC
void DefinePointClass(mrb_state *mrb);

PUBLIC
void DefineRectClass(mrb_state *mrb);

PUBLIC
void DefineColorClass(mrb_state *mrb);

PUBLIC
void DefineImageClass(mrb_state *mrb, SDL_Renderer *renderer);

PUBLIC
void DefineSpriteClass(mrb_state *mrb, SDL_Renderer *renderer);

PUBLIC
void DefineCameraClass(mrb_state *mrb, SDL_Renderer *renderer);

// ===============
// Audio Subsystem
// ===============

PUBLIC
void DefineAudioRecorderClass(mrb_state *mrb);

PUBLIC
void DefineSoundClass(mrb_state *mrb, MIX_Mixer *mixer, MIX_Track **tracks);

PUBLIC
void DefineMixerModule(mrb_state *mrb);

PUBLIC
void DefineLocationClass(mrb_state *mrb);

// ===============
// Event Subsystem
// ===============

PUBLIC
void DefineEventModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineKeyboardModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineKeyboardDeviceModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineGamepadButtonModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineGamepadAxisModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineGamepadTouchpadModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineGamepadDeviceModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineGamepadSensorModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineAudioDeviceModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineCameraDeviceModule(mrb_state *mrb, SDL_Event *event);

PUBLIC
void DefineGamepadClass(mrb_state *mrb);

#endif /*INTERNAL_H*/
