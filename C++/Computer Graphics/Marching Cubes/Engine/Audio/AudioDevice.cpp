/*
AudioDevice.cpp
Written by Matthew Fisher

AudioDevice plays wave files.
*/

AudioDevice::AudioDevice()
{
#ifdef USE_DIRECTX_AUDIO
    _Device = NULL;
    _MasteringVoice = NULL;
#endif
}

AudioDevice::~AudioDevice()
{
    FreeMemory();
}

void AudioDevice::FreeMemory()
{
#ifdef USE_DIRECTX_AUDIO
    RemoveVoices(false);
    if(_MasteringVoice)
    {
        _MasteringVoice->DestroyVoice();
        _MasteringVoice = NULL;
    }
    if(_Device)
    {
        _Device->Release();
        _Device = NULL;
    }
#endif
}

void AudioDevice::RemoveVoices(bool CompleteOnly)
{
#ifdef USE_DIRECTX_AUDIO
    XAUDIO2_VOICE_STATE State;

    for(int Index = 0; Index < int(_ActiveSourceVoices.Length()); Index++)
    {
        _ActiveSourceVoices[Index]->GetState( &State );
        bool Running = ( State.BuffersQueued > 0);
        if(!Running || !CompleteOnly)
        {
            _ActiveSourceVoices[Index]->DestroyVoice();
            _ActiveSourceVoices.RemoveSwap(Index);
            Index--;
        }
    }
#endif
}

void AudioDevice::ResetAllSounds()
{
#ifdef USE_DIRECTX_AUDIO
    FreeMemory();
    Init();
#endif
}

void AudioDevice::Init()
{
#ifdef USE_DIRECTX_AUDIO
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

    FreeMemory();

    DWORD Flags = 0;
    //Flags |= XAUDIO2_DEBUG_ENGINE;

    _Device = NULL;
    HRESULT hr = XAudio2Create(&_Device, Flags);
    if(!SUCCEEDED(hr))
    {
        Utility::MessageBox("Failed to initialize audio; try upgrading to the latest version of DirectX.  Game will continue without sound.");
    }
    else
    {
        hr = _Device->CreateMasteringVoice(&_MasteringVoice);
        PersistentAssert(SUCCEEDED(hr), "CreateMasteringVoice failed");
    }
#endif
}

void AudioDevice::PlayWaveFile(WaveFile &File, bool LoopForever)
{
#ifdef USE_DIRECTX_AUDIO
    if(_Device == NULL)
    {
        return;
    }
    RemoveVoices(true);

    if(_ActiveSourceVoices.Length() > 4)
    {
        return;
    }

    // Get format of wave file
    WAVEFORMATEX& pwfx = File.Format();
    
    // Create the source voice
    IXAudio2SourceVoice* _SourceVoice;
    HRESULT hr = _Device->CreateSourceVoice( &_SourceVoice, &pwfx );
    Assert(SUCCEEDED(hr), "CreateSourceVoice failed");
    _ActiveSourceVoices.PushEnd(_SourceVoice);
    
    // Submit the wave sample data using an XAUDIO2_BUFFER structure
    XAUDIO2_BUFFER buffer = {0};
    buffer.pAudioData = (BYTE *)File.Data().CArray();
    buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
    buffer.AudioBytes = File.Data().Length();// * sizeof(DWORD);

    if(LoopForever)
    {
        buffer.LoopBegin = 1;
        buffer.LoopLength = 0;
        buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
    }

    hr = _SourceVoice->SubmitSourceBuffer( &buffer );
    Assert(SUCCEEDED(hr), "SubmitSourceBuffer failed");

    hr = _SourceVoice->Start( 0 );
    Assert(SUCCEEDED(hr), "SubmitSourceBuffer failed");

    //delete[] pbWaveData;

    //Sleep(3000);
    //_SourceVoice->DestroyVoice();
    // Let the sound play
    /*BOOL isRunning = TRUE;
    while( SUCCEEDED( hr ) && isRunning )
    {
        XAUDIO2_VOICE_STATE state;
        pSourceVoice->GetState( &state );
        isRunning = ( state.BuffersQueued > 0 ) != 0;

        // Wait till the escape key is pressed
        if( GetAsyncKeyState( VK_ESCAPE ) )
            break;

        Sleep( 10 );
    }

    // Wait till the escape key is released
    while( GetAsyncKeyState( VK_ESCAPE ) )
        Sleep( 10 );

    pSourceVoice->DestroyVoice();
    SAFE_DELETE_ARRAY( pbWaveData );

    return hr;*/
#endif
}
