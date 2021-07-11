/*
Compression.h
Written by Matthew Fisher
*/

class Compression
{
public:
    static void CompressStreamToFile(const Vector<BYTE> &stream, const String &filename);
    static void CompressStreamToFile(const BYTE *stream, UINT byteCount, const String &filename);
    static void DecompressStreamFromFile(const String &filename, Vector<BYTE> &stream);
};
