// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Abstract File System Management
#ifndef FILE_H
#define FILE_H

#include "Memory.h"

enum {
    FILE_MODE_READ,
    FILE_MODE_WRITE,
    FILE_MODE_APPEND,
};

typedef void     File;
typedef Sint64   FileSize;
typedef SDL_Time FileTime;

typedef File    *(*OpenFileFunc)           (const char *, const int);
typedef bool     (*CloseFileFunc)          (File *);
typedef FileSize (*ReadFileFunc)           (File *, Buffer *, BufferSize);
typedef bool     (*ReadFileS8Func)         (File *, Sint8 *);
typedef bool     (*ReadFileU8Func)         (File *, Uint8 *);
typedef bool     (*ReadFileS16BEFunc)      (File *, Sint16 *);
typedef bool     (*ReadFileS16LEFunc)      (File *, Sint16 *);
typedef bool     (*ReadFileS32BEFunc)      (File *, Sint32 *);
typedef bool     (*ReadFileS32LEFunc)      (File *, Sint32 *);
typedef bool     (*ReadFileS64BEFunc)      (File *, Sint64 *);
typedef bool     (*ReadFileS64LEFunc)      (File *, Sint64 *);
typedef bool     (*ReadFileU16BEFunc)      (File *, Uint16 *);
typedef bool     (*ReadFileU16LEFunc)      (File *, Uint16 *);
typedef bool     (*ReadFileU32BEFunc)      (File *, Uint32 *);
typedef bool     (*ReadFileU32LEFunc)      (File *, Uint32 *);
typedef bool     (*ReadFileU64BEFunc)      (File *, Uint64 *);
typedef bool     (*ReadFileU64LEFunc)      (File *, Uint64 *);
typedef FileSize (*WriteFileFunc)          (File *, Buffer *, BufferSize);
typedef bool     (*WriteFileS8Func)        (File *, Sint8);
typedef bool     (*WriteFileU8Func)        (File *, Uint8);
typedef bool     (*WriteFileS16BEFunc)     (File *, Sint16);
typedef bool     (*WriteFileS16LEFunc)     (File *, Sint16);
typedef bool     (*WriteFileS32BEFunc)     (File *, Sint32);
typedef bool     (*WriteFileS32LEFunc)     (File *, Sint32);
typedef bool     (*WriteFileS64BEFunc)     (File *, Sint64);
typedef bool     (*WriteFileS64LEFunc)     (File *, Sint64);
typedef bool     (*WriteFileU16BEFunc)     (File *, Uint16);
typedef bool     (*WriteFileU16LEFunc)     (File *, Uint16);
typedef bool     (*WriteFileU32BEFunc)     (File *, Uint32);
typedef bool     (*WriteFileU32LEFunc)     (File *, Uint32);
typedef bool     (*WriteFileU64BEFunc)     (File *, Uint64);
typedef bool     (*WriteFileU64LEFunc)     (File *, Uint64);
typedef bool     (*FlushFileFunc)          (File *);
typedef FileSize (*GetFileSizeFunc)        (File *);
typedef bool     (*SeekFileFunc)           (File *, Sint64, SDL_IOWhence);
typedef Sint64   (*TellFileFunc)           (File *);

typedef bool     (*DoesExistFileUtilsFunc) (const char *);
typedef bool     (*IsNormalFileUtilsFunc)  (const char *);
typedef bool     (*IsDirFileUtilsFunc)     (const char *);
typedef bool     (*IsOtherFileUtilsFunc)   (const char *);

typedef FileSize (*GetSizeFileUtilsFunc)   (const char *);
typedef FileTime (*CreateTimeFileUtilsFunc)(const char *);
typedef FileTime (*ModifyTimeFileUtilsFunc)(const char *);
typedef FileTime (*AccessTimeFileUtilsFunc)(const char *);

typedef char   **(*EntriesFileUtilsFunc)   (const char *, const char *, int *);

PUBLIC OpenFileFunc            OpenFile;
PUBLIC CloseFileFunc           CloseFile;
PUBLIC ReadFileFunc            ReadFile;
PUBLIC ReadFileS8Func          ReadFileS8;
PUBLIC ReadFileU8Func          ReadFileU8;
PUBLIC ReadFileS16BEFunc       ReadFileS16BE;
PUBLIC ReadFileS16LEFunc       ReadFileS16LE;
PUBLIC ReadFileS32BEFunc       ReadFileS32BE;
PUBLIC ReadFileS32LEFunc       ReadFileS32LE;
PUBLIC ReadFileS64BEFunc       ReadFileS64BE;
PUBLIC ReadFileS64LEFunc       ReadFileS64LE;
PUBLIC ReadFileU16BEFunc       ReadFileU16BE;
PUBLIC ReadFileU16LEFunc       ReadFileU16LE;
PUBLIC ReadFileU32BEFunc       ReadFileU32BE;
PUBLIC ReadFileU32LEFunc       ReadFileU32LE;
PUBLIC ReadFileU64BEFunc       ReadFileU64BE;
PUBLIC ReadFileU64LEFunc       ReadFileU64LE;
PUBLIC WriteFileFunc           WriteFile;
PUBLIC WriteFileS8Func         WriteFileS8;
PUBLIC WriteFileU8Func         WriteFileU8;
PUBLIC WriteFileS16BEFunc      WriteFileS16BE;
PUBLIC WriteFileS16LEFunc      WriteFileS16LE;
PUBLIC WriteFileS32BEFunc      WriteFileS32BE;
PUBLIC WriteFileS32LEFunc      WriteFileS32LE;
PUBLIC WriteFileS64BEFunc      WriteFileS64BE;
PUBLIC WriteFileS64LEFunc      WriteFileS64LE;
PUBLIC WriteFileU16BEFunc      WriteFileU16BE;
PUBLIC WriteFileU16LEFunc      WriteFileU16LE;
PUBLIC WriteFileU32BEFunc      WriteFileU32BE;
PUBLIC WriteFileU32LEFunc      WriteFileU32LE;
PUBLIC WriteFileU64BEFunc      WriteFileU64BE;
PUBLIC WriteFileU64LEFunc      WriteFileU64LE;
PUBLIC FlushFileFunc           FlushFile;
PUBLIC GetFileSizeFunc         GetFileSize;
PUBLIC SeekFileFunc            SeekFile;
PUBLIC TellFileFunc            TellFile;

PUBLIC DoesExistFileUtilsFunc  DoesExistFileUtils;
PUBLIC IsNormalFileUtilsFunc   IsNormalFileUtils;
PUBLIC IsDirFileUtilsFunc      IsDirFileUtils;
PUBLIC IsOtherFileUtilsFunc    IsOtherFileUtils;

PUBLIC GetSizeFileUtilsFunc    GetSizeFileUtils;
PUBLIC CreateTimeFileUtilsFunc CreateTimeFileUtils;
PUBLIC ModifyTimeFileUtilsFunc ModifyTimeFileUtils;
PUBLIC AccessTimeFileUtilsFunc AccessTimeFileUtils;

PUBLIC EntriesFileUtilsFunc    EntriesFileUtils;

#endif /*FILE_H*/
