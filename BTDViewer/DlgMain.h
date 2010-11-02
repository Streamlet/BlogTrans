//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   DlgMain.h
//    Author:      Streamlet
//    Create Time: 2010-11-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __DLGMAIN_H_C3FCED4E_9F91_4051_BDE3_8CAE0A0E4481_INCLUDED__
#define __DLGMAIN_H_C3FCED4E_9F91_4051_BDE3_8CAE0A0E4481_INCLUDED__


#include "BTDViewer.h"
#include "WebBrowser.h"

class CDlgMain : public CDialogImpl<CDlgMain>,
                 public CMessageFilter,
                 public CIdleHandler,
                 public CUpdateUI<CDlgMain>,
                 public CWinDataExchange<CDlgMain>
{
public:
    enum { IDD = IDD_DLG_MAIN };

protected:

    BEGIN_DDX_MAP(CDlgMain)
    END_DDX_MAP()

protected:
    HANDLE m_hWorkingThread;
    HANDLE m_hEventCancel;
    CRITICAL_SECTION m_cs;
    WebBrowser m_wb;

public:
    CDlgMain()
    {

    }

    ~CDlgMain()
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
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //    LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //    LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //    LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

public:
    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        DoDataExchange();

        // center the dialog on the screen
        CenterWindow();

        // set icons
//         HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_APP_ICON), 
//             IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
//         SetIcon(hIcon, TRUE);
//         SetIcon(hIcon, FALSE);

        // register object for message filtering and idle updates
        CMessageLoop* pLoop = _Module.GetMessageLoop();
        ATLASSERT(pLoop != NULL);
        pLoop->AddMessageFilter(this);
        pLoop->AddIdleHandler(this);

        UIAddChildWindowContainer(m_hWnd);

//         m_wb.Create(m_hWnd);

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
        DestroyWindow();
        PostQuitMessage(IDOK);

        return TRUE;
    }
};

#endif // #ifndef __DLGMAIN_H_C3FCED4E_9F91_4051_BDE3_8CAE0A0E4481_INCLUDED__
