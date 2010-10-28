//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   MetaWeblog.cpp
//    Author:      Streamlet
//    Create Time: 2010-10-28
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "MetaWeblog.h"
#include <tchar.h>

MetaWeblog::MetaWeblog(HANDLE hEventCancel, const xl::String &strUserAgent /*= L"MetaWeblogClient"*/)
    : m_hEventCancel(hEventCancel), m_xmlrpc(strUserAgent)
{

}

MetaWeblog::~MetaWeblog()
{
    Disconnect();
}

bool MetaWeblog::Connect(const xl::String &strUrl, const xl::String &strUserName, const xl::String &strPassword)
{
    m_strUserName = strUserName;
    m_strPassword = strPassword;

    m_xmlrpc.SetApiUrl(strUrl);

    return m_xmlrpc.Connect();
}

void MetaWeblog::Disconnect()
{
    m_xmlrpc.Disconnect();
}

// method blogger.deletePost
//     Deletes a post.
// 
//     Parameters
//     string appKey 
//     string postid 
//     string username 
//     string password 
//     boolean publish - Where applicable, this specifies whether the blog should be republished after the post has been deleted. 
// 
//     Return Value
//     boolean Always returns true. 

bool MetaWeblog::DeletePost(const xl::String &postid, bool publish)
{
    xl::String strMethodName = _T("blogger.deletePost");

    xl::Array<XmlRpcValue> arrParameters;
    arrParameters.PushBack(StringToXmlRpcValue(_T("")));
    arrParameters.PushBack(StringToXmlRpcValue(postid));
    arrParameters.PushBack(StringToXmlRpcValue(m_strUserName));
    arrParameters.PushBack(StringToXmlRpcValue(m_strPassword));
    arrParameters.PushBack(BoolToXmlRpcValue(publish));

    XmlRpcValue vReturnValue;

    m_xmlrpc.ExecuteMethod(strMethodName, arrParameters, &vReturnValue, m_hEventCancel);

    return BoolFromXmlRpcValue(vReturnValue);
}

// method blogger.getUsersBlogs
//     Returns information on all the blogs a given user is a member.
// 
//     Parameters
//     string appKey 
//     string username 
//     string password 
// 
//     Return Value
//     array of struct BlogInfo 

xl::Array<BlogInfoPtr> MetaWeblog::GetUsersBlogs()
{
    xl::String strMethodName = _T("blogger.getUsersBlogs");

    xl::Array<XmlRpcValue> arrParameters;
    arrParameters.PushBack(StringToXmlRpcValue(_T("")));
    arrParameters.PushBack(StringToXmlRpcValue(m_strUserName));
    arrParameters.PushBack(StringToXmlRpcValue(m_strPassword));

    XmlRpcValue vReturnValue;

    m_xmlrpc.ExecuteMethod(strMethodName, arrParameters, &vReturnValue, m_hEventCancel);

    return BlogInfoArrayFromXmlRpcValue(vReturnValue);
}

// method metaWeblog.editPost
//     Updates and existing post to a designated blog using the metaWeblog API. Returns true if completed.
// 
//     Parameters
//     string postid 
//     string username 
//     string password 
//     struct Post post 
//     boolean publish 
// 
//     Return Value
//     boolean 

bool MetaWeblog::EditPost(const xl::String &postid, const Post &post, bool publish)
{
    xl::String strMethodName = _T("metaWeblog.editPost");

    xl::Array<XmlRpcValue> arrParameters;
    arrParameters.PushBack(StringToXmlRpcValue(postid));
    arrParameters.PushBack(StringToXmlRpcValue(m_strUserName));
    arrParameters.PushBack(StringToXmlRpcValue(m_strPassword));
    arrParameters.PushBack(PostToXmlRpcValue(post));
    arrParameters.PushBack(BoolToXmlRpcValue(publish));

    XmlRpcValue vReturnValue;

    m_xmlrpc.ExecuteMethod(strMethodName, arrParameters, &vReturnValue, m_hEventCancel);

    return BoolFromXmlRpcValue(vReturnValue);
}

// method metaWeblog.getCategories
//     Retrieves a list of valid categories for a post using the metaWeblog API. Returns the metaWeblog categories struct collection.
// 
//     Parameters
//     string blogid 
//     string username 
//     string password 
// 
//     Return Value
//     array of struct CategoryInfo 

xl::Array<CategoryInfoPtr> MetaWeblog::GetCategories(const xl::String &blogid)
{
    xl::String strMethodName = _T("metaWeblog.getCategories");

    xl::Array<XmlRpcValue> arrParameters;
    arrParameters.PushBack(StringToXmlRpcValue(blogid));
    arrParameters.PushBack(StringToXmlRpcValue(m_strUserName));
    arrParameters.PushBack(StringToXmlRpcValue(m_strPassword));

    XmlRpcValue vReturnValue;

    m_xmlrpc.ExecuteMethod(strMethodName, arrParameters, &vReturnValue, m_hEventCancel);

    return CategoryInfoArrayFromXmlRpcValue(vReturnValue);
}

// method metaWeblog.getPost
//     Retrieves an existing post using the metaWeblog API. Returns the metaWeblog struct.
// 
//     Parameters
//     string postid 
//     string username 
//     string password 
// 
//     Return Value
// struct Post 

PostPtr MetaWeblog::GetPost(const xl::String &postid)
{
    xl::String strMethodName = _T("metaWeblog.getPost");

    xl::Array<XmlRpcValue> arrParameters;
    arrParameters.PushBack(StringToXmlRpcValue(postid));
    arrParameters.PushBack(StringToXmlRpcValue(m_strUserName));
    arrParameters.PushBack(StringToXmlRpcValue(m_strPassword));

    XmlRpcValue vReturnValue;

    m_xmlrpc.ExecuteMethod(strMethodName, arrParameters, &vReturnValue, m_hEventCancel);

    return PostFromXmlRpcValue(vReturnValue);
}

// method metaWeblog.getRecentPosts
//     Retrieves a list of the most recent existing post using the metaWeblog API. Returns the metaWeblog struct collection.
// 
//     Parameters
//     string blogid 
//     string username 
//     string password 
//     integer numberOfPosts 
// 
//     Return Value
//     array of struct Post 

xl::Array<PostPtr> MetaWeblog::GetRecentPosts(const xl::String &blogid, int numberOfPosts)
{
    xl::String strMethodName = _T("metaWeblog.getRecentPosts");

    xl::Array<XmlRpcValue> arrParameters;
    arrParameters.PushBack(StringToXmlRpcValue(blogid));
    arrParameters.PushBack(StringToXmlRpcValue(m_strUserName));
    arrParameters.PushBack(StringToXmlRpcValue(m_strPassword));
    arrParameters.PushBack(IntToXmlRpcValue(numberOfPosts));

    XmlRpcValue vReturnValue;

    m_xmlrpc.ExecuteMethod(strMethodName, arrParameters, &vReturnValue, m_hEventCancel);

    return PostArrayFromXmlRpcValue(vReturnValue);
}

// method metaWeblog.newMediaObject
//     Add a media object to a post using the metaWeblog API. Returns media url as a string.
// 
//     Parameters
//     string blogid 
//     string username 
//     string password 
// struct MediaObject mediaObject 
// 
//     Return Value
// struct MediaObjectUrl 

MediaObjectUrlPtr MetaWeblog::NewMediaObject(const xl::String &blogid, const MediaObject &mediaObject)
{
    xl::String strMethodName = _T("metaWeblog.newMediaObject");

    xl::Array<XmlRpcValue> arrParameters;
    arrParameters.PushBack(StringToXmlRpcValue(blogid));
    arrParameters.PushBack(StringToXmlRpcValue(m_strUserName));
    arrParameters.PushBack(StringToXmlRpcValue(m_strPassword));
    arrParameters.PushBack(MediaObjectToXmlRpcValue(mediaObject));

    XmlRpcValue vReturnValue;

    m_xmlrpc.ExecuteMethod(strMethodName, arrParameters, &vReturnValue, m_hEventCancel);

    return MediaObjectUrlFromXmlRpcValue(vReturnValue);
}

// method metaWeblog.newPost
//     Makes a new post to a designated blog using the metaWeblog API. Returns postid as a string.
// 
//     Parameters
//     string blogid 
//     string username 
//     string password 
// struct Post post 
//     boolean publish 
// 
//     Return Value
//     string 

xl::String MetaWeblog::NewPost(const xl::String &blogid, const Post &post, bool publish)
{
    xl::String strMethodName = _T("metaWeblog.newPost");

    xl::Array<XmlRpcValue> arrParameters;
    arrParameters.PushBack(StringToXmlRpcValue(blogid));
    arrParameters.PushBack(StringToXmlRpcValue(m_strUserName));
    arrParameters.PushBack(StringToXmlRpcValue(m_strPassword));
    arrParameters.PushBack(PostToXmlRpcValue(post));
    arrParameters.PushBack(BoolToXmlRpcValue(publish));

    XmlRpcValue vReturnValue;

    m_xmlrpc.ExecuteMethod(strMethodName, arrParameters, &vReturnValue, m_hEventCancel);

    return StringFromXmlRpcValue(vReturnValue);
}

XmlRpcValue MetaWeblog::BoolToXmlRpcValue(bool b)
{
    XmlRpcValue vXmlRpc;
    vXmlRpc.SetBoolValue(b);
    return vXmlRpc;
}

XmlRpcValue MetaWeblog::IntToXmlRpcValue(int i)
{
    XmlRpcValue vXmlRpc;
    vXmlRpc.SetIntValue(i);
    return vXmlRpc;
}

XmlRpcValue MetaWeblog::StringToXmlRpcValue(const xl::String &str)
{
    XmlRpcValue vXmlRpc;
    vXmlRpc.SetStringValue(str);
    return vXmlRpc;
}

// struct Post
//     Members
//     dateTime dateCreated - Required when posting. 
//     string description - Required when posting. 
//     string title - Required when posting. 
//     array of string categories (optional)  
//     struct Enclosure enclosure (optional)  
//     string link (optional)  
//     string permalink (optional)  
//     any postid (optional)  
//     struct Source source (optional)  
//     string userid (optional)  

XmlRpcValue MetaWeblog::PostToXmlRpcValue(const Post &post)
{
    XmlRpcValue vXmlRpc;;

    XmlRpcValue dateCreated;
    dateCreated.SetDateTimeValue(post.dateCreated);

    XmlRpcValue description;
    description.SetStringValue(post.description);

    XmlRpcValue title;
    description.SetStringValue(post.title);

    XmlRpcValue categories;
    XmlRpcArray arrCategories;

    for (xl::Array<xl::String>::Iterator it = post.categories.Begin(); it != post.categories.End(); ++it)
    {
        XmlRpcValue category;
        category.SetStringValue(*it);
        arrCategories.PushBack(category);
    }

    categories.SetArrayValue(arrCategories);

    XmlRpcValue enclosure;
    enclosure.SetStructValue(EnclosureToXmlRpcValue(*post.enclosure).GetStructValue());

    XmlRpcValue link;
    link.SetStringValue(post.link);

    XmlRpcValue permalink;
    permalink.SetStringValue(post.permalink);

    XmlRpcValue postid;
    postid.SetStringValue(post.postid);

    XmlRpcValue source;
    source.SetStructValue(SourceToXmlRpcValue(*post.source).GetStructValue());

    XmlRpcValue userid;
    userid.SetStringValue(post.userid);
    
    XmlRpcStruct xrStruct;
    xrStruct.Insert(L"dateCreated", dateCreated);
    xrStruct.Insert(L"description", description);
    xrStruct.Insert(L"title", title);
    xrStruct.Insert(L"categories", categories);
    xrStruct.Insert(L"enclosure", enclosure);
    xrStruct.Insert(L"link", link);
    xrStruct.Insert(L"permalink", permalink);
    xrStruct.Insert(L"postid", postid);
    xrStruct.Insert(L"source", source);
    xrStruct.Insert(L"userid", userid);

    vXmlRpc.SetStructValue(xrStruct);
    return vXmlRpc;
}

// struct Enclosure
//     Members
//     integer length (optional)  
//     string type (optional)  
//     string url (optional)  

XmlRpcValue MetaWeblog::EnclosureToXmlRpcValue(const Enclosure &enclosure)
{
    XmlRpcValue vXmlRpc;

    XmlRpcValue length;
    length.SetIntValue(enclosure.length);
    
    XmlRpcValue type;
    type.SetStringValue(enclosure.type);

    XmlRpcValue url;
    url.SetStringValue(enclosure.url);

    XmlRpcStruct xrStruct;
    xrStruct.Insert(L"length", length);
    xrStruct.Insert(L"type", type);
    xrStruct.Insert(L"url", url);

    vXmlRpc.SetStructValue(xrStruct);
    return vXmlRpc;
}

// struct Source
//     Members
//     string name (optional)  
//     string url (optional)  

XmlRpcValue MetaWeblog::SourceToXmlRpcValue(const Source &source)
{
    XmlRpcValue vXmlRpc;

    XmlRpcValue name;
    name.SetStringValue(source.name);

    XmlRpcValue url;
    url.SetStringValue(source.url);

    XmlRpcStruct xrStruct;
    xrStruct.Insert(L"name", name);
    xrStruct.Insert(L"url", url);

    vXmlRpc.SetStructValue(xrStruct);
    return vXmlRpc;
}

// struct MediaObject
//     Members
//     string name  
//     string type  
//     base64 bits  

XmlRpcValue MetaWeblog::MediaObjectToXmlRpcValue(const MediaObject &mediaObject)
{
    XmlRpcValue vXmlRpc;

    XmlRpcValue name;
    name.SetStringValue(mediaObject.name);

    XmlRpcValue type;
    type.SetStringValue(mediaObject.type);

    XmlRpcValue bits;
    bits.SetBase64Value(mediaObject.bits);

    XmlRpcStruct xrStruct;
    xrStruct.Insert(L"name", name);
    xrStruct.Insert(L"type", type);
    xrStruct.Insert(L"bits", bits);

    vXmlRpc.SetStructValue(xrStruct);
    return vXmlRpc;
}

bool MetaWeblog::BoolFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    if (vXmlRpc.GetType() != XRDT_BOOL)
    {
        return false;
    }
    else
    {
        return vXmlRpc.GetBoolValue();
    }
}

xl::String MetaWeblog::StringFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    if (vXmlRpc.GetType() != XRDT_STRING)
    {
        return L"";
    }
    else
    {
        return vXmlRpc.GetStringValue();
    }
}

// struct MediaObjectUrl
//     Members
//     string url  

MediaObjectUrlPtr MetaWeblog::MediaObjectUrlFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    MediaObjectUrlPtr pMediaObjectUrl = new MediaObjectUrl;

    if (vXmlRpc.GetType() != XRDT_STRUCT)
    {
        return pMediaObjectUrl;
    }

    XmlRpcStruct xrStruct = vXmlRpc.GetStructValue();
    XmlRpcValue url = xrStruct[L"url"];

    if (url.GetType() != XRDT_STRING)
    {
        return pMediaObjectUrl;
    }

    pMediaObjectUrl->url = url.GetStringValue();

    return pMediaObjectUrl;
}

// struct BlogInfo
//     Members
//     string blogid  
//     string url  
//     string blogName  

BlogInfoPtr MetaWeblog::BlogInfoFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    BlogInfoPtr pBlogInfo = new BlogInfo;

    if (vXmlRpc.GetType() != XRDT_STRUCT)
    {
        return pBlogInfo;
    }

    XmlRpcStruct xrStruct   = vXmlRpc.GetStructValue();
    XmlRpcValue blogid      = xrStruct[L"blogid"];
    XmlRpcValue url         = xrStruct[L"url"];
    XmlRpcValue blogName    = xrStruct[L"blogName"];

    if (blogid.GetType() != XRDT_STRING)
    {
        return pBlogInfo;
    }

    pBlogInfo->blogid = blogid.GetStringValue();

    if (url.GetType() != XRDT_STRING)
    {
        return pBlogInfo;
    }

    pBlogInfo->url = url.GetStringValue();

    if (blogName.GetType() != XRDT_STRING)
    {
        return pBlogInfo;
    }

    pBlogInfo->blogName = blogName.GetStringValue();

    return pBlogInfo;
}

// struct CategoryInfo
//     Members
//     string description  
//     string htmlUrl  
//     string rssUrl  
//     string title  
//     string categoryid  

CategoryInfoPtr MetaWeblog::CategoryInfoFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    CategoryInfoPtr pCategoryInfo = new CategoryInfo;

    if (vXmlRpc.GetType() != XRDT_STRUCT)
    {
        return pCategoryInfo;
    }

    XmlRpcStruct xrStruct   = vXmlRpc.GetStructValue();
    XmlRpcValue description = xrStruct[L"description"];
    XmlRpcValue htmlUrl     = xrStruct[L"htmlUrl"];
    XmlRpcValue rssUrl      = xrStruct[L"rssUrl"];
    XmlRpcValue title       = xrStruct[L"title"];
    XmlRpcValue categoryid  = xrStruct[L"categoryid"];

    if (description.GetType() != XRDT_STRING)
    {
        return pCategoryInfo;
    }

    pCategoryInfo->description = description.GetStringValue();

    if (htmlUrl.GetType() != XRDT_STRING)
    {
        return pCategoryInfo;
    }

    pCategoryInfo->htmlUrl = htmlUrl.GetStringValue();

    if (rssUrl.GetType() != XRDT_STRING)
    {
        return pCategoryInfo;
    }

    pCategoryInfo->rssUrl = rssUrl.GetStringValue();

    if (title.GetType() != XRDT_STRING)
    {
        return pCategoryInfo;
    }

    pCategoryInfo->title = title.GetStringValue();

    if (categoryid.GetType() != XRDT_STRING)
    {
        return pCategoryInfo;
    }

    pCategoryInfo->categoryid = categoryid.GetStringValue();

    return pCategoryInfo;
}

// struct Post
//     Members
//     dateTime dateCreated - Required when posting. 
//     string description - Required when posting. 
//     string title - Required when posting. 
//     array of string categories (optional)  
//     struct Enclosure enclosure (optional)  
//     string link (optional)  
//     string permalink (optional)  
//     any postid (optional)  
//     struct Source source (optional)  
//     string userid (optional)  

PostPtr MetaWeblog::PostFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    PostPtr pPost = new Post;

    if (vXmlRpc.GetType() != XRDT_STRUCT)
    {
        return pPost;
    }

    XmlRpcStruct xrStruct   = vXmlRpc.GetStructValue();
    XmlRpcValue dateCreated = xrStruct[L"dateCreated"];
    XmlRpcValue description = xrStruct[L"description"];
    XmlRpcValue title       = xrStruct[L"title"];
    XmlRpcValue categories  = xrStruct[L"categories"];
    XmlRpcValue enclosure   = xrStruct[L"enclosure"];
    XmlRpcValue link        = xrStruct[L"link"];
    XmlRpcValue permalink   = xrStruct[L"permalink"];
    XmlRpcValue postid      = xrStruct[L"postid"];
    XmlRpcValue source      = xrStruct[L"source"];
    XmlRpcValue userid      = xrStruct[L"userid"];

    if (dateCreated.GetType() != XRDT_DATETIME)
    {
        return pPost;
    }

    pPost->dateCreated = dateCreated.GetDateTimeValue();

    if (description.GetType() != XRDT_STRING)
    {
        return pPost;
    }

    pPost->description = description.GetStringValue();

    if (title.GetType() != XRDT_STRING)
    {
        return pPost;
    }

    pPost->title = title.GetStringValue();

    if (categories.GetType() != XRDT_ARRAY)
    {
        return pPost;
    }
        
    XmlRpcArray xrArray = categories.GetArrayValue();

    for (XmlRpcArray::Iterator it = xrArray.Begin(); it != xrArray.End(); ++it)
    {
        if (it->GetType() != XRDT_STRING)
        {
            return pPost;
        }

        pPost->categories.PushBack(it->GetStringValue());
    }

    if (enclosure.GetType() != XRDT_STRUCT)
    {
        return pPost;
    }

    pPost->enclosure = EnclosureFromXmlRpcValue(enclosure);

    if (link.GetType() != XRDT_STRING)
    {
        return pPost;
    }

    pPost->link = link.GetStringValue();

    if (permalink.GetType() != XRDT_STRING)
    {
        return pPost;
    }

    pPost->permalink = permalink.GetStringValue();

    if (postid.GetType() == XRDT_STRING)
    {
        pPost->postid = postid.GetStringValue();
    }
    else if (postid.GetType() == XRDT_INT)
    {
        int nPostid = postid.GetIntValue();

        const DWORD BUFFER_SIZE = 100;
        TCHAR BUFFER[100];
        _stprintf(BUFFER, _T("%d"), nPostid);

        pPost->postid = BUFFER;
    }
    else
    {
        return pPost;
    }

    if (source.GetType() != XRDT_STRUCT)
    {
        return pPost;
    }

    pPost->source = SourceFromXmlRpcValue(source);

    if (userid.GetType() != XRDT_STRING)
    {
        return pPost;
    }

    pPost->userid = userid.GetStringValue();

    return pPost;
}

// struct Source
//     Members
//     string name (optional)  
//     string url (optional)  

SourcePtr MetaWeblog::SourceFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    SourcePtr pSource = new Source;

    if (vXmlRpc.GetType() != XRDT_STRUCT)
    {
        return pSource;
    }

    XmlRpcStruct xrStruct = vXmlRpc.GetStructValue();
    XmlRpcValue name = xrStruct[L"name"];
    XmlRpcValue url = xrStruct[L"url"];

    if (name.GetType() != XRDT_STRING)
    {
        return pSource;
    }

    pSource->name = name.GetStringValue();

    if (url.GetType() != XRDT_STRING)
    {
        return pSource;
    }

    pSource->url = url.GetStringValue();

    return pSource;
}

// struct Enclosure
//     Members
//     integer length (optional)  
//     string type (optional)  
//     string url (optional)  

EnclosurePtr MetaWeblog::EnclosureFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    EnclosurePtr pEnclosure = new Enclosure;

    if (vXmlRpc.GetType() != XRDT_STRUCT)
    {
        return pEnclosure;
    }

    XmlRpcStruct xrStruct = vXmlRpc.GetStructValue();
    XmlRpcValue length = xrStruct[L"length"];
    XmlRpcValue type = xrStruct[L"type"];
    XmlRpcValue url = xrStruct[L"url"];

    if (length.GetType() != XRDT_INT)
    {
        return pEnclosure;
    }

    pEnclosure->length = length.GetIntValue();

    if (type.GetType() != XRDT_STRING)
    {
        return pEnclosure;
    }

    pEnclosure->type = type.GetStringValue();

    if (url.GetType() != XRDT_STRING)
    {
        return pEnclosure;
    }

    pEnclosure->url = url.GetStringValue();

    return pEnclosure;
}

xl::Array<PostPtr> MetaWeblog::PostArrayFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    xl::Array<PostPtr> arrPost;

    if (vXmlRpc.GetType() != XRDT_ARRAY)
    {
        return arrPost;
    }

    XmlRpcArray xrArray = vXmlRpc.GetArrayValue();

    for (XmlRpcArray::Iterator it = xrArray.Begin(); it != xrArray.End(); ++it)
    {
        arrPost.PushBack(PostFromXmlRpcValue(*it));
    }
 
    return arrPost;
}

xl::Array<BlogInfoPtr> MetaWeblog::BlogInfoArrayFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    xl::Array<BlogInfoPtr> arrBlogInfo;

    if (vXmlRpc.GetType() != XRDT_ARRAY)
    {
        return arrBlogInfo;
    }

    XmlRpcArray xrArray = vXmlRpc.GetArrayValue();

    for (XmlRpcArray::Iterator it = xrArray.Begin(); it != xrArray.End(); ++it)
    {
        arrBlogInfo.PushBack(BlogInfoFromXmlRpcValue(*it));
    }

    return arrBlogInfo;
}

xl::Array<CategoryInfoPtr> MetaWeblog::CategoryInfoArrayFromXmlRpcValue(const XmlRpcValue &vXmlRpc)
{
    xl::Array<CategoryInfoPtr> arrCategoryInfo;

    if (vXmlRpc.GetType() != XRDT_ARRAY)
    {
        return arrCategoryInfo;
    }

    XmlRpcArray xrArray = vXmlRpc.GetArrayValue();

    for (XmlRpcArray::Iterator it = xrArray.Begin(); it != xrArray.End(); ++it)
    {
        arrCategoryInfo.PushBack(CategoryInfoFromXmlRpcValue(*it));
    }

    return arrCategoryInfo;
}
