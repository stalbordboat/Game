// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: 2D Rendering object for a whole(non-cliped) static texture.
#include "Internal.h"

#define KLASS_NAME "Image"

PRIVATE SDL_Renderer *private_renderer = NULL;

PRIVATE SDL_INLINE
SDL_Color *ColorKey(mrb_value *kw_values) {
    SDL_Color *color_key = NULL;

    if(mrb_data_p(kw_values[0])) {
        const char *name = DATA_TYPE(kw_values[0])->struct_name;

        if(SDL_strcmp(name, "Color") == 0) {
            color_key = DATA_PTR(kw_values[0]);
        }
    }

    return color_key;
}

PRIVATE
void SetupImageClassInstanceVariables(mrb_state *mrb, mrb_value self, Image *image) {
    struct RClass *klass   = NULL;
    mrb_value      argv[4] = {0};
    mrb_sym        sym     = 0;
    mrb_value      val     = {0};
    bool           status  = true;
    float          width   = 0.0;
    float          height  = 0.0;

    status = SDL_GetTextureSize(image->texture, &width, &height);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    klass = mrb_class_get(mrb,  "Rect");

    sym     = mrb_intern_lit(mrb, "@dest");
    argv[0] = mrb_float_value(mrb, 0);
    argv[1] = mrb_float_value(mrb, 0);
    argv[2] = mrb_float_value(mrb, width);
    argv[3] = mrb_float_value(mrb, height);
    val     = mrb_obj_new(mrb, klass, 4, argv);
    mrb_iv_set(mrb, self, sym, val);

    klass   = mrb_class_get(mrb,  "Color");
    sym     = mrb_intern_lit(mrb, "@color");
    argv[0] = mrb_int_value(mrb, OPAQUE_COLOR_VALUE);
    argv[1] = mrb_int_value(mrb, OPAQUE_COLOR_VALUE);
    argv[2] = mrb_int_value(mrb, OPAQUE_COLOR_VALUE);
    argv[3] = mrb_int_value(mrb, OPAQUE_COLOR_VALUE);
    val     = mrb_obj_new(mrb, klass, 4, argv);
    mrb_iv_set(mrb, self, sym, val);

    klass   = mrb_class_get(mrb,  "Point");
    sym     = mrb_intern_lit(mrb, "@center");
    argv[0] = mrb_float_value(mrb, 0.0);
    argv[1] = mrb_float_value(mrb, 0.0);
    val     = mrb_obj_new(mrb, klass, 2, argv);
    mrb_iv_set(mrb, self, sym, val);
}

PRIVATE
void DuplicateImageClassInstanceVariables(mrb_state *mrb, mrb_value orig, mrb_value copy) {
    mrb_sym   sym = 0;
    mrb_value val = {0};

    sym = mrb_intern_lit(mrb, "@center");
    val = mrb_iv_get(mrb, orig, sym);
    val = mrb_obj_dup(mrb, val);
    mrb_iv_set(mrb, copy, sym, val);

    sym = mrb_intern_lit(mrb, "@dest");
    val = mrb_iv_get(mrb, orig, sym);
    val = mrb_obj_dup(mrb, val);
    mrb_iv_set(mrb, copy, sym, val);

    sym = mrb_intern_lit(mrb, "@color");
    val = mrb_iv_get(mrb, orig, sym);
    val = mrb_obj_dup(mrb, val);
    mrb_iv_set(mrb, copy, sym, val);
}

PRIVATE
void image_dispose(mrb_state *mrb, Buffer *image) {
    UNUSED_ARGUMENT mrb;

    DestroyImage(image);
}

PRIVATE struct mrb_data_type image_data = { KLASS_NAME, image_dispose };

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    Image         *image        = NULL;
    mrb_value      ex_path      = {0};
    char          *in_path      = NULL;
    mrb_value      kw_values[1] = {0};
    mrb_kwargs     kw_args      = {0};
    mrb_sym        kw_names[1]  = {0};
    SDL_Color     *color_key    = NULL;

    kw_names[0]  = mrb_intern_cstr(mrb, "color_key");
    kw_values[0] = mrb_nil_value();

    kw_args.num      = 1;
    kw_args.required = 0;
    kw_args.table    = kw_names;
    kw_args.values   = kw_values;

    IGNORE_RETURN mrb_get_args(mrb, "S:", &ex_path, &kw_args);

    color_key = ColorKey(kw_values);
    in_path   = mrb_str_to_cstr(mrb, ex_path);
    image     = CreateImage(in_path, color_key);
    if(!image) {
        RaiseRuntimeError(mrb);
    }

    SetupImageClassInstanceVariables(mrb, self, image);

    DATA_PTR(self)  = image;
    DATA_TYPE(self) = &image_data;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    mrb_value  orig = {0};
    Image     *src  = NULL;
    Image     *dest = NULL;

    IGNORE_RETURN mrb_get_args(mrb, "o", &orig);

    src   = DATA_PTR(orig);
    dest  = mrb_calloc(mrb, 1, sizeof(Image));
    *dest = *src;

    src->texture->refcount++;

    DuplicateImageClassInstanceVariables(mrb, orig, copy);

    DATA_PTR(copy)  = dest;
    DATA_TYPE(copy) = DATA_TYPE(orig);

    return copy;
}

PRIVATE
mrb_value update(mrb_state *mrb, mrb_value self) {
    Image      *image  = DATA_PTR(self);
    bool        status = true;
    mrb_value   val    = {0};
    mrb_sym     sym    = 0;
    SDL_Color  *color  = NULL;
    SDL_FRect  *dest   = NULL;
    SDL_FPoint *center = NULL;

    sym   = mrb_intern_lit(mrb, "@color");
    val   = mrb_iv_get(mrb, self, sym);
    color = DATA_PTR(val);

    sym  = mrb_intern_lit(mrb, "@dest");
    val  = mrb_iv_get(mrb, self, sym);
    dest = DATA_PTR(val);

    sym    = mrb_intern_lit(mrb, "@center");
    val    = mrb_iv_get(mrb, self, sym);
    center = DATA_PTR(val);

    status = UpdateImage(image, NULL, dest, center, color);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value dest(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@dest"));
}

PRIVATE
mrb_value color(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@color"));
}

PRIVATE
mrb_value center(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@center"));
}

PRIVATE
mrb_value get_angle(mrb_state *mrb, mrb_value self) {
    Image *image = DATA_PTR(self);

    return mrb_float_value(mrb, image->angle);
}

PRIVATE
mrb_value get_flip(mrb_state *mrb, mrb_value self) {
    Image *image = DATA_PTR(self);

    return mrb_int_value(mrb, image->flip);
}

PRIVATE
mrb_value get_blend(mrb_state *mrb, mrb_value self) {
    Image *image = DATA_PTR(self);

    return mrb_int_value(mrb, image->blend);
}

PRIVATE
mrb_value set_angle(mrb_state *mrb, mrb_value self) {
    Image     *image = NULL;
    mrb_float  angle = 0.0;

    IGNORE_RETURN mrb_get_args(mrb, "f", &angle);

    image        = DATA_PTR(self);
    image->angle = angle;

    return mrb_float_value(mrb, image->angle);
}

PRIVATE
mrb_value set_flip(mrb_state *mrb, mrb_value self) {
    Image   *image = NULL;
    mrb_int  flip  = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &flip);

    image       = DATA_PTR(self);
    image->flip = flip;

    return mrb_int_value(mrb, image->flip);
}

PRIVATE
mrb_value set_blend(mrb_state *mrb, mrb_value self) {
    Image   *image = NULL;
    mrb_int  blend = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &blend);

    image        = DATA_PTR(self);
    image->blend = blend;

    return mrb_int_value(mrb, image->blend);
}

PUBLIC
void DefineImageClass(mrb_state *mrb, SDL_Renderer *renderer) {
    struct RClass *image = NULL;

    private_renderer = renderer;

    SAVE_ARENA(mrb);

    image = mrb_define_class(mrb, KLASS_NAME, mrb->object_class);
    SET_INSTANCE_TYPE(image);

    mrb_define_method(mrb, image, "initialize",      initialize,      MRB_ARGS_REQ(1)|MRB_ARGS_KEY(1, 1));
    mrb_define_method(mrb, image, "initialize_copy", initialize_copy, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, image, "update",          update,          MRB_ARGS_NONE());
    mrb_define_method(mrb, image, "dest",            dest,            MRB_ARGS_NONE());
    mrb_define_method(mrb, image, "color",           color,           MRB_ARGS_NONE());
    mrb_define_method(mrb, image, "center",          center,          MRB_ARGS_NONE());
    mrb_define_method(mrb, image, "angle",           get_angle,       MRB_ARGS_NONE());
    mrb_define_method(mrb, image, "flip",            get_flip,        MRB_ARGS_NONE());
    mrb_define_method(mrb, image, "blend",           get_blend,       MRB_ARGS_NONE());
    mrb_define_method(mrb, image, "angle=",          set_angle,       MRB_ARGS_REQ(1));
    mrb_define_method(mrb, image, "flip=",           set_flip,        MRB_ARGS_REQ(1));
    mrb_define_method(mrb, image, "blend=",          set_blend,       MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}
