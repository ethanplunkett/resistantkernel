#ifndef _SPREAD_H_
#define _SPREAD_H_
/*
** DESCRIPTION
** The function takes a spread value, the focal cell coordinates and
** two matrices (resistance and influence), executes the spread and
** returns the final snapshot of the spread into the resistance matrix
** which acts as a receiver of the output.
** If the function is successful it returns a positive value equal to the
** number of touched cells in the final snapshot otherwise it returns a
** negative number representing the error code
**
** ASSUMPTIONS:
** 1. spread_val >  0           ERR_BAD_SPREAD_VAL
** 2. row_focal  >= 1           ERR_BAD_ROW_FOCAL
** 3. col_focal  >= 1           ERR_BAD_COL_FOCAL
** 4. row_count  >  0           ERR_BAD_ROW_COUNT
** 5. col_count  >  0           ERR_BAD_COL_COUNT
** 6. resistance_matrix != NULL ERR_NULL_RESISTANCE_MATRIX
** Any negative value in the resistance matrix is considered as NO_DATA
**
** NOTES:
** a. the error code is the negative of the id of the violated assumption (see above)
** b. error codes of -100 and under (-101, -102 etc) represent internal 
**    errors or exceptions caught during execution
** c. the array allocation, deallocation and other memory management issues are the
**    responsability of the caller, no deallocation should occur before the return 
**    from the function (by another thread in the caller application for instance)
** d. once the caller does not need the spread routine anymore it should call
**    clean_up() to free internally used buffers.
** e. internally used bufffers are reallocated when the row / col counts change
**    therefore repeatedly changing the input data extents may decrease performance
**    due to reallocation costs
** f. row_focal and col_focal are expected to use a base value of 1 (that is the 
**    first row = first column = 1 ) conforming to APL and S+ standards
*/


extern "C"  void clean_up();


int spread(	double	spread_val,       /* bank account */
											int		row_focal,
											int		col_focal,
											int		row_count,        /* R */
											int		col_count,        /* C */
											double *resistance_matrix);/* R x C */


/* ERROR CODES */
#define ERR_BAD_SPREAD_VAL         -1
#define ERR_BAD_ROW_FOCAL          -2
#define ERR_BAD_COL_FOCAL          -3
#define ERR_BAD_ROW_COUNT          -4
#define ERR_BAD_COL_COUNT          -5
#define ERR_NULL_RESISTANCE_MATRIX -6

#endif
