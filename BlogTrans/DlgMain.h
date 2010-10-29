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

class CDlgMain : public CDialogImpl<CDlgMain>,
                 public CMessageFilter,
                 public CIdleHandler,
                 public CUpdateUI<CDlgMain>,
                 public CWinDataExchange<CDlgMain>
{
public:
    enum { IDD = IDD_DLG_MAIN };

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

    BEGIN_UPDATE_UI_MAP(CDlgMain)
    END_UPDATE_UI_MAP()

    BEGIN_DDX_MAP(CDlgMain)
    END_DDX_MAP()

    BEGIN_MSG_MAP(CDlgMain)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        // center the dialog on the screen
        CenterWindow();

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
        CloseDialog(IDCANCEL);
        return TRUE;
    }

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CloseDialog(IDOK);
        return TRUE;
    }

    void CloseDialog(int nVal)
    {
        DestroyWindow();
        PostQuitMessage(nVal);
    }

};

#endif // #ifndef __DLGMAIN_H_C609D6B5_74C5_4B05_A346_EA3EB90E4277_INCLUDED__
