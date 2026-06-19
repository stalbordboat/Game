// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Internal Window Subsystem Management
#ifndef INTERNAL_WINDOW_H
#define INTERNAL_WINDOW_H

#include "Native/Native.h"

#define OPAQUE_COLOR_VALUE 255

typedef struct {
    double       angle;
    SDL_Texture *texture;
    int          flip;
    int          blend;
}Image, Sprite;

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitWindowSubsystem(bool disable);

PUBLIC
void QuitWindowSubsystem(void);

// =================
// General Functions
// =================

PUBLIC
SDL_Window *Window(void);

PUBLIC
SDL_Renderer *Renderer(void);

PUBLIC
bool HasExtname(const char *path, const char *extname);

// ==================
// Graphics Functions
// ==================

PUBLIC
SDL_Surface *CreateSurfaceFromRenderer(SDL_Renderer *renderer, SDL_Rect *rect);

// ===============
// Image Functions
// ===============

PUBLIC
Image *CreateImage(const char *path, SDL_Color *key);

PUBLIC
void DestroyImage(Image *image);

PUBLIC
bool UpdateImage(Image *image, SDL_FRect *src, SDL_FRect *dest, SDL_FPoint *pos, SDL_Color *color);

// ================
// Sprite Functions
// ================

PUBLIC
Sprite *CreateSprite(Image *image);

PUBLIC
void DestroySprite(Sprite *sprite);

#endif // INTERNAL_WINDOW_H
