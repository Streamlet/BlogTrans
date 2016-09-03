//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   HttpGet.cpp
//    Author:      Streamlet
//    Create Time: 2010-10-29
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include "HttpGet.h"
#include "HttpIO.h"

HttpGet::HttpGet(LPCTSTR lpAgent /* = NULL */)
    : m_strAgent(lpAgent)
{

}

HttpGet::~HttpGet()
{

}

bool HttpGet::SendRequest(LPCTSTR lpUrl, HANDLE hEventCancel, xl::Array<BYTE> *pContent)
{
    URL_COMPONENTS urlComp = { sizeof(URL_COMPONENTS) };

    urlComp.dwHostNameLength  = (DWORD)-1;
    urlComp.dwUrlPathLength   = (DWORD)-1;
    urlComp.dwExtraInfoLength = (DWORD)-1;

    if (!WinHttpCrackUrl(lpUrl, 0, 0, &urlComp))
    {
        return false;
    }

    xl::String strHostName = xl::String(urlComp.lpszHostName, urlComp.dwHostNameLength);
    xl::String strPagePath = xl::String(urlComp.lpszUrlPath, urlComp.dwUrlPathLength) +
                             xl::String(urlComp.lpszExtraInfo, urlComp.dwExtraInfoLength);
    
    HttpIO http(m_strAgent);

    if (!http.Connect(strHostName))
    {
        return false;
    }

    if (!http.SendRequest(L"GET", strPagePath, NULL, NULL, 0, hEventCancel, pContent))
    {
        return false;
    }

    return true;
}
