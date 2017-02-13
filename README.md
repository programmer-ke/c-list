# NAME

List_create, List_destroy, List_clear, List_clear_destroy, List_push, List_pop,
List_unshift, List_shift, List_remove - manipulation of a doubly linked list

# SYNOPSIS

\#include "list.h"

List *List_create()

void List_destroy(List *list)

void List_clear(List *list)

void List_clear_destroy(List *list)

void List_push(List *list, void *value)

void *List_pop(List *list)

void List_unshift(List *list, void *value)

void *List_shift(List *list)

void *List_remove(List *list, ListNode *node)

# DESCRIPTION

`list *list_create()` returns a pointer to a newly created list

`void list_destroy(list *list)` destroys the list and all nodes in it. ignores the
fact that the nodes may have values

`void list_clear(list *list)` clears the values of all nodes in the list

`void list_clear_destroy(list *list)` first clears the values in all the list 
nodes, then destroys the list and all its nodes

`void list_push(list *list, void *value)` creates a node at the end of the list 
and assigns value to it

`void *list_pop(list *list)` removes the last node in the list and returns its 
value

`void list_unshift(list *list, void *value)` creates a new node at the beginning 
of the list and gives it the specified value

`void *list_shift(list *list)` removes the first node if it exists and returns its
value

`void *list_remove(list *list, listnode *node)` removes the given node from the 
list and returns its value

The the list node structure is defined as:

     typedef struct ListNode {
       struct ListNode *next;
       struct ListNode *prev;
       void *value;
     } ListNode;

The structure of the list itself is:

     typedef struct List {
       int count;
       ListNode *first;
       ListNode *last;
     } List;
