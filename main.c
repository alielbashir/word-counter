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
Node *head; // first node
Node *tail; // last node

Node *getNode() {
    Node *node = (Node *) malloc(sizeof(Node));
    node->word = NULL;
    node->count = 0;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

//void addToMiddle(char *word, Node *node) {
//
//    // create node and populate it
//    Node *newNode = getNode();
//    newNode->word = word;
//    newNode->count++;
//
//}



void addToEnd(const char *word) {
    // handling for 1st node
    if (head->word == NULL) {
        // allocate space for word and copy it
        head->word = malloc(strlen(word) + 1);
        strcpy(head->word, word);
        // increment count and add tail pointer
        head->count++;
        head->next = tail;
    }
    // create and populate new node
    Node *node = getNode();
    node->word = malloc(strlen(word) + 1);
    strcpy(node->word, word);
    // increment count
    node->count ++;
    // add next and prev pointers, and set new node as tail
    node->prev = tail;
    tail->next = node;
    tail = node;
    printf("Added : %s\n", tail->word);
}

void add(const char* word) {
    // add as last element
    addToEnd(word);
}
void printList() {
    Node* node = head;
    while (node != NULL) {
        printf("%s : %d\n", node->word, node->count);
        node = node->next;
    }
}

void readToList(char *line) {
    char *word = NULL;
    word = strtok(line, " ");
    while (word != NULL) {
        add(word);
        word = strtok(NULL, " ");
    }
}


int main() {
    head = getNode();
    tail = head;
    FILE *fp = fopen("input.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp))
        readToList(line);
    fclose(fp);
    printList();

    return 0;
}