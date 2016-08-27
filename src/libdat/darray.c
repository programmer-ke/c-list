#include <libdat/darray.h>
#include <assert.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
  DArray *array = malloc(sizeof(DArray));
  check_mem(array);
  array->max = initial_max;
  check(array->max > 0, "You must set an initial_max > 0.");

  array->contents = calloc(initial_max, sizeof(void *));;
  check_mem(array->contents);
  
  array->end = -1;
  array->element_size = element_size;
  array->expand_rate = DEFAULT_EXPAND_RATE;

  return array;
 error:
  if (array) free(array);
  return NULL;
}

void DArray_clear(DArray *array)
{
  int i = 0;
  if (array->element_size > 0) {
    for (i = 0; i < array->max; i++) {
      if (array->contents[i] != NULL) {
	free(array->contents[i]);
      }
    }
  }
}


// Resizes array->contents to newsize returning 0 on success
static inline int DArray_resize(DArray *array, size_t newsize) 
{
  array->max = newsize;
  check(array->max > 0, "The newsize must be > 0");
  
  void *contents = realloc(array->contents, array->max * sizeof(void *));
  
  check_mem(contents);
  
  array->contents = contents;

  return 0;
 error:
  return -1;
}

// expand array by its expand rate
int DArray_expand(DArray *array)
{
  size_t old_max = array->max;
  check(DArray_resize(array, array->max + array->expand_rate) == 0,
	"Failed to expand array to new size: %d",
	array->max + (int)array->expand_rate);

  // initialize the extra space with zeros
  memset(array->contents + old_max, 0, array->expand_rate + 1); // why expand-rate + 1?
  return 0;
 error:
  return -1;
}


int DArray_contract(DArray *array)
{
  int maxels = DArray_end(array) + 1; // max possible elements in array
  int new_size = maxels < (int)array->expand_rate ? (int)array->expand_rate : maxels;
  
  return DArray_resize(array, new_size + 1);
}

void DArray_destroy(DArray *array)
{
  if (array) {
    if (array->contents) free(array->contents);
    free(array);
  }
}


void DArray_clear_destroy(DArray *array)
{
  DArray_clear(array);
  DArray_destroy(array);
}

int DArray_push(DArray *array, void *el)
{
  // Expand array if necessary
  int nxt = DArray_end(array) + 1;
  if (nxt >= DArray_max(array)) {
    int rc = DArray_expand(array);
    check(rc == 0, "Failed to expand array");
  }
  
  array->contents[++array->end] = el;
  return 0;
  
  error:
  return -1;
}

void *DArray_pop(DArray *array)
{
  check(DArray_end(array) >  -1, "attempt to pop from empty array.");
  void *el = DArray_remove(array, array->end--);

  int maxels = DArray_end(array) + 1;
  if(maxels > (int)array->expand_rate && maxels % array->expand_rate) {
    DArray_contract(array);
  }

  return el;
 error:
  return NULL;
}
