#include "XmlRpcValue.h"
#include <tchar.h>

XmlRpcValue::XmlRpcValue()
    : m_type(XRDT_NIL), m_bool(false), m_int(0), m_double(0.0), m_string(nullptr),
      m_datetime(nullptr), m_base64(nullptr), m_array(nullptr), m_struct(nullptr)
{

}

XmlRpcValue::XmlRpcValue(const XmlRpcValue &that)
    : m_type(XRDT_NIL), m_bool(false), m_int(0), m_double(0.0), m_string(nullptr),
      m_datetime(nullptr), m_base64(nullptr), m_array(nullptr), m_struct(nullptr)
{
    *this = that;
}

XmlRpcValue &XmlRpcValue::operator = (const XmlRpcValue &that)
{
    ClearValue();

    this->m_type = that.m_type;

    switch (m_type)
    {
    case XRDT_BOOL:
        this->m_bool = that.m_bool;
        break;
    case XRDT_INT:
        this->m_int = that.m_int;
        break;
    case XRDT_DOUBLE:
        this->m_double = that.m_double;
        break;
    case XRDT_STRING:
        this->m_string = new XmlRpcString;
        *this->m_string = *that.m_string;
        break;
    case XRDT_DATETIME:
        this->m_datetime = new XmlRpcDateTime;
        *this->m_datetime = *that.m_datetime;
        break;
    case XRDT_BASE64:
        this->m_base64 = new XmlRpcBase64;
        *this->m_base64 = *that.m_base64;
        break;
    case XRDT_ARRAY:
        this->m_array = new XmlRpcArray;
        *this->m_base64 = *that.m_base64;
        break;
    case XRDT_STRUCT:
        this->m_struct = new XmlRpcStruct;
        *this->m_struct = *that.m_struct;
        break;
    case XRDT_NIL:
    default:
        break;
    }

    return *this;
}

XmlRpcValue::~XmlRpcValue()
{
    ClearValue();
}

XmlRpcDataTypes XmlRpcValue::GetType() const
{
    return m_type;
}

XmlRpcBool XmlRpcValue::GetBoolValue() const
{
    return m_bool;
}

XmlRpcInt XmlRpcValue::GetIntValue() const
{
    return m_int;
}

XmlRpcDouble XmlRpcValue::GetDoubleValue() const
{
    return m_double;
}

XmlRpcString XmlRpcValue::GetStringValue() const
{
    return *m_string;
}

XmlRpcDateTime XmlRpcValue::GetDateTimeValue() const
{
    return *m_datetime;
}

XmlRpcBase64 XmlRpcValue::GetBase64Value() const
{
    return *m_base64;
}

XmlRpcArray XmlRpcValue::GetArrayValue() const
{
    return *m_array;
}

XmlRpcStruct XmlRpcValue::GetStructValue() const
{
    return *m_struct;
}

void XmlRpcValue::ClearValue()
{
    switch (m_type)
    {
    case XRDT_BOOL:
        m_bool = false;
        break;
    case XRDT_INT:
        m_int = 0;
        break;
    case XRDT_DOUBLE:
        m_double = 0.0;
        break;
    case XRDT_STRING:
        delete m_string;
        m_string = nullptr;
        break;
    case XRDT_DATETIME:
        delete m_datetime;
        m_datetime = nullptr;
        break;
    case XRDT_BASE64:
        delete m_base64;
        m_base64 = nullptr;
        break;
    case XRDT_ARRAY:
        delete m_array;
        m_base64 = nullptr;
        break;
    case XRDT_STRUCT:
        delete m_struct;
        m_struct = nullptr;
        break;
    case XRDT_NIL:
    default:
        break;
    }

    m_type = XRDT_NIL;
}

void XmlRpcValue::SetNilValue()
{
    ClearValue();
}

void XmlRpcValue::SetBoolValue(const XmlRpcBool &value)
{
    ClearValue();

    m_type = XRDT_BOOL;
    m_bool = value;
}

void XmlRpcValue::SetIntValue(const XmlRpcInt &value)
{
    ClearValue();

    m_type = XRDT_INT;
    m_int = value;
}

void XmlRpcValue::SetDoubleValue(const XmlRpcDouble &value)
{
    ClearValue();

    m_type = XRDT_DOUBLE;
    m_double = value;
}

void XmlRpcValue::SetStringValue(const XmlRpcString &value)
{
    ClearValue();

    m_type = XRDT_STRING;
    m_string = new XmlRpcString;
    *m_string = value;
}

void XmlRpcValue::SetDateTimeValue(const XmlRpcDateTime &value)
{
    ClearValue();

    m_type = XRDT_DATETIME;
    m_datetime = new XmlRpcDateTime;
    *m_datetime = value;
}

void XmlRpcValue::SetDateTimeValue(const time_t &value)
{
    m_type = XRDT_DATETIME;
    m_datetime = new XmlRpcDateTime;
    *m_datetime = nullptr;  // TODO
}

void XmlRpcValue::SetBase64Value(const XmlRpcBase64 &value)
{
    ClearValue();

    m_type = XRDT_BASE64;
    m_base64 = new XmlRpcBase64;
    *m_base64 = value;
}

void XmlRpcValue::SetArrayValue(const XmlRpcArray &value)
{
    ClearValue();

    m_type = XRDT_ARRAY;
    m_array = new XmlRpcArray;
    *m_array = value;
}

void XmlRpcValue::SetStructValue(const XmlRpcStruct &value)
{
    ClearValue();

    m_type = XRDT_STRUCT;
    m_struct = new XmlRpcStruct;
    *m_struct = value;
}

bool XmlRpcValue::operator == (const XmlRpcValue &that) const
{
    if (this->m_type != that.m_type)
    {
        return false;
    }

    switch (m_type)
    {
    case XRDT_BOOL:
        return this->m_bool == that.m_bool;
    case XRDT_INT:
        return this->m_int == that.m_int;
    case XRDT_DOUBLE:
        return this->m_double == that.m_double;
    case XRDT_STRING:
        return *this->m_string == *that.m_string;
        break;
    case XRDT_DATETIME:
        return *this->m_datetime == *that.m_datetime;
        break;
    case XRDT_BASE64:
        return *this->m_base64 == *that.m_base64;
        break;
    case XRDT_ARRAY:
        return *this->m_base64 == *that.m_base64;
        break;
    case XRDT_STRUCT:
        return *this->m_struct == *that.m_struct;
        break;
    case XRDT_NIL:
    default:
        break;
    }

    return true;
}

bool XmlRpcValue::operator != (const XmlRpcValue &that) const
{
    return !(*this == that);
}

XmlNodePtr XmlRpcValue::ToXml()
{
    XmlNodePtr pValue = new XmlNode;
    pValue->SetTagName(L"value");

    XmlNodePtr pNode = new XmlNode;
    XmlNodePtr pSubNode = new XmlNode;
    pSubNode->SetType(XmlNode::XML_VALUE);

    const size_t BUFFER_SIZE = 100;
    TCHAR BUFFER[BUFFER_SIZE];

    switch (m_type)
    {
    case XRDT_BOOL:
        pNode->SetTagName(L"boolean");
        pSubNode->SetValue(m_bool ? L"1" : L"0");
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_INT:
        pNode->SetTagName(L"int");
        _stprintf(BUFFER, _T("%d"), m_int);
        pSubNode->SetValue(BUFFER);
        pNode->SubNodes().PushBack(pSubNode);
        break;;
    case XRDT_DOUBLE:
        pNode->SetTagName(L"double");
        _stprintf(BUFFER, _T("%lf"), m_double);
        pSubNode->SetValue(BUFFER);
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_STRING:
        pNode->SetTagName(L"string");
        pSubNode->SetValue(*m_string);
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_DATETIME:
        pNode->SetTagName(L"dateTime.iso8601");
        pSubNode->SetValue(*m_datetime);
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_BASE64:
        pNode->SetTagName(L"base64");
        pSubNode->SetValue(L"");    // TODO
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_ARRAY:
        pNode->SetTagName(L"array");
        pSubNode->SetTagName(L"data");
        pSubNode->SetType(XmlNode::XML_NODE);

        for (XmlRpcArray::Iterator it = m_array->Begin(); it != m_array->End(); ++it)
        {
            pSubNode->SubNodes().PushBack(it->ToXml());
        }

        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_STRUCT:
        pNode->SetTagName(L"struct");

        for (XmlRpcStruct::Iterator it = m_struct->Begin(); it != m_struct->End(); ++it)
        {
            XmlNodePtr pMember = new XmlNode;
            pMember->SetTagName(L"member");

            XmlNodePtr pName = new XmlNode;
            pName->SetTagName(L"name");
            pName->SetValue(it->Key);

            pMember->SubNodes().PushBack(pName);
            pMember->SubNodes().PushBack(it->Value.ToXml());

            pNode->SubNodes().PushBack(pMember);
        }

        break;
    case XRDT_NIL:
    default:
        pNode->SetTagName(L"nil");
        break;
    }

    pValue->SubNodes().PushBack(pNode);
    
    return pValue;
}