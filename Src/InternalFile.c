// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: The game executable's implementation of an abstract file system.
#include "Internal.h"

#define NOT_IMPLEMENTED_PHYSFS "Not implemented for physfs!"

OpenFileFunc            OpenFile            = NULL;
CloseFileFunc           CloseFile           = NULL;
ReadFileFunc            ReadFile            = NULL;
ReadFileS8Func          ReadFileS8          = NULL;
ReadFileU8Func          ReadFileU8          = NULL;
ReadFileS16BEFunc       ReadFileS16BE       = NULL;
ReadFileS16LEFunc       ReadFileS16LE       = NULL;
ReadFileS32BEFunc       ReadFileS32BE       = NULL;
ReadFileS32LEFunc       ReadFileS32LE       = NULL;
ReadFileS64BEFunc       ReadFileS64BE       = NULL;
ReadFileS64LEFunc       ReadFileS64LE       = NULL;
ReadFileU16BEFunc       ReadFileU16BE       = NULL;
ReadFileU16LEFunc       ReadFileU16LE       = NULL;
ReadFileU32BEFunc       ReadFileU32BE       = NULL;
ReadFileU32LEFunc       ReadFileU32LE       = NULL;
ReadFileU64BEFunc       ReadFileU64BE       = NULL;
ReadFileU64LEFunc       ReadFileU64LE       = NULL;
WriteFileFunc           WriteFile           = NULL;
WriteFileS8Func         WriteFileS8         = NULL;
WriteFileU8Func         WriteFileU8         = NULL;
WriteFileS16BEFunc      WriteFileS16BE      = NULL;
WriteFileS16LEFunc      WriteFileS16LE      = NULL;
WriteFileS32BEFunc      WriteFileS32BE      = NULL;
WriteFileS32LEFunc      WriteFileS32LE      = NULL;
WriteFileS64BEFunc      WriteFileS64BE      = NULL;
WriteFileS64LEFunc      WriteFileS64LE      = NULL;
WriteFileU16BEFunc      WriteFileU16BE      = NULL;
WriteFileU16LEFunc      WriteFileU16LE      = NULL;
WriteFileU32BEFunc      WriteFileU32BE      = NULL;
WriteFileU32LEFunc      WriteFileU32LE      = NULL;
WriteFileU64BEFunc      WriteFileU64BE      = NULL;
WriteFileU64LEFunc      WriteFileU64LE      = NULL;
FlushFileFunc           FlushFile           = NULL;
GetFileSizeFunc         GetFileSize         = NULL;
SeekFileFunc            SeekFile            = NULL;
TellFileFunc            TellFile            = NULL;

DoesExistFileUtilsFunc  DoesExistFileUtils  = NULL;
IsNormalFileUtilsFunc   IsNormalFileUtils   = NULL;
IsDirFileUtilsFunc      IsDirFileUtils      = NULL;
IsOtherFileUtilsFunc    IsOtherFileUtils    = NULL;

GetSizeFileUtilsFunc    GetSizeFileUtils    = NULL;
CreateTimeFileUtilsFunc CreateTimeFileUtils = NULL;
ModifyTimeFileUtilsFunc ModifyTimeFileUtils = NULL;
AccessTimeFileUtilsFunc AccessTimeFileUtils = NULL;

EntriesFileUtilsFunc    EntriesFileUtils    = NULL;

#define IS_MOUNTED true

PRIVATE bool mount_status = false;

PRIVATE
File *OpenFilePhysfs(const char *path, const int mode) {
    File *file = NULL;

    switch(mode) {
        case FILE_MODE_WRITE:
                file = PHYSFS_openWrite(path);
                break;
        case FILE_MODE_APPEND:
                file = PHYSFS_openAppend(path);
                break;
        default: // FILE_MODE_READ
                file = PHYSFS_openRead(path);
                break;
    }

    if(!file) {
        SetErrorPhysfs();
    }

    return file;
}

PRIVATE
bool CloseFilePhysfs(File *file) {
    bool status = false;

    status = PHYSFS_close(file);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE SDL_INLINE
bool GetEOFStatusPhysfs(File *file) {
    return PHYSFS_eof(file);
}

PRIVATE
FileSize ReadFilePhysfs(File *file, Buffer *buf, BufferSize size) {
    FileSize bytes_read = 0;
    bool     eof_status = false;

    bytes_read = PHYSFS_readBytes(file, buf, size);

    if(bytes_read == -1) {
        SetErrorPhysfs();
        return -1;
    }

    if((BufferSize)bytes_read < size) {
        eof_status = GetEOFStatusPhysfs(file);
        if(!eof_status) {
            SetErrorPhysfs();
            return -1;
        }
    }

    return bytes_read;
}

PRIVATE
bool ReadFileS8Physfs(File *file, Sint8 *value) {
    IGNORE_RETURN file;
    IGNORE_RETURN value;

    return SDL_SetError(NOT_IMPLEMENTED_PHYSFS);
}

PRIVATE
bool ReadFileU8Physfs(File *file, Uint8 *value) {
    IGNORE_RETURN file;
    IGNORE_RETURN value;

    return SDL_SetError(NOT_IMPLEMENTED_PHYSFS);
}

PRIVATE
bool ReadFileS16BEPhysfs(File *file, Sint16 *value) {
    bool status = false;

    status = PHYSFS_readSBE16(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool ReadFileS16LEPhysfs(File *file, Sint16 *value) {
    bool status = false;

    status = PHYSFS_readSLE16(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool ReadFileS32BEPhysfs(File *file, Sint32 *value) {
    bool status = false;

    status = PHYSFS_readSBE32(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool ReadFileS32LEPhysfs(File *file, Sint32 *value) {
    bool status = false;

    status = PHYSFS_readSLE32(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool ReadFileS64BEPhysfs(File *file, Sint64 *value) {
    bool          status = false;
    PHYSFS_sint64 temp   = 0;

    status = PHYSFS_readSBE64(file, &temp);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    *value = (Sint64)temp;

    return true;
}

PRIVATE
bool ReadFileS64LEPhysfs(File *file, Sint64 *value) {
    bool          status = false;
    PHYSFS_sint64 temp   = 0;

    status = PHYSFS_readSLE64(file, &temp);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    *value = (Sint64)temp;

    return true;
}

PRIVATE
bool ReadFileU16BEPhysfs(File *file, Uint16 *value) {
    bool status = false;

    status = PHYSFS_readUBE16(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }


    return true;
}

PRIVATE
bool ReadFileU16LEPhysfs(File *file, Uint16 *value) {
    bool status = false;

    status = PHYSFS_readULE16(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool ReadFileU32BEPhysfs(File *file, Uint32 *value) {
    bool status = false;

    status = PHYSFS_readUBE32(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool ReadFileU32LEPhysfs(File *file, Uint32 *value) {
    bool status = false;

    status = PHYSFS_readULE32(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool ReadFileU64BEPhysfs(File *file, Uint64 *value) {
    bool          status = false;
    PHYSFS_uint64 temp   = 0;

    status = PHYSFS_readUBE64(file, &temp);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    *value = (Uint64)temp;

    return true;
}

PRIVATE
bool ReadFileU64LEPhysfs(File *file, Uint64 *value) {
    bool          status = false;
    PHYSFS_uint64 temp   = 0;

    status = PHYSFS_readULE64(file, &temp);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    *value = (Uint64)temp;

    return true;
}

PRIVATE
FileSize WriteFilePhysfs(File *file, Buffer *buf, BufferSize size) {
    FileSize bytes_read = 0;
    bool     eof_status = false;

    bytes_read = PHYSFS_writeBytes(file, buf, size);

    if(bytes_read == -1) {
        SetErrorPhysfs();
        return -1;
    }

    if((BufferSize)bytes_read < size) {
        eof_status = GetEOFStatusPhysfs(file);
        if(!eof_status) {
            SetErrorPhysfs();
            return -1;
        }
    }

    return bytes_read;
}

PRIVATE
bool WriteFileS8Physfs(File *file, Sint8 value) {
    IGNORE_RETURN file;
    IGNORE_RETURN value;

    return SDL_SetError(NOT_IMPLEMENTED_PHYSFS);
}

PRIVATE
bool WriteFileU8Physfs(File *file, Uint8 value) {
    IGNORE_RETURN file;
    IGNORE_RETURN value;

    return SDL_SetError(NOT_IMPLEMENTED_PHYSFS);
}

PRIVATE
bool WriteFileS16BEPhysfs(File *file, Sint16 value) {
    bool status = false;

    status = PHYSFS_writeSBE16(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileS16LEPhysfs(File *file, Sint16 value) {
    bool status = false;

    status = PHYSFS_writeSLE16(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileS32BEPhysfs(File *file, Sint32 value) {
    bool status = false;

    status = PHYSFS_writeSBE32(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileS32LEPhysfs(File *file, Sint32 value) {
    bool status = false;

    status = PHYSFS_writeSLE32(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileS64BEPhysfs(File *file, Sint64 value) {
    bool status = false;

    status = PHYSFS_writeSBE64(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileS64LEPhysfs(File *file, Sint64 value) {
    bool status = false;

    status = PHYSFS_writeSLE64(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileU16BEPhysfs(File *file, Uint16 value) {
    bool status = false;

    status = PHYSFS_writeUBE16(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileU16LEPhysfs(File *file, Uint16 value) {
    bool status = false;

    status = PHYSFS_writeULE16(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileU32BEPhysfs(File *file, Uint32 value) {
    bool status = false;

    status = PHYSFS_writeUBE32(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileU32LEPhysfs(File *file, Uint32 value) {
    bool status = false;

    status = PHYSFS_writeULE32(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileU64BEPhysfs(File *file, Uint64 value) {
    bool status = false;

    status = PHYSFS_writeUBE64(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool WriteFileU64LEPhysfs(File *file, Uint64 value) {
    bool status = false;

    status = PHYSFS_writeULE64(file, value);
    if(!status) {
        SetErrorPhysfs();
        return false;
    }

    return true;
}

PRIVATE
bool FlushFilePhysfs(File *file) {
    return PHYSFS_flush(file);
}

PRIVATE
FileSize GetFileSizePhysfs(File *file) {
    return PHYSFS_fileLength(file);
}

PRIVATE
bool SeekFilePhysfs(File *file, Sint64 offset, SDL_IOWhence whence) {
    bool status = false;

    UNUSED_ARGUMENT whence;

    status = PHYSFS_seek(file, offset);
    if(!status) {
        SetErrorPhysfs();
    }

    return status;
}

PRIVATE
Sint64 TellFilePhysfs(File *file) {
    PHYSFS_sint64 offset = 0;

    offset = PHYSFS_tell(file);
    if(offset == -1) {
        SetErrorPhysfs();
    }

    return offset;
}

PRIVATE
File *OpenFileIOStream(const char *path, const int mode) {
    const char *_mode = NULL;

    switch(mode) {
        case FILE_MODE_WRITE:
                _mode = "wb";
                break;
        case FILE_MODE_APPEND:
                _mode = "ab";
                break;
        default: // FILE_MODE_READ
                _mode = "rb";
                break;
    }

    return SDL_IOFromFile(path, _mode);
}

PRIVATE
bool CloseFileIOStream(File *file) {
    bool status = true;

    status = SDL_CloseIO(file);
    if(!status) {
        return false;
    }

    return true;
}

PRIVATE SDL_INLINE
bool GetEOFStatusIOStream(File *file) {
    SDL_IOStatus io_status = -1;
    bool         status    = false;

    io_status = SDL_GetIOStatus(file);
    status    = (io_status == SDL_IO_STATUS_EOF);

    return status;
}

PRIVATE
FileSize ReadFileIOStream(File *file, Buffer *buf, BufferSize size) {
    FileSize bytes_read = 0;
    bool     eof_status = false;

    bytes_read = SDL_ReadIO(file, buf, size);
    if((BufferSize)bytes_read < size) {
        eof_status = GetEOFStatusIOStream(file);
        if(!eof_status) {
            return -1;
        }
    }

    return bytes_read;
}

PRIVATE
bool ReadFileS8IOStream(File *file, Sint8 *value) {
    return SDL_ReadS8(file, value);
}

PRIVATE
bool ReadFileU8IOStream(File *file, Uint8 *value) {
    return SDL_ReadU8(file, value);
}

PRIVATE
bool ReadFileS16BEIOStream(File *file, Sint16 *value) {
    return SDL_ReadS16BE(file, value);
}

PRIVATE
bool ReadFileS16LEIOStream(File *file, Sint16 *value) {
    return SDL_ReadS16LE(file, value);
}

PRIVATE
bool ReadFileS32BEIOStream(File *file, Sint32 *value) {
    return SDL_ReadS32BE(file, value);
}

PRIVATE
bool ReadFileS32LEIOStream(File *file, Sint32 *value) {
    return SDL_ReadS32LE(file, value);
}

PRIVATE
bool ReadFileS64BEIOStream(File *file, Sint64 *value) {
    return SDL_ReadS64BE(file, value);
}

PRIVATE
bool ReadFileS64LEIOStream(File *file, Sint64 *value) {
    return SDL_ReadS64LE(file, value);
}

PRIVATE
bool ReadFileU16BEIOStream(File *file, Uint16 *value) {
    return SDL_ReadU16BE(file, value);
}

PRIVATE
bool ReadFileU16LEIOStream(File *file, Uint16 *value) {
    return SDL_ReadU16LE(file, value);
}

PRIVATE
bool ReadFileU32BEIOStream(File *file, Uint32 *value) {
    return SDL_ReadU32BE(file, value);
}

PRIVATE
bool ReadFileU32LEIOStream(File *file, Uint32 *value) {
    return SDL_ReadU32LE(file, value);
}

PRIVATE
bool ReadFileU64BEIOStream(File *file, Uint64 *value) {
    return SDL_ReadU64BE(file, value);
}

PRIVATE
bool ReadFileU64LEIOStream(File *file, Uint64 *value) {
    return SDL_ReadU64LE(file, value);
}

PRIVATE
FileSize WriteFileIOStream(File *file, Buffer *buf, BufferSize size) {
    FileSize bytes_read = 0;

    bytes_read = SDL_WriteIO(file, buf, size);
    if((BufferSize)bytes_read < size) {
        return -1;
    }

    return bytes_read;
}

PRIVATE
bool WriteFileS8IOStream(File *file, Sint8 value) {
    return SDL_WriteS8(file, value);
}

PRIVATE
bool WriteFileU8IOStream(File *file, Uint8 value) {
    return SDL_WriteU8(file, value);
}

PRIVATE
bool WriteFileS16BEIOStream(File *file, Sint16 value) {
    return SDL_WriteS16BE(file, value);
}

PRIVATE
bool WriteFileS16LEIOStream(File *file, Sint16 value) {
    return SDL_WriteS16LE(file, value);
}

PRIVATE
bool WriteFileS32BEIOStream(File *file, Sint32 value) {
    return SDL_WriteS32BE(file, value);
}

PRIVATE
bool WriteFileS32LEIOStream(File *file, Sint32 value) {
    return SDL_WriteS32LE(file, value);
}

PRIVATE
bool WriteFileS64BEIOStream(File *file, Sint64 value) {
    return SDL_WriteS64BE(file, value);
}

PRIVATE
bool WriteFileS64LEIOStream(File *file, Sint64 value) {
    return SDL_WriteS64LE(file, value);
}

PRIVATE
bool WriteFileU16BEIOStream(File *file, Uint16 value) {
    return SDL_WriteU16BE(file, value);
}

PRIVATE
bool WriteFileU16LEIOStream(File *file, Uint16 value) {
    return SDL_WriteU16LE(file, value);
}

PRIVATE
bool WriteFileU32BEIOStream(File *file, Uint32 value) {
    return SDL_WriteU32BE(file, value);
}

PRIVATE
bool WriteFileU32LEIOStream(File *file, Uint32 value) {
    return SDL_WriteU32LE(file, value);
}

PRIVATE
bool WriteFileU64BEIOStream(File *file, Uint64 value) {
    return SDL_WriteU64BE(file, value);
}

PRIVATE
bool WriteFileU64LEIOStream(File *file, Uint64 value) {
    return SDL_WriteU64LE(file, value);
}

PRIVATE
bool FlushFileIOStream(File *file) {
    return SDL_FlushIO(file);
}

PRIVATE
FileSize GetFileSizeIOStream(File *file) {
    return SDL_GetIOSize(file);
}

PRIVATE
bool SeekFileIOStream(File *file, Sint64 offset, SDL_IOWhence whence) {
    Sint64 status = 0;

    status = SDL_SeekIO(file, offset, whence);
    if(status == -1) {
        return false;
    }

    return true;
}

PRIVATE
Sint64 TellFileIOStream(File *file) {
    return SDL_TellIO(file);
}

PRIVATE
bool DoesExistFileUtilsPhysfs(const char *path) {
    return PHYSFS_exists(path);
}

PRIVATE
bool IsNormalFileUtilsPhysfs(const char *path) {
    PHYSFS_Stat stat   = {0};
    bool        status = false;

    status = PHYSFS_stat(path, &stat);
    if(!status) {
        return false;
    }

    status = (stat.filetype == PHYSFS_FILETYPE_REGULAR);

    return status;
}

PRIVATE
bool IsDirFileUtilsPhysfs(const char *path) {
    PHYSFS_Stat stat   = {0};
    bool        status = false;

    status = PHYSFS_stat(path, &stat);
    if(!status) {
        return false;
    }

    status = (stat.filetype == PHYSFS_FILETYPE_DIRECTORY);

    return status;
}

PRIVATE
bool IsOtherFileUtilsPhysfs(const char *path) {
    PHYSFS_Stat stat   = {0};
    bool        status = false;

    status = PHYSFS_stat(path, &stat);
    if(!status) {
        return false;
    }

    status = (stat.filetype == PHYSFS_FILETYPE_OTHER);

    return status;
}

PRIVATE
FileSize GetSizeFileUtilsPhysfs(const char *path) {
    PHYSFS_Stat stat   = {0};
    bool        status = false;

    status = PHYSFS_stat(path, &stat);
    if(!status) {
        return -1;
    }

    return stat.filesize;
}

PRIVATE
FileSize CreateTimeFileUtilsPhysfs(const char *path) {
    PHYSFS_Stat stat   = {0};
    bool        status = false;

    status = PHYSFS_stat(path, &stat);
    if(!status) {
        return -1;
    }

    return SDL_SECONDS_TO_NS(stat.createtime);
}

PRIVATE
FileSize ModifyTimeFileUtilsPhysfs(const char *path) {
    PHYSFS_Stat stat   = {0};
    bool        status = false;

    status = PHYSFS_stat(path, &stat);
    if(!status) {
        return -1;
    }

    return SDL_SECONDS_TO_NS(stat.modtime);
}

PRIVATE
FileSize AccessTimeFileUtilsPhysfs(const char *path) {
    PHYSFS_Stat stat   = {0};
    bool        status = false;

    status = PHYSFS_stat(path, &stat);
    if(!status) {
        return -1;
    }

    return SDL_SECONDS_TO_NS(stat.accesstime);
}

PRIVATE
char **EntriesFileUtilsPhysfs(const char *path, const char *pattern, int *count) {
    UNUSED_ARGUMENT pattern;
    UNUSED_ARGUMENT count;

    return PHYSFS_enumerateFiles(path);
}

PRIVATE
bool DoesExistFileUtilsFs(const char *path) {
    return SDL_GetPathInfo(path, NULL);
}

PRIVATE
bool IsNormalFileUtilsFs(const char *path) {
    bool         status = false;
    SDL_PathInfo info   = {0};

    status = SDL_GetPathInfo(path, &info);
    if(!status) {
        return false;
    }

    status = (info.type == SDL_PATHTYPE_FILE);

    return status;
}

PRIVATE
bool IsDirFileUtilsFs(const char *path) {
    bool         status = false;
    SDL_PathInfo info   = {0};

    status = SDL_GetPathInfo(path, &info);
    if(!status) {
        return false;
    }

    status = (info.type == SDL_PATHTYPE_DIRECTORY);

    return status;
}

PRIVATE
bool IsOtherFileUtilsFs(const char *path) {
    bool         status = false;
    SDL_PathInfo info   = {0};

    status = SDL_GetPathInfo(path, &info);
    if(!status) {
        return false;
    }

    status = (info.type == SDL_PATHTYPE_OTHER);

    return status;
}

PRIVATE
FileSize GetSizeFileUtilsFs(const char *path) {
    bool         status = false;
    SDL_PathInfo info   = {0};

    status = SDL_GetPathInfo(path, &info);
    if(!status) {
        return -1;
    }

    return info.size;
}

PRIVATE
FileSize CreateTimeFileUtilsFs(const char *path) {
    bool         status = false;
    SDL_PathInfo info   = {0};

    status = SDL_GetPathInfo(path, &info);
    if(!status) {
        return -1;
    }

    return info.create_time;
}

PRIVATE
FileSize ModifyTimeFileUtilsFs(const char *path) {
    bool         status = false;
    SDL_PathInfo info   = {0};

    status = SDL_GetPathInfo(path, &info);
    if(!status) {
        return -1;
    }

    return info.modify_time;
}

PRIVATE
FileSize AccessTimeFileUtilsFs(const char *path) {
    bool         status = false;
    SDL_PathInfo info   = {0};

    status = SDL_GetPathInfo(path, &info);
    if(!status) {
        return -1;
    }

    return info.access_time;
}

PRIVATE
char **EntriesFileUtilsFs(const char *path, const char *pattern, int *count) {
    return SDL_GlobDirectory(path, pattern, SDL_GLOB_CASEINSENSITIVE, count);
}

PRIVATE
void SetupPhysfsAllocator(void) {
    bool             status = false;
    PHYSFS_Allocator alloc  = {0};

    status = PHYSFS_isInit();
    if(status) {
        alloc.Malloc  = (MallocBufferPhysfs)MallocBuffer;
        alloc.Realloc = (ReallocBufferPhysfs)ReallocBuffer;
        alloc.Free    = FreeBuffer;

        IGNORE_RETURN PHYSFS_setAllocator(&alloc);
    }
}

PRIVATE
void SetupPhysfsMount(const char *path, char *argv0) {
    bool status = false;

    status = PHYSFS_init(argv0);
    if(status) {
        status = PHYSFS_mount(path, NULL, 0);
        if(!status) {
            path = "(nil)";
            IGNORE_RETURN SDL_SetError("Failed to mount: %s", path);
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
            IGNORE_RETURN SDL_ClearError();
            return;
        }
        mount_status = true;
    }
}

PRIVATE
void SetupVirtualFilesystem(void) {
    switch(mount_status) {
        case IS_MOUNTED:
            OpenFile            = OpenFilePhysfs;
            CloseFile           = CloseFilePhysfs;
            ReadFile            = ReadFilePhysfs;
            ReadFileS8          = ReadFileS8Physfs;
            ReadFileU8          = ReadFileU8Physfs;
            ReadFileS16BE       = ReadFileS16BEPhysfs;
            ReadFileS16LE       = ReadFileS16LEPhysfs;
            ReadFileS32BE       = ReadFileS32BEPhysfs;
            ReadFileS32LE       = ReadFileS32LEPhysfs;
            ReadFileS64BE       = ReadFileS64BEPhysfs;
            ReadFileS64LE       = ReadFileS64LEPhysfs;
            ReadFileU16BE       = ReadFileU16BEPhysfs;
            ReadFileU16LE       = ReadFileU16LEPhysfs;
            ReadFileU32BE       = ReadFileU32BEPhysfs;
            ReadFileU32LE       = ReadFileU32LEPhysfs;
            ReadFileU64BE       = ReadFileU64BEPhysfs;
            ReadFileU64LE       = ReadFileU64LEPhysfs;
            WriteFile           = WriteFilePhysfs;
            WriteFileS8         = WriteFileS8Physfs;
            WriteFileU8         = WriteFileU8Physfs;
            WriteFileS16BE      = WriteFileS16BEPhysfs;
            WriteFileS16LE      = WriteFileS16LEPhysfs;
            WriteFileS32BE      = WriteFileS32BEPhysfs;
            WriteFileS32LE      = WriteFileS32LEPhysfs;
            WriteFileS64BE      = WriteFileS64BEPhysfs;
            WriteFileS64LE      = WriteFileS64LEPhysfs;
            WriteFileU16BE      = WriteFileU16BEPhysfs;
            WriteFileU16LE      = WriteFileU16LEPhysfs;
            WriteFileU32BE      = WriteFileU32BEPhysfs;
            WriteFileU32LE      = WriteFileU32LEPhysfs;
            WriteFileU64BE      = WriteFileU64BEPhysfs;
            WriteFileU64LE      = WriteFileU64LEPhysfs;
            FlushFile           = FlushFilePhysfs;
            GetFileSize         = GetFileSizePhysfs;
            SeekFile            = SeekFilePhysfs;
            TellFile            = TellFilePhysfs;

            DoesExistFileUtils  = DoesExistFileUtilsPhysfs;
            IsNormalFileUtils   = IsNormalFileUtilsPhysfs;
            IsDirFileUtils      = IsDirFileUtilsPhysfs;
            IsOtherFileUtils    = IsOtherFileUtilsPhysfs;
            GetSizeFileUtils    = GetSizeFileUtilsPhysfs;
            CreateTimeFileUtils = CreateTimeFileUtilsPhysfs;
            ModifyTimeFileUtils = ModifyTimeFileUtilsPhysfs;
            AccessTimeFileUtils = AccessTimeFileUtilsPhysfs;
            EntriesFileUtils    = EntriesFileUtilsPhysfs;
            break;
        default:
            OpenFile            = OpenFileIOStream;
            CloseFile           = CloseFileIOStream;
            ReadFile            = ReadFileIOStream;
            ReadFileS8          = ReadFileS8IOStream;
            ReadFileU8          = ReadFileU8IOStream;
            ReadFileS16BE       = ReadFileS16BEIOStream;
            ReadFileS16LE       = ReadFileS16LEIOStream;
            ReadFileS32BE       = ReadFileS32BEIOStream;
            ReadFileS32LE       = ReadFileS32LEIOStream;
            ReadFileS64BE       = ReadFileS64BEIOStream;
            ReadFileS64LE       = ReadFileS64LEIOStream;
            ReadFileU16BE       = ReadFileU16BEIOStream;
            ReadFileU16LE       = ReadFileU16LEIOStream;
            ReadFileU32BE       = ReadFileU32BEIOStream;
            ReadFileU32LE       = ReadFileU32LEIOStream;
            ReadFileU64BE       = ReadFileU64BEIOStream;
            ReadFileU64LE       = ReadFileU64LEIOStream;
            WriteFile           = WriteFileIOStream;
            WriteFileS8         = WriteFileS8IOStream;
            WriteFileU8         = WriteFileU8IOStream;
            WriteFileS16BE      = WriteFileS16BEIOStream;
            WriteFileS16LE      = WriteFileS16LEIOStream;
            WriteFileS32BE      = WriteFileS32BEIOStream;
            WriteFileS32LE      = WriteFileS32LEIOStream;
            WriteFileS64BE      = WriteFileS64BEIOStream;
            WriteFileS64LE      = WriteFileS64LEIOStream;
            WriteFileU16BE      = WriteFileU16BEIOStream;
            WriteFileU16LE      = WriteFileU16LEIOStream;
            WriteFileU32BE      = WriteFileU32BEIOStream;
            WriteFileU32LE      = WriteFileU32LEIOStream;
            WriteFileU64BE      = WriteFileU64BEIOStream;
            WriteFileU64LE      = WriteFileU64LEIOStream;
            FlushFile           = FlushFileIOStream;
            GetFileSize         = GetFileSizeIOStream;
            SeekFile            = SeekFileIOStream;
            TellFile            = TellFileIOStream;

            DoesExistFileUtils  = DoesExistFileUtilsFs;
            IsNormalFileUtils   = IsNormalFileUtilsFs;
            IsDirFileUtils      = IsDirFileUtilsFs;
            IsOtherFileUtils    = IsOtherFileUtilsFs;
            GetSizeFileUtils    = GetSizeFileUtilsFs;
            CreateTimeFileUtils = CreateTimeFileUtilsFs;
            ModifyTimeFileUtils = ModifyTimeFileUtilsFs;
            AccessTimeFileUtils = AccessTimeFileUtilsFs;
            EntriesFileUtils    = EntriesFileUtilsFs;
            break;
    }
}

PRIVATE
void TerminatePhysfs(void) {
    bool status = false;

    status = PHYSFS_isInit();
    if(status) {
        status = PHYSFS_deinit();
        if(!status) {
            SetErrorPhysfs();
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
            IGNORE_RETURN SDL_ClearError();
            return;
        }
    }
}

PRIVATE
void TerminateVirtualFilesystem(void) {
    mount_status        = false;

    OpenFile            = NULL;
    CloseFile           = NULL;
    ReadFile            = NULL;
    ReadFileS8          = NULL;
    ReadFileU8          = NULL;
    ReadFileS16BE       = NULL;
    ReadFileS16LE       = NULL;
    ReadFileS32BE       = NULL;
    ReadFileS32LE       = NULL;
    ReadFileS64BE       = NULL;
    ReadFileS64LE       = NULL;
    ReadFileU16BE       = NULL;
    ReadFileU16LE       = NULL;
    ReadFileU32BE       = NULL;
    ReadFileU32LE       = NULL;
    ReadFileU64BE       = NULL;
    ReadFileU64LE       = NULL;
    WriteFile           = NULL;
    WriteFileS8         = NULL;
    WriteFileU8         = NULL;
    WriteFileS16BE      = NULL;
    WriteFileS16LE      = NULL;
    WriteFileS32BE      = NULL;
    WriteFileS32LE      = NULL;
    WriteFileS64BE      = NULL;
    WriteFileS64LE      = NULL;
    WriteFileU16BE      = NULL;
    WriteFileU16LE      = NULL;
    WriteFileU32BE      = NULL;
    WriteFileU32LE      = NULL;
    WriteFileU64BE      = NULL;
    WriteFileU64LE      = NULL;
    FlushFile           = NULL;
    GetFileSize         = NULL;
    SeekFile            = NULL;
    TellFile            = NULL;

    DoesExistFileUtils  = NULL;
    IsNormalFileUtils   = NULL;
    IsDirFileUtils      = NULL;
    IsOtherFileUtils    = NULL;
    GetSizeFileUtils    = NULL;
    CreateTimeFileUtils = NULL;
    ModifyTimeFileUtils = NULL;
    AccessTimeFileUtils = NULL;
    EntriesFileUtils    = NULL;
}

PUBLIC
bool InitFileInternal(const char *path, char *argv0) {
    SetupPhysfsAllocator();
    SetupPhysfsMount(path, argv0);
    SetupVirtualFilesystem();

    return true;
}

PUBLIC
void QuitFileInternal(void) {
    TerminatePhysfs();
    TerminateVirtualFilesystem();
}

PUBLIC
bool IsPhysfsMounted(void) {
    return mount_status;
}

PUBLIC
Buffer *GetFileBuffer(const char *path, BufferSize *get_size) {
    File     *file       = NULL;
    char     *buf        = NULL;
    FileSize  size       = 0;
    FileSize  bytes_read = 0;
    bool      status     = false;

    SDL_assert(OpenFile);
    SDL_assert(GetFileSize);
    SDL_assert(ReadFile);
    SDL_assert(CloseFile);

    file = OpenFile(path, FILE_MODE_READ);
    if(!file) {
        return NULL;
    }

    size = GetFileSize(file);
    if(size == -1) {
        CloseFile(file);
        return NULL;
    }

    if(get_size) {
        *get_size = (BufferSize)size;
    }

    buf = CallocBuffer((BufferSize)size + 1, sizeof(char));
    if(!buf) {
        CloseFile(file);
        return NULL;
    }

    bytes_read = ReadFile(file, buf, (BufferSize)size);
    if(bytes_read == -1) {
        FreeBuffer(buf);
        CloseFile(file);
        return NULL;
    }

    status = CloseFile(file);
    if(!status) {
        FreeBuffer(buf);
        return NULL;
    }

    return buf;
}
