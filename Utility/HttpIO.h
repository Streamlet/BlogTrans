//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   HttpIO.h
//    Author:      Streamlet
//    Create Time: 2010-10-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __HTTPIO_H_2059AD7B_5F50_4E99_AB5A_AEA1956C9EC6_INCLUDED__
#define __HTTPIO_H_2059AD7B_5F50_4E99_AB5A_AEA1956C9EC6_INCLUDED__


#include <xl/Containers/xlArray.h>
#include <xl/Containers/xlMap.h>
#include <xl/String/xlString.h>
#include <Windows.h>
#include <WinHttp.h>


class HttpIO
{
public:
    HttpIO(LPCTSTR lpAgent = NULL);
    ~HttpIO();

private:
    bool Initialize();
    void Release();

public:
    bool Connect(LPCTSTR lpHost, INTERNET_PORT nPort = INTERNET_DEFAULT_PORT);
    void Disconnect();

public:
    bool SendRequest(LPCTSTR lpVerb,
                     LPCTSTR lpPagePath,
                     LPCTSTR lpExtraHeader,
                     LPVOID  pData,
                     DWORD   dwCbDataSize,
                     HANDLE hEventCancel,
                     xl::Array<BYTE> *pContent = NULL);

private:
    void CancelRequest();

private:
    xl::String m_strAgent;

    HINTERNET m_hSession;
    HINTERNET m_hConnect;
    HINTERNET m_hRequest;
    HANDLE m_hHttpReady;
    HANDLE m_hHttpFailed;

    DWORD m_dwBytesAvailable;
    DWORD m_dwBytesRead;


private:
    void CALLBACK WinHttpStatusCallback(HINTERNET hInternet,
                                        DWORD dwInternetStatus,
                                        LPVOID lpvStatusInformation,
                                        DWORD dwStatusInformationLength);

private:
    static void CALLBACK StaticWinHttpStatusCallback(HINTERNET hInternet,
                                                     DWORD_PTR dwContext,
                                                     DWORD dwInternetStatus,
                                                     LPVOID lpvStatusInformation,
                                                     DWORD dwStatusInformationLength);
};

#endif // #ifndef __HTTPIO_H_2059AD7B_5F50_4E99_AB5A_AEA1956C9EC6_INCLUDED__
