// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Internal General Subsystem Management
#ifndef INTERNALGENERAL_H
#define INTERNALGENERAL_H

#include "Native/Native.h"

// This number is arbitrary. Hopefully this is more than enough.
#define NATIVE_LOAD_COUNT_MAX 50

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitFileInternal(const char *path, char *argv0);

PUBLIC
void QuitFileInternal(void);

PUBLIC
bool InitGeneralSubsystem(const char *path, int argc, char **argv);

PUBLIC
void QuitGeneralSubsystem(void);

// =================
// General Functions
// =================

PUBLIC
int Argc(void);

PUBLIC
char **Argv(void);

PUBLIC
char *AbsolutePath(const char *relative_path, char *resolved_path);

PUBLIC
bool NativeLoadBasic(mrb_state *mrb, const char *path);

PUBLIC
void NativeUnLoad(mrb_state *mrb);

// The following are defined in Src/InternalFile.c.

PUBLIC
bool IsPhysfsMounted(void);

PUBLIC
Buffer *GetFileBuffer(const char *path, BufferSize *get_size);

#endif // INTERNALGENERAL_H
