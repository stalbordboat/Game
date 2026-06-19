// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Internal Window Subsystem Management
#include "Internal.h"

#define NORMAL_VSYNC 1

PRIVATE SDL_Window   *window    = NULL;
PRIVATE SDL_Renderer *renderer  = NULL;
PRIVATE bool          no_window = false;

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitWindowSubsystem(bool disable) {
    bool status = false;

    if(disable) {
        IGNORE_RETURN SDL_SetError("Window Mode: %s", "(disabled)");
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        IGNORE_RETURN SDL_ClearError();
        return true;
    }

    no_window = disable;

    status = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if(!status) {
        return false;
    }

    status = SDL_InitSubSystem(SDL_INIT_CAMERA);
    if(!status) {
        return false;
    }

    window = SDL_CreateWindow("", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_HIDDEN);
    if(!window) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer) {
        return false;
    }

    status = SDL_SetRenderVSync(renderer, NORMAL_VSYNC);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
void QuitWindowSubsystem(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_CAMERA);

    renderer = NULL;
    window   = NULL;
}

// =================
// General Functions
// =================

PUBLIC
SDL_Window *Window(void) {
    if(!no_window) {
        SDL_assert(window);
    }

    return window;
}

PUBLIC
SDL_Renderer *Renderer(void) {
    if(!no_window) {
        SDL_assert(renderer);
    }

    return renderer;
}

// ==================
// Graphics Functions
// ==================

PUBLIC
SDL_Surface *CreateSurfaceFromRenderer(SDL_Renderer *renderer, SDL_Rect *rect) {
    SDL_Surface *surface = NULL;

    surface = SDL_RenderReadPixels(renderer, rect);
    if(!surface) {
        return NULL;
    }

    return surface;
}

// ===============
// Image Functions
// ===============

PRIVATE
bool SetColorKey(SDL_Surface *surface, SDL_Color *color) {
    Uint32 key    = 0;
    bool   status = false;

    key = SDL_MapRGB(SDL_GetPixelFormatDetails(surface->format),
                     NULL,
                     color->r,
                     color->g,
                     color->b);

    status = SDL_SetSurfaceColorKey(surface, true, key);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool HasExtname(const char *path, const char *extname) {
    size_t path_len = 0;
    size_t ext_len  = 0;

    if(!path || !extname) {
        return false;
    }

    path_len = SDL_strlen(path);
    ext_len  = SDL_strlen(extname);

    if(ext_len == 0 || ext_len > path_len) {
        return false;
    }

    // Compare from the end of the path
    return (SDL_strcmp(path + path_len - ext_len, extname) == 0);
}

PRIVATE
SDL_Surface *CreateSurfaceForImage(const char *path, SDL_Color *key) {
    SDL_Surface  *surface = NULL;
    BufferSize    size    = 0;
    char         *buf     = NULL;
    SDL_IOStream *io      = NULL;
    bool          status  = false;

    buf = GetFileBuffer(path, &size);
    if(!buf) {
        return NULL;
    }

    io = SDL_IOFromMem(buf, size);
    if(!io) {
        FreeBuffer(buf);
        return NULL;
    }

    status = HasExtname(path, ".bmp");
    if(status) {
        surface = SDL_LoadBMP_IO(io, false);
    }

    status = HasExtname(path, ".png");
    if(status) {
        surface = SDL_LoadPNG_IO(io, false);
    }

    if(!surface) {
        IGNORE_RETURN SDL_CloseIO(io);
        FreeBuffer(buf);
        return NULL;
    }

    status = SDL_CloseIO(io);
    if(!status) {
        FreeBuffer(buf);
        return NULL;
    }

    FreeBuffer(buf);

    if(key) {
        status = SetColorKey(surface, key);
        if(!status) {
            SDL_DestroySurface(surface);
            return NULL;
        }
    }

    return surface;
}

PUBLIC
Image *CreateImage(const char *path, SDL_Color *color_key) {
    Image       *image   = NULL;
    SDL_Surface *surface = NULL;

    image = CallocBuffer(1, sizeof(Image));
    if(!image) {
        return NULL;
    }

    surface = CreateSurfaceForImage(path, color_key);
    if(!surface) {
        DestroyImage(image);
        return NULL;
    }

    image->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!image->texture) {
        SDL_DestroySurface(surface);
        DestroyImage(image);
        return NULL;
    }

    SDL_DestroySurface(surface);

    image->blend = SDL_BLENDMODE_BLEND;
    image->flip  = SDL_FLIP_NONE;
    image->angle = 0.0;

    return image;
}

PUBLIC
void DestroyImage(Image *image) {
    if(!image) {
        return;
    }

    if(image->texture) {
        SDL_DestroyTexture(image->texture);
    }

    FreeBuffer(image);
}

PUBLIC
bool UpdateImage(Image      *image,
                 SDL_FRect  *src,
                 SDL_FRect  *dest,
                 SDL_FPoint *pos,
                 SDL_Color  *color) {
    bool status = true;

    status = SDL_SetTextureBlendMode(image->texture, image->blend);
    if(!status) {
        return false;
    }

    status = SDL_SetTextureAlphaMod(image->texture, color->a);
    if(!status) {
        return false;
    }

    status = SDL_SetTextureColorMod(image->texture,
                                    color->r,
                                    color->g,
                                    color->b);
    if(!status) {
        return false;
    }

    status = SDL_RenderTextureRotated(renderer,
                                      image->texture,
                                      src,
                                      dest,
                                      image->angle,
                                      pos,
                                      image->flip);
    if(!status) {
        return false;
    }

    return true;
}

// ================
// Sprite Functions
// ================

PUBLIC
Sprite *CreateSprite(Image *image) {
    Sprite *sprite = NULL;

    sprite = CallocBuffer(1, sizeof(Sprite));
    if(!sprite) {
        return NULL;
    }

    sprite->texture = image->texture;
    sprite->blend   = image->blend;

    return sprite;
}

PUBLIC
void DestroySprite(Sprite *sprite) {
    if(!sprite) {
        return;
    }

    FreeBuffer(sprite);
}
