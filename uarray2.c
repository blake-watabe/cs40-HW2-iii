#include "uarray2.h"
#include "uarray.h"
#include "assert.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

#define T UArray2_T


/* WRITE THE CONTRACT FOR UARRAY2 */
struct T {
    int width; /* the number of elements in each row */
    int height; /* the mumber of elements in each column */
    UArray_T elems; /* A uarray */
};

T UArray2_new(int width, int height, int elemsize)
{
    /* construct UArray2 */
    T uarray2;
    NEW(uarray2);

    /* non negative dimension error check */
    assert(width >= 0);
    assert(height >= 0);
    assert(elemsize > 0);

    uarray2->width = width;
    uarray2->height = height;
    uarray2->elems = UArray_new((width * height), elemsize);

    return uarray2;

}
void UArray2_free(T *uarray2)
{
    assert((uarray2 != NULL) && (*uarray2 != NULL));
    UArray_free(&((*uarray2)->elems));
    FREE(*uarray2);
}

int UArray2_width(T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->width;
}

int UArray2_height(T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->height;
}

int UArray2_size(T uarray2)
{
    assert(uarray2 != NULL);
    return UArray_size(uarray2->elems);
}

void *UArray2_at(T uarray2, int col, int row)
{
    assert(uarray2 != NULL);
    assert((row >= 0) && (row < uarray2->height));
    assert((col >= 0) && (col < uarray2->width));
    return UArray_at(uarray2->elems, (col + (uarray2->width * row)));
}

void UArray2_map_row_major(T uarray2,
                           void apply(int col, int row, UArray2_T uarray2,
                                      void *val, void *cl),
                           void *cl)
{
    assert(uarray2 != NULL);
    assert(apply != NULL);

    
    for (int i = 0; i < uarray2->height; i++) {
        for (int j = 0; j < uarray2->width; j++) {
            apply(j, i, uarray2, UArray2_at(uarray2, j, i), cl);
        }
    }
}

void UArray2_map_col_major(T uarray2,
                           void apply(int col, int row, UArray2_T uarray2,
                                      void *val, void *cl),
                           void *cl)
{
    assert(uarray2 != NULL);
    assert(apply != NULL);
    
    for (int i = 0; i < uarray2->width; i++) {
        for (int j = 0; j < uarray2->height; j++) {
            apply(i, j, uarray2, UArray2_at(uarray2, i, j), cl);
        }
    }
}
