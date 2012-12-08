//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   IntegerBox.h
//    Author:      Streamlet
//    Create Time: 2011-12-18
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __INTEGERBOX_H_1909CEF5_194D_4AF0_B0CB_486D6E725632_INCLUDED__
#define __INTEGERBOX_H_1909CEF5_194D_4AF0_B0CB_486D6E725632_INCLUDED__


#include <xl/Win32/GUI/xlStdEdit.h>

class IntegerBox : public xl::StdEdit
{
public:
    IntegerBox();
    ~IntegerBox();

public:
    int GetValue();
    void SetValue(int nValue);

private:
    // Message Map Handlers
    // LRESULT OnMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT OnChar(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
    LRESULT Skip  (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
};


#endif // #ifndef __INTEGERBOX_H_1909CEF5_194D_4AF0_B0CB_486D6E725632_INCLUDED__
