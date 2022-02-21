#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

#include <stdio.h>

/*
 *               FILE IO
 *
 *   Purpose:
 *  
 *     An interface to provide functions that open and close files.
 *
 *   Errors: If a file is unable to be opened, it will print a message
 *          to standard error and the program will terminate
 *
 */

/* fileopen: Opens a file and returns a file pointer to it.
 * arguments: a char pointer to the filename
 */
FILE *fileopen(char *filename);

/* fileclose: Closes the file.
 * arguments: a File pointer from file open
 */
void fileclose(FILE *fp);


#endif
