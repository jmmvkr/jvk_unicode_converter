#ifndef JVK_UTF16_TO_UTF8_H
#define JVK_UTF16_TO_UTF8_H

namespace jvk {

namespace unicode {


// convert utf-16 sequence to utf-8 sequence
// note that surrogate characters are discarded
template <typename xchar_t>
struct utf16_to_utf8 {

    xchar_t utf8_bytes[4];  // fixed-size array to store encoded bytes
    int byte_count;      // number of bytes in the current encoded sequence

    int feed(wchar_t ch)
    {
        byte_count = 0;

        if (ch <= 0x7f) {
            // one-byte sequence (ASCII)
            utf8_bytes[0] = static_cast<xchar_t>(ch);
            byte_count = 1;
        } 
        else if (ch <= 0x7ff) {
            // two-byte sequence
            utf8_bytes[0] = static_cast<xchar_t>(0xc0 | ((ch >> 6) & 0x1f));
            utf8_bytes[1] = static_cast<xchar_t>(0x80 | (ch & 0x3f));
            byte_count = 2;
        } 
        else if (ch >= 0xd800 && ch <= 0xdfff) {
            // skipping surrogate characters
            return -1;  
        }
        else {
            // three-byte sequence
            utf8_bytes[0] = static_cast<xchar_t>(0xe0 | ((ch >> 12) & 0x0f));
            utf8_bytes[1] = static_cast<xchar_t>(0x80 | ((ch >> 6) & 0x3f));
            utf8_bytes[2] = static_cast<xchar_t>(0x80 | (ch & 0x3f));
            byte_count = 3;
        }

        return 0;  // successful encoding
    }

};


} // namespace unicode

} // namespace jvk

#endif // !JVK_UTF16_TO_UTF8_H
