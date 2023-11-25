#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* t;
    int count_sentence;
    int size;
} Text;

typedef struct {
    char* text_sentence;
    int count_words;
    int len;
} Sentence;

char* get_text(int* count_sentence, int* size);
char* get_sentence(char* text, int i, int* count_words);
char* valid_sent(char* str, int* count_words);
char** sep_to_words(char* sentence, int count_words);
char* get_marks(char* sentence, int count_words);

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
    Sentence* sentences = (Sentence*)malloc(sizeof(Sentence) * text.count_sentence);
    
    for (int i = 0; i < text.count_sentence; i++){
        sentences[i].text_sentence = get_sentence(text.t, i, &sentences[i].count_words);
        sentences[i].len = strlen(sentences[i].text_sentence) + 1;
        printf("%s - %d words\n", sentences[i].text_sentence, sentences[i].count_words);
    }
    
    char* mark1 = get_marks(sentences[0].text_sentence, sentences[0].count_words);
    printf("\n%s\n", mark1);

    switch (choise){
        case 1:
            //раскраска слов
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
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

char* get_marks(char* sentence, int count_words){
    char* marks = (char*)malloc(sizeof(char) * (count_words * 2));
    int i = 0, size = 0;
    while (1){
        if (sentence[i] == '\0'){
            break;
        }
        if (sentence[i] == ' ' || sentence[i] == ',' || sentence[i] == '.'){
            marks[size++] = sentence[i];
        }
        i++;
    }
    marks[size] = '\0';
    return marks;
}