#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* Test case for linked list */
int main() {
    /* Data for testing */
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    /* Received data pointer */
    void* removedData;
    LinkedList* list = createLinkedList();
    printf("Insert 1 to the list end\n");
    insertLast(list, &data1);  
    printf("Insert 2 to the list front\n");
    insertFirst(list, &data2);
    printf("Insert 3 to the list end\n");
    insertLast(list, &data3);
    printf("Insert 5 to the list front\n");
    insertFirst(list, &data5);   
    printf("Insert 4 to the list end\n");
    insertLast(list, &data4);
    printf("The size of the linked list is %d\n", getSize(list));
    printf("Current list: ");
    display(list);
    removedData = removeLast(list);
    printf("Removed last value: %d\n", *(int*)removedData);
    printf("Current list: ");
    display(list);
    removedData = removeFirst(list);
    printf("Removed first value: %d\n", *(int*)removedData);
    printf("Current list: ");
    display(list);
    printf("The size of the linked list is %d\n", getSize(list));
    printf("The 1st value: %d\n", *(int*)getElement(list, 0));
    printf("The 2nd value: %d\n", *(int*)getElement(list, 1));
    printf("The 3rd value: %d\n", *(int*)getElement(list, 2));
    printf("The last value: %d\n", *(int*)getElement(list, getSize(list)-1));
    removedData = removeLast(list);
    printf("Removed last value: %d\n", *(int*)removedData);
    printf("Current list: ");
    display(list); 
    removedData = removeFirst(list);
    printf("Removed first value: %d\n", *(int*)removedData);
    printf("Current list: ");
    display(list);
    removedData = removeLast(list);
    printf("Removed last value: %d\n", *(int*)removedData);
    printf("Current list: ");
    display(list);
    printf("Attempt to remove an element from the empty list by calling the remove first function to see the robustness of the linked list.\n");
    removedData = removeFirst(list);
    printf("Current list: ");
    display(list);
    printf("The size of the linked list is %d\n", getSize(list));
    printf("Insert 1 to the list end\n");
    insertLast(list, &data1); 
    printf("The size of the linked list is %d\n", getSize(list));
    printf("Current list: ");
    display(list);
    freeList(list);
    printf("Free up the memory allocated for the linked list and its' node(s).\n");
    return 0;
}
