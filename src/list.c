#include "list.h"
#include "dbg.h"

List *List_create()
{
  return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
  check(list != NULL, "List to be destroyed in NULL");
  check((list->count > 0 && list->first != NULL) || 
	(list->count == 0 && list->first == NULL), 
	"list count is incorrect");

  LIST_FOREACH(list, first, next, cur) {
    if (cur->prev) {
      free(cur->prev);
    }
  }

  free(list->last);
  free(list);
 error:
  return;
}

void List_clear(List *list)
{
  check(list != NULL, "List to be destroyed is NULL");
  check((list->count > 0 && list->first != NULL) || 
	(list->count == 0 && list->first == NULL), 
	"list count is incorrect");

  LIST_FOREACH(list, first, next, cur) {
    free(cur->value);
  }
 error:
  return;
}

void List_clear_destroy(List *list) 
{
  /*assertions*/
  check(list != NULL, "list to be destroyed is NULL");
  check((list->count > 0 && list->first != NULL) || 
	(list->count == 0 && list->first == NULL), 
	"list count is incorrect");
    
  LIST_FOREACH(list, first, next, cur) {
    if (cur->value) 
      free(cur->value); // but what if value is stack allocated.. undefined behaviour
    if (cur->prev)
      free(cur->prev);
  }
  
  if (list->last != NULL) {
    free(list->last);
  }
  
  free(list);
 error:
  return;
}

void List_push(List *list, void *value)
{
  check(list != NULL, "list to be modified is NULL");
  check((list->count > 0 && list->first != NULL) || 
	(list->count == 0 && list->first == NULL), 
	"list count is incorrect");

  ListNode *node = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;
  
  if (list->last == NULL) {
    list->first = node;
    list->last = node;
  } else {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }
  list->count++;
 error:
  return;
}

void *List_pop(List *list)
{
  check(list != NULL, "List to pop item from is NULL");
  ListNode *node = list->last;
  return node != NULL ? List_remove(list, node) : NULL;
 error:
  return NULL;
}

void List_unshift(List *list, void *value)
{
  check(list != NULL, "list to be unshifted is NULL");
  check((list->count > 0 && list->first != NULL) || 
	(list->count == 0 && list->first == NULL), 
	"list count is incorrect");

  ListNode *node = calloc(1, sizeof(ListNode));
  check_mem(node);
  
  node->value = value;
  
  if (list->first == NULL) {
    list->first = node;
    list->last = node;
  } else {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
  }
  list->count++;

 error:
  return;
}

void *List_shift(List *list)
{
  check(list != NULL, "List to be shifted is NULL");
  ListNode  *node = list->first;
  return node != NULL ? List_remove(list, node) : NULL;
 error:
  return NULL;
}

void *List_remove(List *list, ListNode *node)
{
  void *result = NULL;

  check(list != NULL, "list to be modified is NULL");
  check((list->count > 0 && list->first != NULL) || 
	(list->count == 0 && list->first == NULL), 
	"list count is incorrect");
  
  check(list->first && list->last, "List is empty.");
  check(node != NULL, "node can't be null");
  
  if (node == list->first && node == list->last) {
    // node to remove is only item in list
    list->first = NULL;
    list->last = NULL;
  } else if(node == list->first) {
    // node to remove is the first item
    list->first = node->next;
    check(list->first != NULL, "Invalid list, somehow got a node that is a NULL.");
    list->first->prev = NULL;
  } else if(node == list->last) {
    // node to remove is the last item
    list->last = node->prev;
    check(list->last != NULL, "Invalid list, somehow got a node that is a NULL.");
    list->last->next = NULL;
  } else {
    // node to remove is neither first nor last
    ListNode *after = node->next;
    ListNode *before = node->prev;
    after->prev = before;
    before->next = after;
  }

  list->count--;
  result = node->value;
  free(node);

  /*invariant*/
  check((list->count > 0 && list->first != NULL) || 
	(list->count == 0 && list->first == NULL && list->last == NULL),
	"list count is incorrect");

 error:
  return result;
}
