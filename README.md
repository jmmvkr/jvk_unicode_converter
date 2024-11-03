# jvk_unicode_converter
A Unicode converter library that focus on conversion between UTF-8 and UTF-16 strings 

## Usage

Include the header first
```C++
#include "utf8_converter.h"
```

Convert UTF-8 string to wstring
```C++
using jvk::unicode::utf8_converter;

/* more code goes here */
string utf8_string;
wstring wide_string = utf8_converter::to_wstring(utf8_string);
```

Convert wstring to UTF-8 string
```C++
using jvk::unicode::utf8_converter;

/* more code goes here */
wstring wide_string;
string utf8_string = utf8_converter::from_wstring(wide_string);
```
