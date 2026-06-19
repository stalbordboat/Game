// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Memory Management Interface
#ifndef MEMORY_H
#define MEMORY_H

#include "Common.h"

typedef void   Buffer;
typedef size_t BufferSize;

typedef void *(*MallocBufferPhysfs)(PHYSFS_uint64);
typedef void *(*ReallocBufferPhysfs)(void *, PHYSFS_uint64);

PRIVATE SDL_INLINE
Buffer *MallocBuffer(BufferSize total_size) {
    Buffer *buf = NULL;

    buf = SDL_malloc(total_size);
    if(!buf) {
        SDL_OutOfMemory();
        return NULL;
    }

    return buf;
}

PRIVATE SDL_INLINE
Buffer *CallocBuffer(BufferSize size, BufferSize type_size) {
    Buffer *buf = NULL;

    buf = SDL_calloc(size, type_size);
    if(!buf) {
        SDL_OutOfMemory();
        return NULL;
    }

    return buf;
}

PRIVATE SDL_INLINE
Buffer *ReallocBuffer(Buffer *ptr, BufferSize total_size) {
    Buffer *buf = NULL;

    buf = SDL_realloc(ptr, total_size);
    if(!buf) {
        SDL_OutOfMemory();
        return NULL;
    }

    return buf;
}

PRIVATE SDL_INLINE
void FreeBuffer(Buffer *buf) {
    if(!buf) {
        return;
    }

    SDL_free(buf);
}

#endif /*MEMORY_H*/
