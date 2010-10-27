//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Base64.h
//    Author:      Streamlet
//    Create Time: 2010-10-28
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __BASE64_H_4BE77292_183C_4343_A33D_FC9AA85E6D77_INCLUDED__
#define __BASE64_H_4BE77292_183C_4343_A33D_FC9AA85E6D77_INCLUDED__


#include <xl/Containers/xlArray.h>
#include <xl/Containers/xlMap.h>
#include <xl/Objects/xlString.h>
#include <xl/Objects/xlQIPtr.h>

typedef unsigned char           Base64Byte;
typedef xl::Array<Base64Byte>   Base64Bytes;
typedef xl::Char                Base64Char;
typedef xl::String              Base64String;
typedef xl::QIPtr<Base64Bytes>  Base64BytesPtr;
typedef xl::QIPtr<Base64String> Base64StringPtr;

class Base64
{
public:
    Base64();
    ~Base64();
    
public:
    Base64StringPtr Encode(const void *lpPlain, size_t nLength);
    Base64BytesPtr  Decode(const Base64String &strEncoded);

private:
    xl::Map<Base64Char, Base64Byte> m_alphabet_reverse;
};

#endif // #ifndef __BASE64_H_4BE77292_183C_4343_A33D_FC9AA85E6D77_INCLUDED__
