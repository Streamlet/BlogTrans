//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   DlgMain.h
//    Author:      Streamlet
//    Create Time: 2010-10-29
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __DLGMAIN_H_C609D6B5_74C5_4B05_A346_EA3EB90E4277_INCLUDED__
#define __DLGMAIN_H_C609D6B5_74C5_4B05_A346_EA3EB90E4277_INCLUDED__


#include "BlogTrans.h"
#include "IntegerBox.h"
#include <ShellAPI.h>
#include <xl/String/xlString.h>
#include <xl/Meta/xlScopeExit.h>
#include <xl/Win32/GUI/xlDialog.h>
#include <xl/Win32/GUI/xlStdStatic.h>
#include <xl/Win32/GUI/xlStdButton.h>
#include <xl/Win32/GUI/xlStdLink.h>
#include <xl/Win32/GUI/xlStdProgressBar.h>
#include <xl/Win32/Threads/xlCriticalSection.h>
#include "../Utility/MetaWeblog.h"
#include "../Utility/ImgPicker.h"
#include "../Utility/HttpGet.h"


class DlgMain : public xl::Dialog
{
public:
    static void ShowDialog();

private:
    DlgMain();
    ~DlgMain();

private:
    bool OnInitDialog();
    bool OnOK();
    bool OnCancel();

private:
    void CreateControls();
    void SetTexts();

private:
    // Message Map Handlers
    // LRESULT OnMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

private:
    // Command Message Handlers
    // LRESULT OnCommandMessage(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled);
    LRESULT OnButtonStart(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled);
    
private:
    // Notify Message Handlers
    // LRESULT OnNotifyMessage(HWND hWnd, UINT_PTR uID, UINT uCode, HWND hControl, BOOL &bHandled);
    LRESULT OnLinkWebsite(HWND hWnd, UINT_PTR uID, UINT uCode, HWND hControl, BOOL &bHandled);


private:
    BOOL BeforeEnterThread();
    void BeforeExitThread();
    void PutMsg(LPCTSTR lpFormat, ...);
    void SetProgressBarMarquee();
    void SetProgressBarNormal(int nStep, int nSteps);
    void StepProgressBar();
    void OffsetProgressBar(int nOffset);
    DWORD ThreadProc();
    static DWORD WINAPI StaticThreadProc(LPVOID lpThreadParameter);

protected:
    xl::StdButton       m_groupSource;
    xl::StdStatic       m_labelSourceUrl;
    xl::StdEdit         m_editSourceUrl;
    xl::StdStatic       m_labelSourceUserName;
    xl::StdEdit         m_editSourceUserName;
    xl::StdStatic       m_labelSourcePassword;
    xl::StdEdit         m_editSourcePassword;
    xl::StdButton       m_groupDest;
    xl::StdStatic       m_labelDestUrl;
    xl::StdEdit         m_editDestUrl;
    xl::StdStatic       m_labelDestUserName;
    xl::StdEdit         m_editDestUserName;
    xl::StdStatic       m_labelDestPassword;
    xl::StdEdit         m_editDestPassword;
    xl::StdStatic       m_labelPostsNumber;
    IntegerBox          m_editPostsNumber;
    xl::StdButton       m_checkUploadPicture;
    xl::StdEdit         m_editMessage;
    xl::StdProgressBar  m_process;
    xl::StdButton       m_buttonStart;
    xl::StdLink         m_link;

protected:
    HANDLE m_hWorkingThread;
    HANDLE m_hEventCancel;
    xl::CriticalSection m_cs;

protected:
    xl::String m_strSourceUrl;
    xl::String m_strSourceUserName;
    xl::String m_strSourcePassword;
    xl::String m_strDestUrl;
    xl::String m_strDestUserName;
    xl::String m_strDestPassword;
    int        m_nPostsNumber;
    bool       m_bUploadPicture;
};

#endif // #ifndef __DLGMAIN_H_C609D6B5_74C5_4B05_A346_EA3EB90E4277_INCLUDED__
