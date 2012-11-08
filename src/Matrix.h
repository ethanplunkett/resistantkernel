/*BGN::ERB_DEFINITION <%= get_block('..\spread\_spread.h', 'FILE_INFO') %> */
// This file is part of the spread library.
// Historically this algorithm has started life as a way to measure connectedness in CAPS
// (aka Conservation Assessment and Prioritization System), a software package conceived at
// the University of Massachusetts by Brad Compton, Kevin Mcgarigal and Eduard Ene, and 
// implemented in C++ by Eduard Ene.
// It has then been extracted and converted into a DLL for use from within APL by Eduard Ene
// Ethan Plunkett has adapted the library into an R package, and updated the formula for
// computing resistance loss.
// This package is made available in the hope that it will be useful. Enjoy!
/*END::ERB_EXPANSION*/
#ifndef _SPREAD_MATRIX_H_
#define _SPREAD_MATRIX_H_
 
/*
** CLASS DEFINITION
** ----------------------------------------------------------------------------
** Wrapper class for two-dimensional arrays of double allocated with new.
** The memory of the array is NOT owned by the CMatrix object.
*/
class CSpreadMatrix
{
	/*
	** CONSTRUCTION / DESTRUCTION
	** ------------------------------------------------------------------------
	*/
public:
	CSpreadMatrix(double *data_ptr, int row_count, int col_count) :
	  _DataPtr(data_ptr),
	  _RowCount(row_count),
	  _ColCount(col_count),
	  _NoData(-1)
	  {};
	
    /* accessors */
	inline int    getRowCount(){return _RowCount;};
	inline int	  getColCount(){return _ColCount;};
	inline double getNoData  (){return _NoData;};
	
	/* overloaded operator to make the class use more intuitive */
	inline double& operator()(int row, int col)
	{
		return _DataPtr[row * _ColCount + col];
	};

	/* checks that a set of coordinates is valid for the managed array */
	inline bool is_valid(int row, int col)
	{
		return	(row >= 0) && 
				(row < _RowCount) &&
				(col >= 0) &&
				(col < _ColCount);
	};

	/* fills all cells in the managed array with the given value, defaults to zero */
	void fill(double a_val = 0) 
	{
		CSpreadMatrix &mtx   = *this;
		for(int r = 0; r < _RowCount; ++r)
			for(int c = 0; c < _ColCount; ++c)
			{
				mtx(r, c) = a_val;
			};
	};

	/* copy the values of another matrix into this one and return count of non-zero cells */
	int copy(CSpreadMatrix &src)
	{
		CSpreadMatrix &mtx  = *this;
		int		      count = 0;

		for(int r = 0; r < _RowCount; ++r)
		{
			for(int c = 0; c < _ColCount; ++c)
			{
				mtx(r, c) = src(r, c);
				if(mtx(r, c) > 0) ++count;
			};
		};

		return count;
	};

	/* counts how many cells differ from the first one, for debugging mainly */
	int homogeneity()
	{
		double const ref_val = (*this)(0, 0);
		int       diff_count = 0;

		for(int r = 0; r < _RowCount; ++r)
		{
			for(int c = 0; c < _ColCount; ++c)
			{
				if(ref_val != (*this)(r, c))
				{
					++diff_count;
				};
			};
		};

		return diff_count;
	};

	/* returns a pointer to the managed array */
	inline double *ptr(){return _DataPtr;};

	/* returns the size (cell count) of the managed array */
	inline int	   size(){return _RowCount * _ColCount;};
 
	/*
	** ATTRIBUTES
	** ------------------------------------------------------------------------
	*/
private:
	double *_DataPtr;
	double	_NoData;
	int		_RowCount;
	int		_ColCount;
 };
#endif //_SPREAD_MATRIX_H_