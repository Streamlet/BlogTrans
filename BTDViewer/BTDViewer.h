//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   BTDViewer.h
//    Author:      Streamlet
//    Create Time: 2010-11-02
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __BTDVIEWER_H_76B8FCD1_857A_47C2_B35D_B1DF264F6476_INCLUDED__
#define __BTDVIEWER_H_76B8FCD1_857A_47C2_B35D_B1DF264F6476_INCLUDED__


#pragma warning(disable: 4996)

#include <atlwin.h>

#include "WTL/atlapp.h"
#include "WTL/atlframe.h"
#include "WTL/atlctrls.h"
#include "WTL/atldlgs.h"
#include "WTL/atlddx.h"
#include "WTL/atlcrack.h"

#include "resource.h"

#include <xl/Containers/xlSet.h>
#include <xl/Objects/xlString.h>

struct GlobalVar
{
    xl::Set<xl::String> recentApiUrl;
};

extern CAppModule _Module;

#endif // #ifndef __BTDVIEWER_H_76B8FCD1_857A_47C2_B35D_B1DF264F6476_INCLUDED__
