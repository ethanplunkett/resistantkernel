#include "ConnRoamer.h"


/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	Constructor
===============================================================================
*/
CConnRoamer::CConnRoamer(CMatrix &work_mtx, CMatrix &resist_mtx, double spread_val, bool symmetrical) :
	_WorkMTX(work_mtx),
	_ResistMTX(resist_mtx),
	_SpreadVal(spread_val),
	_Symmetrical(symmetrical),
	nb(_ResistMTX, EIGHT_NEIGHBOR)
{
	m_iColCount	= _ResistMTX.getColCount();
	m_iRowCount	= _ResistMTX.getRowCount();
	_NoData		= _ResistMTX.getNoData();
}

/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	Destructor
===============================================================================
*/
CConnRoamer::~CConnRoamer()
{
}
 
/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	Main entry point for the spread algorithm
===============================================================================
*/
double CConnRoamer::Spread(int aRow, int aCol)
{
	CNeighborhoodCell *nc = NULL;
	double	visited_cells = 1 /* correction for the focal cell */;
	double   new_cell_val = 0;
	double        org_val = 0;
	int            r = aRow;
	int            c = aCol;

	/* init the priority queue and the starter cell */
	_WorkMTX(aRow, aCol) = getBankAccount();
	pq.push(CRoamerCell(getBankAccount(), r, c));

	while(pq.size())
	{
		/* go to the next highest cell */
		r       = pq.top().row;
		c       = pq.top().col;
		org_val = pq.top().bank_account;
		pq.pop();

		/* find out the current bank account of the pivot cell */
		double pivot_cell_val = _WorkMTX(r, c);

		/*
		** if the cell has been assigned a larger bank account since being
		** originally pushed into the stack it would be a waste to reprocess it
		*/
		if(org_val < pivot_cell_val) continue;

		/* re-center the neighborhood */
		nb.SetPivot(r, c);

		/* visit all neighbors of the current cell (8) */
		for(int i = 0; i < nb.NeighborCount(); ++i)
		{
			nc = nb[i];
			if(nc->Valid())
			{				
				double &work_cell = _WorkMTX(nc->Row(), nc->Col());
				if(!(work_cell < 0)) 
				{
				  if(_Symmetrical)
				  {
				    new_cell_val = pivot_cell_val - nc->Coef() * ( _ResistMTX(nc->Row(), nc->Col()) +  _ResistMTX(r, c))/2;  // Modified by EBP to use the average of the two cell's resistances
				  }  else {
  					new_cell_val = pivot_cell_val - nc->Coef() * _ResistMTX(nc->Row(), nc->Col());  // Non symmetrical
				  };

					if((new_cell_val > 0) && (work_cell < new_cell_val))
					{
						if(work_cell == 0)
						{
							++visited_cells;
						};

						pq.push(CRoamerCell(new_cell_val, nc->Row(), nc->Col()));
						work_cell = new_cell_val;
					};
				};
			};
		};
	}
	return visited_cells ;
}
