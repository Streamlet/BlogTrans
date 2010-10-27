#include "XmlRpcValue.h"
#include <tchar.h>

#define XRDT_TAG_VALUE      L"value"
#define XRDT_TAG_NIL        L"nil"
#define XRDT_TAG_BOOLEAN    L"boolean"
#define XRDT_TAG_INT        L"int"
#define XRDT_TAG_I4         L"i4"
#define XRDT_TAG_DOUBLE     L"double"
#define XRDT_TAG_STRING     L"string"
#define XRDT_TAG_DATETIME   L"dateTime.iso8601"
#define XRDT_TAG_BASE64     L"base64"
#define XRDT_TAG_ARRAY      L"array"
#define XRDT_TAG_DATA       L"data"
#define XRDT_TAG_STRUCT     L"struct"
#define XRDT_TAG_MEMBER     L"member"
#define XRDT_TAG_NAME       L"name"

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
        *this->m_array = *that.m_array;
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
    *m_datetime = nullptr;  //TODO: make iso date time
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
        pNode->SetTagName(XRDT_TAG_BOOLEAN);
        pSubNode->SetValue(m_bool ? L"1" : L"0");
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_INT:
        pNode->SetTagName(XRDT_TAG_INT);
        _stprintf(BUFFER, _T("%d"), m_int);
        pSubNode->SetValue(BUFFER);
        pNode->SubNodes().PushBack(pSubNode);
        break;;
    case XRDT_DOUBLE:
        pNode->SetTagName(XRDT_TAG_DOUBLE);
        _stprintf(BUFFER, _T("%lf"), m_double);
        pSubNode->SetValue(BUFFER);
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_STRING:
        pNode->SetTagName(XRDT_TAG_STRING);
        pSubNode->SetValue(*m_string);
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_DATETIME:
        pNode->SetTagName(XRDT_TAG_DATETIME);
        pSubNode->SetValue(*m_datetime);
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_BASE64:
        pNode->SetTagName(XRDT_TAG_BASE64);
        pSubNode->SetValue(L"");    //TODO: Base64 encode
        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_ARRAY:
        pNode->SetTagName(XRDT_TAG_ARRAY);
        pSubNode->SetTagName(XRDT_TAG_DATA);
        pSubNode->SetType(XmlNode::XML_NODE);

        for (XmlRpcArray::Iterator it = m_array->Begin(); it != m_array->End(); ++it)
        {
            pSubNode->SubNodes().PushBack(it->ToXml());
        }

        pNode->SubNodes().PushBack(pSubNode);
        break;
    case XRDT_STRUCT:
        pNode->SetTagName(XRDT_TAG_STRUCT);

        for (XmlRpcStruct::Iterator it = m_struct->Begin(); it != m_struct->End(); ++it)
        {
            XmlNodePtr pMember = new XmlNode;
            pMember->SetTagName(XRDT_TAG_MEMBER);

            XmlNodePtr pName = new XmlNode;
            pName->SetTagName(XRDT_TAG_NAME);

            XmlNodePtr pNameValue = new XmlNode;
            pNameValue->SetType(XmlNode::XML_VALUE);
            pNameValue->SetValue(it->Key);

            pName->SubNodes().PushBack(pNameValue);

            pMember->SubNodes().PushBack(pName);
            pMember->SubNodes().PushBack(it->Value.ToXml());

            pNode->SubNodes().PushBack(pMember);
        }

        break;
    case XRDT_NIL:
    default:
        pNode->SetTagName(XRDT_TAG_NIL);
        break;
    }

    pValue->SubNodes().PushBack(pNode);
    
    return pValue;
}

bool XmlRpcValue::FromXml(const XmlNodePtr &pNode)
{
    ClearValue();

    if (pNode->GetType() != XmlNode::XML_NODE || pNode->GetTagName() != XRDT_TAG_VALUE || pNode->SubNodes().Size() != 1)
    {
        return false;
    }

    XmlNodePtr pSubNode = *pNode->SubNodes().Begin();

    if (pSubNode->GetType() != XmlNode::XML_NODE)
    {
        return false;
    }

    xl::String strTagName = pSubNode->GetTagName();

    if (strTagName == XRDT_TAG_NIL)
    {
        if (!pSubNode->SubNodes().Empty())
        {
            return false;
        }

        SetNilValue();
    }
    else if (strTagName == XRDT_TAG_BOOLEAN)
    {
        if (pSubNode->SubNodes().Size() != 1)
        {
            return false;
        }

        XmlNodePtr pValueNode = *pSubNode->SubNodes().Begin();
        
        if (pValueNode->GetType() != XmlNode::XML_VALUE)
        {
            return false;
        }

        xl::String strValue = pValueNode->GetValue();

        if (strValue != L"0" && strValue != L"1")
        {
            return false;
        }

        SetBoolValue(strValue != L"0");
    }
    else if (strTagName == XRDT_TAG_INT || strTagName == XRDT_TAG_I4)
    {
        if (pSubNode->SubNodes().Size() != 1)
        {
            return false;
        }

        XmlNodePtr pValueNode = *pSubNode->SubNodes().Begin();

        if (pValueNode->GetType() != XmlNode::XML_VALUE)
        {
            return false;
        }

        xl::String strValue = pValueNode->GetValue();

        XmlRpcInt nValue;
        _stscanf(strValue.GetAddress(), _T("%d"), &nValue);

        SetIntValue(nValue);
    }
    else if (strTagName == XRDT_TAG_DOUBLE)
    {
        if (pSubNode->SubNodes().Size() != 1)
        {
            return false;
        }

        XmlNodePtr pValueNode = *pSubNode->SubNodes().Begin();

        if (pValueNode->GetType() != XmlNode::XML_VALUE)
        {
            return false;
        }

        xl::String strValue = pValueNode->GetValue();

        XmlRpcDouble lfValue;
        _stscanf(strValue.GetAddress(), _T("%lf"), &lfValue);

        SetDoubleValue(lfValue);
    }
    else if (strTagName == XRDT_TAG_STRING)
    {
        if (pSubNode->SubNodes().Size() != 1)
        {
            return false;
        }

        XmlNodePtr pValueNode = *pSubNode->SubNodes().Begin();

        if (pValueNode->GetType() != XmlNode::XML_VALUE)
        {
            return false;
        }

        xl::String strValue = pValueNode->GetValue();

        SetStringValue(strValue);
    }
    else if (strTagName == XRDT_TAG_DATETIME)
    {
        if (pSubNode->SubNodes().Size() != 1)
        {
            return false;
        }

        XmlNodePtr pValueNode = *pSubNode->SubNodes().Begin();

        if (pValueNode->GetType() != XmlNode::XML_VALUE)
        {
            return false;
        }

        xl::String strValue = pValueNode->GetValue();

        SetDateTimeValue(strValue);
    }
    else if (strTagName == XRDT_TAG_BASE64)
    {
        if (pSubNode->SubNodes().Size() != 1)
        {
            return false;
        }

        XmlNodePtr pValueNode = *pSubNode->SubNodes().Begin();

        if (pValueNode->GetType() != XmlNode::XML_VALUE)
        {
            return false;
        }

        xl::String strValue = pValueNode->GetValue();

        // TODO: Base64 decode
        //SetBase64Value();
    }
    else if (strTagName == XRDT_TAG_ARRAY)
    {
        if (pSubNode->SubNodes().Size() != 1)
        {
            return false;
        }

        XmlNodePtr pDataNode = *pSubNode->SubNodes().Begin();

        if (pDataNode->GetType() != XmlNode::XML_NODE ||
            pDataNode->GetTagName() != XRDT_TAG_DATA)
        {
            return false;
        }

        XmlRpcArray arrValue;

        for (XmlNodeList::Iterator it = pDataNode->SubNodes().Begin(); it != pDataNode->SubNodes().End(); ++it)
        {
            XmlRpcValue value;
            
            if (!value.FromXml(*it))
            {
                return false;
            }

            arrValue.PushBack(value);
        }

        SetArrayValue(arrValue);
    }
    else if (strTagName == XRDT_TAG_STRUCT)
    {
        XmlRpcStruct stValue;

        for (XmlNodeList::Iterator it = pSubNode->SubNodes().Begin(); it != pSubNode->SubNodes().End(); ++it)
        {
            XmlNodePtr pMemberNode = *it;

            if (pMemberNode->GetType() != XmlNode::XML_NODE ||
                pMemberNode->GetTagName() != XRDT_TAG_MEMBER ||
                pMemberNode->SubNodes().Size() != 2)
            {
                return false;
            }

            XmlNodePtr pNameNode = *pMemberNode->SubNodes().Begin();

            if (pNameNode->GetType() != XmlNode::XML_NODE ||
                pNameNode->GetTagName() != XRDT_TAG_NAME ||
                pNameNode->SubNodes().Size() != 1)
            {
                return false;
            }

            XmlNodePtr pNameValue = *pNameNode->SubNodes().Begin();

            if (pNameValue->GetType() != XmlNode::XML_VALUE)
            {
                return false;
            }

            xl::String strName = pNameValue->GetValue();

            XmlNodePtr pValueNode = *++pMemberNode->SubNodes().Begin();

            XmlRpcValue value;

            if (!value.FromXml(pValueNode))
            {
                return false;
            }

            stValue.Insert(strName, value);
        }
        
        SetStructValue(stValue);
    }
    else
    {
        return false;
    }

    return true;
}
