//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   ImgPicker.h
//    Author:      Streamlet
//    Create Time: 2010-10-29
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __IMGPICKER_H_952954BA_28B8_41DA_9173_4881EB074782_INCLUDED__
#define __IMGPICKER_H_952954BA_28B8_41DA_9173_4881EB074782_INCLUDED__


#include <xl/Containers/xlArray.h>
#include <xl/Objects/xlString.h>
#include "ImgPicker.h"

struct ImgItem
{
    int nIndex;
    int nLength;
};

typedef xl::Array<ImgItem> ImgItems;

class ImgPicker
{
public:
    ImgPicker();
    ~ImgPicker();

public:
    ImgItems Analyze(const xl::String &strHtml);

private:
    ImgItem AnalyzeImgTag(const xl::String &strImgTag);
};


#endif // #ifndef __IMGPICKER_H_952954BA_28B8_41DA_9173_4881EB074782_INCLUDED__
