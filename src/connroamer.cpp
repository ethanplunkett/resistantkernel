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
#include "ConnRoamer.h"

/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	Constructor
===============================================================================
*/
CConnRoamer::CConnRoamer(CSpreadMatrix &work_mtx, CSpreadMatrix &resist_mtx, double bank_account) :
	_WorkMTX(work_mtx),
	_ResistMTX(resist_mtx),
	_BankAccount(bank_account),
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

	int    r                = aRow;
	int    c                = aCol;
	double visited_cells    = 1 /* correction for the focal cell */;
	double org_cell_account = 0;
	volatile double neighbor_new_cell_account = 0;
	volatile double current_cell_account      = 0;

	/* init the priority queue and the starter cell */
	_WorkMTX(aRow, aCol) = getBankAccount();
	pq.push(CRoamerCell(getBankAccount(), r, c));

	while(pq.size() > 0)
	{
		/* go to the next highest cell */
		r                = pq.top().row;
		c                = pq.top().col;
		org_cell_account = pq.top().bank_account;
		pq.pop();

		/* find out the current bank account of the pivot cell */
		current_cell_account = _WorkMTX(r, c);

		/*
		** if the cell has been assigned a larger bank account since being
		** originally pushed into the stack it would be a waste to reprocess it
		*/
		if(org_cell_account < current_cell_account) continue;

		/* re-center the neighborhood */
		nb.SetPivot(r, c);

		/* visit all neighbors of the current cell (8) */
		for(int i = 0; i < nb.NeighborCount(); ++i)
		{
			nc = nb[i];
			if(nc->Valid()) /* is this neighbor still in the given matrix? */
			{		
				/* volatile here prevents the optimizer from taking a bad decision :-( */
				volatile double &neighbor_current_cell_account = _WorkMTX(nc->Row(), nc->Col());

				if(neighbor_current_cell_account >= 0) 
				{
					double resistance_loss = nc->Coef() * ( _ResistMTX(nc->Row(), nc->Col()) +  _ResistMTX(r, c)) / 2;
					neighbor_new_cell_account = current_cell_account - resistance_loss;

					if((neighbor_new_cell_account > 0) && (neighbor_new_cell_account > neighbor_current_cell_account))
					{
						/* count the cells only when they are first altered to avoid multiple counts */
						if(neighbor_current_cell_account == 0)
						{
							++visited_cells;
						};

						pq.push(CRoamerCell(neighbor_new_cell_account, nc->Row(), nc->Col()));
						neighbor_current_cell_account = neighbor_new_cell_account;
					};
				};
			};
		};
	}; // while

	return visited_cells ;
}
