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
#include "CommonControlImpl.h"
#include "IntegerBox.h"
#include <ShellAPI.h>


class CDlgMain : public CDialogImpl<CDlgMain>,
                 public CMessageFilter,
                 public CIdleHandler,
                 public CUpdateUI<CDlgMain>,
                 public CWinDataExchange<CDlgMain>
{
public:
    enum { IDD = IDD_DLG_MAIN };

protected:
    CEditImpl               m_editSourceUrl;
    CEditImpl               m_editSourceUsername;
    CEditImpl               m_editSourcePassword;
    CEditImpl               m_editDestUrl;
    CEditImpl               m_editDestUsername;
    CEditImpl               m_editDestPassword;
    CIntegerBox             m_editPostsNumber;
    CButtonImpl             m_checkUploadPicture;
    CEditImpl               m_editMessage;
    CProgressBarCtrlImpl    m_process;
    CButtonImpl             m_buttonStart;
    CLinkCtrlImpl           m_link;

    BEGIN_DDX_MAP(CDlgMain)
        DDX_CONTROL(IDC_EDIT_SOURCE_URL, m_editSourceUrl)
        DDX_CONTROL(IDC_EDIT_SOURCE_USERNAME, m_editSourceUsername)
        DDX_CONTROL(IDC_EDIT_SOURCE_PASSWORD, m_editSourcePassword)
        DDX_CONTROL(IDC_EDIT_DEST_URL, m_editDestUrl)
        DDX_CONTROL(IDC_EDIT_DEST_USERNAME, m_editDestUsername)
        DDX_CONTROL(IDC_EDIT_DEST_PASSWORD, m_editDestPassword)
        DDX_CONTROL(IDC_EDIT_POSTS_NUMBER, m_editPostsNumber)
        DDX_CONTROL(IDC_CHECK_UPLOAD_PICTURE, m_checkUploadPicture)
        DDX_CONTROL(IDC_EDIT_MESSAGE, m_editMessage)
        DDX_CONTROL(IDC_PROGRESS, m_process)
        DDX_CONTROL(IDC_BUTTON_START, m_buttonStart)
        DDX_CONTROL(IDC_SYSLINK, m_link)
    END_DDX_MAP()

public:
    CDlgMain()
    {

    }

    virtual BOOL PreTranslateMessage(MSG* pMsg)
    {
        return CWindow::IsDialogMessage(pMsg);
    }

    virtual BOOL OnIdle()
    {
        return FALSE;
    }

public:
    BEGIN_UPDATE_UI_MAP(CDlgMain)
    END_UPDATE_UI_MAP()

    BEGIN_MSG_MAP(CDlgMain)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
        COMMAND_ID_HANDLER(IDC_BUTTON_START, OnButtonStart)
        NOTIFY_HANDLER(IDC_SYSLINK, NM_CLICK, OnLinkClick)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

public:
    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        DoDataExchange();

        // center the dialog on the screen
        CenterWindow();

        // set icons
        HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_APP_ICON), 
            IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
        SetIcon(hIcon, TRUE);
        SetIcon(hIcon, FALSE);

        // register object for message filtering and idle updates
        CMessageLoop* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->AddMessageFilter(this);
        pLoop->AddIdleHandler(this);

        UIAddChildWindowContainer(m_hWnd);

        return TRUE;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        // unregister message filtering and idle updates
        CMessageLoop* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->RemoveMessageFilter(this);
        pLoop->RemoveIdleHandler(this);

        return 0;
    }

    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        DestroyWindow();
        PostQuitMessage(IDCANCEL);
        return TRUE;
    }

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return TRUE;
    }
    
    LRESULT OnButtonStart(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return TRUE;
    }

    LRESULT OnLinkClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
    {
        ShellExecute(NULL, _T("open"), _T("http://www.streamlet.org/"), NULL, NULL, SW_SHOWNORMAL);
        return TRUE;
    }
};

#endif // #ifndef __DLGMAIN_H_C609D6B5_74C5_4B05_A346_EA3EB90E4277_INCLUDED__
