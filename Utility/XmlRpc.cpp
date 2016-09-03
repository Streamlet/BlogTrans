//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   XmlRpc.cpp
//    Author:      Streamlet
//    Create Time: 2010-10-28
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include "XmlRpc.h"
#include "XmlRpcValue.h"
#include "Encoding.h"
#include <WinHttp.h>
#pragma comment(lib, "WinHttp.lib")

#define XML_RPC_METHOD_CALL     L"methodCall"
#define XML_RPC_METHOD_NAME     L"methodName"
#define XML_RPC_PARAMS          L"params"
#define XML_RPC_PARAM           L"param"
#define XML_RPC_METHOD_RESPONSE L"methodResponse"
#define XML_RPC_FAULT           L"fault"

XmlRpc::XmlRpc(const xl::String &strUserAgent /*= L"XmlRpcClient"*/)
    : m_bConnected(false), m_http(strUserAgent)
{

}

XmlRpc::~XmlRpc()
{
    Disconnect();
}

bool XmlRpc::SetApiUrl(const xl::String &strUrl)
{
    URL_COMPONENTS urlComp = { sizeof(URL_COMPONENTS) };

    urlComp.dwHostNameLength  = (DWORD)-1;
    urlComp.dwUrlPathLength   = (DWORD)-1;
    urlComp.dwExtraInfoLength = (DWORD)-1;

    if (!WinHttpCrackUrl(strUrl, 0, 0, &urlComp))
    {
        return false;
    }

    m_strHostName = xl::String(urlComp.lpszHostName, urlComp.dwHostNameLength);
    m_strPagePath = xl::String(urlComp.lpszUrlPath, urlComp.dwUrlPathLength) +
                    xl::String(urlComp.lpszExtraInfo, urlComp.dwExtraInfoLength);
    
    return true;
}

bool XmlRpc::Connect()
{
    Disconnect();

    if (!m_http.Connect(m_strHostName))
    {
        return false;
    }

    m_bConnected = true;

    return true;
}

void XmlRpc::Disconnect()
{
    if (!m_bConnected)
    {
        return;
    }

    m_http.Disconnect();

    m_bConnected = false;
}

bool XmlRpc::ExecuteMethod(const xl::String &strMethodName,
                           const xl::Array<XmlRpcValue> &arrParameters,
                           XmlRpcValue *pReturnValue,
                           HANDLE hEventCancel)
{
    XmlInstPtr pInst = MakeXmlInst();
    XmlNodePtr pMethodCall = MakeMethodCall(strMethodName, arrParameters);

    xl::String strRequest = pInst->GetXmlString(L"") + pMethodCall->GetXmlString(L"", L"");
    xl::StringA strRequestUtf8 = Encoding::StringToUtf8(strRequest);

    xl::Array<BYTE> arrResponse;

    if (!m_http.SendRequest(L"POST", m_strPagePath, NULL,
        (LPVOID)(const CHAR *)strRequestUtf8, strRequestUtf8.Length(), hEventCancel, &arrResponse))
    {
        return false;
    }

    arrResponse.PushBack('\0');
    xl::StringA strResponseUtf8 = (LPCSTR)&arrResponse[0];
    xl::String strResponse = Encoding::Utf8ToString(strResponseUtf8);

    XmlInstList xmlInst;
    XmlNodeList xmlNode;

    if (!XmlParser::ParseXml(strResponse, &xmlInst, &xmlNode))
    {
        return false;
    }

    return ParseResponse(*xmlNode.Begin(), pReturnValue);
}

XmlInstPtr XmlRpc::MakeXmlInst()
{
    XmlInstPtr pInst = new XmlInst;

    pInst->SetTagName(XML_INST_XML);
    pInst->Properties().Insert(XML_INST_VERSION, XML_INST_VERSION_1_0);
//  pInst->Properties().Insert(XML_INST_ENCODING, XML_INST_ENCODING_UTF8);

    return pInst;
}

XmlNodePtr XmlRpc::MakeMethodCall(const xl::String &strMethodName,
                                  const xl::Array<XmlRpcValue> &arrParameters)
{
    XmlNodePtr pMethodCall = new XmlNode;
    pMethodCall->SetTagName(XML_RPC_METHOD_CALL);

    XmlNodePtr pMethodName = new XmlNode;
    pMethodName->SetTagName(XML_RPC_METHOD_NAME);

    XmlNodePtr pMethodNameValue = new XmlNode;
    pMethodNameValue->SetType(XmlNode::XML_VALUE);
    pMethodNameValue->SetValue(strMethodName);

    pMethodName->SubNodes().PushBack(pMethodNameValue);

    XmlNodePtr pParams = new XmlNode;
    pParams->SetTagName(XML_RPC_PARAMS);

    for (xl::Array<XmlRpcValue>::Iterator it = arrParameters.Begin(); it != arrParameters.End(); ++it)
    {
        XmlNodePtr pParam = new XmlNode;
        pParam->SetTagName(XML_RPC_PARAM);

        XmlNodePtr pValue = it->ToXml();

        pParam->SubNodes().PushBack(pValue);
        pParams->SubNodes().PushBack(pParam);
    }

    pMethodCall->SubNodes().PushBack(pMethodName);
    pMethodCall->SubNodes().PushBack(pParams);

    return pMethodCall;
}

bool XmlRpc::ParseResponse(XmlNodePtr pNode, XmlRpcValue *pReturnValue)
{
    if (pNode->GetType() != XmlNode::XML_NODE ||
        pNode->GetTagName() != XML_RPC_METHOD_RESPONSE ||
        pNode->SubNodes().Size() != 1)
    {
        return false;
    }

    XmlNodePtr pResult = *pNode->SubNodes().Begin();

    if (pResult->GetType() != XmlNode::XML_NODE ||
        pResult->SubNodes().Size() != 1)
    {
        return false;
    }

    xl::String strRet = pResult->GetTagName();

    if (strRet != XML_RPC_PARAMS && strRet != XML_RPC_FAULT)
    {
        return false;
    }

    bool bRet = (strRet == XML_RPC_PARAMS);
    XmlRpcValue value;

    if (bRet)
    {
        XmlNodePtr pParam = *pResult->SubNodes().Begin();

        if (pParam->GetType() != XmlNode::XML_NODE ||
            pParam->GetTagName() != XML_RPC_PARAM ||
            pParam->SubNodes().Size() != 1)
        {
            return false;
        }

        XmlNodePtr pValue = *pParam->SubNodes().Begin();

        if (!value.FromXml(pValue))
        {
            return false;
        }
    }
    else
    {
        XmlNodePtr pValue = *pResult->SubNodes().Begin();

        if (!value.FromXml(pValue))
        {
            return false;
        }
    }

    if (pReturnValue != nullptr)
    {
        *pReturnValue = value;
    }

    return bRet;
}
