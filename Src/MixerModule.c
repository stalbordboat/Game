// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Handles control over mixing functions some of which are mixed-in with other audio related objects.
#include "Internal.h"

PRIVATE
mrb_value self_reopen(mrb_state *mrb, mrb_value self) {
    bool              status   = false;
    SDL_AudioSpec     spec     = {0};
    SDL_AudioDeviceID id       = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;
    mrb_int           channels = MIX_DEFAULT_CHANNELS;
    mrb_int           format   = MIX_DEFAULT_FORMAT;
    mrb_int           freq     = MIX_DEFAULT_FREQUENCY;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "|iii", &channels, &format, &freq);

    mrb_full_gc(mrb);

    CloseAudio();

    spec.channels = channels;
    spec.format   = format;
    spec.freq     = freq;

    status = OpenAudio(id, &spec);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_stop(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    bool status = false;

    status = FadeOutMixer(0);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_fadeout(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    bool    status       = false;
    mrb_int milliseconds = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &milliseconds);

    status = FadeOutMixer(milliseconds);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_get_volume(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    return mrb_float_value(mrb, GetVolumeMixer());
}

PRIVATE
mrb_value self_set_volume(mrb_state *mrb, mrb_value self) {
    UNUSED_ARGUMENT self;

    bool      status = false;
    mrb_float value  = 0.0;

    IGNORE_RETURN mrb_get_args(mrb, "f", &value);

    status = SetVolumeMixer(value);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_float_value(mrb, value);
}

PRIVATE
mrb_value pause(mrb_state *mrb, mrb_value self) {
    bool      status = false;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = PauseMixer(track);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value resume(mrb_state *mrb, mrb_value self) {
    bool      status = false;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = ResumeMixer(track);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value stop(mrb_state *mrb, mrb_value self) {
    bool      status = false;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = StopMixer(track);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value is_playing(mrb_state *mrb, mrb_value self) {
    bool      status = 0;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = IsPlayingMixer(track);

    return mrb_bool_value(status);
}

PRIVATE
mrb_value is_paused(mrb_state *mrb, mrb_value self) {
    bool      status = 0;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = IsPausedMixer(track);

    return mrb_bool_value(status);
}

PRIVATE
mrb_value reverse_stereo(mrb_state *mrb, mrb_value self) {
    bool      status = true;
    mrb_bool  enable = TRUE;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "|b", &enable);

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = SetReverseStereoMixer(track, enable);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value position(mrb_state *mrb, mrb_value self) {
    bool         status   = false;
    mrb_value    ex_point = {0};
    MIX_Point3D *in_point = NULL;
    mrb_int      track    = 0;
    mrb_sym      sym      = 0;
    mrb_value    val      = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "o", &ex_point);

    sym      = mrb_intern_lit(mrb, "@track");
    val      = mrb_iv_get(mrb, self, sym);
    track    = mrb_int(mrb, val);
    in_point = DATA_PTR(ex_point);
    status   = SetPositionEffect(track, in_point);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return ex_point;
}

PRIVATE
mrb_value unset(mrb_state *mrb, mrb_value self) {
    bool      status = false;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = SetUnsetEffect(track);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value mono(mrb_state *mrb, mrb_value self) {
    bool      status = false;
    mrb_int   track  = 0;
    mrb_sym   sym    = 0;
    mrb_value val    = {0};

    sym    = mrb_intern_lit(mrb, "@track");
    val    = mrb_iv_get(mrb, self, sym);
    track  = mrb_int(mrb, val);
    status = SetMonoEffect(track);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PUBLIC
void DefineMixerModule(mrb_state *mrb) {
    struct RClass *mixer = NULL;

    SAVE_ARENA(mrb);

    mixer = mrb_define_module(mrb, "Mixer");

    mrb_define_const(mrb, mixer, "DEFAULT_FREQUENCY", mrb_int_value  (mrb, MIX_DEFAULT_FREQUENCY));
    mrb_define_const(mrb, mixer, "DEFAULT_FORMAT",    mrb_int_value  (mrb, MIX_DEFAULT_FORMAT));
    mrb_define_const(mrb, mixer, "DEFAULT_CHANNELS",  mrb_int_value  (mrb, MIX_DEFAULT_CHANNELS));
    mrb_define_const(mrb, mixer, "DEFAULT_VOLUME",    mrb_float_value(mrb, MIX_DEFAULT_VOLUME));
    mrb_define_const(mrb, mixer, "COUNT_TRACKS",      mrb_int_value  (mrb, MIXER_COUNT_TRACKS));
    mrb_define_const(mrb, mixer, "FORMAT_U8",         mrb_int_value  (mrb, SDL_AUDIO_U8));
    mrb_define_const(mrb, mixer, "FORMAT_S8",         mrb_int_value  (mrb, SDL_AUDIO_S8));
    mrb_define_const(mrb, mixer, "FORMAT_S16",        mrb_int_value  (mrb, SDL_AUDIO_S16));
    mrb_define_const(mrb, mixer, "FORMAT_S32",        mrb_int_value  (mrb, SDL_AUDIO_S32));
    mrb_define_const(mrb, mixer, "FORMAT_F32",        mrb_float_value(mrb, SDL_AUDIO_F32));
    mrb_define_const(mrb, mixer, "FORMAT_S16LE",      mrb_int_value  (mrb, SDL_AUDIO_S16LE));
    mrb_define_const(mrb, mixer, "FORMAT_S16BE",      mrb_int_value  (mrb, SDL_AUDIO_S16BE));
    mrb_define_const(mrb, mixer, "FORMAT_S32LE",      mrb_int_value  (mrb, SDL_AUDIO_S32LE));
    mrb_define_const(mrb, mixer, "FORMAT_S32BE",      mrb_int_value  (mrb, SDL_AUDIO_S32BE));
    mrb_define_const(mrb, mixer, "FORMAT_F32LE",      mrb_float_value(mrb, SDL_AUDIO_F32LE));
    mrb_define_const(mrb, mixer, "FORMAT_F32BE",      mrb_float_value(mrb, SDL_AUDIO_F32BE));

    mrb_define_module_function(mrb, mixer, "reopen",  self_reopen,     MRB_ARGS_OPT(3));
    mrb_define_module_function(mrb, mixer, "stop",    self_stop,       MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mixer, "fadeout", self_fadeout,    MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mixer, "volume",  self_get_volume, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mixer, "volume=", self_set_volume, MRB_ARGS_REQ(1));

    mrb_define_method(mrb, mixer, "pause",          pause,          MRB_ARGS_NONE());
    mrb_define_method(mrb, mixer, "resume",         resume,         MRB_ARGS_NONE());
    mrb_define_method(mrb, mixer, "stop",           stop,           MRB_ARGS_NONE());
    mrb_define_method(mrb, mixer, "playing?",       is_playing,     MRB_ARGS_NONE());
    mrb_define_method(mrb, mixer, "paused?",        is_paused,      MRB_ARGS_NONE());
    mrb_define_method(mrb, mixer, "reverse_stereo", reverse_stereo, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, mixer, "position",       position,       MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mixer, "unset",          unset,          MRB_ARGS_NONE());
    mrb_define_method(mrb, mixer, "mono",           mono,           MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
