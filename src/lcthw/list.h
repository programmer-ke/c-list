#ifndef _lcthw_List_h
#define _lcthw_List_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
  struct ListNode *next;
  struct ListNode *prev;
  void *value;
} ListNode;

typedef struct List {
  int count;
  ListNode *first;
  ListNode *last;
} List;

/* Returns a pointer to a newly created list*/
List *List_create();

/*Destroys the list and all nodes in it. Ignores the fact that the nodes may have values*/
void List_destroy(List *list);

/*Clears the values of all nodes in the list */
void List_clear(List *list);

/*Clears the values in all the list nodes then destroys the list
 and all it's nodes*/
void List_clear_destroy(List *list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

/*Creates a node at the end of the list and assigns value to it*/
void List_push(List *list, void *value);

/*Removes the last node in the list and returns its value*/
void *List_pop(List *list);

/*Creates a new node at the beginning of the list and gives it the specified value */
void List_unshift(List *list, void *value);

/*Removes the first node if it exists and returns its value*/
void *List_shift(List *list);

/*Removes the given node from the list and returns its value*/
void *List_remove(List *list, ListNode *node);

/*Macro to iterate from first to last element in the list*/
#define LIST_FOREACH(L, S, M, V)				\
  ListNode *_node = NULL;					\
  ListNode *V = NULL;						\
  for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
