#ifndef JVK_UTF8_CONVERTER_H
#define JVK_UTF8_CONVERTER_H

#include <string>
#include "utf8_to_utf16.h"
#include "utf16_to_utf8.h"

namespace jvk {

namespace unicode {


class utf8_converter {
public:

    utf8_converter() = delete;

    static size_t count_wstr(size_t szInput, const char* input)
    {
        utf8_to_utf16<char> converter = {};
        int n_follow = 0;
        size_t num_of_wch = 0;

        // count wstr result using converter.feed()
        for (size_t i = 0; i < szInput; i++)
        {
            n_follow = converter.feed(n_follow, input[i]);
            if (0 == n_follow) {
                num_of_wch++;
            }
        }
        return num_of_wch;
    }

    static size_t fill_wstr(size_t szInput, const char* input, size_t szOutBuffer, wchar_t* outBuffer)
    {
        utf8_to_utf16<char> converter = {};
        int n_follow = 0;
        size_t pos = 0;

        // fill wstr result using converter.feed()
        for (size_t i = 0; i < szInput; i++)
        {
            n_follow = converter.feed(n_follow, input[i]);
            if (0 == n_follow) {
                // copy each wch to the result wstring
                if (pos >= szOutBuffer) break;
                outBuffer[pos++] = 0xffff & converter.wch;
            }
        }
        return pos;
    }

    static size_t count_mbstr(size_t szInput, const wchar_t* input)
    {
        utf16_to_utf8<char> converter = {};
        size_t num_of_bytes = 0;

        // count mbstr result using converter.feed()
        for (size_t i = 0; i < szInput; i++)
        {
            if (0 == converter.feed(input[i])) {
                num_of_bytes += converter.byte_count;
            }
        }
        return num_of_bytes;
    }

    static size_t fill_mbstr(size_t szInput, const wchar_t* input, size_t szOutBuffer, char* outBuffer)
    {
        utf16_to_utf8<char> converter = {};
        size_t pos = 0;

        // fill mbstr result using converter.feed()
        for (size_t i = 0; i < szInput; i++)
        {
            if (0 == converter.feed(input[i])) {
                if ((pos + converter.byte_count) > szOutBuffer) break;
                for (int i = 0; i < converter.byte_count; i++) {
                    // copy each byte to the result string
                    outBuffer[pos++] = converter.utf8_bytes[i];
                }
            }
        }
        return pos;
    }

    static std::wstring to_wstring(const std::string& input)
    {
        // count the size of result wstring
        size_t num_of_wch = count_wstr(input.size(), input.c_str());

        // fill the result wstring
        std::wstring result(num_of_wch, '\0');
        fill_wstr(input.size(), input.c_str(), num_of_wch, (wchar_t*)result.c_str());
        return result;
    }

    static std::string from_wstring(const std::wstring& input)
    {
        // count the size of result string
        size_t num_of_bytes = count_mbstr(input.size(), input.c_str());

        // fill the result string
        std::string result(num_of_bytes, '\0');
        fill_mbstr(input.size(), input.c_str(), num_of_bytes, (char*)result.c_str());
        return result;
    }

};


} // namespace unicode

} // namespace jvk

#endif // !JVK_UTF8_CONVERTER_H
