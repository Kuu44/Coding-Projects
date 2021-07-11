/*
ParameterFile.cpp
Written by Matthew Fisher

the Parameter class loads a paramater file as a simple set of "Parameter=Option" lines.
*/

ParameterFile::ParameterFile(const String &Filename)
{
    AddFile(Filename);
}

void ParameterFile::AddFile(const String &Filename)
{
    PersistentAssert(Utility::FileExists(Filename), "Parameter file not found");
    ifstream File(Filename.CString());
    Vector<String> Lines;
    Utility::GetFileLines(File, Lines);
    for(UINT i = 0; i < Lines.Length(); i++)
    {
        String &CurLine = Lines[i];
        if(CurLine.StartsWith("#include "))
        {
            Vector<String> Partition;
            CurLine.Partition("#include ", Partition);
            PersistentAssert(Partition.Length() == 1, String("Invalid line in parameter file: ") + CurLine);
            String IncludeFilename = Partition[0];
            IncludeFilename.Partition("\"", Partition);
            PersistentAssert(Partition.Length() == 1, String("Invalid line in parameter file: ") + CurLine);
            AddFile(Partition[0]);
        }
        else if(CurLine.Length() > 2)
        {
            Vector<String> Partition;
            CurLine.Partition('=', Partition);
            PersistentAssert(Partition.Length() == 2, String("Invalid line in parameter file: ") + CurLine);
            Parameters.PushEnd(ParameterEntry(Partition[0], Partition[1]));
        }
    }
}

String ParameterFile::GetRequiredString(const String &ParameterName)
{
    for(UINT i = 0; i < Parameters.Length(); i++)
    {
        if(Parameters[i].Name.MakeLowercase() == ParameterName.MakeLowercase())
        {
            return Parameters[i].Value;
        }
    }
    PersistentSignalError(String("Parameter not found: ") + ParameterName);
    return String("Parameter not found");
}

String ParameterFile::GetOptionalString(const String &ParameterName)
{
    for(UINT i = 0; i < Parameters.Length(); i++)
    {
        if(Parameters[i].Name.MakeLowercase() == ParameterName.MakeLowercase())
        {
            return Parameters[i].Value;
        }
    }
    return String();
}

bool ParameterFile::GetBoolean(const String &ParameterName)
{
    String Str = GetRequiredString(ParameterName);
    Str = Str.MakeLowercase();
    if(Str == "true")
    {
        return true;
    }
    else if(Str == "false")
    {
        return false;
    }
    else
    {
        SignalError(String("Invalid boolean value: ") + Str);
        return false;
    }
}

int ParameterFile::GetInteger(const String &ParameterName)
{
    return GetRequiredString(ParameterName).ConvertToInteger();
}

UINT ParameterFile::GetUnsignedInteger(const String &ParameterName)
{
    return GetRequiredString(ParameterName).ConvertToUnsignedInteger();
}

double ParameterFile::GetDouble(const String &ParameterName)
{
    return GetRequiredString(ParameterName).ConvertToDouble();
}

float ParameterFile::GetFloat(const String &ParameterName)
{
    return GetRequiredString(ParameterName).ConvertToFloat();
}

Vec3f ParameterFile::GetVec3(const String &ParameterName)
{
    String VecString = GetRequiredString(ParameterName);
    Vector<String> Elements;
    VecString.Partition(' ', Elements);
    Assert(Elements.Length() == 3, "Vector with invalid element count");
    Vec3f Result;
    for(UINT i = 0; i < 3; i++)
    {
        Result[i] = Elements[i].ConvertToFloat();
    }
    return Result;
}

String ParameterFile::GetString(const String &ParameterName, const String &Default)
{
    String Result = GetOptionalString(ParameterName);
    if(Result.Length() == 0)
    {
        return Default;
    }
    else
    {
        return Result;
    }
}

bool ParameterFile::GetBoolean(const String &ParameterName, bool Default)
{
    String Str = GetOptionalString(ParameterName);
    Str = Str.MakeLowercase();
    if(Str == "true")
    {
        return true;
    }
    else if(Str == "false")
    {
        return false;
    }
    else
    {
        return Default;
    }
}

int ParameterFile::GetInteger(const String &ParameterName, int Default)
{
    return GetString(ParameterName, String(Default)).ConvertToInteger();
}

UINT ParameterFile::GetUnsignedInteger(const String &ParameterName, UINT Default)
{
    return GetString(ParameterName, String(Default)).ConvertToUnsignedInteger();
}

double ParameterFile::GetDouble(const String &ParameterName, double Default)
{
    return GetString(ParameterName, String(Default)).ConvertToDouble();
}

float ParameterFile::GetFloat(const String &ParameterName, float Default)
{
    return GetString(ParameterName, String(Default)).ConvertToFloat();
}

Vec3f ParameterFile::GetVec3(const String &ParameterName, const Vec3f &Default)
{
    String VecString = GetOptionalString(ParameterName);
    if(VecString.Length() == 0)
    {
        return Default;
    }
    Vector<String> Elements;
    VecString.Partition(' ', Elements);
    Assert(Elements.Length() == 3, "Vector with invalid element count");
    Vec3f Result;
    for(UINT i = 0; i < 3; i++)
    {
        Result[i] = Elements[i].ConvertToFloat();
    }
    return Result;
}
