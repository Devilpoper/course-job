#pragma once

typedef struct {
    wchar_t* t;
    int count_sentence;
    int size;
} Text;

typedef struct {
    wchar_t** text_sentence;
    wchar_t** punct_sentence;
    int count_words;
    int len;
    int self_number_in_text;
    int last_word;
} Sentence;

Sentence* get_structure_sentences(int *count_sentence, wchar_t* text);
wchar_t** get_sentence(wchar_t* text, int i, int *count_words);
wchar_t* get_structure_text(int* count_sentence, int* size);
wchar_t* get_first_str();
