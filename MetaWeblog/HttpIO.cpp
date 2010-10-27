//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   HttpIO.cpp
//    Author:      Streamlet
//    Create Time: 2010-10-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include "HttpIO.h"
#include <tchar.h>
#include <Loki/ScopeGuard.h>
#pragma comment(lib, "WinHttp.lib")

HttpIO::HttpIO(LPCTSTR lpAgent /*= NULL*/)
    : m_hSession(NULL), m_hConnect(NULL), m_hRequest(NULL), m_hHttpReady(NULL)
{
    m_strAgent = lpAgent;

    Initialize();
}

HttpIO::~HttpIO()
{
    Release();
}

bool HttpIO::Initialize()
{
    m_hHttpReady = CreateEvent(NULL, FALSE, FALSE, NULL);

    if (m_hHttpReady == NULL)
    {
        return FALSE;
    }

    m_hHttpFailed = CreateEvent(NULL, FALSE, FALSE, NULL);

    if (m_hHttpFailed == NULL)
    {
        return FALSE;
    }

    return true;
}

void HttpIO::Release()
{
    Disconnect();

    if (m_hHttpFailed != NULL)
    {
        CloseHandle(m_hHttpFailed);
        m_hHttpFailed = NULL;
    }

    if (m_hHttpReady != NULL)
    {
        CloseHandle(m_hHttpReady);
        m_hHttpReady = NULL;
    }
}

bool HttpIO::Connect(LPCTSTR lpHost, INTERNET_PORT nPort /*= INTERNET_DEFAULT_PORT*/)
{
    if (m_hSession != NULL && m_hConnect != NULL)
    {
        return true;
    }

    Disconnect();

    m_hSession = WinHttpOpen(m_strAgent.GetAddress(),
                              WINHTTP_ACCESS_TYPE_NO_PROXY,
                              WINHTTP_NO_PROXY_NAME,
                              WINHTTP_NO_PROXY_BYPASS,
                              WINHTTP_FLAG_ASYNC);

    if (m_hSession == NULL)
    {
        return false;
    }

    WinHttpSetStatusCallback(m_hSession, StaticWinHttpStatusCallback, WINHTTP_CALLBACK_FLAG_ALL_COMPLETIONS, 0);

    m_hConnect = WinHttpConnect(m_hSession, lpHost, nPort, 0);

    if (m_hConnect == NULL)
    {
        return false;
    }

    return true;
}

void HttpIO::Disconnect()
{
    CancelRequest();

    if (m_hSession == NULL)
    {
        return;
    }

    if (m_hConnect != NULL)
    {
        WinHttpCloseHandle(m_hConnect);
        m_hConnect = NULL;
    }

    if (m_hSession != NULL)
    {
        WinHttpSetStatusCallback(m_hSession, NULL, WINHTTP_CALLBACK_FLAG_ALL_COMPLETIONS, 0);

        WinHttpCloseHandle(m_hSession);
        m_hSession = NULL;
    }
}

bool HttpIO::SendRequest(LPCTSTR lpVerb,
                         LPCTSTR lpPagePath,
                         LPCTSTR lpExtraHeader,
                         LPVOID  pData,
                         DWORD   dwCbDataSize,
                         HANDLE hEventCancel,
                         xl::Array<BYTE> *pContent /*= NULL*/)
{
    LPCTSTR lpAcceptTypes = _T("text/*\0");

    m_hRequest = WinHttpOpenRequest(m_hConnect, lpVerb, lpPagePath,
        NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_ESCAPE_PERCENT | WINHTTP_FLAG_REFRESH);
    
    if (m_hRequest == NULL)
    {
        return false;
    }

    LOKI_ON_BLOCK_EXIT_OBJ(*this, &HttpIO::CancelRequest);

    if (!WinHttpSendRequest(m_hRequest,
                            lpExtraHeader,
                            -1L,
                            pData,
                            dwCbDataSize,
                            dwCbDataSize,
                            (DWORD_PTR)this))
    {
        DWORD dwError = GetLastError();
        return false;
    }

    enum
    {
        EVENT_READY = 0,
        EVENT_FAILED,
        EVENT_CANCEL,
        EVENT_COUNT
    };

    HANDLE lpHandles[] = { m_hHttpReady, m_hHttpFailed, hEventCancel };
    DWORD dwWaitResult = WaitForMultipleObjects(EVENT_COUNT, lpHandles, FALSE, INFINITE);

    if (dwWaitResult != EVENT_READY)
    {
        return false;
    }

    if (!WinHttpReceiveResponse(m_hRequest, NULL))
    {
        return false;
    }

    dwWaitResult = WaitForMultipleObjects(EVENT_COUNT, lpHandles, FALSE, INFINITE);

    if (dwWaitResult != EVENT_READY)
    {
        return false;
    }

    if (pContent == NULL)
    {
        return true;
    }

    const DWORD BUFFER_SIZE = 4096;
    BYTE BUFFER[BUFFER_SIZE];

    while (true)
    {
        if (!WinHttpQueryDataAvailable(m_hRequest, NULL))
        {
            return false;
        }

        dwWaitResult = WaitForMultipleObjects(EVENT_COUNT, lpHandles, FALSE, INFINITE);

        if (dwWaitResult != EVENT_READY)
        {
            return false;
        }

        if (m_dwBytesAvailable == 0)
        {
            break;
        }

        while (m_dwBytesAvailable > 0)
        {
            DWORD dwBytesToRead = (m_dwBytesAvailable < BUFFER_SIZE ? m_dwBytesAvailable : BUFFER_SIZE);

            if (!WinHttpReadData(m_hRequest, BUFFER, dwBytesToRead, NULL))
            {
                return false;
            }

            dwWaitResult = WaitForMultipleObjects(EVENT_COUNT, lpHandles, FALSE, INFINITE);

            if (dwWaitResult != EVENT_READY)
            {
                return false;
            }

            pContent->InsertBuffer(pContent->Size(), BUFFER, dwBytesToRead);

            m_dwBytesAvailable -= m_dwBytesRead;
        }
    }

    return true;
}

void HttpIO::CancelRequest()
{
    if (m_hRequest != NULL)
    {
        WinHttpCloseHandle(m_hRequest);
        m_hRequest = NULL;
    }
}

void CALLBACK HttpIO::WinHttpStatusCallback(HINTERNET hInternet,
                                            DWORD dwInternetStatus,
                                            LPVOID lpvStatusInformation,
                                            DWORD dwStatusInformationLength)
{
    switch (dwInternetStatus)
    {
    case WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE:
        SetEvent(m_hHttpReady);
        break;
    case WINHTTP_CALLBACK_STATUS_HEADERS_AVAILABLE:
        SetEvent(m_hHttpReady);
        break;
    case WINHTTP_CALLBACK_STATUS_DATA_AVAILABLE:
        m_dwBytesAvailable = *(DWORD *)lpvStatusInformation;
        SetEvent(m_hHttpReady);
        break;
    case WINHTTP_CALLBACK_STATUS_READ_COMPLETE:
        m_dwBytesRead = dwStatusInformationLength;
        SetEvent(m_hHttpReady);
        break;
    case WINHTTP_CALLBACK_STATUS_REQUEST_ERROR:
        SetEvent(m_hHttpFailed);
        break;
    default:
        break;
    }
}

void CALLBACK HttpIO::StaticWinHttpStatusCallback(HINTERNET hInternet,
                                                  DWORD_PTR dwContext,
                                                  DWORD dwInternetStatus,
                                                  LPVOID lpvStatusInformation,
                                                  DWORD dwStatusInformationLength)
{
    ((HttpIO *)dwContext)->WinHttpStatusCallback(hInternet,
                                                 dwInternetStatus,
                                                 lpvStatusInformation,
                                                 dwStatusInformationLength);
}


