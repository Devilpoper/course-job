#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <wctype.h>

wchar_t* wcdup_with_symb(wchar_t* word, wchar_t symb){
    int size = wcslen(word) + 2;
    wchar_t* new_word = (wchar_t*)malloc(sizeof(wchar_t) * size);
    for (int i = 0 ; i < wcslen(word); i++){
        new_word[i] = word[i];
    }
    new_word[size-2] = symb;
    new_word[size-1] = '\0';
    return new_word;
}

wchar_t** validate_sentence(wchar_t* sentence, int *count_words){
    int capacity = 1, size = 0;
    wchar_t** arr_words = (wchar_t**)malloc(sizeof(wchar_t*) * capacity);

    wchar_t* ptr;
    wchar_t* sep_word = wcstok(sentence, L" \n\t", &ptr);

    while (sep_word != NULL){
        if (wcslen(sep_word) == 1 && sep_word[0] == L','){
            wchar_t* new_sep_word = wcdup_with_symb(arr_words[size-1], sep_word[0]);
            arr_words[size-1] = new_sep_word;
        }
        else{
            arr_words[size++] = sep_word;
        }

        if (size >= capacity){
            capacity++;
            arr_words = (wchar_t**)realloc(arr_words, sizeof(wchar_t*) * capacity);
        }
        sep_word = wcstok(NULL, L" \n\t", &ptr);
    }
    (*count_words) = size;
    return arr_words;
}

