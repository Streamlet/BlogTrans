//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   HttpGet.h
//    Author:      Streamlet
//    Create Time: 2010-10-29
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __HTTPGET_H_9427F415_86D0_49DD_B1E9_C22AD416CBC9_INCLUDED__
#define __HTTPGET_H_9427F415_86D0_49DD_B1E9_C22AD416CBC9_INCLUDED__


#include <xl/Common/Containers/xlArray.h>
#include <xl/Common/String/xlString.h>
#include <Windows.h>

class HttpGet
{
public:
    HttpGet(LPCTSTR lpAgent = NULL);
    ~HttpGet();

public:
    bool SendRequest(LPCTSTR lpUrl, HANDLE hEventCancel, xl::Array<BYTE> *pContent);

private:
    xl::String m_strAgent;
};

#endif // #ifndef __HTTPGET_H_9427F415_86D0_49DD_B1E9_C22AD416CBC9_INCLUDED__
