//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   BlogTrans.h
//    Author:      Streamlet
//    Create Time: 2010-10-29
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __BLOGTRANS_H_510B76C5_6B2E_42F7_BFAF_1C28169ECB02_INCLUDED__
#define __BLOGTRANS_H_510B76C5_6B2E_42F7_BFAF_1C28169ECB02_INCLUDED__


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
extern GlobalVar g;

#endif // #ifndef __BLOGTRANS_H_510B76C5_6B2E_42F7_BFAF_1C28169ECB02_INCLUDED__
