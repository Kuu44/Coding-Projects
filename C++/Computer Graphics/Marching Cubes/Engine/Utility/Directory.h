/*
Directory.h
Written by Matthew Fisher
*/

class Directory
{
public:
    Directory() {}
    Directory(const String &DirectoryPath);
    void Load(const String &DirectoryPath);

    __forceinline const String& DirectoryPath()
    {
        return _DirectoryPath;
    }
    __forceinline const Vector<String>& Files()
    {
        return _Files;
    }
    __forceinline const Vector<String>& Directories()
    {
        return _Directories;
    }

private:
    String _DirectoryPath;
    Vector<String> _Files;
    Vector<String> _Directories;
};

