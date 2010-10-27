
#include <xl/Containers/xlArray.h>
#include <xl/Containers/xlMap.h>
#include <xl/Objects/xlString.h>
#include <xl/Objects/xlQIPtr.h>

typedef unsigned char           Base64Byte;
typedef xl::Array<Base64Byte>   Base64Bytes;
typedef xl::Char                Base64Char;
typedef xl::String              Base64String;
typedef xl::QIPtr<Base64Bytes>  Base64BytesPtr;
typedef xl::QIPtr<Base64String> Base64StringPtr;

class Base64
{
public:
    Base64();
    ~Base64();
    
public:
    Base64StringPtr Encode(const void *lpPlain, size_t nLength);
    Base64BytesPtr  Decode(const Base64String &strEncoded);

private:
    xl::Map<Base64Char, Base64Byte> m_alphabet_reverse;
};