#ifndef _UARRAY2_INCLUDED
#define _UARRAY2_INCLUDED
#define T UArray2_T
typedef struct T *T;

/*
 *               UArray2
 *
 *   Purpose:
 *  
 *     An interface for the UArray2, a 2 dimensional array modification
 *     of Hanson's UArray interface
 * 
 *
 */


/* Uarray2_new: Creates a new instance of a Uarray2.
 *   input: int width (must be non-negative)
 *          int height (must be non-negative)
 *          size_t elemsize (must be positive)
 *  output: A UArray2 instance with the corresponding height
 *          and width values, sets the elems paramter to a UArray
 *          with a length of height * width (elems will be an 
 *          empty UArray if either height or width = 0). The bytes
 *          in each element are initialized to 0.
 */
extern T UArray2_new(int width, int height, int elemsize);

/* Uarray2_free: Frees the memory of an instance of UArray2
 *   input: T *uarray2 (*uarray2 and uarray2 both must be non-null)
 *  output: None (clears and deallocates *uarray2)
 */
extern void UArray2_free(T *uarray2);

/* Uarray2_width: Returns the width of an instance of UArray2
 *   input: T uarray2 (must be non-null)
 *  output: A non-negative integer that represents the width of
 *          uarray2
 */
extern int UArray2_width(T uarray2);

/* Uarray2_height: Returns the height of an instance of UArray2
 *   input: T uarray2 (must be non-null)
 *  output: A non-negative integer that represents the height of
 *          uarray2
 */
extern int UArray2_height(T uarray2);

/* Uarray2_size: Returns the height of an instance of UArray2
 *   input: T uarray2 (must be non-null)
 *  output: A positive size_t that represents the size of the
 *          elements in uarray2
 */
extern int UArray2_size(T uarray2);

/* Uarray2_at: Returns a pointer to the element of an instance
               of UArray2 at (x, y)
 *   input: T uarray2 (must be non-null)
 *          int x (must be >= 0 and < width)
 *          int y (must be >= 0 and < height)
 *  output: A pointer to the element at (x, y) in uarray2
 */
extern void *UArray2_at(T uarray2, int col, int row);

/* Uarray2_map_row_major: Calls an apply function for each
 *                        element in an instance of UArray2 in
 *                        the row major order
 *   input: T uarray2 (must be non-null)
 *          void apply() (must be non-null)
 *          void *cl
 *  output: None (the apply function is called for each element
 *          of uarray2)
 */
extern void UArray2_map_row_major(T uarray2,
                                  void apply(int col, int row,
                                             UArray2_T uarray2,
                                             void *val, void *cl),
                                  void *cl);

/* Uarray2_map_col_major: Calls an apply function for each
 *                        element in an instance of UArray2 in
 *                        the column major order
 *   input: T uarray2 (must be non-null)
 *          void apply() (must be non-null)
 *          void *cl
 *  output: None (the apply function is called for each element
 *          of uarray2)
 */
extern void UArray2_map_col_major(T uarray2,
                                  void apply(int col, int row,
                                             UArray2_T uarray2,
                                             void *val, void *cl),
                                  void *cl);

#undef T
#endif