#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO:
//    1. arayip_ekle() fonksiyonu yaz
//    2. araya_ekle() fonksiyonu yaz
struct List {
    char *word;
    int count;
    struct List *next, *prev;

};
typedef struct List Node;


Node *getNode() {
    Node *node = (Node *) malloc(sizeof(Node));
    node->count = 0;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void addToMiddle(char *word, Node *node) {

    // create node and populate it
    Node *newNode = getNode();
    newNode->word = word;
    newNode->count++;

}

_Noreturn void addToBeginning(char *word, Node *node) {
    // word: kelime
    // node: listede herhangi bir node

    // ilk elemani arama islemi
    while (1) {
        if (node->prev == NULL) {
            // yeni nodeu tanimla ve doldur
            Node *newNode = getNode();
            newNode->word = word;
            newNode->count++;
            newNode->next = node;
            // yeni node, ilk nodeun sonuna ekle
            node->prev = newNode;
        }
        node = node->prev;
    }
}

void append(char *word, Node *node) {
    node->word = word;
    Node *tmp = getNode();
    tmp->prev = node;
    node->next = tmp;
    printf("Added : %s\n", node->word);
    // FIXME: orphaned
    node = node->next;
}


void printList(Node *root) {

}

void readToList(char *line, Node *node) {
    char *word = NULL;
    word = strtok(line, " ");
    printf("\nı\n");
    while (word != NULL) {
        append(word, node);
        word = strtok(NULL, " ");
    }
}


int main() {
    Node *head = getNode();
    Node *iter = head;
    FILE *fp = fopen("input.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp))
        readToList(line, iter);
    fclose(fp);

    return 0;
}