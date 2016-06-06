#include <libdat/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
  qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
  return 0;
}

/*seem to not exit in stdlib, will write own implementation
int DArray_heapsort(DArray *array, DArray_compare cmp)
{
  return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
  return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}
*/
