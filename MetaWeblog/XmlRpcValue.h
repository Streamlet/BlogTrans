//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   XmlRpcValue.h
//    Author:      Streamlet
//    Create Time: 2010-10-28
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XMLRPCVALUE_H_5EF83F6C_F2D4_465E_B965_CC8FBB4987DF_INCLUDED__
#define __XMLRPCVALUE_H_5EF83F6C_F2D4_465E_B965_CC8FBB4987DF_INCLUDED__


#include <xl/Containers/xlArray.h>
#include <xl/Containers/xlMap.h>
#include <xl/Objects/xlString.h>
#include <time.h>
#include "XmlParser.h"

enum XmlRpcDataTypes
{
    XRDT_NIL = 0,
    XRDT_BOOL,
    XRDT_INT,
    XRDT_DOUBLE,
    XRDT_STRING,
    XRDT_DATETIME,
    XRDT_BASE64,
    XRDT_ARRAY,
    XRDT_STRUCT
};

class XmlRpcValue;
typedef bool                                XmlRpcBool;
typedef int                                 XmlRpcInt;
typedef double                              XmlRpcDouble;
typedef xl::String                          XmlRpcString;
typedef xl::String                          XmlRpcDateTime;
typedef xl::Array<unsigned char>            XmlRpcBase64;
typedef xl::Array<XmlRpcValue>              XmlRpcArray;
typedef xl::Map<xl::String, XmlRpcValue>    XmlRpcStruct;

class XmlRpcValue
{
public:
    XmlRpcValue();
    XmlRpcValue(const XmlRpcValue &that);
    XmlRpcValue &operator = (const XmlRpcValue &that);
    ~XmlRpcValue();

private:
    XmlRpcDataTypes m_type;
    XmlRpcBool      m_bool;
    XmlRpcInt       m_int;
    XmlRpcDouble    m_double;
    XmlRpcString   *m_string;
    XmlRpcDateTime *m_datetime;
    XmlRpcBase64   *m_base64;
    XmlRpcArray    *m_array;
    XmlRpcStruct   *m_struct;

public:
    XmlRpcDataTypes GetType() const;

    XmlRpcBool      GetBoolValue() const;
    XmlRpcInt       GetIntValue() const;
    XmlRpcDouble    GetDoubleValue() const;
    XmlRpcString    GetStringValue() const;
    XmlRpcDateTime  GetDateTimeValue() const;
    XmlRpcBase64    GetBase64Value() const;
    XmlRpcArray     GetArrayValue() const;
    XmlRpcStruct    GetStructValue() const;

    void ClearValue();
    void SetNilValue();
    void SetBoolValue(const XmlRpcBool &value);
    void SetIntValue(const XmlRpcInt &value);
    void SetDoubleValue(const XmlRpcDouble &value);
    void SetStringValue(const XmlRpcString &value);
    void SetDateTimeValue(const XmlRpcDateTime &value);
    void SetDateTimeValue(const time_t &value);
    void SetBase64Value(const XmlRpcBase64 &value);
    void SetArrayValue(const XmlRpcArray &value);
    void SetStructValue(const XmlRpcStruct &value);

public:
    bool operator == (const XmlRpcValue &that) const;
    bool operator != (const XmlRpcValue &that) const;

public:
    XmlNodePtr ToXml();
    bool FromXml(const XmlNodePtr &pNode);
};


#endif // #ifndef __XMLRPCVALUE_H_5EF83F6C_F2D4_465E_B965_CC8FBB4987DF_INCLUDED__
