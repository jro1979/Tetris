#include "rect.h"


Cell::Cell(int topL, int topR, int botL, int botR)
{
	m_topLeft = topL;
	m_topRight = topR;
	m_botLeft = botL;
	m_botRight = botR;
}

Cell::~Cell()
{
}