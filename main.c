#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 1024
struct List {
    char *word;
    int count;
    struct List *next;
};
typedef struct List Node;
Node *head; // first node
Node *tail; // last node

Node *getNode(const char *word, int count) {
    Node *node = malloc(sizeof(Node));
    node->word = malloc(strlen(word) + 1);
    strcpy(node->word, word);
    node->count = count;
    node->next = NULL;
    return node;
}

void printList() {
    Node *node = head;
    int i = 1;
    while (node != NULL) {
        printf("%d. %s: %d\n", i, node->word, node->count);
        node = node->next;
        i++;
    }
}

void destroyList() {
    // free all nodes in the list
    Node *node = head;
    Node *tmp;
    while (node != NULL) {
        tmp = node->next;
        free(node->word);
        free(node);
        node = tmp;
    }
}

int search(FILE *fp, const char *word) {
    // check if in list
    Node *node = head;
    // linear search for newWord
    while (node != NULL) {
        // if found return -1
        if (strcmp(node->word, word) == 0) {
            return 0;
        }
        node = node->next;
    }
    // if not in list count occurences in all of file
    char newWord[MAX_WORD];
    int count = 1;

    while (fscanf(fp, "%s", newWord) != EOF) {
        if (strcmp(newWord, word) == 0)
            count++;
    }
    return count;
}

void insertToMiddle(Node *node1, Node *node2) {
    // node1: node to be behind node2
    // node2: node to be inserted in front of node1
    node2->next = node1->next;
    node1->next = node2;
//    printf("Added : %s\n", node2->word);

}

void prepend(Node *node) {
    // adds node to beginning of list
    node->next = head;
    head = node;
}

void append(Node *node) {
    // adds node to end of list
    tail->next = node;
    tail = node;
}

void searchAndInsert(Node *nodeToInsert) {

    // optimizations for case of first or last node
    // if very first node
    if (head == NULL) {
        prepend(nodeToInsert);
        tail = head;
        return;
    }
    // if count bigger than head
    if (nodeToInsert->count > head->count) {
        prepend(nodeToInsert);
        return;
    }
    // if count lower than or equal to tail, or 2nd element to be added
    if (nodeToInsert->count <= tail->count || tail == head) {
        append(nodeToInsert);
        return;
    }

    // searches for equivalent count and adds word to its end
    Node *node = head;
    while (node->next != NULL) {
        if (node->next->count < nodeToInsert->count) {
            insertToMiddle(node, nodeToInsert);
            return;
        }
        node = node->next;
    }
}

int main() {
    int count;
    long cur;
    FILE *fp = fopen("input.txt", "r");
    char word[MAX_WORD];
    while (fscanf(fp, "%s", word) != EOF) {
        cur = ftell(fp);
        count = search(fp, word);

        if (count > 0) {
            Node *node = getNode(word, count);
            searchAndInsert(node);
            fseek(fp, cur, SEEK_SET);
        }
    }
    fclose(fp);
    printList();
    destroyList();
    return 0;
}
