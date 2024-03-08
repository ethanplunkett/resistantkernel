#include "_spread.h"
#include "spread.h"
#include "Matrix.h"
#include "ConnRoamer.h"

 
/*
** Internally used variables
** ----------------------------------------------------------------------------
*/
double *wrk_buf			= NULL;
int		last_row_count	= -1;
int		last_col_count	= -1;

 
/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	This function allocates a matrix of doubles to be used for the spreading
**	process every time the size changes in terms of rows and columns.
**	When reallocating the old storage is released.
**	This function is for internal use only.
===============================================================================
*/
double *_reset_buf(int row_count, int col_count)
{
	if((wrk_buf == NULL) || (last_row_count != row_count) || (last_col_count != col_count))
	{
		last_row_count = row_count;
		last_col_count = col_count;

		delete[] wrk_buf;

		wrk_buf = new double[row_count * col_count];



	};

	CMatrix tmp_mtx(wrk_buf, row_count, col_count);
	tmp_mtx.fill(0);

	return wrk_buf;
};






/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	Does a connectedness style spread and returns the result in the
**	resistance_matrix
**	This function is exported for use from APL
===============================================================================
*/
int spread(	double	spread_val,       /* bank account */
			int		row_focal,
			int		col_focal,
			int		row_count,        /* R */
			int		col_count,        /* C */
			double *resistance_matrix) /* R x C */
{
	/* verify assumptions */
	if(spread_val <= 0)           return ERR_BAD_SPREAD_VAL        ;
	if(row_focal  <  1)           return ERR_BAD_ROW_FOCAL         ;
	if(col_focal  <  1)           return ERR_BAD_COL_FOCAL         ;
	if(row_count  <= 0)           return ERR_BAD_ROW_COUNT         ;
	if(col_count  <= 0)           return ERR_BAD_COL_COUNT         ;
	if(resistance_matrix == NULL) return ERR_NULL_RESISTANCE_MATRIX;

	/*
	** APL uses an array index base of one so we need to 
	** do a small correction here (re-basing)
	*/
	row_focal -= 1; /* re-base to zero */
	col_focal -= 1; /* re-base to zero */

	/* re-init the work buffer */
	_reset_buf(row_count, col_count);

	/* buid the needed wrapper objects */
	CMatrix res_mtx(resistance_matrix, row_count, col_count);
	CMatrix wrk_mtx(wrk_buf,           row_count, col_count);
	CConnRoamer roamer(wrk_mtx, res_mtx, spread_val);

	/* -------------------------------------------------- */
//	std::string msg = str(boost::format("spread(%f, %d, %d, %d, %d, %X) : M(%d, %d)->%.20f, H[%d]")
//											% spread_val
//											% row_focal
//											% col_focal
//											% row_count
//											% col_count
//											% resistance_matrix
//											% 0
//											% 0
//											% res_mtx(0, 0)
//											% res_mtx.homogeneity());
//	OutputDebugString(msg.c_str());
	/* -------------------------------------------------- */

	/* spread around */
	roamer.Spread(row_focal, col_focal);

	/*
	** copy the resulting spread back into the resistence matrix
	** and return the count of non-zero cells
	*/
	return res_mtx.copy(wrk_mtx);
};
 
/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	Frees the work buffer and reinitializes the internal variables.
**	This function is exported for use from APL
===============================================================================
*/
void clean_up()
{
	delete[] wrk_buf;

	/* re-init everything just in case */
	wrk_buf			= NULL;
	last_row_count	= -1;
	last_col_count	= -1;
}
