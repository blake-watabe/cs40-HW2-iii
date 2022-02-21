/*
 *     fileio.c
 *     by Blake Watabe (bwatab01), Matt Sims (msims01)
 *     CS 40 HW1
 *     
 * 	   Summary: Helpful wrapper for file open and close functions.
 *              Allows for extra error checking/detail as necessary.
 */ 

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "fileio.h"


/* Takes a filename as a string and returns a file pointer pointing to
 * the open file (read-only) of the same name. Prints to stderr and exits if 
 * it can't open the file.
 */
FILE *fileopen(char *filename)
{
    FILE *fp = fopen(filename, "r");
        /* Error checking */
        assert(fp != NULL );
        return fp;
}

/* Closes the file, doesn't do anything else for now */
void fileclose(FILE *fp)
{
    fclose(fp);
}