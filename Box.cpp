#include "pch.h"
#include "Box.h"

namespace dx4_win2d
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// BOX //////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// dropBox1(). Lowers each cell in Box by 1 along Y-axis.
	void dx4_win2d::Box::dropBox1(int & speed)
	{
		for (int j = 0; j < speed; j++)
		{
			for (size_t i = 0; i < BOXCELLS; i++)
			{
				m_cellArr[i].Y += DROPSPEED;
			}
			addToCounter(1);
			if (m_counter >= MOVECELL *2)
			{
				m_row--;
				resetCounter();
			}
		}
		/*for (float j = 0.0; j < (float)speed / 2; j += .5)
		{
			for (size_t i = 0; i < BOXCELLS; i++)
			{
				m_cellArr[i].Y += 1;
			}
			addToCounter(1);
			if (m_counter >= MOVECELL)
			{
				m_row--;
				resetCounter();
			}
		}*/
	}
	// shiftBoxLeft(). Shifts 1 Box's cells Left 1 position (25 pixels)
	void dx4_win2d::Box::shiftBoxLeft()
	{
		m_col--;
		for (size_t i = 0; i < BOXCELLS; i++)
			m_cellArr[i].X -= MOVECELL;
	}
	// shiftBoxRight(). Shifts 1 Box's cells Right 1 position (25 pixels)
	void dx4_win2d::Box::shiftBoxRight()
	{
		m_col++;
		for (size_t i = 0; i < BOXCELLS; i++)
			m_cellArr[i].X += MOVECELL;
	}
	void dx4_win2d::Box::putInNext(void)
	{
		for (size_t i = 0; i < BOXCELLS; i++)
		{
			m_cellArr[i].X += MOVECELL * (NEXT_COL +1);
			m_cellArr[i].Y += MOVECELL * NEXT_ROW;
		}
	}
	bool dx4_win2d::Box::boxOffGrid(void)
	{
		return (m_cellArr[0].Y >= FLOOR_POS) ? true : false;
	}

}