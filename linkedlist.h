#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*  Node structure */
typedef struct Node {
    void* data;
    struct Node* prev;
    struct Node* next;
} Node;
/*  Linked list structure */
typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;
LinkedList* createLinkedList();
Node* createNode(void* data);
void insertFirst(LinkedList* list, void* data);
void insertLast(LinkedList* list, void* data);
void* removeFirst(LinkedList* list);
void* removeLast(LinkedList* list);
void* getElement(LinkedList* list, int index);
void display(LinkedList* list);
int getSize(LinkedList* list);
void clearData(LinkedList* list);
void freeList(LinkedList* list);

#endif
