
#include "Base64.h"

#define BASE64_ALPHABET_LENGTH  64
#define BASE64_ALPHABET L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"   \
                        L"abcdefghijklmnopqrstuvwxyz"   \
                        L"0123456789"   \
                        L"+/="

Base64::Base64()
{
    for (Base64Byte i = 0; i <= BASE64_ALPHABET_LENGTH; ++i)
    {
        m_alphabet_reverse.Insert(BASE64_ALPHABET[i], i);
    }
}

Base64::~Base64()
{

}

Base64StringPtr Base64::Encode(const void *lpPlain, size_t nLength)
{
    Base64StringPtr pEncoded = new Base64String;
    const Base64Byte *lpBytes = (const Base64Byte *)lpPlain;

    for (size_t i = 0; i < nLength; i += 3)
    {
        pEncoded->AppendBack(BASE64_ALPHABET[(lpBytes[i] >> 2) & 0x3f]);

        if (i + 1 >= nLength)
        {
            pEncoded->AppendBack(BASE64_ALPHABET[(lpBytes[i] & 0x03) << 4]);
            pEncoded->AppendBack(BASE64_ALPHABET[BASE64_ALPHABET_LENGTH]);
            pEncoded->AppendBack(BASE64_ALPHABET[BASE64_ALPHABET_LENGTH]);
        }
        else
        {
            pEncoded->AppendBack(BASE64_ALPHABET[((lpBytes[i] & 0x03) << 4) | ((lpBytes[i + 1] >> 4) & 0x0f)]);

            if (i + 2 >= nLength)
            {
                pEncoded->AppendBack(BASE64_ALPHABET[(lpBytes[i + 1] & 0x0f) << 2]);
                pEncoded->AppendBack(BASE64_ALPHABET[BASE64_ALPHABET_LENGTH]);
            }
            else
            {
                pEncoded->AppendBack(BASE64_ALPHABET[((lpBytes[i + 1] & 0x0f) << 2) | ((lpBytes[i + 2] >> 6) & 0x03)]);
                pEncoded->AppendBack(BASE64_ALPHABET[lpBytes[i + 2] & 0x3f]);
            }
        }
    }

    return pEncoded;
}

Base64BytesPtr Base64::Decode(const Base64String &strEncoded)
{
    Base64BytesPtr pPlain = new Base64Bytes;

    int len = strEncoded.Length();

    for (int i = 0; i < len; i += 4)
    {
        if (i + 1 < len && strEncoded[i] != BASE64_ALPHABET[64] && strEncoded[i + 1] != BASE64_ALPHABET[BASE64_ALPHABET_LENGTH])
        {
            pPlain->PushBack((m_alphabet_reverse[strEncoded[i]] << 2) | ((m_alphabet_reverse[strEncoded[i + 1]] >> 4) & 0x03));
        }

        if (i + 2 < len && strEncoded[i + 2] != BASE64_ALPHABET[64])
        {
            pPlain->PushBack((m_alphabet_reverse[strEncoded[i + 1]] << 4) | ((m_alphabet_reverse[strEncoded[i + 2]] >> 2) & 0x0f));
        }

        if (i + 3 < len && strEncoded[i + 3] != BASE64_ALPHABET[64])
        {
            pPlain->PushBack((m_alphabet_reverse[strEncoded[i + 2]] << 6) | m_alphabet_reverse[strEncoded[i + 3]]);
        }
    }

    return pPlain;
}