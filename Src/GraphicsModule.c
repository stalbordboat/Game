// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: The Graphics Context
#include "Internal.h"

PRIVATE mrb_bool    private_fullscreen = FALSE;
PRIVATE mrb_bool    private_hidden     = TRUE;
PRIVATE SDL_Window *private_window     = NULL;

PRIVATE SDL_Color     private_color    = {0, 0, 0, 0};
PRIVATE Uint32        private_blend    = SDL_BLENDMODE_BLEND;
PRIVATE bool          private_is_vsync = TRUE;
PRIVATE SDL_Renderer *private_renderer = NULL;

PRIVATE
mrb_value self_show(mrb_state *mrb, mrb_value self) {
    bool status = false;

    UNUSED_ARGUMENT self;

    status = SDL_ShowWindow(private_window);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    private_hidden = FALSE;

    return mrb_nil_value();
}

PRIVATE
mrb_value self_hide(mrb_state *mrb, mrb_value self) {
    bool status = false;

    UNUSED_ARGUMENT self;

    status = SDL_HideWindow(private_window);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    private_hidden = TRUE;

    return mrb_nil_value();
}

PRIVATE
mrb_value self_size(mrb_state *mrb, mrb_value self) {
    mrb_int width  = 0;
    mrb_int height = 0;
    bool    status = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "ii", &width, &height);

    status = SDL_SetWindowSize(private_window, width, height);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_width(mrb_state *mrb, mrb_value self) {
    int  width  = 0;
    bool status = false;

    UNUSED_ARGUMENT self;

    status = SDL_GetWindowSize(private_window, &width, NULL);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, width);
}

PRIVATE
mrb_value self_height(mrb_state *mrb, mrb_value self) {
    int  height = 0;
    bool status = false;

    UNUSED_ARGUMENT self;

    status = SDL_GetWindowSize(private_window, NULL, &height);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, height);
}

PRIVATE
mrb_value self_title(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_title = {0};
    char      *in_title = NULL;
    bool       status   = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_title);

    in_title = mrb_str_to_cstr(mrb, ex_title);
    status   = SDL_SetWindowTitle(private_window, in_title);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_icon(mrb_state *mrb, mrb_value self) {
    mrb_value    ex_path = {0};
    char        *in_path = NULL;
    SDL_Surface *surface = NULL;
    bool         status  = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_path);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    surface = SDL_LoadBMP(in_path);
    if(!surface) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_SetWindowIcon(private_window, surface);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    SDL_DestroySurface(surface);

    return mrb_nil_value();
}

PRIVATE
mrb_value self_fullscreen(mrb_state *mrb, mrb_value self) {
    mrb_bool value  = FALSE;
    bool     status = false;

    UNUSED_ARGUMENT self;

    mrb_get_args(mrb, "b", &value);

    status = SDL_SetWindowFullscreen(private_window, value);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    private_fullscreen = value;

    return mrb_bool_value(value);
}

PRIVATE
mrb_value self_is_hidden(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(private_hidden);
}

PRIVATE
mrb_value self_is_fullscreen(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(private_fullscreen);
}

PRIVATE
mrb_value self_update(mrb_state *mrb, mrb_value self) {
    bool status = true;

    UNUSED_ARGUMENT self;

    status = SDL_SetRenderDrawBlendMode(private_renderer, private_blend);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_SetRenderDrawColor(private_renderer,
                                    private_color.r,
                                    private_color.g,
                                    private_color.b,
                                    private_color.a);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_RenderClear(private_renderer);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_draw(mrb_state *mrb, mrb_value self) {
    bool status = true;

    UNUSED_ARGUMENT self;

    status = SDL_RenderPresent(private_renderer);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_fill_rect(mrb_state *mrb, mrb_value self) {
    SDL_FRect *in_rect  = DATA_PTR(self);
    SDL_Color *in_color = NULL;
    mrb_value  ex_color = {0};
    mrb_value  ex_rect  = {0};
    bool       status   = true;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "oo", &ex_rect, &ex_color);

    CheckMrbObject(mrb, ex_rect,  "Rect",  "Graphics.fill_rect");
    CheckMrbObject(mrb, ex_color, "Color", "Graphics.fill_rect");

    in_rect  = DATA_PTR(ex_rect);
    in_color = DATA_PTR(ex_color);

    status = SDL_SetRenderDrawColor(private_renderer,
                                    in_color->r,
                                    in_color->g,
                                    in_color->b,
                                    in_color->a);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_RenderFillRect(private_renderer, in_rect);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_fill_point(mrb_state *mrb, mrb_value self) {
    mrb_float  x        = 0;
    mrb_float  y        = 0;
    mrb_value  ex_color = {0};
    SDL_Color *in_color = NULL;
    bool       status   = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "ffo", &x, &y, &ex_color);

    CheckMrbObject(mrb, ex_color, "Color", "Graphics.fill_point");

    in_color = DATA_PTR(ex_color);
    status   = SDL_SetRenderDrawColor(private_renderer,
                                      in_color->r,
                                      in_color->g,
                                      in_color->b,
                                      in_color->a);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_RenderPoint(private_renderer, x, y);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_fill_line(mrb_state *mrb, mrb_value self) {
    mrb_float  x1       = 0;
    mrb_float  y1       = 0;
    mrb_float  x2       = 0;
    mrb_float  y2       = 0;
    mrb_value  ex_color = {0};
    SDL_Color *in_color = NULL;
    bool       status   = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "ffffo", &x1, &y1, &x2, &y2, &ex_color);

    CheckMrbObject(mrb, ex_color, "Color", "Graphics.fill_line");

    in_color = DATA_PTR(ex_color);
    status   = SDL_SetRenderDrawColor(private_renderer,
                                      in_color->r,
                                      in_color->g,
                                      in_color->b,
                                      in_color->a);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_RenderLine(private_renderer, x1, y1, x2, y2);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_blend(mrb_state *mrb, mrb_value self) {
    mrb_int ex_blend = 0;

    UNUSED_ARGUMENT self;

    mrb_get_args(mrb, "i", &ex_blend);

    private_blend = ex_blend;

    return mrb_int_value(mrb, ex_blend);
}

PRIVATE
mrb_value self_color(mrb_state *mrb, mrb_value self) {
    mrb_value  ex_color = {0};
    SDL_Color *color    = NULL;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "o", &ex_color);

    CheckMrbObject(mrb, ex_color, "Color", "Graphics.color");

    color = DATA_PTR(ex_color);

    private_color.r = color->r;
    private_color.g = color->g;
    private_color.b = color->b;
    private_color.a = color->a;

    return ex_color;
}

PRIVATE
mrb_value self_vsync(mrb_state *mrb, mrb_value self) {
    mrb_bool value  = FALSE;
    mrb_bool status = FALSE;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "b", &value);

    status = SDL_SetRenderVSync(private_renderer, value);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    private_is_vsync = value;

    return mrb_bool_value(value);
}

mrb_value self_is_vsync(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    return mrb_bool_value(private_is_vsync);
}

PRIVATE
mrb_value self_get_name(mrb_state *mrb, mrb_value self) {
    const char *name = NULL;

    UNUSED_ARGUMENT self;

    name = SDL_GetRendererName(private_renderer);
    if(!name) {
        RaiseRuntimeError(mrb);
    }

    return mrb_str_new_cstr(mrb, name);
}

PRIVATE
mrb_value self_max_size(mrb_state *mrb, mrb_value self) {
    SDL_PropertiesID prop  = 0;
    mrb_int          value = 0;

    UNUSED_ARGUMENT self;

    prop = SDL_GetRendererProperties(private_renderer);
    if(prop == 0) {
        RaiseRuntimeError(mrb);
    }

    value = SDL_GetNumberProperty(prop, SDL_PROP_RENDERER_MAX_TEXTURE_SIZE_NUMBER, 0);

    return mrb_int_value(mrb, value);
}

PRIVATE
mrb_value self_viewport(mrb_state *mrb, mrb_value self) {
    SDL_FRect *f_rect  = NULL;
    SDL_Rect   rect    = {0};
    mrb_value  ex_rect = {0};
    bool       status  = true;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "o", &ex_rect);

    CheckMrbObject(mrb, ex_rect, "Rect", "Graphics.viewport");

    f_rect = DATA_PTR(ex_rect);
    rect.x = f_rect->x;
    rect.y = f_rect->y;
    rect.w = f_rect->w;
    rect.h = f_rect->h;

    status = SDL_SetRenderViewport(private_renderer, &rect);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
bool InternalSave(SDL_Surface *surface, const char *path) {
    bool status = true;

    status = HasExtname(path, ".bmp");
    if(status) {
        status = SDL_SaveBMP(surface, path);
        if(!status) {
                return false;
        }
    }

    status = HasExtname(path, ".png");
    if(status) {
        status = SDL_SavePNG(surface, path);
        if(!status) {
            return false;
        }
    }

    return true;
}

PRIVATE
mrb_value self_save(mrb_state *mrb, mrb_value self) {
    SDL_Surface  *surface = NULL;
    char         *in_path = NULL;
    mrb_value     ex_path = {0};
    bool          status  = true;
    mrb_value     ex_rect = {0};
    SDL_FRect    *in_rect = NULL;
    SDL_Rect      rect    = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S|o", &ex_path, &ex_rect);

    if(!mrb_nil_p(ex_rect)) {
        CheckMrbObject(mrb, ex_rect, "Rect", "Graphics.save");

        in_rect = DATA_PTR(ex_rect);
        rect.x  = in_rect->x;
        rect.y  = in_rect->y;
        rect.w  = in_rect->w;
        rect.h  = in_rect->h;

        surface = CreateSurfaceFromRenderer(private_renderer, &rect);
    }
    else {
        surface = CreateSurfaceFromRenderer(private_renderer, NULL);
    }

    if(!surface) {
        RaiseRuntimeError(mrb);
    }

    in_path = mrb_str_to_cstr(mrb, ex_path);
    status  = InternalSave(surface, in_path);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    SDL_DestroySurface(surface);

    return mrb_nil_value();
}

PRIVATE
mrb_value self_get_pixel(mrb_state *mrb, mrb_value self) {
    mrb_int        x        = 0;
    mrb_int        y        = 0;
    SDL_Surface   *surface  = NULL;
    SDL_Color      in_color = {0};
    struct RClass *klass    = NULL;
    mrb_value      argv[4]  = {0};
    mrb_value      ex_color = {0};
    bool           status   = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "ii", &x, &y);

    surface = CreateSurfaceFromRenderer(private_renderer, NULL);
    if(!surface) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_ReadSurfacePixel(surface, x, y, &in_color.r, &in_color.g, &in_color.b, &in_color.a);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    klass    = mrb_class_get(mrb, "Color");
    argv[0]  = mrb_int_value(mrb, in_color.r);
    argv[1]  = mrb_int_value(mrb, in_color.g);
    argv[2]  = mrb_int_value(mrb, in_color.b);
    argv[3]  = mrb_int_value(mrb, in_color.a);
    ex_color = mrb_obj_new(mrb, klass, 4, argv);

    SDL_DestroySurface(surface);

    return ex_color;
}

PRIVATE
mrb_value self_presentation(mrb_state *mrb, mrb_value self) {
    mrb_int mode   = SDL_LOGICAL_PRESENTATION_LETTERBOX;
    mrb_int width  = DEFAULT_WINDOW_WIDTH;
    mrb_int height = DEFAULT_WINDOW_HEIGHT;
    bool    status = false;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "|iii", &mode, &width, &height);

    status = SDL_SetRenderLogicalPresentation(private_renderer,
                                              width,
                                              height,
                                              mode);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_screenshot(mrb_state *mrb, mrb_value self) {
    mrb_value      ex_dest = {0};
    mrb_value      image   = {0};
    struct RClass *klass   = {0};
    mrb_value      argv[1] = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "o", &ex_dest);

    CheckMrbObject(mrb, ex_dest, "Rect", "Graphics.screenshot");

    klass   = mrb_class_get(mrb, "Image");
    argv[0] = ex_dest;
    image   = mrb_obj_new(mrb, klass, 1, argv);

    return image;
}

PUBLIC
void DefineGraphicsModule(mrb_state *mrb, SDL_Window *window, SDL_Renderer *renderer) {
    struct RClass *graphics = NULL;

    private_window   = window;
    private_renderer = renderer;

    SAVE_ARENA(mrb);

    graphics = mrb_define_module(mrb, "Graphics");

    mrb_define_const(mrb, graphics, "FLIP_NONE",                  mrb_int_value(mrb, SDL_FLIP_NONE));
    mrb_define_const(mrb, graphics, "FLIP_HORZ",                  mrb_int_value(mrb, SDL_FLIP_HORIZONTAL));
    mrb_define_const(mrb, graphics, "FLIP_VERT",                  mrb_int_value(mrb, SDL_FLIP_VERTICAL));
    mrb_define_const(mrb, graphics, "BLEND_NONE",                 mrb_int_value(mrb, SDL_BLENDMODE_NONE));
    mrb_define_const(mrb, graphics, "BLEND_ALPHA",                mrb_int_value(mrb, SDL_BLENDMODE_BLEND));
    mrb_define_const(mrb, graphics, "BLEND_ADD",                  mrb_int_value(mrb, SDL_BLENDMODE_ADD));
    mrb_define_const(mrb, graphics, "BLEND_MULTIPLY",             mrb_int_value(mrb, SDL_BLENDMODE_MOD));
    mrb_define_const(mrb, graphics, "PRESENTATION_DISABLED",      mrb_int_value(mrb, SDL_LOGICAL_PRESENTATION_DISABLED));
    mrb_define_const(mrb, graphics, "PRESENTATION_STRETCH",       mrb_int_value(mrb, SDL_LOGICAL_PRESENTATION_STRETCH));
    mrb_define_const(mrb, graphics, "PRESENTATION_LETTERBOX",     mrb_int_value(mrb, SDL_LOGICAL_PRESENTATION_LETTERBOX));
    mrb_define_const(mrb, graphics, "PRESENTATION_OVERSCAN",      mrb_int_value(mrb, SDL_LOGICAL_PRESENTATION_OVERSCAN));
    mrb_define_const(mrb, graphics, "PRESENTATION_INTEGER_SCALE", mrb_int_value(mrb, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE));

    // Window Abstraction

    mrb_define_module_function(mrb, graphics, "show",        self_show,          MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "hide",        self_hide,          MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "size",        self_size,          MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, graphics, "width",       self_width,         MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "height",      self_height,        MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "title",       self_title,         MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, graphics, "icon",        self_icon,          MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, graphics, "fullscreen",  self_fullscreen,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, graphics, "hidden?",     self_is_hidden,     MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "fullscreen?", self_is_fullscreen, MRB_ARGS_NONE());

    // Renderer Abstraction

    mrb_define_module_function(mrb, graphics, "update",       self_update,       MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "draw",         self_draw,         MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "fill_rect",    self_fill_rect,    MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, graphics, "fill_point",   self_fill_point,   MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, graphics, "fill_line",    self_fill_line,    MRB_ARGS_REQ(5));
    mrb_define_module_function(mrb, graphics, "blend",        self_blend,        MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, graphics, "color",        self_color,        MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, graphics, "vsync",        self_vsync,        MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, graphics, "vsync?",       self_is_vsync,     MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "name",         self_get_name,     MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "max_size",     self_max_size,     MRB_ARGS_NONE());
    mrb_define_module_function(mrb, graphics, "viewport",     self_viewport,     MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, graphics, "save",         self_save,         MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, graphics, "get_pixel",    self_get_pixel,    MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, graphics, "presentation", self_presentation, MRB_ARGS_OPT(3));
    mrb_define_module_function(mrb, graphics, "screenshot",   self_screenshot,   MRB_ARGS_REQ(1)|MRB_ARGS_KEY(1, 1));

    RESTORE_ARENA(mrb);
}
