#ifndef SORTED_LINK_LIST
#define SORTED_LINK_LIST
#include <stdbool.h>


typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;

typedef enum {
    SUCCESS=0, 
    MEMORY_ERROR, 
    EMPTY_LIST, 
    UNSORTED_LIST, 
    NULL_ARGUMENT,
} ErrorCode;

/* Return value- the list length, counting the amount of nodes in the list */
/* Error values-  */
int getListLength(Node list);

/* Return valus- true or false if the list is Sorted in ascending order */
/* Error values-  */
bool isListSorted(Node list);

/* Return valus- */
/* Error values- */
ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut);

/* Return valus- */
/* Error values- */
void destroyList(Node list);

/* Return valus- */
/* Error values- */
Node createNode(int value);

/* Return valus- if list is NULL return new_node, else add new_node to the end of list and return pointer to the head of list */
/* Error values- null if create next node was failed*/
Node addNextNode (Node head, Node new_node);

/* Return valus- */
/* Error values- */
const int duplicate(int value);

/* Return valus- if list is NULL return new_node, else add new_node to the end of list and return pointer to the head of list */
/* Error values- */
int compareNodes(Node list1, Node list2);

/* Return valus- if list one of the lists is NULL mergedOut=NULL and return true */
/* Error values- */
bool cheackIflistsAreNull (Node list1, Node list2);

/* Return valus- if create return NULL mergedOut=NULL and return true */
/* Error values- */
bool cheackIfCreateReturnNUll (Node list);

#endif
