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
#include "Neighborhood.h"

/* CONSTRUCTOR IMPLEMENTATION
============================================================================
============================================================================ */
CNeighborhood::CNeighborhood(CSpreadMatrix &aGrid, int aNeighborhoodType) :
    m_oSrcGrid(aGrid), m_iNeighborhoodType(aNeighborhoodType),
		m_oNE_Neighbor(/*row*/ N_SHIFT, /*col*/E_SHIFT, DIAG_COEF),
		m_oNW_Neighbor(/*row*/ N_SHIFT, /*col*/W_SHIFT, DIAG_COEF),
		m_oSE_Neighbor(/*row*/ S_SHIFT, /*col*/E_SHIFT, DIAG_COEF),
		m_oSW_Neighbor(/*row*/ S_SHIFT, /*col*/W_SHIFT, DIAG_COEF),
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

/* DESTRUCTOR IMPLEMENTATION
============================================================================
============================================================================ */
CNeighborhood::~CNeighborhood()
{
}
