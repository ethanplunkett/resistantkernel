#if !defined(AFX_CONNROAMER_H__0585A3A7_1FC1_47FA_96FA_65AAAED7C76A__INCLUDED_)
#define AFX_CONNROAMER_H__0585A3A7_1FC1_47FA_96FA_65AAAED7C76A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
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
class CRoamerCell
{
public:
 
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
public:
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
	CConnRoamer(CMatrix &work_mtx, CMatrix &resist_mtx, double spread_val);
 
	/*
	** METHODS
	** ------------------------------------------------------------------------
	*/
	double Spread(int aRow, int aCol);
	const double &getBankAccount(){return _SpreadVal;};
	virtual ~CConnRoamer();
 
	/*
	** ATTRIBUTES
	** ------------------------------------------------------------------------
	*/
private:
	CMatrix &_WorkMTX;
	CMatrix &_ResistMTX;
	double	 _NoData;
	double	 _SpreadVal;
	int		m_iColCount;
	int		m_iRowCount;

	std::priority_queue<CRoamerCell, 
						std::vector<CRoamerCell>,
						std::less<CRoamerCell>
						> pq;
	CNeighborhood nb;
};

#endif // !defined(AFX_CONNROAMER_H__0585A3A7_1FC1_47FA_96FA_65AAAED7C76A__INCLUDED_)
