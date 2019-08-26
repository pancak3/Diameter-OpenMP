#include <stdio.h>
#include <stdlib.h>
#include "search.h"

int values[] = {88, 56, 100, 2, 25};

int cmpfunc(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

int compare(int *x, int *y)
{
    return (*x - *y);
}
int main() {
    int n;

    printf("Before sorting the list is: \n");
    for (n = 0; n < 5; n++) {
        printf("%d ", values[n]);
    }

    qsort(values, 5, sizeof(int), cmpfunc);

    printf("\nAfter sorting the list is: \n");
    for (n = 0; n < 5; n++) {
        printf("%d \n", values[n]);
    }
    int array[5] = {44, 69, 3, 17, 23};
    size_t elems = 5;
    int key = 69;
    int *result;
    result = (int *) lfind(&key, &array, &elems, sizeof(int), (int (*)(const void *, const void *)) compare);
    if (result)
        printf("Key %d found in linear search, res is %d\n", key,*result);
    else
        printf("Key %d not found in linear search\n", key);
    return (0);
}