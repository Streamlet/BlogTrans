//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-10-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include "../MetaWeblog/XmlParser.h"
#include "../MetaWeblog/HttpIO.h"
#include "../MetaWeblog/XmlRpcValue.h"

#include <Windows.h>
#include <tchar.h>

int main()
{
//     XmlInstList xmlInstList;
//     XmlNodeList xmlNodeList;
//     XmlParser::ParseXml(L"<?xml encoding=\"utf-8\"?><doc>123</doc>", &xmlInstList, &xmlNodeList);
// 
//     XmlString str = (*xmlNodeList.Begin())->GetXmlString();
// 
//     const XmlChar *p = str.GetAddress();

//     HttpIO http;
// 
//     if (!http.Connect(_T("www.baidu.com")))
//     {
//         return 0;
//     }
// 
//     HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
// 
//     xl::Array<BYTE> arrBytes;
// 
//     if (!http.SendRequest(_T("GET"), _T("/"), NULL, NULL, hEvent, &arrBytes))
//     {
//         return 0;
//     }
// 
//     CloseHandle(hEvent);
// 
//     arrBytes.PushBack(0);
//     LPCSTR p = (LPCSTR)&arrBytes[0];

    XmlRpcValue v;
    v.SetStringValue(L"123");

    XmlRpcArray a;
    a.PushBack(v);
    a.PushBack(v);
    a.PushBack(v);

    v.SetArrayValue(a);

    xl::String s = v.ToXml()->GetXmlString(L"\t");
    LPCTSTR p = s.GetAddress();

    return 0;
}

