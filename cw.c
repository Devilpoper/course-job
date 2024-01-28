#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wctype.h>

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
wchar_t** validate_sentence(wchar_t* sentence, int* count);
wchar_t* wcdup_with_symb(wchar_t* word, wchar_t symb);
wchar_t** get_sentence(wchar_t* text, int i, int *count_words);
void sort_by_last(Sentence* sentences, int count_sentence);
int compare(const void* a, const void* b);
wchar_t* get_structure_text(int* count_sentence, int* size);
void print_word_with_cap(Sentence sen);
void input_choise(wchar_t choise);
void output_sentense(wchar_t** arr_words, int size);
void paint_words(Sentence sent);
void delete_numbers(Sentence sent);

int main(){
    setlocale(LC_ALL, "ru_RU.utf8");
    wprintf(L"Course work for option 5.7, created by Ryabov Mikhail.\n");

    wint_t choise = getwchar();
    wchar_t stub = getwchar();
    input_choise(choise);
    
    return 0;
}

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
    if (wcstol(&choise, NULL, 10) >= 5 || wcstol(&choise, NULL, 10) < 0 || iswdigit(choise) == 0){
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

wchar_t** validate_sentence(wchar_t* sentence, int *count_words){
    int capacity = 1, size = 0;
    wchar_t** arr_words = (wchar_t**)malloc(sizeof(wchar_t*) * capacity);

    wchar_t* ptr;
    wchar_t* sep_word = wcstok(sentence, L" ", &ptr);

    while (sep_word != NULL){
        if (wcslen(sep_word) == 1 && (iswalpha(sep_word[0]) == 0 && iswdigit(sep_word[0]) == 0)){
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
        sep_word = wcstok(NULL, L" ", &ptr);
    }
    (*count_words) = size;
    return arr_words;
}

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