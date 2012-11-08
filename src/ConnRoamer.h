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
#ifndef _CONN_ROAMER_H_
#define _CONN_ROAMER_H_

/*
** INCLUDES
** ----------------------------------------------------------------------------
*/
#include "_spread.h"
#include "Neighborhood.h"
 
/*
** HELPER CLASS
** ----------------------------------------------------------------------------
** Needed as building block for the priority queue. It stores the coordinates
** and a bank_account snapshot of a cell.
*/
struct CRoamerCell
{ 
	/*
	** CONSTRUCTION / DESTRUCTION
	** ------------------------------------------------------------------------
	*/
	CRoamerCell(double a_bank_account, int a_row, int a_col) :
	  bank_account(a_bank_account), row(a_row), col(a_col)
	  {};
 
	/*
	** ATTRIBUTES
	** ------------------------------------------------------------------------
	*/
	double bank_account;
	int    row;
	int    col;
};
 
/*
===============================================================================
**	FUNCTION DESCRIPTION:
**	---------------------
**	Utility operator needed for proper ordering of the priority queue
===============================================================================
*/
inline bool operator< (const CRoamerCell &one_cell, const CRoamerCell &another_cell)
{
	return one_cell.bank_account < another_cell.bank_account;
}; 
 
/*
** CLASS DEFINITION
** ----------------------------------------------------------------------------
** The class enbedding the spread algorithm
*/
class CConnRoamer  
{ 
	/*
	** CONSTRUCTION / DESTRUCTION
	** ------------------------------------------------------------------------
	*/
public:
	CConnRoamer(CSpreadMatrix &work_mtx, CSpreadMatrix &resist_mtx, double bank_account);
 
	/*
	** METHODS
	** ------------------------------------------------------------------------
	*/
	double Spread(int aRow, int aCol);
	const double &getBankAccount(){return _BankAccount;};
	virtual ~CConnRoamer();
 
	/*
	** ATTRIBUTES
	** ------------------------------------------------------------------------
	*/
private:
	CSpreadMatrix &_WorkMTX;
	CSpreadMatrix &_ResistMTX;
	double	 _NoData;
	double	 _BankAccount;
	int		m_iColCount;
	int		m_iRowCount;

	std::priority_queue<CRoamerCell, 
						std::deque<CRoamerCell>,
						std::less<CRoamerCell>
						> pq;
	CNeighborhood nb;
};

#endif // _CONN_ROAMER_H_
