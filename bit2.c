#include "assert.h"
#include "bit2.h"
#include "mem.h"
#include "bit.h"
#include <stdio.h>
#include <stdlib.h>

#define T Bit2_T


struct T {
    int width;
    int height;
    Bit_T elems; /* A uarray */
};

T Bit2_new(int width, int height)
{
    /* construct UArray2 */
    T bit2;
    NEW(bit2);

    assert(height >= 0);
    assert(width >= 0);

    bit2->width = width;
    bit2->height = height;
    bit2->elems = Bit_new(width * height);

    return bit2;
}

void Bit2_free(T *bit2)
{
    assert((bit2 != NULL) && (*bit2 != NULL));
    Bit_free(&((*bit2)->elems));
    FREE(*bit2);
}

int Bit2_width(T bit2)
{
    assert(bit2 != NULL);
    return bit2->width;
}

int Bit2_height(T bit2)
{
    assert(bit2 != NULL);
    return bit2->height;
}

int Bit2_put(T bit2, int col, int row, int bit)
{
    assert(bit2 != NULL);
    assert((col >= 0) && (col < bit2->width));
    assert((row >= 0) && (row < bit2->height));
    assert((bit == 0) || (bit == 1)); // ASK TA?????????????

    return Bit_put(bit2->elems, (col + (bit2->width * row)), bit);
}

int Bit2_get(T bit2, int col, int row)
{
    assert(bit2 != NULL);
    assert((col >= 0) && (col < bit2->width));
    assert((row >= 0) && (row < bit2->height));

    return Bit_get(bit2->elems, (col + (bit2->width * row)));
}

extern void Bit2_map_col_major(T bit2,
                               void apply(int col, int row, T bit2,
                                          int bit, void *cl),
                               void *cl)
{
    assert(bit2 != NULL);
    assert(apply != NULL);

    for (int i = 0; i < bit2->width; i++) {
        for (int j = 0; j < bit2->height; j++) {
            apply(i, j, bit2, Bit2_get(bit2, i, j), cl);
        }
    }
}

extern void Bit2_map_row_major(T bit2,
                               void apply(int col, int row, T bit2,
                                          int bit, void *cl),
                               void *cl)
{
    assert(bit2 != NULL);
    assert(apply != NULL);

    for (int i = 0; i < bit2->height; i++) {
        for (int j = 0; j < bit2->width; j++) {
            apply(j, i, bit2, Bit2_get(bit2, j, i), cl);
        }
    }
}