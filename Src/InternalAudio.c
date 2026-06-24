// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Internal Audio Subsystem Management
#include "Internal.h"

PRIVATE bool       no_audio                   = false;
PRIVATE MIX_Mixer *mixer                      = NULL;
PRIVATE MIX_Track *tracks[MIXER_COUNT_TRACKS] = {0};

PUBLIC
bool OpenAudio(SDL_AudioDeviceID devid, SDL_AudioSpec *spec) {
    bool status = false;

    status = MIX_Init();
    if(!status) {
        return false;
    }

    mixer = MIX_CreateMixerDevice(devid, spec);
    if(!mixer) {
        return false;
    }

    for(int i = 0;i < MIXER_COUNT_TRACKS;++i) {
        tracks[i] = MIX_CreateTrack(mixer);
        if(!tracks[i]) {
            return false;
        }
    }

    return true;
}

PUBLIC
void CloseAudio(void) {
    for(int i = 0;i < MIXER_COUNT_TRACKS;++i) {
        MIX_DestroyTrack(tracks[i]);
    }
    MIX_DestroyMixer(mixer);
    MIX_Quit();
}

PUBLIC
bool InitAudioSubsystem(bool disable) {
    bool              status = false;
    SDL_AudioDeviceID devid  = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;
    SDL_AudioSpec     spec   = {0};

    if(disable) {
        IGNORE_RETURN SDL_SetError("Audio Mode: %s", "(disabled)");
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        IGNORE_RETURN SDL_ClearError();
        return true;
    }

    no_audio = disable;

    status = SDL_InitSubSystem(SDL_INIT_AUDIO);
    if(!status) {
        return false;
    }

    spec.channels = MIX_DEFAULT_CHANNELS;
    spec.format   = MIX_DEFAULT_FORMAT;
    spec.freq     = MIX_DEFAULT_FREQUENCY;

    status = OpenAudio(devid, &spec);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
void QuitAudioSubsystem(void) {
    CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

// =================
// General Functions
// =================

PUBLIC
MIX_Mixer *Mixer(void) {
    if(!no_audio) {
        SDL_assert(mixer);
    }

    return mixer;
}

PUBLIC
MIX_Track **Tracks(void) {
    if(!no_audio) {
        SDL_assert(tracks);
    }

    return tracks;
}

// ===============
// Mixer Functions
// ===============

PRIVATE SDL_INLINE
Sint64 MillisecondsToFrames(int milliseconds, int sample_rate) {
    return ((Sint64)milliseconds * sample_rate) / 1000;
}

PUBLIC
bool FadeOutTrackMixer(int track, int milliseconds) {
    bool          status = false;
    Sint64        frames = 0;
    SDL_AudioSpec spec   = {0};

    status = MIX_GetMixerFormat(mixer, &spec);
    if(!status) {
        return false;
    }

    frames = MillisecondsToFrames(milliseconds, spec.freq);
    status = MIX_StopTrack(tracks[track], frames);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool PauseMixer(int track) {
    bool status = false;

    status = MIX_PauseTrack(tracks[track]);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool ResumeMixer(int track) {
    bool status = false;

    status = MIX_ResumeTrack(tracks[track]);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool StopMixer(int track) {
    bool status = false;

    status = MIX_StopTrack(tracks[track], 0);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool IsPlayingMixer(int track) {
    return MIX_TrackPlaying(tracks[track]);
}

PUBLIC
bool IsPausedMixer(int track) {
    return MIX_TrackPaused(tracks[track]);
}

PUBLIC
bool FadeOutMixer(int milliseconds) {
    bool          status = false;
    Sint64        frames = 0;
    SDL_AudioSpec spec   = {0};

    status = MIX_GetMixerFormat(mixer, &spec);
    if(!status) {
        return false;
    }

    frames = MillisecondsToFrames(milliseconds, spec.freq);
    status = MIX_StopAllTracks(mixer, frames);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool SetVolumeTrackMixer(int track, float value) {
    bool status = false;

    status = MIX_SetTrackGain(tracks[track], value);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
float GetVolumeTrackMixer(int track) {
    return MIX_GetTrackGain(tracks[track]);
}

PUBLIC
bool SetVolumeMixer(float value) {
    bool status = false;

    status = MIX_SetMixerGain(mixer, value);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
float GetVolumeMixer(void) {
    return MIX_GetMixerGain(mixer);
}

PUBLIC
bool SetReverseStereoMixer(int track, bool enable) {
    bool          status   = false;
    int           chmap[2] = {0};
    SDL_AudioSpec spec     = {0};

    if(enable) {
        chmap[0] = 1;
        chmap[1] = 0;
    }
    else {
        chmap[0] = 0;
        chmap[1] = 1;
    }

    status = MIX_GetMixerFormat(mixer, &spec);
    if(!status) {
        return false;
    }

    status = MIX_SetTrackOutputChannelMap(tracks[track], chmap, spec.channels);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool SetUnsetEffect(int track) {
    return MIX_SetTrackCookedCallback(tracks[track], NULL, NULL);
}

PRIVATE
void MonoCallback(void                *userdata,
                  MIX_Track           *track,
                  const SDL_AudioSpec *spec,
                  float               *pcm,
                  int                  samples) {
    UNUSED_ARGUMENT userdata;
    UNUSED_ARGUMENT track;

    if(spec->channels != 2) {
        return;
    }

    for(int i = 0; i < samples; i += 2) {
        float mono = (pcm[i] + pcm[i + 1]) * 0.5f;

        pcm[i]     = mono;
        pcm[i + 1] = mono;
    }
}

PUBLIC
bool SetMonoEffect(int track) {
    bool status = false;

    status = MIX_SetTrackCookedCallback(tracks[track], MonoCallback, NULL);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool SetPositionEffect(int track, const MIX_Point3D *position) {
    bool status = false;

    status = MIX_SetTrack3DPosition(tracks[track], position);
    if(!status) {
        return false;
    }

    return true;
}

// ===============
// Sound Functions
// ===============

PUBLIC
Sound *LoadSoundFromFile(const char *path) {
    Sound        *sound  = NULL;
    char         *buf    = NULL;
    SDL_IOStream *io     = NULL;
    BufferSize    size   = 0;
    bool          status = false;

    buf = GetFileBuffer(path, &size);
    if(!buf) {
        return NULL;
    }

    io = SDL_IOFromMem(buf, size);
    if(!io) {
        FreeBuffer(buf);
        return NULL;
    }

    sound = MIX_LoadAudio_IO(mixer, io, true, false);
    if(!sound) {
        IGNORE_RETURN SDL_SetError("%s", "Unrecognized file format");
        IGNORE_RETURN SDL_CloseIO(io);
        FreeBuffer(buf);
        return NULL;
    }

    status = SDL_CloseIO(io);
    if(!status) {
        FreeBuffer(buf);
        return NULL;
    }

    FreeBuffer(buf);

    return sound;
}

PUBLIC
void FreeSound(Sound *sound) {
    if(!sound) {
        return;
    }

    MIX_DestroyAudio(sound);
}

PUBLIC
bool PlaySound(Sound *sound, int track, int loops) {
    bool             status = false;
    SDL_PropertiesID prop   = 0;

    status = MIX_SetTrackAudio(tracks[track], sound);
    if(!status) {
        return false;
    }

    prop = MIX_GetAudioProperties(sound);

    status = SDL_SetNumberProperty(prop, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
    if(!status) {
        return false;
    }

    status = MIX_PlayTrack(tracks[track], prop);
    if(!status) {
        return false;
    }

    return true;
}

PUBLIC
bool FadeInSound(Sound *sound, int track, int loops, int milliseconds) {
    bool             status = false;
    SDL_PropertiesID prop   = 0;

    status = MIX_SetTrackAudio(tracks[track], sound);
    if(!status) {
        return false;
    }

    prop = MIX_GetAudioProperties(sound);

    status = SDL_SetNumberProperty(prop, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
    if(!status) {
        return false;
    }

    status = SDL_SetNumberProperty(prop, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, milliseconds);
    if(!status) {
        return false;
    }

    status = MIX_PlayTrack(tracks[track], prop);
    if(!status) {
        return false;
    }

    return true;
}
