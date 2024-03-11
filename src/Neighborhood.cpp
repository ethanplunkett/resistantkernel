#include "Neighborhood.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNeighborhood::CNeighborhood(CMatrix &aGrid, int aNeighborhoodType, bool use_long_diag) :
    m_oSrcGrid(aGrid), m_iNeighborhoodType(aNeighborhoodType),
		m_oNE_Neighbor(/*row*/ N_SHIFT, /*col*/E_SHIFT, (use_long_diag ? DIAG_COEF_LONG : DIAG_COEF_SHORT)),
		m_oNW_Neighbor(/*row*/ N_SHIFT, /*col*/W_SHIFT, (use_long_diag ? DIAG_COEF_LONG : DIAG_COEF_SHORT)),
		m_oSE_Neighbor(/*row*/ S_SHIFT, /*col*/E_SHIFT, (use_long_diag ? DIAG_COEF_LONG : DIAG_COEF_SHORT)),
		m_oSW_Neighbor(/*row*/ S_SHIFT, /*col*/W_SHIFT, (use_long_diag ? DIAG_COEF_LONG : DIAG_COEF_SHORT)),
		m_oN_Neighbor (/*row*/ N_SHIFT, /*col*/NOSHIFT),
		m_oS_Neighbor (/*row*/ S_SHIFT, /*col*/NOSHIFT),
		m_oE_Neighbor (/*row*/ NOSHIFT, /*col*/E_SHIFT),
		m_oW_Neighbor (/*row*/ NOSHIFT, /*col*/W_SHIFT)
{
	m_iNeighborCount = 4;
	m_iRowCount = m_oSrcGrid.getRowCount();
	m_iColCount = m_oSrcGrid.getColCount();
	switch(aNeighborhoodType)
	{
		case EIGHT_NEIGHBOR:
		{
			m_iNeighborCount = 8;
			m_arrNeighbors[4] = &m_oNE_Neighbor;
			m_arrNeighbors[5] = &m_oNW_Neighbor;
			m_arrNeighbors[6] = &m_oSE_Neighbor;
			m_arrNeighbors[7] = &m_oSW_Neighbor;

		};
		case FOUR_NEIGHBOR:
		{
			m_arrNeighbors[0] = &m_oN_Neighbor;
			m_arrNeighbors[1] = &m_oS_Neighbor;
			m_arrNeighbors[2] = &m_oE_Neighbor;
			m_arrNeighbors[3] = &m_oW_Neighbor;
		};
	};
	m_oNE_Neighbor.Name() = "NE";
	m_oNW_Neighbor.Name() = "NW";
	m_oSE_Neighbor.Name() = "SE";
	m_oSW_Neighbor.Name() = "SW";
	m_oN_Neighbor.Name () = "N";
	m_oS_Neighbor.Name () = "S";
	m_oE_Neighbor.Name () = "E";
	m_oW_Neighbor.Name () = "W";
}

CNeighborhood::~CNeighborhood()
{
}
