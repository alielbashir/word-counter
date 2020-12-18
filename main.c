#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct List {
    char *word;
    int count;
    struct List *next, *prev;

};
typedef struct List Node;
Node *head; // first node
Node *tail; // last node

Node *getNode() {
    Node *node = malloc(sizeof(Node));
    node->word = NULL;
    node->count = 0;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void extract(Node *node) {
    // removes node from current position, connecting its previous and next elements
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = NULL;
    node->prev = NULL;
}

void insert(Node *node1, Node *node2) {
    // node1: node to be inserted behind node2
    // node2: node to be in front of node1
    node2->prev->next = node1;
    node1->prev = node2->prev;

    node1->next = node2;
    node2->prev = node1;
}

void addToMiddle(Node *node) {

    // increment word count
    node->count++;
    Node *tmp = node->prev;
    // if the node is the head then don't do anything. It is a 2 element list
    if (node == head) {
        return;
    }
    // iterate if tmp's count is lower than node's
    while (tmp->count < node->count) {
        // if tmp's previous node's count is larger than or equal to node's count
        if (tmp->prev->count >= node->count) {
            extract(node); // remove node from where it was, while connecting it's previous and next elements
            insert(node, tmp); // insert node behind tmp
            break;
        }
        tmp = tmp->prev;
    }
//    printf("incremented : %s\n", node->word);

}


void addToBeginning(const char *word) {

    // allocate space for word and copy it
    head->word = malloc(strlen(word) + 1);
    strcpy(head->word, word);
    // increment count and add tail pointer
    head->count++;
    head->next = tail;
//    printf("Added : %s\n", head->word);
}

void addToEnd(const char *word) {

    // create and populate new node
    Node *node = getNode();
    node->word = malloc(strlen(word) + 1);
    strcpy(node->word, word);
    // increment count
    node->count++;
    // add next and prev pointers, and set new node as tail
    node->prev = tail;
    tail->next = node;
    tail = node;
//    printf("Added : %s\n", tail->word);
}

bool searchAndAdd(const char *word) {
    Node *node = head;
    bool b = false;
    // linear search for word
    while (node != NULL) {
        // if found
        if (strcmp(node->word, word) == 0) {
            addToMiddle(node);
            return b = true;
        }
        if (node == node->next) {
            break;
        }
        node = node->next;
    }
    return b;
}

void add(const char *word) {
    // handling for 1st node
    if (head->word == NULL) {
        addToBeginning(word);
    } else if (searchAndAdd(word)) {
        // do nothing, function side effects handle that
    } else {
        // add as last element
        addToEnd(word);
    }
}

void printList() {
    Node *node = head;
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

int main() {
    head = getNode();
    tail = head;
    FILE *fp = fopen("input.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp))
        readToList(line);
    fclose(fp);
    printList();
    destroyList();
    return 0;
}
