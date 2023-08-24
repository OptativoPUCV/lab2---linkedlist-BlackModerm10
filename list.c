#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *newList = (List *)malloc(sizeof(List));
    if (newList) {
        newList->head = NULL;
        newList->tail = NULL;
        newList->current = NULL;
    }
    return newList;
}


void * firstList(List *list) {
    if (list && list->head) {
        list->current = list->head;
        return list->current->data;
    }
    return NULL;
}

void * nextList(List *list) {
    if (list && list->current && list->current->next) {
        list->current = list->current->next;
        return list->current->data;
    }
    return NULL;
}

void * lastList(List *list) {
    if (list && list->tail) {
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List *list) {
    if (list && list->current && list->current->prev) {
        list->current = list->current->prev;
        return list->current->data;
    }
    return NULL;
}

void pushFront(List *list, void *data) {
    if (list) {
        Node *newNode = createNode(data);
        if (newNode) {
            newNode->next = list->head;
            if (list->head) {
                list->head->prev = newNode;
            } else {
                list->tail = newNode;
            }
            list->head = newNode;
        }
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List *list, void *data) {
    if (list && list->current) {
        Node *newNode = createNode(data);
        if (newNode) {
            newNode->next = list->current->next;
            if (list->current->next) {
                list->current->next->prev = newNode;
            } else {
                list->tail = newNode;
            }
            newNode->prev = list->current;
            list->current->next = newNode;
        }
    }
}


void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void *popCurrent(List *list) {
    if (list && list->current) {
        void *data = list->current->data;
        Node *temp = list->current;
        
        if (list->current->prev) {
            list->current->prev->next = list->current->next;
        } else {
            list->head = list->current->next;
        }
        
        if (list->current->next) {
            list->current->next->prev = list->current->prev;
        } else {
            list->tail = list->current->prev;
        }
        
        list->current = list->current->next;
        free(temp);
        return data;
    }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}