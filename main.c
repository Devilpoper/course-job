#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char* t;
    int count_sentence;
    int size;
} Text;

typedef struct {
    char* text_sentence;
    int count_words;
    int len;
    int self_number_in_text;
} Sentence;

char* get_text(int* count_sentence, int* size);
char* get_sentence(char* text, int i, int* count_words);
char* valid_sent(char* str, int* count_words);
char** sep_to_words(char* sentence, int count_words);
char** get_marks(char* sentence, int count_words);

Sentence* get_structure_sentences(int count_sentence, char* text);
void print_word_with_cap(Sentence sen);
void delete_numbers(Sentence sen);
void paint_words(Sentence sen);

int main(){
    printf("Course work for option 5.7, created by Ryabov Mikhail.\n");

    int choise;
    scanf("%d", &choise);

    if (choise == 5){
        // Вывод справки о функциях
        exit(0);
    }

    Text text;
    text.t = get_text(&text.count_sentence, &text.size);   
    Sentence* sentences = get_structure_sentences(text.count_sentence, text.t);


    switch (choise){
        case 0:
            for (int i = 0; i < text.count_sentence; i++){
                if (sentences[i].len == 1){
                    continue;
                }
                printf("%s\n", sentences[i].text_sentence);
            }
            break;
        case 1:
            for (int i = 0; i < text.count_sentence; i++){
                if (sentences[i].len == 1){
                    continue;
                }
                paint_words(sentences[i]);
            }
            break;
        case 2:
            for (int i = 0; i < text.count_sentence; i++){
                if (sentences[i].len == 1){
                    continue;
                }
                print_word_with_cap(sentences[i]);
            }
            break;
        case 3:
            for (int i = 0; i < text.count_sentence; i++){
                if (sentences[i].len == 1){
                    continue;
                }
                print_word_with_cap(sentences[i]);
            }
            break;
        case 4:
            for (int i = 0; i < text.count_sentence; i++){
                if (sentences[i].len == 1){
                    continue;
                }
                delete_numbers(sentences[i]);
            }
            break;
        default:
            printf("Error: incorrect choise (choose 5 for view all options)");
    }
    return 0;
}

char* get_text(int* count_sentence, int* size){
    (*count_sentence) = 0;
    (*size) = 0;
    int capacity = 2, count_n = 0;
    char* text = (char*)malloc(sizeof(char) * capacity);
    char letter = getchar();

    while (count_n < 2){
        if (letter == '.') { (*count_sentence)++; }
        text[(*size) ++] = letter;

        if ((*size) >= capacity){
            capacity ++;
            char* check = (char*)realloc(text, sizeof(char) * capacity);

            if (check == NULL){
                printf("Error: not enought memory");
                exit(1);
            }

            text = check;
        }

        letter = getchar();
        if (letter == '\n') { count_n++; }
        else { count_n = 0; }
    }

    text[(*size)] = '\0';
    return text;
}

char* valid_sent(char* str, int* count_words){
    (*count_words) = 1;
    int len = strlen(str)+1;
    char* new_str = (char*)malloc(sizeof(char) * (len + 1));
    if (new_str == NULL) {
        printf("Error: not enought memory");
        exit(1);
    }

    int i = 0, j = 0;
    if (str[i] == '\n' || str[i] == '\t' || str[i] == ' ') { i = 1; }

    for (;i < len-1; i++) {
        if (str[i] == '\n' || str[i] == '\t' || str[i] == ' ') {
            new_str[j++] = ' ';
            (*count_words) ++;
        }
        else {
            new_str[j++] = str[i];
        }
    }

    new_str[j++] = '.';
    new_str[j] = '\0';
    return new_str;
}

char* get_sentence(char* text, int i, int* count_words){
    int counter = 0;
    char sep[] = ".";

    if (i == 0) { 
        return valid_sent(strtok(text, sep), count_words);
    }

    else {  
        return valid_sent(strtok(NULL, sep), count_words);
    } 
}

char** sep_to_words(char* sentence, int count_words) {
    char** arr_words = (char**)malloc(sizeof(char*) * count_words);
    
    char sep[] = " .";
    char* word = strtok(sentence, sep);

    int i = 0;
    while (word != NULL) {
        arr_words[i] = malloc(sizeof(char) * (strlen(word) + 1));

        if (word[strlen(word) - 1] == ',') { word[strlen(word) - 1] = '\0'; }

        strcpy(arr_words[i], word);
        word = strtok(NULL, sep);

        i++;
    }
    return arr_words;
}

char** get_marks(char* sentence, int count_words){
    char** marks = (char**)malloc(sizeof(char*) * (count_words));
    int i = 0, size = 0;

    while (sentence[i] != '\0'){
        if (sentence[i] == ' ' || sentence[i] == '.'){
            marks[size] = (char*)malloc(sizeof(char)*2);
            marks[size][0] = sentence[i];
            marks[size++][1] = '\0';
        }

        if (sentence[i] == ','){
            marks[size] = (char*)malloc(sizeof(char)*3);
            marks[size][0] = sentence[i];
            marks[size][1] = ' ';
            marks[size++][2] = '\0';
            i++;
        }

        i++;
    }

    marks[size] = '\0';
    return marks;
}

void paint_words(Sentence sen){
    char** marks = get_marks(sen.text_sentence, sen.count_words);
    char** words = sep_to_words(sen.text_sentence, sen.count_words);

    for (int i = 0; i < sen.count_words; i++){
        int result = strlen(words[i]) % 4;
        if (result == 0) {
            printf("\x1b[31m%s\x1b[0m%s", words[i], marks[i]);
        }
        if (result == 1) {
            printf("\x1b[34m%s\x1b[0m%s", words[i], marks[i]);
        }
        if (result == 2) {
            printf("\x1b[32m%s\x1b[0m%s", words[i], marks[i]);
        }
        if (result == 3) {
            printf("\x1b[33m%s\x1b[0m%s", words[i], marks[i]);
        }
    }
    printf("\n");
}

Sentence* get_structure_sentences(int count_sentence, char* text){
    Sentence* sentences = (Sentence*)malloc(sizeof(Sentence) * count_sentence);
    char* null_ptr = (char*)malloc(sizeof(char));
    null_ptr[0] = '\0';

    for (int i = 0; i < count_sentence; i++){
        sentences[i].self_number_in_text = i+1;
        sentences[i].text_sentence = get_sentence(text, i, &sentences[i].count_words);
        sentences[i].len = strlen(sentences[i].text_sentence) + 1;
    }

    for( int i = 0; i < count_sentence; i++){
        for (int j = i+1; j < count_sentence; j++){
            if(strcasecmp(sentences[i].text_sentence, sentences[j].text_sentence) == 0){
                sentences[j].text_sentence = null_ptr;
                sentences[j].len = 1;
            }
        }
    }
    return sentences;
}

void print_word_with_cap(Sentence sen){
    char** words = sep_to_words(sen.text_sentence, sen.count_words);
    for (int i = 0; i < sen.count_words; i++){
        int end = strlen(words[i]);
        if (isupper(words[i][0]) && isupper(words[i][end-1])){
            printf("%s number sentense - %d\n", words[i], sen.self_number_in_text);
        }
    }
}

void delete_numbers(Sentence sen){
    char** marks = get_marks(sen.text_sentence, sen.count_words);
    char** words = sep_to_words(sen.text_sentence, sen.count_words);
    
    for (int i = 0; i < sen.count_words; i++){
        if (strtol(words[i], NULL, 10) == 0){
            printf("%s%s", words[i], marks[i]);
        }
    }
    printf("\n");
}