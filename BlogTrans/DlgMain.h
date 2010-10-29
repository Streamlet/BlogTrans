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
#include <Loki/ScopeGuard.h>
#include "../MetaWeblog/MetaWeblog.h"
#include "../MetaWeblog/ImgPicker.h"
#include "../MetaWeblog/HttpGet.h"


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
    CEditImpl               m_editSourceUserName;
    CEditImpl               m_editSourcePassword;
    CEditImpl               m_editDestUrl;
    CEditImpl               m_editDestUserName;
    CEditImpl               m_editDestPassword;
    CIntegerBox             m_editPostsNumber;
    CButtonImpl             m_checkUploadPicture;
    CEditImpl               m_editMessage;
    CProgressBarCtrlImpl    m_process;
    CButtonImpl             m_buttonStart;
    CLinkCtrlImpl           m_link;

    BEGIN_DDX_MAP(CDlgMain)
        DDX_CONTROL(IDC_EDIT_SOURCE_URL, m_editSourceUrl)
        DDX_CONTROL(IDC_EDIT_SOURCE_USERNAME, m_editSourceUserName)
        DDX_CONTROL(IDC_EDIT_SOURCE_PASSWORD, m_editSourcePassword)
        DDX_CONTROL(IDC_EDIT_DEST_URL, m_editDestUrl)
        DDX_CONTROL(IDC_EDIT_DEST_USERNAME, m_editDestUserName)
        DDX_CONTROL(IDC_EDIT_DEST_PASSWORD, m_editDestPassword)
        DDX_CONTROL(IDC_EDIT_POSTS_NUMBER, m_editPostsNumber)
        DDX_CONTROL(IDC_CHECK_UPLOAD_PICTURE, m_checkUploadPicture)
        DDX_CONTROL(IDC_EDIT_MESSAGE, m_editMessage)
        DDX_CONTROL(IDC_PROGRESS, m_process)
        DDX_CONTROL(IDC_BUTTON_START, m_buttonStart)
        DDX_CONTROL(IDC_SYSLINK, m_link)
    END_DDX_MAP()

protected:
    HANDLE m_hWorkingThread;
    HANDLE m_hEventCancel;
    CRITICAL_SECTION m_cs;

public:
    CDlgMain()
        : m_hWorkingThread(NULL), m_hEventCancel(NULL)
    {
        m_hEventCancel = CreateEvent(NULL, TRUE, TRUE, NULL);

        InitializeCriticalSection(&m_cs);
    }

    ~CDlgMain()
    {
        DeleteCriticalSection(&m_cs);

        CloseHandle(m_hEventCancel);
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
        if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
        {
            DestroyWindow();
            PostQuitMessage(IDCANCEL);
        }

        return TRUE;
    }

    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return TRUE;
    }
    
    LRESULT OnLinkClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
    {
        ShellExecute(NULL, _T("open"), _T("http://www.streamlet.org/"), NULL, NULL, SW_SHOWNORMAL);
        return TRUE;
    }

    LRESULT OnButtonStart(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
        {
            if (BeforeEnterThread())
            {
                ResetEvent(m_hEventCancel);
                m_hWorkingThread = CreateThread(NULL, 0, StaticThreadProc, (LPVOID)this, 0, NULL);
            }
        }
        else
        {
            if (AtlMessageBox(m_hWnd, _T("Blog Transporter is working. Cancel now?"), _T("Message"), MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
            {
                return FALSE;
            }

            if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
            {
                return FALSE;
            }

            SetEvent(m_hEventCancel);
        }

        return TRUE;
    }

protected:
    CAtlString m_strSourceUrl;
    CAtlString m_strSourceUserName;
    CAtlString m_strSourcePassword;
    CAtlString m_strDestUrl;
    CAtlString m_strDestUserName;
    CAtlString m_strDestPassword;
    int        m_nPostsNumber;
    BOOL       m_bUploadPicture;

protected:
    BOOL BeforeEnterThread()
    {
        Loki::ScopeGuard sgRestoreControls = Loki::MakeObjGuard(*this, &CDlgMain::BeforeExitThread);

        m_buttonStart.EnableWindow(FALSE);

        m_editSourceUrl.GetWindowText(m_strSourceUrl);
        m_editSourceUserName.GetWindowText(m_strSourceUserName);
        m_editSourcePassword.GetWindowText(m_strSourcePassword);
        m_editDestUrl.GetWindowText(m_strDestUrl);
        m_editDestUserName.GetWindowText(m_strDestUserName);
        m_editDestPassword.GetWindowText(m_strDestPassword);
        m_nPostsNumber = m_editPostsNumber.GetValue();
        m_bUploadPicture = (m_checkUploadPicture.GetCheck() == BST_CHECKED);

        if (m_strSourceUrl.IsEmpty() ||
            m_strSourceUserName.IsEmpty() ||
            m_strSourcePassword.IsEmpty() ||
            m_strDestUrl.IsEmpty() ||
            m_strDestUserName.IsEmpty() ||
            m_strDestPassword.IsEmpty())
        {
            AtlMessageBox(m_hWnd, _T("Please input blog information."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        if (m_nPostsNumber <= 0)
        {
            AtlMessageBox(m_hWnd, _T("Please input the number of posts you want to transport."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        if (!m_bUploadPicture)
        {
            if (AtlMessageBox(m_hWnd, _T("You choose not to upload pictures to destnation blog. Are you sure?"), _T("Error"), MB_OKCANCEL | MB_ICONEXCLAMATION) != IDOK)
            {
                return FALSE;
            }
        }

        m_editSourceUrl.EnableWindow(FALSE);
        m_editSourceUserName.EnableWindow(FALSE);
        m_editSourcePassword.EnableWindow(FALSE);
        m_editDestUrl.EnableWindow(FALSE);
        m_editDestUserName.EnableWindow(FALSE);
        m_editDestPassword.EnableWindow(FALSE);
        m_editPostsNumber.EnableWindow(FALSE);
        m_checkUploadPicture.EnableWindow(FALSE);
        m_editMessage.SetWindowText(_T(""));

        sgRestoreControls.Dismiss();

        return TRUE;
    }

    void BeforeExitThread()
    {
        EnterCriticalSection(&m_cs);
        m_buttonStart.EnableWindow(FALSE);
        LeaveCriticalSection(&m_cs);

        if (m_hWorkingThread != NULL)
        {
            CloseHandle(m_hWorkingThread);
            m_hWorkingThread = NULL;
        }

        SetProgressBarNormal(0, 0);

        m_buttonStart.SetWindowText(_T("Start"));
        m_editSourceUrl.EnableWindow();
        m_editSourceUserName.EnableWindow();
        m_editSourcePassword.EnableWindow();
        m_editDestUrl.EnableWindow();
        m_editDestUserName.EnableWindow();
        m_editDestPassword.EnableWindow();
        m_editPostsNumber.EnableWindow();
        m_checkUploadPicture.EnableWindow();
        m_buttonStart.EnableWindow();

        SetEvent(m_hEventCancel);
    }

    void PutMsg(LPCTSTR lpFormat, ...)
    {
        CAtlString strMessage;

        va_list args;
        va_start(args, lpFormat);
        strMessage.FormatV(lpFormat, args);
        va_end(args);

        strMessage += _T("\r\n");

        m_editMessage.AppendText(strMessage);
    }

    void SetProgressBarMarquee()
    {
        m_process.ModifyStyle(0, PBS_MARQUEE);
        m_process.SetMarquee(TRUE, 10);
    }

    void SetProgressBarNormal(int nStep, int nSteps)
    {
        m_process.SetMarquee(FALSE, 0);
        m_process.ModifyStyle(PBS_MARQUEE, 0);
        m_process.SetRange(0, nStep * nSteps);
        m_process.SetStep(nStep);
        m_process.SetPos(0);
    }

    void StepProgressBar()
    {
        m_process.StepIt();
    }

    void OffsetProgressBar(int nOffset)
    {
        m_process.OffsetPos(nOffset);
    }

    DWORD ThreadProc()
    {
        LOKI_ON_BLOCK_EXIT_OBJ(*this, &CDlgMain::BeforeExitThread);

        EnterCriticalSection(&m_cs);
        m_buttonStart.EnableWindow(FALSE);
        m_buttonStart.SetWindowText(_T("Stop"));
        m_buttonStart.EnableWindow(TRUE);
        LeaveCriticalSection(&m_cs);

        MetaWeblog srcBlog(m_hEventCancel);

        PutMsg(_T("Checking source blog..."));
        SetProgressBarMarquee();

        if (!srcBlog.Connect((LPCTSTR)m_strSourceUrl, (LPCTSTR)m_strSourceUserName, (LPCTSTR)m_strSourcePassword))
        {
            PutMsg(_T("Failed to connect to source blog."));
            return 0;
        }

        auto srcBlogs = srcBlog.GetUsersBlogs();

        if (srcBlogs.Empty())
        {
            PutMsg(_T("Failed to get source blog information."));
            return 0;
        }

        if (srcBlogs.Size() > 1)
        {
            PutMsg(_T("Your have more than one blog on the source blog server. Not supported."));
            return 0;
        }

        auto srcBlogInfo = **srcBlogs.Begin();

        if (srcBlogInfo.blogid.Empty())
        {
            PutMsg(_T("Failed to get source blog information."));
            return 0;
        }

        PutMsg(_T("Blog ID: %s"), srcBlogInfo.blogid.GetAddress());;
        PutMsg(_T("Blog Name: %s"), srcBlogInfo.blogName.GetAddress());;
        PutMsg(_T("Blog URL: %s"), srcBlogInfo.url.GetAddress());;

        MetaWeblog destBlog(m_hEventCancel);

        PutMsg(_T("Checking dest blog..."));
        SetProgressBarMarquee();

        if (!destBlog.Connect((LPCTSTR)m_strDestUrl, (LPCTSTR)m_strDestUserName, (LPCTSTR)m_strDestPassword))
        {
            PutMsg(_T("Failed to connect to destination blog."));
            return 0;
        }

        auto destBlogs = destBlog.GetUsersBlogs();

        if (destBlogs.Empty())
        {
            PutMsg(_T("Failed to get destination blog information."));
            return 0;
        }

        if (destBlogs.Size() > 1)
        {
            PutMsg(_T("Your have more than one blog on the destination blog server. Not supported."));
            return 0;
        }

        auto destBlogInfo = **destBlogs.Begin();

        if (destBlogInfo.blogid.Empty())
        {
            PutMsg(_T("Failed to get destination blog information."));
            return 0;
        }

        PutMsg(_T("Blog ID: %s"), destBlogInfo.blogid.GetAddress());;
        PutMsg(_T("Blog Name: %s"), destBlogInfo.blogName.GetAddress());;
        PutMsg(_T("Blog URL: %s"), destBlogInfo.url.GetAddress());;

        PutMsg(_T("Blog information is valid."));

        if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
        {
            PutMsg(_T("User cancelled."));
            return 0;
        }
        
        PutMsg(_T("Getting recent %u from source blog..."), m_nPostsNumber);
        SetProgressBarMarquee();

        auto posts = srcBlog.GetRecentPosts(srcBlogInfo.blogid, m_nPostsNumber);

        if (posts.Empty())
        {
            PutMsg(_T("Get no posts from source blog. Stop."), posts.Size());
            return 0;
        }
        
        PutMsg(_T("Totally got %u posts."), posts.Size());
        SetProgressBarNormal(100, posts.Size());
        StepProgressBar();

        if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
        {
            PutMsg(_T("User cancelled."));
            return 0;
        }

        for (auto it = posts.Begin(); it != posts.End(); ++it)
        {
            auto post = **it;

            PutMsg(_T("Solving post [%s]: %s"), post.postid.GetAddress(), post.title.GetAddress());

            int nProgressUnit = 100;

            if (m_bUploadPicture)
            {
                PutMsg(_T("Analyzing picture links..."));

                ImgPicker imgPicker;
                auto imgs = imgPicker.Analyze(post.description);

                if (imgs.Empty())
                {
                    PutMsg(_T("No picture link found."));
                }
                else // if (imgs.Empty())
                {
                    int nImageUnit = (int)(100.0 / (imgs.Size() + 2));

                    xl::String strNewContent;
                    strNewContent += post.description.Left(imgs.Begin()->nIndex);

                    for (size_t i = 0; i < imgs.Size(); ++i)
                    {
                        xl::String strImgUrl = post.description.SubString(imgs[i].nIndex, imgs[i].nLength);
                        xl::Array<BYTE> arrData;

                        PutMsg(_T("Downloading %s ..."), strImgUrl.GetAddress());

                        HttpGet hg;

                        if (!hg.SendRequest(strImgUrl.GetAddress(), m_hEventCancel, &arrData))
                        {
                            PutMsg(_T("Failed to download picture."));
                        }
                        else // if (!hg.SendRequest(strImgUrl.GetAddress(), m_hEventCancel, &arrData))
                        {
                            PutMsg(_T("Uploading picture to destination blog....."));

                            xl::String strExtName;
                            int nPos = strImgUrl.LastIndexOf(L".");

                            if (nPos != -1)
                            {
                                strExtName += strImgUrl.Right(strImgUrl.Length() - nPos - 1);
                                strExtName.MakeLower();

                                if (strExtName == _T("jpg"))
                                {
                                    strExtName = _T("jpeg");
                                }
                            }
                            else
                            {
                                strExtName += _T("*");
                            }

                            xl::String strMimeType = _T("image/");
                            strMimeType += strExtName;

                            xl::String strName = _T("BlogTransporter-");
                            strName += post.postid + _T("-");
                            CAtlString str;
                            str.Format(_T("%u"), i);
                            strName += (LPCTSTR)str;

                            MediaObject mediaObject;
                            mediaObject.type = strMimeType;
                            mediaObject.name = strName;
                            mediaObject.bits = arrData;

                            auto mediaUrl = *destBlog.NewMediaObject(destBlogInfo.blogid, mediaObject);

                            if (mediaUrl.url.Empty())
                            {
                                PutMsg(_T("Failed to upload picture."));
                            }
                            else
                            {
                                PutMsg(_T("Picture URL: %s"), mediaUrl.url.GetAddress());
                                strImgUrl = mediaUrl.url;
                            }

                        } // if (!hg.SendRequest(strImgUrl.GetAddress(), m_hEventCancel, &arrData))

                        if (i != imgs.Size() - 1)
                        {
                            strNewContent += strImgUrl + post.description.SubString(imgs[i].nIndex + imgs[i].nLength, imgs[i + 1].nIndex - (imgs[i].nIndex + imgs[i].nLength));
                        }
                        else
                        {
                            strNewContent += strImgUrl + post.description.Right(post.description.Length() - (imgs[i].nIndex + imgs[i].nLength));
                        }
                    
                        OffsetProgressBar(nImageUnit);
                        nProgressUnit -= nImageUnit;

                        if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
                        {
                            PutMsg(_T("User cancelled."));
                            return 0;
                        }

                    } // for (int i = 0; i < imgs.Size(); ++i)

                    post.description = strNewContent;

                } // if (imgs.Empty())

            } // if (m_bUploadPicture)

            OffsetProgressBar(nProgressUnit / 2);

            if (WaitForSingleObject(m_hEventCancel, 0) == WAIT_OBJECT_0)
            {
                PutMsg(_T("User cancelled."));
                return 0;
            }

            PutMsg(_T("Publishing to destination blog..."));

            auto postid = destBlog.NewPost(destBlogInfo.blogid, post, true);

            if (postid.Empty())
            {
                PutMsg(_T("Failed to publish."));
            }

            OffsetProgressBar(nProgressUnit - nProgressUnit / 2);

            PutMsg(_T("Delay 5 seconds..."));

            if (WaitForSingleObject(m_hEventCancel, 5000) == WAIT_OBJECT_0)
            {
                PutMsg(_T("User cancelled."));
                return 0;
            }
        }
        
        PutMsg(_T("Done. Please check the log for errors."));

        return 0;
    }

    static DWORD WINAPI StaticThreadProc(LPVOID lpThreadParameter)
    {
        return ((CDlgMain *)lpThreadParameter)->ThreadProc();
    }
};

#endif // #ifndef __DLGMAIN_H_C609D6B5_74C5_4B05_A346_EA3EB90E4277_INCLUDED__
