#include "pch.h"
#include "Bar.h"

namespace dx4_win2d
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////// Bar ////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Lowers a bar shape 1 level along Y-axis.
	void dx4_win2d::Bar::dropBar1(int & speed)
	{
		for (int j = 0; j < speed; j++)
		//for (float j = 0.0; j < (float)speed / 2; j += .5)
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
	}
	void dx4_win2d::Bar::shiftBarLeft()
	{
		m_col--;
		for (size_t i = 0; i < BOXCELLS; i++)
			m_cellArr[i].X -= MOVECELL;
	}
	// shiftbarRight(). Shifts 1 bar's cells Right 1 position (25 pixels)
	void dx4_win2d::Bar::shiftBarRight()
	{
		m_col++;
		for (size_t i = 0; i < BOXCELLS; i++)
			m_cellArr[i].X += MOVECELL;
	}

	void dx4_win2d::Bar::rotateBar()
	{
		//++m_rotation;
		switch (m_rotation)
		{
		case 1:		//upright rotating to right
			m_rotation++;
			m_row += 1;

			m_barHeight = MOVECELL;
			m_cellArr[0].X -= MOVECELL;
			m_cellArr[0].Y -= MOVECELL;
			m_cellArr[2].X += MOVECELL;
			m_cellArr[2].Y += MOVECELL;
			m_cellArr[3].X += MOVECELL * 2;
			m_cellArr[3].Y += MOVECELL * 2;
			// If bar on left or right edges, shift position to stay within the game border
			if (m_col == 0) { shiftBarRight(); }
			else if (m_col == 14) { shiftBarLeft(); }
			else if (m_col == 15) { shiftBarLeft();	shiftBarLeft(); }
			break;
		case 2:		//right rotating back up
			m_rotation--;
			m_row -= 1;
			m_barHeight = MOVECELL * 1;
			m_cellArr[0].X += MOVECELL;
			m_cellArr[0].Y += MOVECELL;
			m_cellArr[2].X -= MOVECELL;
			m_cellArr[2].Y -= MOVECELL;
			m_cellArr[3].X -= MOVECELL * 2;
			m_cellArr[3].Y -= MOVECELL * 2;
			break;
		default:
			break;
		}
	}
	// barOffGrid()
	bool dx4_win2d::Bar::barOffGrid(void)
	{
		return (m_cellArr[3].Y >= FLOOR_POS) ? true : false;
		/*switch (m_rotation)
		{
		case 1: return (m_cellArr[0].Y >= FLOOR_POS) ? true : false; break;
		case 2:
		case 3: return (m_cellArr[1].Y >= FLOOR_POS) ? true : false; break;
		case 4: return (m_cellArr[2].Y >= FLOOR_POS) ? true : false; break;
		default:
		break;
		}
		return false;*/
	}
	void dx4_win2d::Bar::putInNext(void)
	{
		for (size_t i = 0; i < BOXCELLS; i++)
		{
			m_cellArr[i].X += MOVECELL * (NEXT_COL +1);
			m_cellArr[i].Y += MOVECELL * NEXT_ROW;
		}
	}
}

