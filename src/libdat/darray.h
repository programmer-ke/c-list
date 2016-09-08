#ifndef _DArray_h
#define _DArray_h

#include <stdlib.h>
#include <assert.h>
#include <libdat/dbg.h>

typedef struct DArray {
  int end;  // index of last element in array
  int max;  // maximum length of array
  size_t element_size; // Used for creating elements via DArray_new
  size_t expand_rate;
  void **contents;
} DArray;

/*Returns a pointer to a Darray structure on the heap */
/* Initial size of `contents` will be 'void *' `initial_max` times */
DArray *DArray_create(size_t element_size, size_t initial_max);

void DArray_destroy(DArray *array);

void DArray_clear(DArray *array);

// Expand array by its expand rate
int DArray_expand(DArray *array);

// Contract to either last element, or expand rate size
// whichever is bigger
int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);

void *DArray_pop(DArray *array);

void DArray_clear_destroy(DArray *array);

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

// Insert el into array at position i
static inline void DArray_set(DArray *array, int i, void *el)
{
  check(i < array->max, "darray attempt to set past max");
  if (i > array->end) array->end = i;
  array->contents[i] = el;
 error:
  return;
}

// Returns a pointer to the element at position i
static inline void *DArray_get(DArray *array, int i)
{
  check(i < array->max, "darray attempt to get past max");
  return array->contents[i];
 error:
  return NULL;
}

// Returns pointer to element at posiion i, replacing it with NULL
static inline void *DArray_remove(DArray *array, int i)
{
  void *el = array->contents[i];
  array->contents[i] = NULL;
  return el;
}

// Returns a pointer to a blank space that fits the array's element
static inline void *DArray_new(DArray *array)
{
  check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.");
  return calloc(1, array->element_size);

 error:
  return NULL;
}

#define DArray_free(E) free((E))

#endif
