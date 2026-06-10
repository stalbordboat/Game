// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Internal Audio Subsystem Implementation
#ifndef INTERNALAUDIO_H
#define INTERNALAUDIO_H

#include "Native/Native.h"
#include <SDL3_mixer/SDL_mixer.h>

#define MIX_DEFAULT_CHANNELS  2
#define MIX_DEFAULT_FORMAT    SDL_AUDIO_S16
#define MIX_DEFAULT_FREQUENCY 44100

#define MIXER_COUNT_TRACKS 64
#define MIX_DEFAULT_VOLUME 1.0

typedef MIX_Audio Sound;
typedef MIX_Audio Music;

// =============================================
// Initialization and Deinitialization Functions
// =============================================

PUBLIC
bool InitAudioSubsystem(bool disable);

PUBLIC
void QuitAudioSubsystem(void);

PUBLIC
bool OpenAudio(SDL_AudioDeviceID devid, SDL_AudioSpec *spec);

PUBLIC
void CloseAudio(void);

// =================
// General Functions
// =================

PUBLIC
MIX_Mixer *Mixer(void);

PUBLIC
MIX_Track **Tracks(void);

// ===============
// Mixer Functions
// ===============

PUBLIC
bool FadeOutTrackMixer(int track, int milliseconds);

PUBLIC
bool PauseMixer(int track);

PUBLIC
bool ResumeMixer(int track);

PUBLIC
bool StopMixer(int track);

PUBLIC
bool IsPlayingMixer(int track);

PUBLIC
bool IsPausedMixer(int track);

PUBLIC
bool FadeOutMixer(int milliseconds);

PUBLIC
bool SetVolumeTrackMixer(int track, float value);

PUBLIC
float GetVolumeTrackMixer(int track);

PUBLIC
bool SetVolumeMixer(float value);

PUBLIC
float GetVolumeMixer(void);

PUBLIC
bool SetReverseStereoMixer(int track, bool enable);

PUBLIC
bool SetUnsetEffect(int track);

PUBLIC
bool SetMonoEffect(int track);

PUBLIC
bool SetPositionEffect(int track, const MIX_Point3D *position);

// ===============
// Sound Functions
// ===============

PUBLIC
Sound *LoadSoundFromFile(const char *path);

PUBLIC
void FreeSound(Sound *sound);

PUBLIC
bool PlaySound(Sound *sound, int track, int loops);

PUBLIC
bool FadeInSound(Sound *sound, int track, int loops, int milliseconds);

#endif // INTERNALAUDIO_H
