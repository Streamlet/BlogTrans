//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2010-10-26
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "../MetaWeblog/MetaWeblog.h"
#include "../MetaWeblog/ImgPicker.h"
#include <Loki/ScopeGuard.h>

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>

xl::String GetInput(const xl::String &strPrompt)
{
    _tprintf(strPrompt.GetAddress());

    const int BUFFER_SIZE = 80;
    TCHAR BUFFER[BUFFER_SIZE];
    fflush(stdin);

    _tscanf(_T("%s"), BUFFER);
    return BUFFER;
}

xl::String GetPassword(const xl::String &strPrompt)
{
    _tprintf(strPrompt.GetAddress());

    const int BUFFER_SIZE = 80;
    TCHAR BUFFER[BUFFER_SIZE];
    fflush(stdin);

    int i = 0;
    wchar_t ch = _T('\0');

    while ((ch = _gettch()) != _T('\r'))
    {
        if (ch == _T('\b') && i > 0)
        {
            --i;
            _puttch(_T('\b'));
            _puttch(_T(' '));
            _puttch(_T('\b'));
        }
        else
        {
            BUFFER[i++] = ch;
            _puttch(_T('*'));
        }
    }

    BUFFER[i++] = _T('\0');

    _puttch(_T('\n'));

    return BUFFER;
}

int main()
{
    setlocale(LC_ALL, "");

    HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    LOKI_ON_BLOCK_EXIT(CloseHandle, hEvent);

    MetaWeblog metaWeblog(hEvent);

    _tprintf(_T("MetaWeblog Test\n"));
    _tprintf(_T("\n"));
    _tprintf(_T("Please input your cppblog username and password.\n"));

    xl::String strUserName = GetInput(_T("UserName: "));
    xl::String strPassword = GetPassword(_T("Password: "));

    xl::String strUrl;
    strUrl += _T("http://www.cppblog.com/");
    strUrl += strUserName;
    strUrl += _T("/services/metaweblog.aspx");

    _tprintf(_T("\n"));


    _tprintf(_T("Connecting %s ...\n"), strUrl.GetAddress());

    if (!metaWeblog.Connect(strUrl, strUserName, strPassword))
    {
        _tprintf(_T("Failed to connect server.\n"));
        _tprintf(_T("Press any key to quit...\n"));
        _getch();
       return 0;
    }

    _tprintf(_T("Connected!\n"));
    _tprintf(_T("\n"));


    _tprintf(_T("Getting blog information...\n"));

    auto blogs = metaWeblog.GetUsersBlogs();

    if (blogs.Empty())
    {
        _tprintf(_T("Failed to getting blog information...\n"));
        _tprintf(_T("Press any key to quit...\n"));
        _getch();
        return 0;
    }

    auto blog = **blogs.Begin();

    _tprintf(_T("Blog ID: %s\nBlog Name: %s\nBlog URL: %s\n"),
        blog.blogid.GetAddress(), blog.blogName.GetAddress(), blog.url.GetAddress());
    _tprintf(_T("\n"));


    _tprintf(_T("Listing categories...\n"));

    auto categories = metaWeblog.GetCategories(blog.blogid);

    for (auto it = categories.Begin(); it != categories.End(); ++it)
    {
        auto category = **it;
        _tprintf(_T("ID: %s, Title: %s\n"),
            category.categoryid.GetAddress(), category.title.GetAddress());
    }

    _tprintf(_T("\n"));


    _tprintf(_T("Top 20 posts...\n"));
    _tprintf(_T("\n"));

    auto posts = metaWeblog.GetRecentPosts(blog.blogid, 20);
        
    for (auto it = posts.Begin(); it != posts.End(); ++it)
    {
        auto post = **it;
        _tprintf(_T("ID: %s, Time: %s Title:\n%s\n"),
            post.postid.GetAddress(), post.dateCreated.GetAddress(), post.title.GetAddress());

        ImgPicker imgPicker;
        auto imgs = imgPicker.Analyze(post.description);

        if (!imgs.Empty())
        {
            _tprintf(_T("Images:\n"));
        }

        for (auto it = imgs.Begin(); it != imgs.End(); ++it)
        {
            xl::String strImgUrl(post.description.GetAddress() + it->nIndex, it->nLength);
            _tprintf(_T("%s\n"), strImgUrl.GetAddress());
        }

        _tprintf(_T("\n"));
    }

    _tprintf(_T("\n"));


    _tprintf(_T("Press any key to quit...\n"));
    _getch();

    return 0;
}

