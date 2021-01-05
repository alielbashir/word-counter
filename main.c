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
    Node *node = head;
    // linear search for newWord
    while (node != NULL) {
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

void insert(Node *node1, Node *node2) {
    // node1: node to be behind node2
    // node2: node to be inserted in front of node1
    node2->next = node1->next;
    node1->next = node2;
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

void searchAndInsert(Node *node) {

    // optimizations for case of first or last node
    {
        if (head == NULL) {
            prepend(node);
            tail = head;
            return;
        }

        if (node->count > head->count) {
            prepend(node);
            return;
        }

        if (node->count <= tail->count || tail == head) {
            append(node);
            return;
        }
    }

    Node *tmpNode = head;
    while (tmpNode->next != NULL) {
        if (tmpNode->next->count < node->count) {
            insert(tmpNode, node);
            return;
        }
        tmpNode = tmpNode->next;
    }
}

int main() {
    int count;
    long cursor;
    char word[MAX_WORD];

    FILE *fp = fopen("input.txt", "r");
    while (fscanf(fp, "%s", word) != EOF) {
        cursor = ftell(fp);
        count = search(fp, word);

        if (count > 0) {
            Node *node = getNode(word, count);
            searchAndInsert(node);
            fseek(fp, cursor, SEEK_SET);
        }
    }
    fclose(fp);

    printList();
    destroyList();
    return 0;
}
