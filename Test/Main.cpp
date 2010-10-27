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

    XmlRpcStruct b;
    b.Insert(L"sb", v);

    v.SetStructValue(b);

    XmlNodePtr pNode = v.ToXml();
    xl::String s = pNode->GetXmlString();
    LPCTSTR p = s.GetAddress();

    XmlRpcValue v2;
    v2.FromXml(pNode);
    XmlNodePtr pNode2 = v2.ToXml();
    xl::String s2 = pNode2->GetXmlString();
    LPCTSTR p2 = s2.GetAddress();

    return 0;
}

