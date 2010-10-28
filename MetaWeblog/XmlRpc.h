//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   XmlRpc.h
//    Author:      Streamlet
//    Create Time: 2010-10-28
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XMLRPC_H_4F821131_5A3F_41EE_A285_3B2989AF7700_INCLUDED__
#define __XMLRPC_H_4F821131_5A3F_41EE_A285_3B2989AF7700_INCLUDED__


#include <Windows.h>
#include <xl/Containers/xlArray.h>
#include <xl/Objects/xlString.h>
#include "HttpIO.h"
#include "XmlRpcValue.h"
#include "XmlParser.h"

class XmlRpc
{
public:
    XmlRpc(const xl::String &strUserAgent = L"XmlRpcClient");
    ~XmlRpc();

public:
    bool SetApiUrl(const xl::String &strUrl);

public:
    bool Connect();
    void Disconnect();

public:
    bool ExecuteMethod(const xl::String &strMethodName,
                       const xl::Array<XmlRpcValue> &arrParameters,
                       XmlRpcValue *pReturnValue,
                       HANDLE hEventCancel);

private:
    XmlInstPtr MakeXmlInst();
    XmlNodePtr MakeMethodCall(const xl::String &strMethodName,
                              const xl::Array<XmlRpcValue> &arrParameters);
    bool ParseResponse(XmlNodePtr pNode, XmlRpcValue *pReturnValue);

private:
    xl::String m_strHostName;
    xl::String m_strPagePath;

    HttpIO m_http;
    bool m_bConnected;
};

#endif // #ifndef __XMLRPC_H_4F821131_5A3F_41EE_A285_3B2989AF7700_INCLUDED__
