#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef valueType
#define valueType int
#endif
#ifndef UNSET
#define UNSET -1
#endif

typedef struct linkedListNode {
    struct linkedListNode* prev;
    valueType value;
    struct linkedListNode* next;
    } linkedListNode;

typedef struct linkedList {
    linkedListNode head;
    linkedListNode tail;
    int size;
    void (*add)(struct linkedList*, valueType);
    void (*insert)(struct linkedList*, valueType);
    valueType (*get)(struct linkedList*, int);
    valueType (*pop)(struct linkedList*);
    valueType (*remove)(struct linkedList*);
} linkedList;

void linkedListAdd(linkedList* list, valueType value) {
    if (list->tail.value == UNSET) {
        list->tail.value = value;
    } else if (list->head.value == UNSET && list->size == 1) {
        linkedListNode* newNode = (linkedListNode*)malloc(sizeof(linkedListNode));
        newNode->value = value;
        newNode->next = NULL;
        newNode->prev = &list->head;
        list->head.value = list->tail.value;
        list->tail = *newNode;
    } else {
        linkedListNode* newNode = (linkedListNode*)malloc(sizeof(linkedListNode));
        newNode->value = list->tail.value;
        newNode->next = &list->tail;
        newNode->prev = list->tail.prev;
        list->tail.prev->next = newNode;
        list->tail.prev = newNode;
        list->tail.value = value;
    }
    list->size++;
}
void linkedListInsert(linkedList* list, valueType value) {
    if (list->head.value == UNSET) {
        list->head.value = value;
    } else if (list->tail.value == UNSET && list->size == 1) {
        linkedListNode* newNode = (linkedListNode*)malloc(sizeof(linkedListNode));
        newNode->value = value;
        newNode->prev = NULL;
        newNode->next = &list->tail;
        list->tail.value = list->head.value;
        list->head = *newNode;
    } else {
        linkedListNode* newNode = (linkedListNode*)malloc(sizeof(linkedListNode));
        newNode->value = list->head.value;
        newNode->prev = &list->head;
        newNode->next = list->head.next;
        list->head.next->prev = newNode;
        list->head.next = newNode;
        list->head.value = value;
    }
    list->size++;
}
valueType linkedListGet(linkedList* list, int index) {
    if (index >= list->size) {
        perror("IndexError: List index out of range");
        exit(1);
    } else if (index <= ((list->size)/2)) {
        linkedListNode* working = &list->head;
        for (int i = 0; i < index; i++) {
            working = working->next;
        }
        return working->value;
    } else {
        linkedListNode* working = &list->tail;
        for (int i = 0; i < (list->size-index-1); i++) {
            working = working->prev;
        }
        return working->value;
    }
}
valueType linkedListPop(linkedList* list) {
    valueType toReturn = list->head.value;
    list->head = *list->head.next;
    list->head.next->prev = &list->head;
    list->size -= 1;
    return toReturn;
}
valueType linkedListRemove(linkedList* list) {
    valueType toReturn = list->tail.value;
    list->tail = *list->tail.prev;
    if (list->tail.prev != NULL) {
        list->tail.prev->next = &list->tail;
    }
    list->size -= 1;
    return toReturn;
}
linkedList initLinkedList() {
    linkedList list;
    list.head.prev = NULL;
    list.head.value = UNSET;
    list.head.next = &list.tail;
    list.tail.prev = &list.head;
    list.tail.value = UNSET;
    list.tail.next = NULL;
    list.size = 0;
    list.add = linkedListAdd;
    list.insert = linkedListInsert;
    list.get = linkedListGet;
    list.pop = linkedListPop;
    list.remove = linkedListRemove;
    return list;
}

#endif