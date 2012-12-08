//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   DlgMain.cpp
//    Author:      Streamlet
//    Create Time: 2012-12-08
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------


#include "targetver.h"
#include "DlgMain.h"

enum
{
    ID_STATIC   = -1,
    ID_NULL     = 0,

    ID_START    = 100,

    ID_EDIT_SOURCE_URL,
    ID_EDIT_SOURCE_USERNAME,
    ID_EDIT_SOURCE_PASSWORD,
    ID_EDIT_DEST_URL,
    ID_EDIT_DEST_USERNAME,
    ID_EDIT_DEST_PASSWORD,
    ID_EDIT_POSTS_NUMBER,
    ID_CHECK_UPLOAD_PICTURE,
    ID_EDIT_MESSAGE,
    ID_PROGRESS,
    ID_BUTTON_START,
    ID_SYSLINK
};

void DlgMain::ShowDialog()
{
    DlgMain dlg;
    dlg.Create(480, 560);
    dlg.DoModal();
}

DlgMain::DlgMain()
{
    AppendCommandMsgHandler(ID_BUTTON_START, CommandMsgHandler(this, &DlgMain::OnButtonStart));
    AppendNotifyMsgHandler(ID_SYSLINK, NM_CLICK, NotifyMsgHandler(this, &DlgMain::OnButtonStart));
}

DlgMain::~DlgMain()
{

}

bool DlgMain::OnInitDialog()
{
    CreateControls();
    SetTexts();

    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APP_ICON));
    SetIcon(hIcon, TRUE);
    SetIcon(hIcon, FALSE);

    return true;
}

bool DlgMain::OnOK()
{
    return false;
}

bool DlgMain::OnCancel()
{
    if (m_thread.Wait(0))
    {
        return true;
    }

    return false;
}

void DlgMain::CreateControls()
{
    m_groupSource        .Create(ID_STATIC,               this, 10,  10,  454, 112,  WS_CHILD | WS_VISIBLE | BS_GROUPBOX);
    m_labelSourceUrl     .Create(ID_STATIC,               this, 20,  32,  434, 16);
    m_editSourceUrl      .Create(ID_EDIT_SOURCE_URL,      this, 20,  56,  434, 21);
    m_labelSourceUserName.Create(ID_STATIC,               this, 20,  90,  72,  16);
    m_editSourceUserName .Create(ID_EDIT_SOURCE_USERNAME, this, 92,  88,  134, 21);
    m_labelSourcePassword.Create(ID_STATIC,               this, 248, 90,  72,  16);
    m_editSourcePassword .Create(ID_EDIT_SOURCE_PASSWORD, this, 320, 88,  134, 21,  WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_PASSWORD);

    m_groupDest          .Create(ID_STATIC,               this, 10,  132, 454, 112, WS_CHILD | WS_VISIBLE | BS_GROUPBOX);
    m_labelDestUrl       .Create(ID_STATIC,               this, 20,  154, 434, 16);
    m_editDestUrl        .Create(ID_EDIT_DEST_URL,        this, 20,  178, 434, 21);
    m_labelDestUserName  .Create(ID_STATIC,               this, 20,  212, 72,  16);
    m_editDestUserName   .Create(ID_EDIT_DEST_USERNAME,   this, 92,  214, 134, 21);
    m_labelDestPassword  .Create(ID_STATIC,               this, 248, 212, 72,  16);
    m_editDestPassword   .Create(ID_EDIT_DEST_PASSWORD,   this, 320, 214, 134, 21,  WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_PASSWORD);

    m_labelPostsNumber   .Create(ID_STATIC,               this, 20,  256, 106, 16);
    m_editPostsNumber    .Create(ID_EDIT_POSTS_NUMBER,    this, 126, 254, 100, 21);
    m_checkUploadPicture .Create(ID_CHECK_UPLOAD_PICTURE, this, 248, 256, 206, 16,  WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX);

    m_editMessage        .Create(ID_EDIT_MESSAGE,         this, 10,  284, 454, 176, WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY | ES_WANTRETURN | WS_VSCROLL);
    m_process            .Create(ID_PROGRESS,             this, 10,  472, 360, 24);
    m_buttonStart        .Create(ID_BUTTON_START,         this, 384, 472, 80,  24);
    m_link               .Create(ID_SYSLINK,              this, 10,  510, 454, 18);
}

void DlgMain::SetTexts()
{
    SetWindowText(_T("Blog Transporter v1.1"));

    m_groupSource.SetWindowText(_T("Source Blog"));
    m_labelSourceUrl.SetWindowText(_T("MetaWeblog API URL:"));
    m_labelSourceUserName.SetWindowText(_T("Username:"));
    m_labelSourcePassword.SetWindowText(_T("Password:"));

    m_groupDest.SetWindowText(_T("Destination Blog"));
    m_labelDestUrl.SetWindowText(_T("MetaWeblog API URL:"));
    m_labelDestUserName.SetWindowText(_T("Username:"));
    m_labelDestPassword.SetWindowText(_T("Password:"));

    m_labelPostsNumber.SetWindowText(_T("Number of Posts:"));
    m_checkUploadPicture.SetWindowText(_T("Upload pictures to dest blog"));

    m_buttonStart.SetWindowText(_T("Start"));

    m_link.SetWindowText(_T("Powered by Streamlet Studio (<a href=\"http://www.streamlet.org/\">http://www.streamlet.org/</a>)"));
}

LRESULT DlgMain::OnButtonStart(HWND hWnd, WORD wID, WORD wCode, HWND hControl, BOOL &bHandled)
{
    if (m_thread.Wait(0))
    {
        if (BeforeEnterThread())
        {
            m_thread.Create(xl::Thread<>::ProcType(this, &DlgMain::ThreadProc), nullptr);
        }
    }
    else
    {
        if (MessageBox(_T("Blog Transporter is working. Cancel now?"), _T("Message"), MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
        {
            return 0;
        }

        m_thread.NotifyStop();
    }

    return 0;
}

LRESULT DlgMain::OnLinkWebsite(HWND hWnd, UINT_PTR uID, UINT uCode, HWND hControl, BOOL &bHandled)
{
    ShellExecute(NULL, _T("open"), _T("http://www.streamlet.org/"), NULL, NULL, SW_SHOWNORMAL);
    return 0;
}

BOOL DlgMain::BeforeEnterThread()
{
    xl::ScopeGuard sgRestoreControls = xl::MakeGuard(xl::Bind(this, &DlgMain::BeforeExitThread));

    m_buttonStart.EnableWindow(FALSE);

    m_strSourceUrl      = m_editSourceUrl.GetWindowText();
    m_strSourceUserName = m_editSourceUserName.GetWindowText();
    m_strSourcePassword = m_editSourcePassword.GetWindowText();
    m_strDestUrl        = m_editDestUrl.GetWindowText();
    m_strDestUserName   = m_editDestUserName.GetWindowText();
    m_strDestPassword   = m_editDestPassword.GetWindowText();
    m_nPostsNumber      = m_editPostsNumber.GetValue();
    m_bUploadPicture    = (m_checkUploadPicture.GetCheck() == BST_CHECKED);

    if (m_strSourceUrl.Empty() ||
        m_strSourceUserName.Empty() ||
        m_strSourcePassword.Empty() ||
        m_strDestUrl.Empty() ||
        m_strDestUserName.Empty() ||
        m_strDestPassword.Empty())
    {
        MessageBox(_T("Please input blog information."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (m_nPostsNumber <= 0)
    {
        MessageBox(_T("Please input the number of posts you want to transport."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!m_bUploadPicture)
    {
        if (MessageBox(_T("You choose not to upload pictures to destnation blog. Are you sure?"), _T("Error"), MB_OKCANCEL | MB_ICONEXCLAMATION) != IDOK)
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

void DlgMain::BeforeExitThread()
{
    m_cs.Lock();
    m_buttonStart.EnableWindow(FALSE);
    m_cs.UnLock();

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

    m_thread.NotifyStop();
}

void DlgMain::PutMsg(LPCTSTR lpFormat, ...)
{
    TCHAR szBuffer[MAX_PATH] = {};

    va_list args;
    va_start(args, lpFormat);
    _vstprintf_s(szBuffer, lpFormat, args);
    va_end(args);

    m_editMessage.AppendText(szBuffer);
    m_editMessage.AppendText(_T("\r\n"));
}

void DlgMain::SetProgressBarMarquee()
{
    m_process.ModifyStyle(0, PBS_MARQUEE);
    m_process.SetMarquee(TRUE, 10);
}

void DlgMain::SetProgressBarNormal(int nStep, int nSteps)
{
    m_process.SetMarquee(FALSE, 0);
    m_process.ModifyStyle(PBS_MARQUEE, 0);
    m_process.SetRange(0, nStep * nSteps);
    m_process.SetStep(nStep);
    m_process.SetPos(0);
}

void DlgMain::StepProgressBar()
{
    m_process.StepIt();
}

void DlgMain::OffsetProgressBar(int nOffset)
{
    m_process.OffsetPos(nOffset);
}

DWORD DlgMain::ThreadProc(HANDLE hQuit, LPVOID lpParam)
{
    XL_ON_BLOCK_EXIT(this, &DlgMain::BeforeExitThread);

    m_cs.Lock();
    m_buttonStart.EnableWindow(FALSE);
    m_buttonStart.SetWindowText(_T("Stop"));
    m_buttonStart.EnableWindow(TRUE);
    m_cs.UnLock();

    MetaWeblog srcBlog(hQuit);

    PutMsg(_T("Checking source blog..."));
    SetProgressBarMarquee();

    if (!srcBlog.Connect(m_strSourceUrl.GetAddress(), m_strSourceUserName.GetAddress(), m_strSourcePassword.GetAddress()))
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

    MetaWeblog destBlog(hQuit);

    PutMsg(_T("Checking dest blog..."));
    SetProgressBarMarquee();

    if (!destBlog.Connect(m_strDestUrl.GetAddress(), m_strDestUserName.GetAddress(), m_strDestPassword.GetAddress()))
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

    if (WaitForSingleObject(hQuit, 0) == WAIT_OBJECT_0)
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

    if (WaitForSingleObject(hQuit, 0) == WAIT_OBJECT_0)
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

                    if (strImgUrl.IndexOf(_T("http://")) != 0 && strImgUrl.IndexOf(_T("https://")) != 0)
                    {
                        if (strImgUrl[0] == _T('/'))
                        {
                            int nPos = post.link.IndexOf(_T("://"));

                            if (nPos >= 0)
                            {
                                nPos += 3;
                            }
                            else
                            {
                                nPos = 0;
                            }

                            nPos = post.link.IndexOf(_T("/"), nPos);

                            if (nPos >= 0)
                            {
                                strImgUrl = post.link.Left(nPos) + strImgUrl;
                            }
                            else
                            {
                                strImgUrl = post.link + _T("/") + strImgUrl;
                            }
                        }
                        else
                        {
                            int nPos = post.link.LastIndexOf(_T("/"));

                            if (nPos >= 0)
                            {
                                strImgUrl = post.link.Left(nPos + 1) + strImgUrl;
                            }
                            else
                            {
                                strImgUrl = post.link + _T("/") + strImgUrl;
                            }
                        }
                    }

                    PutMsg(_T("Downloading %s ..."), strImgUrl.GetAddress());

                    HttpGet hg;

                    if (!hg.SendRequest(strImgUrl.GetAddress(), hQuit, &arrData))
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
                        
                        TCHAR szBuffer[MAX_PATH] = {};
                        _stprintf_s(szBuffer, _T("%u"), i);
                        strName += szBuffer;

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

                    if (WaitForSingleObject(hQuit, 0) == WAIT_OBJECT_0)
                    {
                        PutMsg(_T("User cancelled."));
                        return 0;
                    }

                } // for (int i = 0; i < imgs.Size(); ++i)

                post.description = strNewContent;

            } // if (imgs.Empty())

        } // if (m_bUploadPicture)

        OffsetProgressBar(nProgressUnit / 2);

        if (WaitForSingleObject(hQuit, 0) == WAIT_OBJECT_0)
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

        if (WaitForSingleObject(hQuit, 5000) == WAIT_OBJECT_0)
        {
            PutMsg(_T("User cancelled."));
            return 0;
        }
    }
        
    PutMsg(_T("Done. Please check the log for errors."));

    return 0;
}
