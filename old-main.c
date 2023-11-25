#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#define END_STR "\0"

typedef struct {
    char* text;
    int count_sentence;
} Text;

typedef struct {
    char* text_sentence;
    int count_words;
    int len;
} Sentence;

char* read_text(int* count);
char* validate_sentence(char* str, int* count_words);
char* get_sentence(char* text, int i, int* count_words);
char** sep_to_words(char* sentence, int count_words);
int paint_words(char* word, int len);
    
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    printf("Course work for option 5.7, created by Ryabov Mikhail.\n");

    int choise;
    scanf("%d", &choise);

    Text text;
    text.text = read_text(&text.count_sentence);

    Sentence* sentences = (Sentence*)malloc(sizeof(Sentence) * text.count_sentence);
    if (sentences == NULL) { exit(1); }

    for (int i = 0; i < text.count_sentence; i++) {

        sentences[i].text_sentence = get_sentence(text.text, i, &sentences[i].count_words);
        sentences[i].len = strlen(sentences[i].text_sentence);

        printf("%s len: %d count words: %d\n\n", sentences[i].text_sentence, sentences[i].len, sentences[i].count_words);
    }
    free(sentences);
    return 0;
}

char* read_text(int * count) {
    (*count) = 0;
    int size = 0, capacity = 2;
    char* sentence = (char*)malloc(sizeof(char) * capacity);
    int count_n = 0;

    wchar_t letter = getwchar();

    while (count_n < 2) {
        if (letter == '.') { (*count)++; }
        sentence[size++] = letter;

        if (size >= capacity) {
            capacity++;
            char* temp = realloc(sentence, sizeof(char) * capacity);
            if (temp == NULL) {
                free(sentence);
                printf("Error\n");
                exit(1);
            }
            sentence = temp;
        }
        letter = getwchar();
        if (letter == '\n') { count_n++; }
        else { count_n = 0; }
    }

    sentence[size] = *END_STR;
    printf("\n%s\n", sentence);
    return sentence;
}

char* validate_sentence(char* str, int* count_words) {
    (*count_words) = 1;
    char* new_str = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    if (new_str == NULL) {exit(1);}

    int i = 0, j = 0;
    if (str[i] == '\n' || str[i] == '\t' || str[i] == ' ') { i = 1; }

    int len = strlen(str);
    for (;i < len; i++) {
        if (str[i] == '\n' || str[i] == '\t' || str[i] == ' ') {
            new_str[j++] = ' ';
            (*count_words)++;
        }
        else {
            new_str[j++] = str[i];
        }
    }

    new_str[j++] = '.';
    new_str[j] = '\0';
    return new_str;
}

char* get_sentence(char* text, int i, int* count_words) {
    int counter = 0;
    char sep[] = ".";
    if (i == 0) { 
        return validate_sentence(strtok(text, sep), count_words); 
    }
    else {  
        return validate_sentence(strtok(NULL, sep), count_words); }  
}

char** sep_to_words(char* sentence, int count_words) {
    char** arr_words = malloc(sizeof(char*) * count_words);
    
    char sep[] = " .";
    char* word = strtok(sentence, sep);

    int i = 0;
    while (word != NULL) {
        arr_words[i] = malloc(sizeof(char) * (strlen(word)));

        if (word[strlen(word) - 1] == ',') { word[strlen(word) - 1] = '\0'; }

        strcpy(arr_words[i], word);
        word = strtok(NULL, sep);

        i++;
    }
    return arr_words;
}

int paint_words(char* word, int len) {
    int result = len % 4;
    if (result == 0) {
        printf("\x1b[31m%s\x1b[0m ", word);
    }
    if (result == 1) {
        printf("\x1b[34m%s\x1b[0m ", word);
    }
    if (result == 2) {
        printf("\x1b[32m%s\x1b[0m ", word);
    }
    if (result == 3) {
        printf("\x1b[33m%s\x1b[0m ", word);
    }
    return 1;
}


