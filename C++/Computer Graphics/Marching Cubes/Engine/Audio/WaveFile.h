/*
WaveFile.h
Written by Matthew Fisher

A wave file defines a (possibly stereo) sound.
*/

class WaveFile
{
public:

    void LoadFromFile(LPWSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags );
    void LoadFromMemory(const Vector<short> &Data, UINT SamplesPerSec);
    void LoadFromMemory(const Vector<DWORD> &Data, UINT SamplesPerSec);
    void LoadFromMemory(const Vector<double> &Data, UINT SamplesPerSec);
    void Save(const String &Filename);

    __forceinline UINT SampleCount() const
    {
        return _Data.Length() / (_Format.wBitsPerSample / 8);
    }
    __forceinline const Vector<BYTE>& Data() const
    {
        return _Data;
    }
    __forceinline WAVEFORMATEX& Format()
    {
        return _Format;
    }

private:
    Vector<BYTE> _Data;
    WAVEFORMATEX _Format;
};
