//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   MetaWebLogDS.h
//    Author:      Streamlet
//    Create Time: 2010-10-28
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __METAWEBLOGDS_H_773930DC_B57E_435C_AD77_4E6C95E3121C_INCLUDED__
#define __METAWEBLOGDS_H_773930DC_B57E_435C_AD77_4E6C95E3121C_INCLUDED__


#include <xl/Objects/xlString.h>
#include <xl/Objects/xlQIPtr.h>


struct BlogInfo
{
    xl::String blogid;
    xl::String url;
    xl::String blogName;
};

typedef xl::QIPtr<BlogInfo> BlogInfoPtr;

struct Enclosure
{
    int length;
    xl::String type;
    xl::String url;
};

typedef xl::QIPtr<Enclosure> EnclosurePtr;

struct Source
{
    xl::String name;
    xl::String url;
};

typedef xl::QIPtr<Source> SourcePtr;

struct Post
{
    xl::String dateCreated;
    xl::String description;
    xl::String title;
    xl::Array<xl::String> categories;
    EnclosurePtr enclosure;
    xl::String link;
    xl::String permalink;
    xl::String postid;
    SourcePtr source;
    xl::String userid;

    Post()
    {
        enclosure = new Enclosure;
        source = new Source;
    }
};

typedef xl::QIPtr<Post> PostPtr;

struct CategoryInfo
{
    xl::String description;
    xl::String htmlUrl;
    xl::String rssUrl;
    xl::String title;
    xl::String categoryid;
};

typedef xl::QIPtr<CategoryInfo> CategoryInfoPtr;

struct MediaObject
{
    xl::String name;
    xl::String type;
    xl::Array<unsigned char> bits;
};

typedef xl::QIPtr<MediaObject> MediaObjectPtr;

struct MediaObjectUrl
{
    xl::String url;
};

typedef xl::QIPtr<MediaObjectUrl> MediaObjectUrlPtr;


#endif // #ifndef __METAWEBLOGDS_H_773930DC_B57E_435C_AD77_4E6C95E3121C_INCLUDED__
