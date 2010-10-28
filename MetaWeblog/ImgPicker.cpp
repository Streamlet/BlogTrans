//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   ImgPicker.cpp
//    Author:      Streamlet
//    Create Time: 2010-10-29
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include "ImgPicker.h"

ImgPicker::ImgPicker()
{

}

ImgPicker::~ImgPicker()
{

}

ImgItems ImgPicker::Analyze(const xl::String &strHtml)
{
    ImgItems imgItems;

    xl::String str = strHtml;
    str.MakeLower();

    int nPos = 0;

    while (true)
    {
        int nStart = str.IndexOf(L"<img", nPos);

        if (nStart == -1)
        {
            break;
        }

        nPos = str.IndexOf(L">", nStart);

        if (nPos == -1)
        {
            break;
        }

        ImgItem imgItem = AnalyzeImgTag(xl::String(&str[nStart], nPos - nStart + 1));

        if (imgItem.nLength > 0)
        {
            imgItem.nIndex += nStart;
            imgItems.PushBack(imgItem);
        }
    }

    return imgItems;
}

ImgItem ImgPicker::AnalyzeImgTag(const xl::String &strImgTag)
{
    ImgItem imgItem = { 0, 0 };

    int nStart = strImgTag.IndexOf(L"src=");

    if (nStart == -1 || nStart + 4 >= strImgTag.Length())
    {
        return imgItem;
    }

    nStart += 4;

    int nEnd = strImgTag.IndexOf(L" ", nStart);

    if (nEnd == -1)
    {
        nEnd = strImgTag.Length() - 1;
    }

    --nEnd;

    if (strImgTag[nStart] == L'\"' || strImgTag[nStart] == L'\'')
    {
        ++nStart;
    }

    if (strImgTag[nEnd] == L'\"' || strImgTag[nEnd] == L'\'')
    {
        --nEnd;
    }

    if (nEnd <= nStart)
    {
        return imgItem;
    }

    imgItem.nIndex = nStart;
    imgItem.nLength = nEnd - nStart + 1;
    
    return imgItem;
}
