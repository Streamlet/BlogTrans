//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   CommonControlImpl.h
//    Author:      Streamlet
//    Create Time: 2010-05-27
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __COMMONCONTROLIMPL_H_3D1BAA1A_7BCB_451B_ABA9_A5A598DD7305_INCLUDED__
#define __COMMONCONTROLIMPL_H_3D1BAA1A_7BCB_451B_ABA9_A5A598DD7305_INCLUDED__


#include <atlbase.h>
#include <atlstr.h>
#include "WTL/atlapp.h"
#include "WTL/atlctrls.h"

class CComboBoxImpl : public CWindowImpl<CComboBoxImpl, CComboBox>
{
    BEGIN_MSG_MAP(CComboBoxImpl)
    END_MSG_MAP()
};

class CListViewCtrlImpl : public CWindowImpl<CListViewCtrlImpl, CListViewCtrl>
{
    BEGIN_MSG_MAP(CListViewCtrlImpl)
    END_MSG_MAP()
};

class CListBoxImpl : public CWindowImpl<CListBoxImpl, CListBox>
{
    BEGIN_MSG_MAP(CListBoxImpl)
    END_MSG_MAP()
};

class CButtonImpl : public CWindowImpl<CButtonImpl, CButton>
{
    BEGIN_MSG_MAP(CButtonImpl)
    END_MSG_MAP()
};

class CLinkCtrlImpl : public CWindowImpl<CLinkCtrlImpl, CLinkCtrl>
{
    BEGIN_MSG_MAP(CLinkCtrlImpl)
    END_MSG_MAP()
};

class CStaticImpl : public CWindowImpl<CStaticImpl, CStatic>
{
    BEGIN_MSG_MAP(CStaticImpl)
    END_MSG_MAP()
};

class CEditImpl : public CWindowImpl<CEditImpl, CEdit>
{
    BEGIN_MSG_MAP(CEditImpl)
    END_MSG_MAP()
};

class CProgressBarCtrlImpl : public CWindowImpl<CProgressBarCtrlImpl, CProgressBarCtrl>
{
    BEGIN_MSG_MAP(CProgressBarCtrlImpl)
    END_MSG_MAP()
};

#endif // #ifndef __COMMONCONTROLIMPL_H_3D1BAA1A_7BCB_451B_ABA9_A5A598DD7305_INCLUDED__
