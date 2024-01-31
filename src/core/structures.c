#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <wctype.h>
#include "validation.h"
#include "functions.h"

Sentence* get_structure_sentences(int *count_sentence, wchar_t* text){
    Sentence* sentences = (Sentence*)malloc(sizeof(Sentence) * (*count_sentence));
    //поделить на предложения и валидировать
    for(int i = 0; i<(*count_sentence); i++){
        sentences[i].self_number_in_text = i+1;
        sentences[i].text_sentence = get_sentence(text, i, &sentences[i].count_words);
    }
    
    //убрать лишние предложения 
    int flag = 0;
    int count_deleted = 0;
    for( int i = 0; i < (*count_sentence); i++){
        for (int j = i+1; j < (*count_sentence); j++){
            //wprintf(L"СРАВНЕНИЕ %d и %d\n", sentences[i].self_number_in_text, sentences[j].self_number_in_text);
            flag = 0;
            if (sentences[i].count_words == sentences[j].count_words){
                for(int k = 0; k < sentences[i].count_words; k++){
                    if (wcscmp(sentences[i].text_sentence[k], sentences[j].text_sentence[k]) != 0){
                        flag = 1;
                    }
                }
            }
            else{
                flag = 1;
            }
            
            if (flag == 0){
                sentences[j].self_number_in_text = 0;
                count_deleted++;
            }
        }
    }
    Sentence* new_sentences = (Sentence*)malloc(sizeof(Sentence) * ((*count_sentence) - count_deleted));
    int j =0;
    for(int i = 0; i < (*count_sentence); i++){
        if(sentences[i].self_number_in_text != 0){
            new_sentences[j++] = sentences[i];
            new_sentences[j-1].self_number_in_text = j;
        }
    }
    (*count_sentence) = (*count_sentence) - count_deleted;
    return new_sentences;
}

wchar_t** get_sentence(wchar_t* text, int i, int* count_words){
    wchar_t* ptr;
    wchar_t* sentence;
    if (i == 0) { 
        sentence = wcstok(text, L".", &ptr);
    }
    else {  
        sentence = wcstok(NULL, L".", &ptr);
    } 
    return validate_sentence(sentence, count_words);
}

wchar_t* get_structure_text(int* count_sentence, int* size){
    (*count_sentence) = 0;
    (*size) = 0;
    int capacity = 2, count_n = 0;
    wchar_t* text = (wchar_t*)malloc(sizeof(wchar_t) * capacity);
    wint_t letter = getwchar();

    while (count_n < 2){
        if (letter == '.') { (*count_sentence)++; }
        text[(*size) ++] = letter;

        if ((*size) >= capacity){
            capacity ++;
            wchar_t* check = (wchar_t*)realloc(text, sizeof(wchar_t) * capacity);

            if (check == NULL){
                wprintf(L"Error: not enought memory");
                exit(1);
            }

            text = check;
        }

        letter = getwchar();
        if (letter == '\n') { count_n++; }
        else { count_n = 0; }
    }

    text[(*size)] = '\0';
    return text;
}