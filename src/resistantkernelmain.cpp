#include "_spread.h"
#include "spread.h"
#include "Matrix.h"
#include "ConnRoamer.h"

/*
 *  spreadmain.cpp
 *  
 *  Created by Ethan Plunkett on 1/21/09.
 *
 */



/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	C wrapper function for calling from R as per R's requirements all
**	arguments are pointers.  The resistance matrix is replaced with the result.
===============================================================================
*/

extern "C" { 
void rspread( double *spread_val,
			 int	*row_focal,
			 int	*col_focal,
			 int	*row_count,        /* R */
			 int	*col_count,        /* C */
			 double *resistance_matrix,
			 int *error_code,
       int *symmetrical
			 )/* R x C */
{
	*error_code = spread( *spread_val,
						 *row_focal,
						 *col_focal,
						 *row_count,        /* R */
						 *col_count,        /* C */
						 resistance_matrix,
						 *symmetrical);
}
} // extern "C"
