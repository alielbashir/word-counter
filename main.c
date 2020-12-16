#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO:
//    1. bagli liste struct'ini hazirla
//    2. metni_oku() fonksiyonu yaz. metnini okuyup bagli listeye koyuyor
//    3. arayip_ekle() fonksiyonu yaz
//    4. basa_ekle() fonksiyonu yaz
//    5. araya_ekle() fonksiyonu yaz
//    6. sona_ekle() fonksiyonu yaz
struct List {
    char *word;
    int count;
    struct List *next,*prev;

};
typedef struct List Node;
Node *head;


void append(char *word) {
    head->word = word;
    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->next = NULL;
    tmp->prev=head;
    head->next = tmp;
    printf("Added : %s\n", head->word);
    head = head->next;
}

void readToList(char *line) {
    char *word = NULL;
    word = strtok(line, " ");
    while (word != NULL) {
        append(word);
        word = strtok(NULL, " ");
    }
}

int main() {
    Node * iter;
    head = (Node *) malloc(sizeof(Node));
    head->next = NULL;
    head = head;
    FILE *fp = fopen("input.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp))
        readToList(line);
    fclose(fp);
    getch();

    return 0;
}