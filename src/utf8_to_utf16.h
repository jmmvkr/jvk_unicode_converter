#ifndef JVK_UTF8_TO_UTF16_H
#define JVK_UTF8_TO_UTF16_H

namespace jvk {

namespace unicode {


// convert utf-8 sequence to utf-16 sequence
// note that 4-byte utf-8 sequence is discarded
template <typename xchar_t>
struct utf8_to_utf16 {

    wchar_t wch;
    
    int feed(int n_follow, xchar_t xch)
    {
        // apply bitmask 0xff to clear invalid bits
        int ch = (0xff & xch);

        if(ch <= 0x7f) {
            // one byte sequence, starts with binary 0xxxxxxx
            n_follow = 0;
            wch = ch;
        } else if((0xc0 & ch) == 0x80) {
            // following byte, starts with binary 10xxxxxx
            if(n_follow > 0) {
                wch = (wch << 6) | (0x3f & ch);
                n_follow--;
            }
        } else if(ch <= 0xdf) {
            // two byte sequence, starts with binary 110xxxxx
            n_follow = 1;
            wch = ch & 0x1f;
        } else if(ch <= 0xef) {
            // three byte sequence, starts with binary 1110xxxx
            n_follow = 2;
            wch = ch & 0x0f;
        }

        // returns 0 when the wch is ready
        return n_follow;
    }
    
};


} // namespace unicode

} // namespace jvk

#endif // !JVK_UTF8_TO_UTF16_H
