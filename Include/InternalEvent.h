// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Internal Event Subsystem Implementation
#ifndef INTERNALEVENT_H
#define INTERNALEVENT_H

#include "Native/Native.h"

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitEventSubsystem(bool disable);

PUBLIC
void QuitEventSubsystem(void);

// =================
// General Functions
// =================

PUBLIC
SDL_Event *Event(void);

#endif // INTERNALEVENT_H
