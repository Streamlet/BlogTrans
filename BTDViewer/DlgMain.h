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


#include <exdisp.h>
#include <exdispid.h>
#include <mshtml.h>
#include <mshtmdid.h>

#include "BTDViewer.h"


class CDlgMain : public CAxDialogImpl<CDlgMain>,
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
    CComPtr<IWebBrowser2> m_pWebBrowser2;

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

//     BEGIN_SINK_MAP(CDlgMain)
//         SINK_ENTRY_EX(IDC_EXPLORER, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete) 
//         SINK_ENTRY_EX(IDC_EXPLORER, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, OnBeforeNavigate2)
//     END_SINK_MAP()

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

        CAxWindow axWin = GetDlgItem(IDC_EXPLORER);
        axWin.QueryControl(&m_pWebBrowser2);

        if (m_pWebBrowser2 == NULL)
        {
            return FALSE;
        }

        //WebBrowser::DispEventAdvise(m_pWebBrowser2);
        m_pWebBrowser2->Navigate(CComBSTR("http://www.streamlet.org/"),NULL,NULL,NULL,NULL);


        return TRUE;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        //WebBrowser::DispEventUnadvise(m_pWebBrowser2);

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

//     void OnDocumentComplete(IDispatch *, VARIANT* )
//     {
//         MessageBox(_T("Document complete!"), _T("Info"), MB_OK|MB_ICONEXCLAMATION);
//     }
// 
//     void OnBeforeNavigate2 (
//         IDispatch* pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName,
//         VARIANT* PostData, VARIANT* Headers, VARIANT_BOOL* Cancel )
//     {
//         MessageBox(_T("Before navigate!"), _T("Info"), MB_OK|MB_ICONEXCLAMATION);
//     };
};

#endif // #ifndef __DLGMAIN_H_C3FCED4E_9F91_4051_BDE3_8CAE0A0E4481_INCLUDED__
