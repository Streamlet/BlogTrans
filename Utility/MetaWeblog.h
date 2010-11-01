//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   MetaWeblog.h
//    Author:      Streamlet
//    Create Time: 2010-10-28
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __METAWEBLOG_H_CA10F5BA_2CBD_4E61_B2A8_488CCA14EA2C_INCLUDED__
#define __METAWEBLOG_H_CA10F5BA_2CBD_4E61_B2A8_488CCA14EA2C_INCLUDED__


#include <Windows.h>
#include "MetaWebLogTypes.h"
#include "XmlRpc.h"
#include <xl/Containers/xlArray.h>

class MetaWeblog
{
public:
    MetaWeblog(HANDLE hEventCancel, const xl::String &strUserAgent = L"MetaWeblogClient");
    ~MetaWeblog();

public:
    bool Connect(const xl::String &strUrl, const xl::String &strUserName, const xl::String &strPassword);
    void Disconnect();

public:
    bool                        DeletePost(const xl::String &postid, bool publish);
    xl::Array<BlogInfoPtr>      GetUsersBlogs();
    bool                        EditPost(const xl::String &postid, const Post &post, bool publish);
    xl::Array<CategoryInfoPtr>  GetCategories(const xl::String &blogid);
    PostPtr                     GetPost(const xl::String &postid);
    xl::Array<PostPtr>          GetRecentPosts(const xl::String &blogid, int numberOfPosts);
    MediaObjectUrlPtr           NewMediaObject(const xl::String &blogid, const MediaObject &mediaObject);
    xl::String                  NewPost(const xl::String &blogid, const Post &post, bool publish);

private:
    XmlRpcValue                 BoolToXmlRpcValue(bool b);
    XmlRpcValue                 IntToXmlRpcValue(int i);
    XmlRpcValue                 StringToXmlRpcValue(const xl::String &str);
    XmlRpcValue                 PostToXmlRpcValue(const Post &post);
    XmlRpcValue                 EnclosureToXmlRpcValue(const Enclosure &enclosure);
    XmlRpcValue                 SourceToXmlRpcValue(const Source &source);
    XmlRpcValue                 MediaObjectToXmlRpcValue(const MediaObject &mediaObject);
    bool                        BoolFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    xl::String                  StringFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    MediaObjectUrlPtr           MediaObjectUrlFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    BlogInfoPtr                 BlogInfoFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    CategoryInfoPtr             CategoryInfoFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    SourcePtr                   SourceFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    EnclosurePtr                EnclosureFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    PostPtr                     PostFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    xl::Array<PostPtr>          PostArrayFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    xl::Array<BlogInfoPtr>      BlogInfoArrayFromXmlRpcValue(const XmlRpcValue &vXmlRpc);
    xl::Array<CategoryInfoPtr>  CategoryInfoArrayFromXmlRpcValue(const XmlRpcValue &vXmlRpc);

private:
    XmlRpc m_xmlrpc;
    HANDLE m_hEventCancel;
    xl::String m_strUserName;
    xl::String m_strPassword;
};

#endif // #ifndef __METAWEBLOG_H_CA10F5BA_2CBD_4E61_B2A8_488CCA14EA2C_INCLUDED__
