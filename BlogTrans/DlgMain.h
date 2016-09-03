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
#include <xl/Common/String/xlString.h>
#include <xl/Common/Meta/xlScopeExit.h>
#include <xl/Windows/GUI/xlDialog.h>
#include <xl/Windows/GUI/xlStdStatic.h>
#include <xl/Windows/GUI/xlStdButton.h>
#include <xl/Windows/GUI/xlStdLink.h>
#include <xl/Windows/GUI/xlStdProgressBar.h>
#include <xl/Windows/Threads/xlCriticalSection.h>
#include <xl/Windows/Threads/xlThread.h>
#include "../Utility/MetaWeblog.h"
#include "../Utility/ImgPicker.h"
#include "../Utility/HttpGet.h"


class DlgMain : public xl::Windows::Dialog
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
    // LRESULT OnNotifyMessage(HWND hWnd, LPNMHDR lpNMHDR, BOOL &bHandled);
    LRESULT OnLinkWebsite(HWND hWnd, LPNMHDR lpNMHDR, BOOL &bHandled);


private:
    BOOL BeforeEnterThread();
    void BeforeExitThread();
    void PutMsg(LPCTSTR lpFormat, ...);
    void SetProgressBarMarquee();
    void SetProgressBarNormal(int nStep, int nSteps);
    void StepProgressBar();
    void OffsetProgressBar(int nOffset);
    DWORD ThreadProc(HANDLE hQuit, LPVOID lpParam);

protected:
    xl::Windows::StdButton       m_groupSource;
    xl::Windows::StdStatic       m_labelSourceUrl;
    xl::Windows::StdEdit         m_editSourceUrl;
    xl::Windows::StdStatic       m_labelSourceUserName;
    xl::Windows::StdEdit         m_editSourceUserName;
    xl::Windows::StdStatic       m_labelSourcePassword;
    xl::Windows::StdEdit         m_editSourcePassword;
    xl::Windows::StdButton       m_groupDest;
    xl::Windows::StdStatic       m_labelDestUrl;
    xl::Windows::StdEdit         m_editDestUrl;
    xl::Windows::StdStatic       m_labelDestUserName;
    xl::Windows::StdEdit         m_editDestUserName;
    xl::Windows::StdStatic       m_labelDestPassword;
    xl::Windows::StdEdit         m_editDestPassword;
    xl::Windows::StdStatic       m_labelPostsNumber;
    IntegerBox	                 m_editPostsNumber;
    xl::Windows::StdButton       m_checkUploadPicture;
    xl::Windows::StdEdit         m_editMessage;
    xl::Windows::StdProgressBar  m_process;
    xl::Windows::StdButton       m_buttonStart;
    xl::Windows::StdLink         m_link;

protected:
    xl::Windows::CriticalSection m_cs;
    xl::Windows::Thread<> m_thread;

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
