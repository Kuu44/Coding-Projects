/*
AudioDevice.h
Written by Matthew Fisher

AudioDevice plays wave files.
*/

#ifdef USE_DIRECTX_AUDIO
#include <xaudio2.h>
#endif

class AudioDevice
{
public:
    AudioDevice();
    ~AudioDevice();
    void FreeMemory();

    void Init();
    void ResetAllSounds();
    void PlayWaveFile(WaveFile &File, bool LoopForever = false);

private:
    void RemoveVoices(bool CompleteOnly);

#ifdef USE_DIRECTX_AUDIO
    IXAudio2* _Device;
    IXAudio2MasteringVoice* _MasteringVoice;
    Vector<IXAudio2SourceVoice*> _ActiveSourceVoices;
#endif
};