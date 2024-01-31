
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include "input_output.h"

int main(){
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.7, created by Ryabov Mikhail.\n");
    wint_t choise = getwchar();
    wchar_t stub = getwchar();
    if (stub == '\0'){
        wprintf(L"Error: incorrect choise");
        exit(0);
    }
    input_choise(choise);
    
    return 0;
}