#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <wctype.h>
#include "validation.h"
#include "structures.h"
#include "input_output.h"


void paint_words(Sentence sent){
    for(int i = 0; i < sent.count_words; i++){
        int size_word = wcslen(sent.text_sentence[i]), skip_sym = 0;
        for(int j = 0; j < size_word; j++){
            if(iswpunct(sent.text_sentence[i][j]) || iswprint(sent.text_sentence[i][j]) == 0){
                skip_sym++;
            }
        }
        size_word -= skip_sym;
        size_word = size_word % 4;
        if (size_word == 0) {
            wprintf(L"\x1b[31m%ls\x1b[0m", sent.text_sentence[i]);
        }
        if (size_word == 1) {
            wprintf(L"\x1b[34m%ls\x1b[0m", sent.text_sentence[i]);
        }
        if (size_word == 2) {
            wprintf(L"\x1b[32m%ls\x1b[0m", sent.text_sentence[i]);
        }
        if (size_word == 3) {
            wprintf(L"\x1b[33m%ls\x1b[0m", sent.text_sentence[i]);
        }
        if (i == sent.count_words - 1){
            wprintf(L".\n");
        }
        else{
            wprintf(L" ");
        }
    }
}

void print_word_with_cap(Sentence sen){
    for (int i = 0; i < sen.count_words; i++){
        int end = wcslen(sen.text_sentence[i]);
        if (sen.text_sentence[i][end-1] == L','){
            if (iswupper(sen.text_sentence[i][0]) && iswupper(sen.text_sentence[i][end-2])){
                sen.text_sentence[i][end-1] = '\0';
                wprintf(L"%ls number sentense - %d\n", sen.text_sentence[i], sen.self_number_in_text);
            }
        }
        else{
            if (iswupper(sen.text_sentence[i][0]) && iswupper(sen.text_sentence[i][end-1])){
                wprintf(L"%ls number sentense - %d\n", sen.text_sentence[i], sen.self_number_in_text);
            } 
        }
    }
}

int compare(const void* a, const void* b){
    Sentence* first = (Sentence*) a;
    Sentence* second = (Sentence*) b;
    first->last_word = wcslen(first->text_sentence[(first->count_words)-1]);
    second->last_word = wcslen(second->text_sentence[(second->count_words)-1]);
    return (second->last_word) - (first->last_word);
}

void sort_by_last(Sentence* sentences, int count_sentence){
    
    qsort(sentences, count_sentence, sizeof(Sentence), compare);
    for (int i = 0; i < count_sentence; i++){
        output_sentense(sentences[i].text_sentence, sentences[i].count_words);
    }
}

void delete_numbers(Sentence sent){
    int count_deleted = 0;
    for (int i = 0; i < sent.count_words; i++){
        if (sent.text_sentence[i][wcslen(sent.text_sentence[i] )-1] == L','){
            sent.text_sentence[i][wcslen(sent.text_sentence[i] )-1] = L'\0';
        }
        if(wcstol(sent.text_sentence[i], NULL, 10) != 0){
            sent.text_sentence[i] = NULL;
            count_deleted++;
        }
    }
    wchar_t** new_words = (wchar_t**)malloc(sizeof(wchar_t*) * (sent.count_words - count_deleted));
    int j = 0;
    for(int i = 0; i < sent.count_words; i++){
        if (sent.text_sentence[i] != NULL){
            new_words[j++] = sent.text_sentence[i];
        }
    }
    output_sentense(new_words, sent.count_words - count_deleted);
}