// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Internal Event Subsystem Management
#include "Internal.h"

PRIVATE SDL_Event *event           = NULL;
PRIVATE bool       events_disabled = false;

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitEventSubsystem(bool disable) {
    bool status = false;

    events_disabled = disable;

    if(disable) {
        IGNORE_RETURN SDL_SetError("Event Mode: %s", "(disabled)");
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        IGNORE_RETURN SDL_ClearError();
        return true;
    }

    status = SDL_InitSubSystem(SDL_INIT_EVENTS|SDL_INIT_GAMEPAD|SDL_INIT_HAPTIC);
    if(!status) {
        return false;
    }

    event = CallocBuffer(1, sizeof(SDL_Event));
    if(!event) {
        return false;
    }

    return true;
}

PUBLIC
void QuitEventSubsystem(void) {
    FreeBuffer(event);
    SDL_QuitSubSystem(SDL_INIT_EVENTS|SDL_INIT_GAMEPAD|SDL_INIT_HAPTIC);

    event = NULL;
}

// =================
// General Functions
// =================

PUBLIC
SDL_Event *Event(void) {
    if(!events_disabled) {
        SDL_assert(event);
    }

    return event;
}
