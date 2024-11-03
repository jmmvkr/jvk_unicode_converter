#include <iostream>
#include <string>
#include "utf8_converter.h"

using namespace std;
using jvk::unicode::utf8_converter;

void usage(const char* exec)
{
    cout << "" << endl;    
    cout << "Usage:" << endl;    
    cout << "    " << exec << " <input-text>" << endl;    
    cout << "" << endl;    
    exit(1);
}

void run_example(const char* input)
{
    string original(input);
    wstring wide = utf8_converter::to_wstring(original);
    string recovered = utf8_converter::from_wstring(wide);

    // print out converted sequence
    printf("wstring wide is: ");
    for(const auto& wch : wide)
    {
        printf("%04x ", (int) wch);
    }
    printf("\n");
    
    // print out recovered sequence
    printf("string recovered is: ");
    for(const auto& ch : recovered)
    {
        printf("%02x ", 0xff & ch);
    }
    printf("\n");
    
    // print out converted string in console
    cout << "recovered: " << recovered << endl;    
}

int main(int argc, const char* argv[])
{
    // check if there is a input string
    if(argc > 1) {
        // run example if input string presents
        run_example(argv[1]);
    } else {
        // show usage otherwise
        usage(argv[0]);
    }

    return 0;
}
