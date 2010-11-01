//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   IntegerBox.h
//    Author:      Streamlet
//    Create Time: 2009-12-13
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __INTEGERBOX_H_CB571A0B_4C4F_4E98_A722_63AD4E7F1741_INCLUDED__
#define __INTEGERBOX_H_CB571A0B_4C4F_4E98_A722_63AD4E7F1741_INCLUDED__


#pragma warning(disable: 4996)

#include <atlbase.h>
#include <atlstr.h>
#include "WTL/atlapp.h"
#include "WTL/atlctrls.h"

class CIntegerBox : public CWindowImpl<CIntegerBox, CEdit>
{
public:
    CIntegerBox()
    {

    }

    ~CIntegerBox()
    {

    }

public:
    int GetValue()
    {
        CAtlString str;
        GetWindowText(str);

        return _ttoi(str);
    }

    void SetValue(int value)
    {
        CAtlString str;
        str.Format(_T("%d"), value);

        SetWindowText(str);
    }

private:
    LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

    LRESULT StopMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return TRUE;
    }

private:
    BEGIN_MSG_MAP(CIntegerBox)
        MESSAGE_HANDLER(WM_CHAR, OnChar)
        MESSAGE_HANDLER(WM_CONTEXTMENU, StopMessage)
        MESSAGE_HANDLER(WM_KEYUP, StopMessage)
        MESSAGE_HANDLER(WM_SYSKEYDOWN, StopMessage)
        MESSAGE_HANDLER(WM_SYSKEYUP, StopMessage)
    END_MSG_MAP()
};

#endif // #ifndef __INTEGERBOX_H_CB571A0B_4C4F_4E98_A722_63AD4E7F1741_INCLUDED__
