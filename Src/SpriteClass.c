// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Represents Texture Atlases
#include "Internal.h"

PRIVATE SDL_Renderer *private_renderer = NULL;

PRIVATE
void SetupSpriteInstanceVariables(mrb_state *mrb,
                                  mrb_value  self,
                                  Image     *in_image,
                                  mrb_value  ex_image,
                                  mrb_int    width,
                                  mrb_int    height) {
    struct RClass *klass          = NULL;
    mrb_value      argv[4]        = {0};
    mrb_sym        sym            = 0;
    mrb_value      val            = {0};
    float          image_width    = 0.0;
    float          image_height   = 0.0;
    SDL_Color      image_color    = {0};
    float          image_center_x = 0.0;
    float          image_center_y = 0.0;

    sym = mrb_intern_lit(mrb, "@image");
    val = ex_image;
    mrb_iv_set(mrb, self, sym, val);

    klass = mrb_class_get(mrb, "Rect");

    val = mrb_funcall(mrb, ex_image, "dest", 0);
    val = mrb_funcall(mrb, val, "width", 0);
    image_width = mrb_float(val);

    val = mrb_funcall(mrb, ex_image, "dest", 0);
    val = mrb_funcall(mrb, val, "height", 0);
    image_height = mrb_float(val);

    sym     = mrb_intern_lit(mrb, "@src");
    argv[0] = mrb_float_value(mrb, 0);
    argv[1] = mrb_float_value(mrb, 0);
    argv[2] = mrb_float_value(mrb, image_width / width);
    argv[3] = mrb_float_value(mrb, image_height / height);
    val     = mrb_obj_new(mrb, klass, 4, argv);
    mrb_iv_set(mrb, self, sym, val);

    sym     = mrb_intern_lit(mrb, "@dest");
    argv[0] = mrb_float_value(mrb, 0);
    argv[1] = mrb_float_value(mrb, 0);
    argv[2] = mrb_float_value(mrb, image_width / width);
    argv[3] = mrb_float_value(mrb, image_height / height);
    val     = mrb_obj_new(mrb, klass, 4, argv);
    mrb_iv_set(mrb, self, sym, val);

    klass = mrb_class_get(mrb, "Color");

    val = mrb_funcall(mrb, ex_image, "color", 0);
    val = mrb_funcall(mrb, val, "red", 0);
    image_color.r = mrb_int(mrb, val);

    val = mrb_funcall(mrb, ex_image, "color", 0);
    val = mrb_funcall(mrb, val, "green", 0);
    image_color.g = mrb_int(mrb, val);

    val = mrb_funcall(mrb, ex_image, "color", 0);
    val = mrb_funcall(mrb, val, "blue", 0);
    image_color.b = mrb_int(mrb, val);

    val = mrb_funcall(mrb, ex_image, "color", 0);
    val = mrb_funcall(mrb, val, "alpha", 0);
    image_color.a = mrb_int(mrb, val);

    sym     = mrb_intern_lit(mrb, "@color");
    argv[0] = mrb_int_value(mrb, image_color.r);
    argv[1] = mrb_int_value(mrb, image_color.g);
    argv[2] = mrb_int_value(mrb, image_color.b);
    argv[3] = mrb_int_value(mrb, image_color.a);
    val     = mrb_obj_new(mrb, klass, 4, argv);
    mrb_iv_set(mrb, self, sym, val);

    klass = mrb_class_get(mrb, "Point");

    val = mrb_funcall(mrb, ex_image, "center", 0);
    val = mrb_funcall(mrb, val, "x", 0);
    image_center_x = mrb_float(val);

    val = mrb_funcall(mrb, ex_image, "center", 0);
    val = mrb_funcall(mrb, val, "y", 0);
    image_center_y = mrb_float(val);

    sym     = mrb_intern_lit(mrb, "@center");
    argv[0] = mrb_float_value(mrb, image_center_x);
    argv[1] = mrb_float_value(mrb, image_center_y);
    val     = mrb_obj_new(mrb, klass, 2, argv);
    mrb_iv_set(mrb, self, sym, val);

    sym = mrb_intern_lit(mrb, "@angle");
    val = mrb_float_value(mrb, in_image->angle);
    mrb_iv_set(mrb, self, sym, val);

    sym = mrb_intern_lit(mrb, "@flip");
    val = mrb_int_value(mrb, in_image->flip);
    mrb_iv_set(mrb, self, sym, val);

    sym = mrb_intern_lit(mrb, "@blend");
    val = mrb_int_value(mrb, in_image->blend);
    mrb_iv_set(mrb, self, sym, val);
}

PRIVATE
void DuplicateSpriteInstanceVariables(mrb_state *mrb, mrb_value orig, mrb_value copy) {
    mrb_value val = {0};
    mrb_sym   sym = 0;

    sym = mrb_intern_lit(mrb, "@image");
    val = mrb_iv_get(mrb, orig, sym);
    val = mrb_obj_dup(mrb, val);
    mrb_iv_set(mrb, copy, sym, val);

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

    sym = mrb_intern_lit(mrb, "@blend");
    val = mrb_iv_get(mrb, orig, sym);
    val = mrb_obj_dup(mrb, val);
    mrb_iv_set(mrb, copy, sym, val);

    sym = mrb_intern_lit(mrb, "@angle");
    val = mrb_iv_get(mrb, orig, sym);
    val = mrb_obj_dup(mrb, val);
    mrb_iv_set(mrb, copy, sym, val);

    sym = mrb_intern_lit(mrb, "@flip");
    val = mrb_iv_get(mrb, orig, sym);
    val = mrb_obj_dup(mrb, val);
    mrb_iv_set(mrb, copy, sym, val);
}

PRIVATE
void sprite_dispose(mrb_state *mrb, Buffer *sprite) {
    UNUSED_ARGUMENT mrb;

    DestroySprite(sprite);
}

PRIVATE struct mrb_data_type sprite_data = { "Sprite", sprite_dispose };

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    Sprite    *sprite   = NULL;
    Image     *in_image = NULL;
    mrb_value  ex_image = {0};
    mrb_int    width    = 0;
    mrb_int    height   = 0;

    IGNORE_RETURN mrb_get_args(mrb, "iio", &width, &height, &ex_image);

    if(mrb_type(ex_image) != MRB_TT_CDATA) {
        IGNORE_RETURN SDL_SetError("Sprite expected an Image object");
        RaiseTypeError(mrb);
    }

    in_image = DATA_PTR(ex_image);
    sprite   = CreateSprite(in_image);
    if(!sprite) {
        RaiseRuntimeError(mrb);
    }

    SetupSpriteInstanceVariables(mrb, self, in_image, ex_image, width, height);

    DATA_PTR(self)  = sprite;
    DATA_TYPE(self) = &sprite_data;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    mrb_value  orig = {0};
    Image     *src  = NULL;
    Image     *dest = NULL;

    IGNORE_RETURN mrb_get_args(mrb, "o", &orig);

    src   = DATA_PTR(orig);
    dest  = mrb_calloc(mrb, 1, sizeof(Sprite));
    *dest = *src;

    DuplicateSpriteInstanceVariables(mrb, orig, copy);

    DATA_PTR(copy)  = dest;
    DATA_TYPE(copy) = DATA_TYPE(orig);

    return copy;
}

PRIVATE
mrb_value sprite_update(mrb_state *mrb, mrb_value self) {
    Sprite     *sprite = DATA_PTR(self);
    SDL_Color  *color  = NULL;
    SDL_FRect  *dest   = NULL;
    SDL_FRect  *src    = NULL;
    SDL_FPoint *center = NULL;
    bool        status = true;
    mrb_value   val    = {0};
    mrb_sym     sym    = 0;

    sym   = mrb_intern_lit(mrb, "@color");
    val   = mrb_iv_get(mrb, self, sym);
    color = DATA_PTR(val);

    sym  = mrb_intern_lit(mrb, "@dest");
    val  = mrb_iv_get(mrb, self, sym);
    dest = DATA_PTR(val);

    sym  = mrb_intern_lit(mrb, "@src");
    val  = mrb_iv_get(mrb, self, sym);
    src  = DATA_PTR(val);

    sym    = mrb_intern_lit(mrb, "@center");
    val    = mrb_iv_get(mrb, self, sym);
    center = DATA_PTR(val);

    status = UpdateImage(sprite, src, dest, center, color);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value sprite_src(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@src"));
}

PRIVATE
mrb_value sprite_dest(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@dest"));
}

PRIVATE
mrb_value sprite_color(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@color"));
}

PRIVATE
mrb_value sprite_center(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@center"));
}

PRIVATE
mrb_value sprite_get_angle(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@angle"));
}

PRIVATE
mrb_value sprite_get_flip(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@flip"));
}

PRIVATE
mrb_value sprite_get_blend(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@blend"));
}

PRIVATE
mrb_value sprite_set_angle(mrb_state *mrb, mrb_value self) {
    Sprite    *sprite = NULL;
    mrb_float  angle  = 0.0;
    mrb_value  val    = {0};
    mrb_sym    sym    = 0;

    IGNORE_RETURN mrb_get_args(mrb, "f", &angle);

    sprite        = DATA_PTR(self);
    sprite->angle = angle;
    sym           = mrb_intern_lit(mrb, "@angle");
    val           = mrb_float_value(mrb, sprite->angle);
    mrb_iv_set(mrb, self, sym, val);

    return val;
}

PRIVATE
mrb_value sprite_set_flip(mrb_state *mrb, mrb_value self) {
    Sprite    *sprite = NULL;
    mrb_int    flip   = 0;
    mrb_value  val    = {0};
    mrb_sym    sym    = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &flip);

    sprite       = DATA_PTR(self);
    sprite->flip = flip;
    sym          = mrb_intern_lit(mrb, "@flip");
    val          = mrb_int_value(mrb, sprite->flip);
    mrb_iv_set(mrb, self, sym, val);

    return val;
}

PRIVATE
mrb_value sprite_set_blend(mrb_state *mrb, mrb_value self) {
    Sprite    *sprite = NULL;
    mrb_int    blend  = 0;
    mrb_value  val    = {0};
    mrb_sym    sym    = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &blend);

    sprite        = DATA_PTR(self);
    sprite->blend = blend;
    sym           = mrb_intern_lit(mrb, "@blend");
    val           = mrb_int_value(mrb, sprite->blend);
    mrb_iv_set(mrb, self, sym, val);

    return val;
}

PRIVATE
mrb_value sprite_get_image(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@image"));
}

PUBLIC
void DefineSpriteClass(mrb_state *mrb, SDL_Renderer *renderer) {
    struct RClass *sprite = NULL;

    private_renderer = renderer;

    SAVE_ARENA(mrb);

    sprite = mrb_define_class(mrb, "Sprite", mrb->object_class);
    SET_INSTANCE_TYPE(sprite);

    mrb_define_method(mrb, sprite, "initialize",      initialize,       MRB_ARGS_REQ(3));
    mrb_define_method(mrb, sprite, "initialize_copy", initialize_copy,  MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "update",          sprite_update,    MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "src",             sprite_src,       MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "dest",            sprite_dest,      MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "color",           sprite_color,     MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "center",          sprite_center,    MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "angle",           sprite_get_angle, MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "flip",            sprite_get_flip,  MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "blend",           sprite_get_blend, MRB_ARGS_NONE());
    mrb_define_method(mrb, sprite, "angle=",          sprite_set_angle, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "flip=",           sprite_set_flip,  MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "blend=",          sprite_set_blend, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sprite, "image",           sprite_get_image, MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
