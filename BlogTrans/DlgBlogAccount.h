//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   DlgBlogAccount.h
//    Author:      Streamlet
//    Create Time: 2010-11-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __DLGBLOGACCOUNT_H_269EA7A9_4519_4B89_9C2D_300AC6759D60_INCLUDED__
#define __DLGBLOGACCOUNT_H_269EA7A9_4519_4B89_9C2D_300AC6759D60_INCLUDED__


#include "BlogTrans.h"
#include "CommonControlImpl.h"
#include <Loki/ScopeGuard.h>
#include <xl/Objects/xlString.h>
#include "../Utility/MetaWeblog.h"
#include "../Utility/ImgPicker.h"
#include "../Utility/HttpGet.h"

struct BlogInformation
{
    xl::String strApiUrl;
    xl::String strUserName;
    xl::String strPassword;
    xl::String strBlogId;
    xl::String strBlogName;
    xl::String strBlogUrl;
};

class CDlgBlogAccount : public CDialogImpl<CDlgBlogAccount>,
                        public CMessageFilter,
                        public CIdleHandler,
                        public CUpdateUI<CDlgBlogAccount>,
                        public CWinDataExchange<CDlgBlogAccount>
{
public:
    static bool GetBlogInfo(BlogInformation *pBlogInfo)
    {
        CDlgBlogAccount dlg;
        dlg.m_pBlogInfo = pBlogInfo;

        if (dlg.DoModal() != IDOK)
        {
            return false;
        }

        return true;
    }

protected:
    BlogInformation *m_pBlogInfo;

public:
    enum { IDD = IDD_DLG_BLOG_ACCOUNT };

protected:
    CComboBoxImpl           m_comboUrl;
    CEditImpl               m_editUserName;
    CEditImpl               m_editPassword;
    CProgressBarCtrlImpl    m_process;
    CButtonImpl             m_buttonOK;
    CButtonImpl             m_buttonCancel;

    BEGIN_DDX_MAP(CDlgBlogAccount)
        DDX_CONTROL(IDC_COMBO_URL, m_comboUrl)
        DDX_CONTROL(IDC_EDIT_USERNAME, m_editUserName)
        DDX_CONTROL(IDC_EDIT_PASSWORD, m_editPassword)
        DDX_CONTROL(IDC_PROGRESS, m_process)
        DDX_CONTROL(IDC_BUTTON_OK, m_buttonOK)
        DDX_CONTROL(IDC_BUTTON_CANCEL, m_buttonCancel)
    END_DDX_MAP()

protected:
    HANDLE m_hThread;
    HANDLE m_hEventCancel;

protected:
    CDlgBlogAccount()
        : m_hThread(NULL), m_hEventCancel(NULL), m_pBlogInfo(nullptr), m_bSuccess(false)
    {
        m_hEventCancel = CreateEvent(NULL, TRUE, TRUE, NULL);
    }

    ~CDlgBlogAccount()
    {
        if (m_hEventCancel != NULL)
        {
            CloseHandle(m_hEventCancel);
            m_hEventCancel = NULL;
        }
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
    BEGIN_UPDATE_UI_MAP(CDlgBlogAccount)
    END_UPDATE_UI_MAP()

protected:
    BEGIN_MSG_MAP(CDlgBlogAccount)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
        COMMAND_ID_HANDLER(IDC_BUTTON_OK, OnOK)
        COMMAND_ID_HANDLER(IDC_BUTTON_CANCEL, OnCancel)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //    LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //    LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //    LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

protected:
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

        for (auto it = g.recentApiUrl.Begin(); it != g.recentApiUrl.End(); ++it)
        {
            m_comboUrl.AddString(it->GetAddress());
        }

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
        if (WaitForSingleObject(m_hEventCancel, 0) != WAIT_OBJECT_0)
        {
            SetEvent(m_hEventCancel);
        }
        else
        {
            EndDialog(IDCANCEL);
        }

        return TRUE;
    }

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        if (!BeforeEnterThread())
        {
            return FALSE;
        }

        ResetEvent(m_hEventCancel);
        m_hThread = CreateThread(NULL, 0, StaticThreadProc, (LPVOID)this, 0, NULL);

        return TRUE;
    }

protected:
    CAtlString m_strUrl;
    CAtlString m_strUserName;
    CAtlString m_strPassword;
    
    bool m_bSuccess;

protected:
    BOOL BeforeEnterThread()
    {
        Loki::ScopeGuard sgRestoreControls = Loki::MakeObjGuard(*this, &CDlgBlogAccount::BeforeExitThread);

        m_bSuccess = false;

        m_buttonOK.EnableWindow(FALSE);

        m_comboUrl.GetWindowText(m_strUrl);
        m_editUserName.GetWindowText(m_strUserName);
        m_editPassword.GetWindowText(m_strPassword);

        if (m_strUrl.IsEmpty() ||
            m_strUserName.IsEmpty() ||
            m_strPassword.IsEmpty())
        {
            AtlMessageBox(m_hWnd, _T("Please input blog information."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        m_comboUrl.EnableWindow(FALSE);
        m_editUserName.EnableWindow(FALSE);
        m_editPassword.EnableWindow(FALSE);
        m_buttonCancel.SetWindowText(_T("Stop"));
        m_process.SetMarquee(TRUE);
        m_process.ShowWindow(SW_SHOW);

        sgRestoreControls.Dismiss();

        return TRUE;
    }

    void BeforeExitThread()
    {
        if (m_hThread != NULL)
        {
            CloseHandle(m_hThread);
            m_hThread = NULL;
        }

        m_process.ShowWindow(SW_HIDE);
        m_process.SetMarquee(FALSE);

        m_comboUrl.EnableWindow();
        m_editUserName.EnableWindow();
        m_editPassword.EnableWindow();
        m_buttonCancel.SetWindowText(_T("Cancel"));
        m_buttonOK.EnableWindow();

        if (m_bSuccess)
        {
            EndDialog(IDOK);
        }

        SetEvent(m_hEventCancel);
    }

    DWORD ThreadProc()
    {
        LOKI_ON_BLOCK_EXIT_OBJ(*this, &CDlgBlogAccount::BeforeExitThread);

        MetaWeblog metaWeblog(m_hEventCancel);

        bool bConnected = metaWeblog.Connect((LPCTSTR)m_strUrl, (LPCTSTR)m_strUserName, (LPCTSTR)m_strPassword);

        if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
        {
            return 0;
        }

        if (!bConnected)
        {
            AtlMessageBox(m_hWnd, _T("Failed to connect to server."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
            return 0;
        }

        auto blogs = metaWeblog.GetUsersBlogs();

        if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
        {
            return 0;
        }

        if (blogs.Empty())
        {
            AtlMessageBox(m_hWnd, _T("Failed to get blog information. User account correct?"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
            return 0;
        }

        if (blogs.Size() > 1)
        {
            AtlMessageBox(m_hWnd, _T("This account has more than one blogs. Blog Transporter doesn't support multiple blogs on one account."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
            return 0;
        }

        auto blog = **blogs.Begin();

        if (blog.blogid.Empty())
        {
            AtlMessageBox(m_hWnd, _T("The blog ID returned from server is empty."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
            return 0;
        }

        if (m_pBlogInfo != nullptr)
        {
            m_pBlogInfo->strApiUrl      = (LPCTSTR)m_strUrl;
            m_pBlogInfo->strUserName    = (LPCTSTR)m_strUserName;
            m_pBlogInfo->strPassword    = (LPCTSTR)m_strPassword;
            m_pBlogInfo->strBlogId      = blog.blogid;
            m_pBlogInfo->strBlogName    = blog.blogName;
            m_pBlogInfo->strBlogUrl     = blog.url;
        }

        g.recentApiUrl.Insert((LPCTSTR)m_strUrl);
        m_bSuccess = true;

        return 0;
    }

    static DWORD WINAPI StaticThreadProc(LPVOID lpThreadParameter)
    {
        return ((CDlgBlogAccount *)lpThreadParameter)->ThreadProc();
    }
};

#endif // #ifndef __DLGBLOGACCOUNT_H_269EA7A9_4519_4B89_9C2D_300AC6759D60_INCLUDED__
