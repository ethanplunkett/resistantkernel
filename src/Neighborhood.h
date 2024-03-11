#if !defined(AFX_NEIGHBORHOOD_H__769CC099_7D7A_4A92_8821_C71AA7BABD1D__INCLUDED_)
#define AFX_NEIGHBORHOOD_H__769CC099_7D7A_4A92_8821_C71AA7BABD1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
/*
** FORWARD DECLARATIONS
** ----------------------------------------------------------------------------
*/
#define RESET_CELL(CELL_NAME) \
		CELL_NAME.Row() = m_iPivotRow + CELL_NAME.RowShift();\
		CELL_NAME.Col() = m_iPivotCol + CELL_NAME.ColShift();\
		CELL_NAME.Valid() = true;
const double DIAG_COEF_LONG  = 1.4;
const double DIAG_COEF_SHORT = 1.0;
const double DIAG_COEF_NONE  = 1.0; // for non-diagonal neighbors

 
/*
** INCLUDES
** ----------------------------------------------------------------------------
*/
#include "_spread.h"
#include "Matrix.h"

 
/*
** HELPER CLASS
** ----------------------------------------------------------------------------
*/
class CNeighborhoodCell
{
	std::string	m_strName;
	int		m_iRow;
	int		m_iCol;
	int		m_iRowShift;
	int		m_iColShift;
	bool	m_bValid;
	double	m_fCoef;
public:
	int			&Row()		{return m_iRow;};
	int			&Col()		{return m_iCol;};
	const int	&RowShift()	{return m_iRowShift;};
	const int	&ColShift()	{return m_iColShift;};
	bool		&Valid()	{return m_bValid;};
	double		&Coef()		{return m_fCoef;};
	std::string	&Name()		{return m_strName;};
	CNeighborhoodCell(int aRowShift, int aColShift, double coef = 1)
	{
		m_iRow		= m_iCol 
					= -1; 
		m_bValid	= false; 
		m_fCoef		= coef;
		m_iRowShift = aRowShift; 
		m_iColShift = aColShift;
	};
};
 
/*
** CLASS DEFINITION
** ----------------------------------------------------------------------------
*/
class CNeighborhood  
{
	CMatrix &m_oSrcGrid;
	int m_iNeighborhoodType;
	int m_iNeighborCount;
	int m_iPivotRow;
	int m_iPivotCol;
	int	m_iRowCount;
	int	m_iColCount;
	CNeighborhoodCell m_oNE_Neighbor;
	CNeighborhoodCell m_oNW_Neighbor;
	CNeighborhoodCell m_oSE_Neighbor;
	CNeighborhoodCell m_oSW_Neighbor;
	CNeighborhoodCell m_oN_Neighbor ;
	CNeighborhoodCell m_oS_Neighbor ;
	CNeighborhoodCell m_oE_Neighbor ;
	CNeighborhoodCell m_oW_Neighbor ;
	CNeighborhoodCell* m_arrNeighbors[8];
	 
public:
	CNeighborhoodCell &NE(){return m_oNE_Neighbor;};
	CNeighborhoodCell &NW(){return m_oNW_Neighbor;};
	CNeighborhoodCell &SE(){return m_oSE_Neighbor;};
	CNeighborhoodCell &SW(){return m_oSW_Neighbor;};
	CNeighborhoodCell &N() {return m_oN_Neighbor ;};
	CNeighborhoodCell &S() {return m_oS_Neighbor ;};
	CNeighborhoodCell &E() {return m_oE_Neighbor ;};
	CNeighborhoodCell &W() {return m_oW_Neighbor ;};

	const int &NeighborCount(){return m_iNeighborCount;};
	CNeighborhoodCell* operator[](int index){return m_arrNeighbors[index];};
	void SetPivot(int aRow, int aCol)
	{
		m_iPivotRow = aRow; 
		m_iPivotCol = aCol;
		switch(m_iNeighborhoodType)
		{
			case EIGHT_NEIGHBOR:
			{
				/* --------------------- */
				RESET_CELL(m_oNE_Neighbor);
					if(m_oNE_Neighbor.Row() < 0)
					{
						m_oNE_Neighbor.Valid() = false;
					}
					else if(m_oNE_Neighbor.Col() >= m_iColCount)
					{
						m_oNE_Neighbor.Valid() = false;
					}
					else if(m_oSrcGrid(m_oNE_Neighbor.Row(),m_oNE_Neighbor.Col()) < 0)
					{
						m_oNE_Neighbor.Valid() = false;
					};
				/* --------------------- */
				RESET_CELL(m_oNW_Neighbor);
					if(m_oNW_Neighbor.Row() < 0)
					{
						m_oNW_Neighbor.Valid() = false;
					}
					else if(m_oNW_Neighbor.Col() < 0)
					{
						m_oNW_Neighbor.Valid() = false;
					}
					else if(m_oSrcGrid(m_oNW_Neighbor.Row(),m_oNW_Neighbor.Col()) < 0)
					{
						m_oNW_Neighbor.Valid() = false;
					};
				/* --------------------- */
				RESET_CELL(m_oSE_Neighbor);
					if(m_oSE_Neighbor.Row() >= m_iRowCount)
					{
						m_oSE_Neighbor.Valid() = false;
					}
					else if(m_oSE_Neighbor.Col() >= m_iColCount)
					{
						m_oSE_Neighbor.Valid() = false;
					}
					else if(m_oSrcGrid(m_oSE_Neighbor.Row(),m_oSE_Neighbor.Col()) < 0)
					{
						m_oSE_Neighbor.Valid() = false;
					};
				/* --------------------- */
				RESET_CELL(m_oSW_Neighbor);
					if(m_oSW_Neighbor.Row() >= m_iRowCount)
					{
						m_oSW_Neighbor.Valid() = false;
					}
					else if(m_oSW_Neighbor.Col() < 0)
					{
						m_oSW_Neighbor.Valid() = false;
					}
					else if(m_oSrcGrid(m_oSW_Neighbor.Row(),m_oSW_Neighbor.Col()) < 0)
					{
						m_oSW_Neighbor.Valid() = false;
					};

			};
			case FOUR_NEIGHBOR:
			{
				/* --------------------- */
				RESET_CELL(m_oN_Neighbor);
					if(m_oN_Neighbor.Row() < 0)
					{
						m_oN_Neighbor.Valid() = false;
					}
					else if(m_oSrcGrid(m_oN_Neighbor.Row(),m_oN_Neighbor.Col()) < 0)
					{
						m_oN_Neighbor.Valid() = false;
					};
				/* --------------------- */
				RESET_CELL(m_oS_Neighbor);
					if(m_oS_Neighbor.Row() >= m_iRowCount)
					{
						m_oS_Neighbor.Valid() = false;
					}
					else if(m_oSrcGrid(m_oS_Neighbor.Row(),m_oS_Neighbor.Col()) < 0)
					{
						m_oS_Neighbor.Valid() = false;
					};
				/* --------------------- */
				RESET_CELL(m_oE_Neighbor);
					if(m_oE_Neighbor.Col() >= m_iColCount)
					{
						m_oE_Neighbor.Valid() = false;
					}
					else if(m_oSrcGrid(m_oE_Neighbor.Row(),m_oE_Neighbor.Col()) < 0)
					{
						m_oE_Neighbor.Valid() = false;
					};
				/* --------------------- */
				RESET_CELL(m_oW_Neighbor);
					if(m_oW_Neighbor.Col() < 0)
					{
						m_oW_Neighbor.Valid() = false;
					}
					else if(m_oSrcGrid(m_oW_Neighbor.Row(),m_oW_Neighbor.Col()) < 0)
					{
						m_oW_Neighbor.Valid() = false;
					};
			};
		};
	};
	CNeighborhood(CMatrix &aGrid, int aNeighborhoodType, bool use_long_diag = true);
	virtual ~CNeighborhood();

};
#undef RESET_CELL

#endif // !defined(AFX_NEIGHBORHOOD_H__769CC099_7D7A_4A92_8821_C71AA7BABD1D__INCLUDED_)
