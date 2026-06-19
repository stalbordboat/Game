// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Represents In-Memory Audio Data
#include "Internal.h"

PRIVATE MIX_Mixer *private_mixer   = NULL;
PRIVATE MIX_Track **private_tracks = NULL;

PRIVATE
void sound_dispose(mrb_state *mrb, Buffer *sound) {
    UNUSED_ARGUMENT mrb;

    FreeSound(sound);
}

PRIVATE struct mrb_data_type sound_data = { "Sound", sound_dispose };

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    Sound      *sound   = NULL;
    char       *in_path = NULL;
    mrb_value   ex_path = {0};
    mrb_int     track   = 0;
    mrb_sym     sym     = 0;
    mrb_value   val     = {0};

    IGNORE_RETURN mrb_get_args(mrb, "S|i", &ex_path, &track);

    in_path = mrb_str_to_cstr(mrb, ex_path);
    sound   = LoadSoundFromFile(in_path);
    if(!sound) {
        RaiseRuntimeError(mrb);
    }

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_int_value(mrb, track);
    mrb_iv_set(mrb, self, sym, val);

    DATA_PTR(self)  = sound;
    DATA_TYPE(self) = &sound_data;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT copy;

    IGNORE_RETURN SDL_SetError("Sound cannot be copied");
    RaiseRuntimeError(mrb);

    return copy;
}

PRIVATE
mrb_value get_volume(mrb_state *mrb, mrb_value self) {
    mrb_int   track = 0;
    mrb_sym   sym   = 0;
    mrb_value val   = {0};

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);

    return mrb_float_value(mrb, GetVolumeTrackMixer(track));
}

PRIVATE
mrb_value set_volume(mrb_state *mrb, mrb_value self) {
    bool      status = false;
    mrb_int   track  = 0;
    mrb_float volume = 0.0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    IGNORE_RETURN mrb_get_args(mrb, "f", &volume);

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = SetVolumeTrackMixer(track, volume);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_float_value(mrb, volume);
}

PRIVATE
mrb_value get_track(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@track"));
}

PRIVATE
mrb_value set_track(mrb_state *mrb, mrb_value self) {
    mrb_int   track = 0;
    mrb_sym   sym   = 0;
    mrb_value val   = {0};

    IGNORE_RETURN mrb_get_args(mrb, "i", &track);

    sym = mrb_intern_lit(mrb, "@track");
    val = mrb_int_value(mrb, track);
    mrb_iv_set(mrb, self, sym, val);

    return val;
}

PRIVATE
mrb_value play(mrb_state *mrb, mrb_value self) {
    Sound    *sound  = DATA_PTR(self);
    bool      status = false;
    mrb_int   loops  = 0;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    IGNORE_RETURN mrb_get_args(mrb, "|i", &loops);

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = PlaySound(sound, track, loops);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value fadein(mrb_state *mrb, mrb_value self) {
    Sound    *sound        = DATA_PTR(self);
    bool      status       = false;
    mrb_int   loops        = 0;
    mrb_int   milliseconds = 0;
    mrb_int   track        = 0;
    mrb_sym   sym          = 0;
    mrb_value val          = {0};

    IGNORE_RETURN mrb_get_args(mrb, "|ii", &loops, &milliseconds);

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = FadeInSound(sound, track, loops, milliseconds);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value fadeout(mrb_state *mrb, mrb_value self) {
    bool      status       = false;
    mrb_int   milliseconds = 0;
    mrb_int   track        = 0;
    mrb_sym   sym          = 0;
    mrb_value val          = {0};

    IGNORE_RETURN mrb_get_args(mrb, "i", &milliseconds);

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = FadeOutTrackMixer(track, milliseconds);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PUBLIC
void DefineSoundClass(mrb_state *mrb, MIX_Mixer *in_mixer, MIX_Track **tracks) {
    struct RClass *sound = NULL;
    struct RClass *mixer = NULL;

    private_mixer  = in_mixer;
    private_tracks = tracks;

    SAVE_ARENA(mrb);

    sound = mrb_define_class(mrb, "Sound", mrb->object_class);
    SET_INSTANCE_TYPE(sound);

    mixer = mrb_module_get(mrb, "Mixer");
    mrb_include_module(mrb, sound, mixer);

    mrb_define_const(mrb, sound, "PLAY_ONCE",     mrb_int_value(mrb, 0));
    mrb_define_const(mrb, sound, "PLAY_INFINITE", mrb_int_value(mrb, -1));

    mrb_define_method(mrb, sound, "initialize",      initialize,      MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
    mrb_define_method(mrb, sound, "initialize_copy", initialize_copy, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sound, "volume",          get_volume,      MRB_ARGS_NONE());
    mrb_define_method(mrb, sound, "volume=",         set_volume,      MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sound, "track",           get_track,       MRB_ARGS_NONE());
    mrb_define_method(mrb, sound, "track=",          set_track,       MRB_ARGS_REQ(1));
    mrb_define_method(mrb, sound, "play",            play,            MRB_ARGS_OPT(1));
    mrb_define_method(mrb, sound, "fadein",          fadein,          MRB_ARGS_OPT(2));
    mrb_define_method(mrb, sound, "fadeout",         fadeout,         MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}
