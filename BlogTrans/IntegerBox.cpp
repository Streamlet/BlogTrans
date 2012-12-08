//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   IntegerBox.cpp
//    Author:      Streamlet
//    Create Time: 2011-12-18
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/Memory/xlMemory.h>
#include <xl/Win32/Memory/xlSafeSmartPtr.h>
#include "IntegerBox.h"


IntegerBox::IntegerBox()
{
    AppendMsgHandler(WM_CHAR,        MsgHandler(this, &IntegerBox::OnChar));
    AppendMsgHandler(WM_KEYUP,       MsgHandler(this, &IntegerBox::Skip));
    AppendMsgHandler(WM_SYSKEYUP,    MsgHandler(this, &IntegerBox::Skip));
    AppendMsgHandler(WM_SYSKEYDOWN,  MsgHandler(this, &IntegerBox::Skip));
    AppendMsgHandler(WM_CONTEXTMENU, MsgHandler(this, &IntegerBox::Skip));
    AppendMsgHandler(WM_RBUTTONDOWN, MsgHandler(this, &IntegerBox::Skip));
    AppendMsgHandler(WM_RBUTTONUP,   MsgHandler(this, &IntegerBox::Skip));
}

IntegerBox::~IntegerBox()
{

}

int IntegerBox::GetValue()
{
    int nLength = GetWindowTextLength() + 1;

    if (nLength <= 0)
    {
        return 0;
    }

    xl::SafeSharedArray<TCHAR> spText = new TCHAR[nLength];
    GetWindowText(spText.RawPointer(), nLength);

    return _ttoi(spText.RawPointer());
}

void IntegerBox::SetValue(int nValue)
{
    TCHAR szText[MAX_PATH] = {};
    _stprintf_s(szText, _T("%d"), nValue);

    SetWindowText(szText);
}

LRESULT IntegerBox::OnChar(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    BYTE vkCode = (BYTE)wParam;

    if (((vkCode >= '0' && vkCode <= '9')
        && !(GetKeyState(VK_SHIFT) & 0x8000))
        || vkCode == VK_BACK
        || vkCode == VK_DELETE
        || vkCode == VK_LEFT
        || vkCode == VK_RIGHT
        || vkCode == VK_HOME
        || vkCode == VK_END)
    {
        bHandled = FALSE;
    }

    return TRUE;
}

LRESULT IntegerBox::Skip(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled)
{
    return FALSE;
}
