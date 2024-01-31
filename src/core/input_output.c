#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <wctype.h>
#include "validation.h"
#include "functions.h"
#include "structures.h"
#include "input_output.h"

void input_choise(wchar_t choise){
    if (choise == '5'){
        wprintf(L"help about functions\n\
        1 - “Color” each word depending on the remainder of dividing its length by 4. If the remainder is \n\
            0 - red, 1 - blue, 2 - green, 3 - yellow.\n\
        2 - Print each word that begins and ends with a capital letter and the sentence numbers in which it appears.\n\
        3 - Sort sentences by the length of the last word in the sentence.\n\
        4 - Remove all numbers from sentences. A number is a set of consecutive numbers preceded and followed by spaces.\n");
        exit(0);
    }
    wchar_t* words_xy;
    wchar_t* ptr;
    if (choise == '9'){
        words_xy = get_first_str();
    }
    if ((wcstol(&choise, NULL, 10) >= 5 || wcstol(&choise, NULL, 10) < 0 || iswdigit(choise) == 0) && choise != '9'){
        wprintf(L"Error: input incorrect number\n");
        exit(0);
    }
    //create struct
    Text text;
    text.t = get_structure_text(&text.count_sentence, &text.size);
    Sentence* sentences = get_structure_sentences(&text.count_sentence, text.t);

    //choose func 
    switch (choise)
    {
    case '0':
        for(int i = 0; i < text.count_sentence; i++){
            output_sentense(sentences[i].text_sentence, sentences[i].count_words);
        }
        break;

    case '1':
        for(int i = 0; i < text.count_sentence; i++){
            paint_words(sentences[i]);
        }
        break;

    case '2':
        for(int i = 0; i < text.count_sentence; i++){
            print_word_with_cap(sentences[i]);
        }
        break;
    
    case '3':
        sort_by_last(sentences, text.count_sentence);
        break;

    case '4':
        for ( int i =0; i < text.count_sentence; i++){
            delete_numbers(sentences[i]);
        }
        break;

    case '9':
        wchar_t* word_x = wcstok(words_xy, L" ", &ptr);
        wchar_t* word_y = wcstok(NULL, L" ", &ptr);
        for ( int i =0; i < text.count_sentence; i++){
            replace_words(sentences[i], word_x, word_y);
        }
        break;
    }
}

void output_sentense(wchar_t** arr_words, int size){
    for(int i = 0; i < size; i++){
        if(arr_words[i] == NULL){continue;}
        if(i == size-1){
            wprintf(L"%ls.", arr_words[i]);
        } 
        else{
            wprintf(L"%ls ", arr_words[i]);
        }
    }
    wprintf(L"\n");
}