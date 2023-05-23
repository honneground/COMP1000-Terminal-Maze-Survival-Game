#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/*  Function to create a new linked list instance */
LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/*  Function to create a new node */
Node* createNode(void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/*  Function to insert a node at the beginning of the list */
void insertFirst(LinkedList* list, void* data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    list->size++;
}

/*  Function to insert a node at the end of the list */
void insertLast(LinkedList* list, void* data) {
    Node* newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

/*  Function to remove the first node from the list and return the pointer to the data */
void* removeFirst(LinkedList* list) {
    Node* firstNode;
    void* data;
    if (list->size == 0) {
        return NULL; /*  Empty list, nothing to remove */
    }

    firstNode = list->head;
    data = firstNode->data;

    if (list->size == 1) {
        /*  Only one node in the list */
        list->head = list->tail = NULL;
    } else {
        list->head = firstNode->next;
        list->head->prev = NULL;
    }

    free(firstNode);
    list->size--;
    return data;
}

/*  Function to remove the last node from the list and return the pointer to the data */
void* removeLast(LinkedList* list) {
    Node* lastNode;
    void* data;
   if (list->size == 0) {
        return NULL; /*  Empty list, nothing to remove */
    }

    lastNode = list->tail;
    data = lastNode->data;

    if (list->size == 1) {
        /*  Only one node in the list */
        list->head = list->tail = NULL;
    } else {
        list->tail = lastNode->prev;
        list->tail->next = NULL;
    }

    free(lastNode);
    list->size--;
    return data;
}
/*  Get the pointer to the data at element of given index */
void* getElement(LinkedList* list, int index) {
    Node* current = list->head;
    if (index < 0 || index >= list->size) {
        return NULL; /*  Invalid index */
    }
    while (index > 0) {
        current = current->next;
        index--;
    }

    return current->data;
}

/*  Function to display the list. */
void display(LinkedList* list) {
    Node* current = list->head;
    if (list->size == 0) {
        printf("[]\n");
        return;
    }

    printf("[");
    while (current != NULL) {
        printf("%d", *(int*)(current->data));
        current = current->next;
        if (current != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

/* Get linked list size */
int getSize(LinkedList* list) {
    return list->size;
}

/*  Shortcunt function to free the memory allocated to the list nodes data field (if data sorted by malloc or calloc) */
void clearData(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        free(current->data);/* Free the memory allocated for the data */
        current->data = NULL;/* Set the data pointer to NULL */
        current = current->next;
    }
}

/*  Function to free the memory allocated to the list */
void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
    list = NULL;
}
