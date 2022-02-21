#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "bit2.h"
#include "assert.h"
#include "fileio.h"
#include "pnmrdr.h"
#include "except.h"

Bit2_T pbmread (FILE *fp);
void pbmwrite(FILE *outputfp, Bit2_T bitmap);

int main(int argc, char *argv[])
{
    /* error checking, expect 2 arguments from command line */
    assert(argc <= 2);

    FILE *fp = argc == 2 ? fileopen(argv[1]) : stdin;

    assert(fp != NULL);
    Bit2_T test = pbmread(fp);
    for (int i = 0; i < Bit2_height(test); i++) {
        for (int j = 0; j < Bit2_width(test); j++) {
            printf("%d ", Bit2_get(test, j, i));
        }
        printf("\n");
    }

    fileclose(fp);


    exit(EXIT_SUCCESS);
}

Bit2_T pbmread (FILE *fp)
{
    assert(fp != NULL);

    /* create the Pnmrdr_T rdr */
    Pnmrdr_T rdr = Pnmrdr_new(fp);
    Pnmrdr_mapdata data = Pnmrdr_data(rdr);
    
    /* check to make sure image is pbm */
    assert(data.type == Pnmrdr_bit);
    
    Bit2_T bit2 = Bit2_new(data.width, data.height);
    for (int i = 0; i < Bit2_height(bit2); i++) {
        for (int j = 0; j < Bit2_width(bit2); j++) {
            unsigned int curr = Pnmrdr_get(rdr);
            Bit2_put(bit2, j, i, curr);
        }
    }

    return bit2;

}


