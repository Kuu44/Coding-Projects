/*
Grid.h
Written by Matthew Fisher

Arbitrary-type grid structure.
*/

#pragma once

template <class type> class Grid
{
public:
    Grid();
    Grid(unsigned int Rows, unsigned int Cols);
    Grid(const Grid<type> &G);

    ~Grid();

    //
    // Memory
    //
    void FreeMemory();
    Grid<type>& operator = (const Grid<type> &G);
    void Allocate(unsigned int Rows, unsigned int Cols);
    void Allocate(const Vec2i &Dimensions)
    {
        Allocate(Dimensions.y, Dimensions.x);
    }
    
    //
    // Accessors
    //
    __forceinline type& operator() (unsigned int Row, unsigned int Col)
    {
#ifdef VECTOR_DEBUG
        Assert( (Row < _Rows) && (Col < _Cols), "Out-of-bounds vector access");
#endif
        return _Data[Row * _Cols + Col];
    }
    __forceinline const type& operator() (unsigned int Row, unsigned int Col) const
    {
#ifdef VECTOR_DEBUG
        Assert( (Row < _Rows) && (Col < _Cols), "Out-of-bounds vector access");
#endif
        return _Data[Row * _Cols + Col];
    }
    __forceinline unsigned int Rows() const
    {
        return _Rows;
    }
    __forceinline unsigned int Cols() const
    {
        return _Cols;
    }
    __forceinline Vec2i Dimensions() const
    {
        return Vec2i(_Cols, _Rows);
    }
    __forceinline bool Square() const
    {
        return (_Rows == _Cols);
    }
    __forceinline type* CArray()
    {
        return _Data;
    }
    __forceinline const type* CArray() const
    {
        return _Data;
    }

    //
    // Query
    //
    __forceinline bool ValidCoordinates(int Row, int Col) const
    {
        return (Row >= 0 && Row < int(_Rows) && Col >= 0 && Col < int(_Cols));
    }
    void ExtractRow(unsigned int Row, Vector<type> &Result)
    {
        const type *CPtr = _Data;
        Result.Allocate(_Cols);
        for(unsigned int Col = 0; Col < _Cols; Col++)
        {
            Result[Col] = CPtr[Row * _Cols + Col];
        }
    }
    void ExtractCol(unsigned int Col, Vector<type> &Result)
    {
        const type *CPtr = _Data;
        Result.Allocate(_Rows);
        for(unsigned int Row = 0; Row < _Rows; Row++)
        {
            Result[Row] = CPtr[Row * _Cols + Col];
        }
    }
    Vec2i MaxIndex() const;
    const type& MaxValue() const;

    //
    // Modifiers
    //
    void Clear(const type &T);

    //
    // File
    //
    void SaveToASCIIFile(const String &Filename)
    {
        ofstream File(Filename.CString());
        PersistentAssert(!File.fail(), "Failed to open file");
        File << _Rows << '\t' << _Cols << endl;
        for(unsigned int Row = 0; Row < _Rows; Row++)
        {
            for(unsigned int Col = 0; Col < _Cols; Col++)
            {
                File << _Data[Row * _Cols + Col] << '\t';
            }
            File << endl;
        }
    }

protected:
    type *_Data;
    unsigned int _Rows, _Cols;
};

#include "Grid.cpp"
