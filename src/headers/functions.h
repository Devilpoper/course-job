#pragma once
#include "structures.h"

void sort_by_last(Sentence* sentences, int count_sentence);
int compare(const void* a, const void* b);
void print_word_with_cap(Sentence sen);
void paint_words(Sentence sent);
void delete_numbers(Sentence sent); 
void replace_words(Sentence sen, wchar_t* word_x, wchar_t* word_y);