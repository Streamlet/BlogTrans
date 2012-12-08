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

#include "resource.h"

#include <xl/Containers/xlSet.h>
#include <xl/String/xlString.h>

struct GlobalVar
{
    xl::Set<xl::String> recentApiUrl;
};

extern GlobalVar g;

#endif // #ifndef __BLOGTRANS_H_510B76C5_6B2E_42F7_BFAF_1C28169ECB02_INCLUDED__
