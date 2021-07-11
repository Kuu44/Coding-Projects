/*
WaveFile.cpp
Written by Matthew Fisher

A wave file defines a (possibly stereo) sound.
*/

void WaveFile::LoadFromFile(LPWSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags )
{
    WaveFileReader File;
    File.Open(strFileName, pwfx, dwFlags);

    _Data.Allocate(File.GetSize());
    DWORD SizeRead;
    HRESULT hr = File.Read((BYTE *)_Data.CArray(), File.GetSize(), &SizeRead );
    Assert(SUCCEEDED(hr), "Wave file read failed");
    _Format = *(File.GetFormat());
}

void WaveFile::LoadFromMemory(const Vector<short> &Data, UINT SamplesPerSec)
{
    _Format.wFormatTag = 1;
    _Format.nChannels = 1;
    _Format.nSamplesPerSec = SamplesPerSec;
    _Format.nAvgBytesPerSec = SamplesPerSec * sizeof(short);
    _Format.nBlockAlign = sizeof(short);
    _Format.wBitsPerSample = sizeof(short) * 8;
    _Format.cbSize = 0;

    _Data.Allocate(Data.Length() * sizeof(short));
    memcpy(_Data.CArray(), Data.CArray(), _Data.Length());
}

void WaveFile::LoadFromMemory(const Vector<DWORD> &Data, UINT SamplesPerSec)
{
    _Format.wFormatTag = 1;
    _Format.nChannels = 1;
    _Format.nSamplesPerSec = SamplesPerSec;
    _Format.nAvgBytesPerSec = SamplesPerSec * sizeof(DWORD);
    _Format.nBlockAlign = sizeof(DWORD);
    _Format.wBitsPerSample = sizeof(DWORD) * 8;
    _Format.cbSize = 0;

    _Data.Allocate(Data.Length() * sizeof(DWORD));
    memcpy(_Data.CArray(), Data.CArray(), _Data.Length());
}

void WaveFile::LoadFromMemory(const Vector<double> &Data, UINT SamplesPerSec)
{
    const double Min = Data.MinValue();
    const double Max = Data.MaxValue();
    const double ScaleFactor = 1.0 / Math::Max(-Min, Max);
    
    const UINT SampleCount = Data.Length();
    Vector<DWORD> NormalizedData(SampleCount);
    for(UINT SampleIndex = 0; SampleIndex < SampleCount; SampleIndex++)
    {
        //NormalizedData[SampleIndex] = DWORD(Math::LinearMap(Min, Max, 0.0, double(0xFFFFFFFF), Data[SampleIndex]));

        //
        // sound should be saved in integer format, not as an unsigned DWORD
        //
        NormalizedData[SampleIndex] = int((Data[SampleIndex] * ScaleFactor) * double(0xFFFFFFFF) * 0.5);
    }
    LoadFromMemory(NormalizedData, SamplesPerSec);
}

void WaveFile::Save(const String &Filename)
{
    PersistentAssert(_Format.nChannels == 1, "Multichannel save not supported");
    FILE *File = Utility::CheckedFOpen(Filename.CString(), "wb");
    UINT ChunkID = 0x46464952;              // RIFF
    UINT ChunkSize = 36 + _Data.Length();
    UINT FileFormat = 0x45564157;           // WAVE
    UINT Subchunk1ID = 0x20746d66;          // fmt
    UINT Subchunk1Size = 16;                // sizeof(WAVEFORMATEX) - sizeof(WORD)
    UINT Subchunk2ID = 0x61746164;          // data
    UINT Subchunk2Size = _Data.Length() * _Format.nChannels * _Format.wBitsPerSample / 8;

    Utility::CheckedFWrite(&ChunkID, sizeof(UINT), 1, File);
    Utility::CheckedFWrite(&ChunkSize, sizeof(UINT), 1, File);
    Utility::CheckedFWrite(&FileFormat, sizeof(UINT), 1, File);
    Utility::CheckedFWrite(&Subchunk1ID, sizeof(UINT), 1, File);
    Utility::CheckedFWrite(&Subchunk1Size, sizeof(UINT), 1, File);
    Utility::CheckedFWrite(&_Format, Subchunk1Size, 1, File);
    Utility::CheckedFWrite(&Subchunk2ID, sizeof(UINT), 1, File);
    Utility::CheckedFWrite(&Subchunk2Size, sizeof(UINT), 1, File);
    Utility::CheckedFWrite(_Data.CArray(), sizeof(BYTE), _Data.Length(), File);
    
    fclose(File);
}
