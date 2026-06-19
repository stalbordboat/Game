// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Represents Camera Devices
#include "Internal.h"

PRIVATE SDL_Renderer *private_renderer = NULL;

typedef struct {
    SDL_Camera  *device;
    SDL_Texture *texture;
}Camera;

PRIVATE
mrb_value self_ids(mrb_state *mrb, mrb_value self) {
    SDL_CameraID *ids   = NULL;
    int           count = 0;
    mrb_value     ary   = {0};

    UNUSED_ARGUMENT self;

    ids = SDL_GetCameras(&count);
    if(!ids) {
        RaiseRuntimeError(mrb);
    }

    ary = mrb_ary_new_capa(mrb, count);

    for(int i = 0;i < count;++i) {
        mrb_ary_push(mrb, ary, mrb_int_value(mrb, ids[i]));
    }

    FreeBuffer(ids);

    return ary;
}

PRIVATE
mrb_value self_name(mrb_state *mrb, mrb_value self) {
    mrb_int id = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i", &id);

    return mrb_str_new_cstr(mrb, SDL_GetCameraName(id));
}

PRIVATE
mrb_value self_driver_current_name(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_str_new_cstr(mrb, SDL_GetCurrentCameraDriver());
}

PRIVATE
mrb_value self_driver_count(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_int_value(mrb, SDL_GetNumCameraDrivers());
}

PRIVATE
mrb_value self_driver_name(mrb_state *mrb, mrb_value self) {
    mrb_int index = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &index);

    UNUSED_ARGUMENT self;

    return mrb_str_new_cstr(mrb, SDL_GetCameraDriver(index));
}

PRIVATE
mrb_value self_open(mrb_state *mrb, mrb_value self) {
    struct RClass *camera  = NULL;
    mrb_value      argv[2] = {0};
    mrb_int        which   = 0;
    mrb_value      dest    = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "io", &which, &dest);

    camera  = mrb_class_get(mrb, "Camera");
    argv[0] = mrb_int_value(mrb, which);
    argv[1] = dest;

    return mrb_obj_new(mrb, camera, 2, argv);
}

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    Camera      *camera  = NULL;
    SDL_Surface *frame   = NULL;
    mrb_int      which   = 0;
    mrb_value    ex_name = {0};
    const char  *in_name = NULL;
    mrb_sym      sym     = 0;
    mrb_value    val     = {0};
    mrb_value    dest    = {0};

    IGNORE_RETURN mrb_get_args(mrb, "io", &which, &dest);

    if(mrb_type(dest) != MRB_TT_CDATA) {
        IGNORE_RETURN SDL_SetError("Camera expected an Rect object");
        RaiseTypeError(mrb);
    }

    camera = mrb_calloc(mrb, 1, sizeof(Camera));

    camera->device = SDL_OpenCamera(which, NULL);
    if(!camera->device) {
        RaiseRuntimeError(mrb);
    }

    while(!(frame = SDL_AcquireCameraFrame(camera->device, NULL))) {
        SDL_Delay(1);
    }

    camera->texture = SDL_CreateTexture(private_renderer,
                                        frame->format,
                                        SDL_TEXTUREACCESS_STREAMING,
                                        frame->w,
                                        frame->h);
    if(!camera->texture) {
        RaiseRuntimeError(mrb);
    }

    SDL_ReleaseCameraFrame(camera->device, frame);

    sym = mrb_intern_lit(mrb, "@is_closed");
    val = mrb_false_value();
    mrb_iv_set(mrb, self, sym, val);

    sym = mrb_intern_lit(mrb, "@dest");
    mrb_iv_set(mrb, self, sym, dest);

    in_name = SDL_GetCameraName(which);
    if(!in_name) {
        RaiseRuntimeError(mrb);
    }
    ex_name = mrb_str_new_cstr(mrb, in_name);

    sym = mrb_intern_lit(mrb, "@name");
    val = ex_name;
    mrb_iv_set(mrb, self, sym, val);

    sym = mrb_intern_lit(mrb, "@id");
    val = mrb_int_value(mrb, which);
    mrb_iv_set(mrb, self, sym, val);

    DATA_PTR(self) = camera;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT copy;

    IGNORE_RETURN SDL_SetError("Camera cannot be copied");
    RaiseRuntimeError(mrb);

    return copy;
}

#define RAISE_RUNTIME_IF_CLOSED(camera) \
    if(!camera) {\
        IGNORE_RETURN SDL_SetError("Camera is closed");\
        RaiseRuntimeError(mrb);\
    }

PRIVATE
mrb_value close(mrb_state *mrb, mrb_value self) {
    Camera    *camera = NULL;
    mrb_sym   sym     = 0;
    mrb_value val     = {0};

    camera = DATA_PTR(self);
    RAISE_RUNTIME_IF_CLOSED(camera);

    SDL_CloseCamera(camera->device);
    mrb_free(mrb, camera);

    DATA_PTR(self) = NULL;

    sym = mrb_intern_lit(mrb, "@is_closed");
    val = mrb_true_value();
    mrb_iv_set(mrb, self, sym, val);

    return mrb_nil_value();
}

PRIVATE
mrb_value is_closed(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@is_closed"));
}

PRIVATE
mrb_value permission(mrb_state *mrb, mrb_value self) {
    Camera *camera = DATA_PTR(self);

    RAISE_RUNTIME_IF_CLOSED(camera);

    return mrb_int_value(mrb, SDL_GetCameraPermissionState(camera->device));
}

PRIVATE
mrb_value name(mrb_state *mrb, mrb_value self) {
    Camera *camera = DATA_PTR(self);

    RAISE_RUNTIME_IF_CLOSED(camera);

    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@name"));
}

PRIVATE
mrb_value save(mrb_state *mrb, mrb_value self) {
    Camera      *camera   = NULL;
    SDL_Surface *frame    = NULL;
    SDL_Surface *latest   = NULL;
    Uint64      timestamp = 0;
    int         status    = 0;
    mrb_value   ex_path   = {0};
    const char  *in_path  = NULL;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    camera = DATA_PTR(self);
    RAISE_RUNTIME_IF_CLOSED(camera);

    // https://wiki.libsdl.org/SDL3/CategoryCamera#camera-gotchas

    // 1. Drain any stale frames
    while((frame = SDL_AcquireCameraFrame(camera->device, &timestamp)) != NULL) {
        SDL_ReleaseCameraFrame(camera->device, frame);
    }

    // 2. Wait for ONE new frame
    while(!frame) {
        frame = SDL_AcquireCameraFrame(camera->device, &timestamp);
        if(!frame) {
            SDL_Delay(1);
        }
    }

    latest = frame;

    while((frame = SDL_AcquireCameraFrame(camera->device, &timestamp)) != NULL) {
        if(latest) {
            SDL_ReleaseCameraFrame(camera->device, latest);
        }
        latest = frame;
    }

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = SDL_SaveBMP(latest, in_path);

    SDL_ReleaseCameraFrame(camera->device, latest);

    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, timestamp);
}

PRIVATE
mrb_value update(mrb_state *mrb, mrb_value self) {
    Camera      *camera    = NULL;
    SDL_Surface *frame     = NULL;
    Uint64       timestamp = 0;
    SDL_FRect   *dest      = NULL;
    mrb_sym      sym       = 0;
    mrb_value    val       = {0};

    IGNORE_RETURN mrb;

    camera = DATA_PTR(self);
    RAISE_RUNTIME_IF_CLOSED(camera);

    while((frame = SDL_AcquireCameraFrame(camera->device, &timestamp)) != NULL) {
        SDL_UpdateTexture(camera->texture, NULL, frame->pixels, frame->pitch);
        SDL_ReleaseCameraFrame(camera->device, frame);
    }

    sym  = mrb_intern_lit(mrb, "@dest");
    val  = mrb_iv_get(mrb, self, sym);
    dest = DATA_PTR(val);

    SDL_RenderTexture(private_renderer, camera->texture, NULL, dest);

    return mrb_nil_value();
}

PRIVATE
mrb_value position(mrb_state *mrb, mrb_value self) {
    mrb_int   id  = 0;
    mrb_value val = {0};

    UNUSED_ARGUMENT self;

    val = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@id"));
    id  = mrb_int(mrb, val);

    return mrb_int_value(mrb, SDL_GetCameraPosition(id));
}

PUBLIC
void DefineCameraClass(mrb_state *mrb, SDL_Renderer *renderer) {
    struct RClass *camera = NULL;

    private_renderer = renderer;

    SAVE_ARENA(mrb);

    camera = mrb_define_class(mrb, "Camera", mrb->object_class);

    mrb_define_const(mrb, camera, "PERMISSION_DENIED",     mrb_int_value(mrb, SDL_CAMERA_PERMISSION_STATE_DENIED));
    mrb_define_const(mrb, camera, "PERMISSION_PENDING",    mrb_int_value(mrb, SDL_CAMERA_PERMISSION_STATE_PENDING));
    mrb_define_const(mrb, camera, "PERMISSION_APPROVED",   mrb_int_value(mrb, SDL_CAMERA_PERMISSION_STATE_APPROVED));
    mrb_define_const(mrb, camera, "POSITION_UNKNOWN",      mrb_int_value(mrb, SDL_CAMERA_POSITION_UNKNOWN));
    mrb_define_const(mrb, camera, "POSITION_FRONT_FACING", mrb_int_value(mrb, SDL_CAMERA_POSITION_FRONT_FACING));
    mrb_define_const(mrb, camera, "POSITION_BACK_FACING",  mrb_int_value(mrb, SDL_CAMERA_POSITION_BACK_FACING));

    mrb_define_class_method(mrb, camera, "ids",                 self_ids,                 MRB_ARGS_NONE());
    mrb_define_class_method(mrb, camera, "name",                self_name,                MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, camera, "driver_current_name", self_driver_current_name, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, camera, "driver_count",        self_driver_count,        MRB_ARGS_NONE());
    mrb_define_class_method(mrb, camera, "driver_name",         self_driver_name,         MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, camera, "open",                self_open,                MRB_ARGS_REQ(2));

    mrb_define_method(mrb, camera, "initialize",      initialize,      MRB_ARGS_REQ(2));
    mrb_define_method(mrb, camera, "initialize_copy", initialize_copy, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, camera, "close",           close,           MRB_ARGS_NONE());
    mrb_define_method(mrb, camera, "closed?",         is_closed,       MRB_ARGS_NONE());
    mrb_define_method(mrb, camera, "permission",      permission,      MRB_ARGS_NONE());
    mrb_define_method(mrb, camera, "name",            name,            MRB_ARGS_NONE());
    mrb_define_method(mrb, camera, "save",            save,            MRB_ARGS_REQ(1));
    mrb_define_method(mrb, camera, "update",          update,          MRB_ARGS_NONE());
    mrb_define_method(mrb, camera, "position",        position,        MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
