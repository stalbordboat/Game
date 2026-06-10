// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Handles Audio Recording Devices.
#include "Internal.h"

PRIVATE
mrb_value self_ids(mrb_state *mrb, mrb_value self) {
    SDL_AudioDeviceID *ids   = NULL;
    int                count = 0;
    mrb_value          ary   = {0};

    UNUSED_ARGUMENT self;

    ids = SDL_GetAudioRecordingDevices(&count);
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
    mrb_int     id   = 0;
    const char *name = NULL;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i", &id);

    name = SDL_GetAudioDeviceName(id);
    if(!name) {
        RaiseRuntimeError(mrb);
    }

    return mrb_str_new_cstr(mrb, name);
}

PRIVATE
mrb_value self_open(mrb_state *mrb, mrb_value self) {
    struct RClass *recorder = NULL;
    mrb_value      argv[4]  = {0};
    mrb_int        which    = 0;
    mrb_int        format   = SDL_AUDIO_S16;
    mrb_int        channels = 2;
    mrb_int        freq     = 44100;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i|iii", &which, &format, &channels, &freq);

    recorder = mrb_class_get(mrb, "AudioRecorder");
    argv[0]  = mrb_int_value(mrb, which);
    argv[1]  = mrb_int_value(mrb, format);
    argv[2]  = mrb_int_value(mrb, channels);
    argv[3]  = mrb_int_value(mrb, freq);

    return mrb_obj_new(mrb, recorder, 4, argv);
}

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    SDL_AudioStream *stream   = NULL;
    mrb_int          id       = 0;
    mrb_int          format   = SDL_AUDIO_S16;
    mrb_int          channels = 2;
    mrb_int          freq     = 44100;
    SDL_AudioSpec    spec     = {0};
    bool             status   = FALSE;
    mrb_sym          sym      = 0;
    mrb_value        val      = {0};
    const char      *name     = NULL;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i|i|i|i", &id, &format, &channels, &freq);

    spec.format   = format;
    spec.channels = channels;
    spec.freq     = freq;

    stream = SDL_OpenAudioDeviceStream(id, &spec, NULL, NULL);
    if(!stream) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_ResumeAudioStreamDevice(stream);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    sym = mrb_intern_lit(mrb, "@id");
    val = mrb_int_value (mrb, id);
    mrb_iv_set(mrb, self, sym, val);

    name = SDL_GetAudioDeviceName(id);
    if(!name) {
        RaiseRuntimeError(mrb);
    }

    sym = mrb_intern_lit  (mrb, "@name");
    val = mrb_str_new_cstr(mrb, name);
    mrb_iv_set(mrb, self, sym, val);

    sym = mrb_intern_lit(mrb, "@is_closed");
    val = mrb_false_value();
    mrb_iv_set(mrb, self, sym, val);

    DATA_PTR(self) = stream;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT copy;

    IGNORE_RETURN SDL_SetError("AudioRecorder cannot be copied");
    RaiseRuntimeError(mrb);

    return copy;
}

PRIVATE
mrb_value close(mrb_state *mrb, mrb_value self) {
    SDL_AudioStream *stream = DATA_PTR(self);
    mrb_sym          sym    = 0;
    mrb_value        val    = {0};

    UNUSED_ARGUMENT mrb;

    SDL_DestroyAudioStream(stream);
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
mrb_value record(mrb_state *mrb, mrb_value self) {
    SDL_AudioStream *stream = DATA_PTR(self);
    const int       bufsize = 4096;
    int             got     = 0;
    char            buffer[bufsize];

    got = SDL_GetAudioStreamData(stream, buffer, bufsize);
    if(got == -1) {
        RaiseRuntimeError(mrb);
    }

    // Got no audio this time? Return an empty string.
    if(got == 0) {
        return mrb_str_new_cstr(mrb, "");
    }

    return mrb_str_new(mrb, buffer, got);
}

PRIVATE
mrb_value name(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@name"));
}

PRIVATE
mrb_value set_volume(mrb_state *mrb, mrb_value self) {
    SDL_AudioStream *stream = DATA_PTR(self);
    mrb_float       vol     = 0;
    bool            status  = FALSE;

    IGNORE_RETURN mrb_get_args(mrb, "f", &vol);

    status = SDL_SetAudioStreamGain(stream, vol);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, vol);
}

PRIVATE
mrb_value get_volume(mrb_state *mrb, mrb_value self) {
    SDL_AudioStream *stream = DATA_PTR(self);
    mrb_float       vol     = 0;

    vol = SDL_GetAudioStreamGain(stream);

    return mrb_float_value(mrb, vol);
}

PUBLIC
void DefineAudioRecorderClass(mrb_state *mrb) {
    struct RClass *recorder = NULL;

    SAVE_ARENA(mrb);

    recorder = mrb_define_class(mrb, "AudioRecorder", mrb->object_class);

    mrb_define_const(mrb, recorder, "FORMAT_U8",    mrb_int_value   (mrb, SDL_AUDIO_U8));
    mrb_define_const(mrb, recorder, "FORMAT_S8",    mrb_int_value   (mrb, SDL_AUDIO_S8));
    mrb_define_const(mrb, recorder, "FORMAT_S16",   mrb_int_value   (mrb, SDL_AUDIO_S16));
    mrb_define_const(mrb, recorder, "FORMAT_S32",   mrb_int_value   (mrb, SDL_AUDIO_S32));
    mrb_define_const(mrb, recorder, "FORMAT_F32",   mrb_float_value (mrb, SDL_AUDIO_F32));
    mrb_define_const(mrb, recorder, "FORMAT_S16LE", mrb_int_value   (mrb, SDL_AUDIO_S16LE));
    mrb_define_const(mrb, recorder, "FORMAT_S16BE", mrb_int_value   (mrb, SDL_AUDIO_S16BE));
    mrb_define_const(mrb, recorder, "FORMAT_S32LE", mrb_int_value   (mrb, SDL_AUDIO_S32LE));
    mrb_define_const(mrb, recorder, "FORMAT_S32BE", mrb_int_value   (mrb, SDL_AUDIO_S32BE));
    mrb_define_const(mrb, recorder, "FORMAT_F32LE", mrb_float_value (mrb, SDL_AUDIO_F32LE));
    mrb_define_const(mrb, recorder, "FORMAT_F32BE", mrb_float_value (mrb, SDL_AUDIO_F32BE));

    mrb_define_class_method(mrb, recorder, "ids",  self_ids,  MRB_ARGS_NONE());
    mrb_define_class_method(mrb, recorder, "name", self_name, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, recorder, "open", self_open, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(3));

    mrb_define_method(mrb, recorder, "initialize",      initialize,      MRB_ARGS_REQ(1)|MRB_ARGS_OPT(3));
    mrb_define_method(mrb, recorder, "initialize_copy", initialize_copy, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, recorder, "close",           close,           MRB_ARGS_NONE());
    mrb_define_method(mrb, recorder, "closed?",         is_closed,       MRB_ARGS_NONE());
    mrb_define_method(mrb, recorder, "record",          record,          MRB_ARGS_NONE());
    mrb_define_method(mrb, recorder, "name",            name,            MRB_ARGS_NONE());
    mrb_define_method(mrb, recorder, "volume=",         set_volume,      MRB_ARGS_REQ(1));
    mrb_define_method(mrb, recorder, "volume",          get_volume,      MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
