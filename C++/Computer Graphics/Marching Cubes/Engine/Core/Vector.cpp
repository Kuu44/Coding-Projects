/*
Vector.cpp
Written by Matthew Fisher
*/

#pragma once

#include "Vector.h"

template <class T> void Vector<T>::Clear(const T &Value)
{
    const unsigned int Length = _Length;
    T *CPtr = _Data;
    for(unsigned int i = 0; i < Length; i++)
    {
        CPtr[i] = Value;
    }
}

#pragma warning(disable : 4700)

template <class T> T Vector<T>::Sum() const
{
    const unsigned int Length = _Length;
    if(_Length == 0)
    {
        T Result;
        return Result;
    }
    else
    {
        const T *CPtr = _Data;
        T Result = CPtr[0];
        for(unsigned int Index = 1; Index < Length; Index++)
        {
            Result += CPtr[Index];
        }
        return Result;
    }
}

template <class T> unsigned int Vector<T>::MaxIndex() const
{
    Assert(_Length > 0, "MaxIndex called on zero-length vector");
    const unsigned int Length = _Length;
    const T *CPtr = _Data;
    unsigned int LargestIndexSeen = 0;
    for(unsigned int Index = 1; Index < Length; Index++)
    {
        if(CPtr[Index] > CPtr[LargestIndexSeen])
        {
            LargestIndexSeen = Index;
        }
    }
    return LargestIndexSeen;
}

template <class T> const T& Vector<T>::MaxValue() const
{
    return _Data[MaxIndex()];
}

template <class T> unsigned int Vector<T>::MinIndex() const
{
    Assert(_Length > 0, "MinIndex called on zero-length vector");
    const unsigned int Length = _Length;
    const T *CPtr = _Data;
    unsigned int SmallestIndexSeen = 0;
    for(unsigned int Index = 1; Index < Length; Index++)
    {
        if(CPtr[Index] < CPtr[SmallestIndexSeen])
        {
            SmallestIndexSeen = Index;
        }
    }
    return SmallestIndexSeen;
}

template <class T> const T& Vector<T>::MinValue() const
{
    return _Data[MinIndex()];
}

template <class T> void Vector<T>::Sort()
{
    std::sort(_Data, _Data + _Length);
}

template <class T> unsigned int Vector<T>::Hash32() const
{
    return Utility::Hash32((const BYTE *)_Data, sizeof(T) * _Length);
}

template <class T> unsigned __int64 Vector<T>::Hash64() const
{
    return Utility::Hash64((const BYTE *)_Data, sizeof(T) * _Length);
}

template <class T> void Vector<T>::Append(const Vector<T> &V)
{
    const unsigned int Length = _Length;
    const unsigned int VLength = V._Length;
    ReSize(Length + VLength);
    for(unsigned int Index = 0; Index < VLength; Index++)
    {
        _Data[Index + Length] = V._Data[Index];
    }
}

template <class T> void Vector<T>::PushEnd(const T &t)
{
    if(_Length >= _Capacity)
    {
        Reserve(_Length * 2 + 4);
    }
    _Data[_Length] = t;
    _Length++;
}

template <class T> void Vector<T>::PushEnd()
{
    if(_Length >= _Capacity)
    {
        Reserve(_Length * 2 + 4);
    }
    _Length++;
}

template <class T> void Vector<T>::PopEnd()
{
#ifdef VECTOR_DEBUG
    Assert(_Length != 0, "PopEnd called on zero-length vector");
#endif
    _Length--;
}

template <class T> void Vector<T>::RemoveSlow(unsigned int Index)
{
#ifdef VECTOR_DEBUG
    Assert(Index < _Length, "Remove called on invalid index");
#endif
    for(unsigned int i = Index; i < _Length - 1; i++)
    {
        _Data[i] = _Data[i + 1];
    }
    _Length--;
}

template <class T> void Vector<T>::Scale(const T &t)
{
    const unsigned int Length = _Length;
    T *CPtr = CArray();
    for(unsigned int Index = 0; Index < Length; Index++)
    {
        CPtr[Index] *= t;
    }
}

template <class T> void Vector<T>::RemoveSwap(unsigned int Index)
{
#ifdef VECTOR_DEBUG
    Assert(Index < _Length, "Remove called on invalid index");
#endif
    Utility::Swap(_Data[Index], _Data[_Length - 1]);
    _Length--;
}

template <class T> bool Vector<T>::Contains(const T &t) const
{
    const unsigned int Length = _Length;
    for(unsigned int Index = 0; Index < Length; Index++)
    {
        if(_Data[Index] == t)
        {
            return true;
        }
    }
    return false;
}

template <class T> int Vector<T>::FindFirstIndex(const T &t) const
{
    const unsigned int Length = _Length;
    for(unsigned int Index = 0; Index < Length; Index++)
    {
        if(_Data[Index] == t)
        {
            return Index;
        }
    }
    return -1;
}

template <class T> void Vector<T>::Randomize()
{
    unsigned int Length = _Length;
    for(unsigned int i = 0; i < Length; i++)
    {
        unsigned int RandomNumber = unsigned int(rand());
        Utility::Swap(_Data[i], _Data[i + RandomNumber % (Length - i)]);
    }
}

template <class T> void Vector<T>::PopFront()
{
    RemoveSlow(0);
}
