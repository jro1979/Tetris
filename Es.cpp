#include "pch.h"
#include "Es.h"

namespace dx4_win2d
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////// Es ////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Lowers a Es shape 1 level along Y-axis.
	void dx4_win2d::Es::dropEs1(int & speed)
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
	}
	void dx4_win2d::Es::shiftEsLeft()
	{
		m_col--;
		for (size_t i = 0; i < BOXCELLS; i++)
			m_cellArr[i].X -= MOVECELL;
	}
	// shiftEsRight(). Shifts 1 Es's cells Right 1 position (25 pixels)
	void dx4_win2d::Es::shiftEsRight()
	{
		m_col++;
		for (size_t i = 0; i < BOXCELLS; i++)
			m_cellArr[i].X += MOVECELL;
	}

	void dx4_win2d::Es::rotateEs()
	{
		//++m_rotation;
		switch (m_rotation)
		{
		case 1:		//upright rotating to right
			m_rotation++;
			m_row--;
			
			m_esHeight = MOVECELL * 3;
			m_cellArr[0].X += MOVECELL * 2;
			//m_cellArr[0].Y += MOVECELL;
			m_cellArr[1].X += MOVECELL;
			m_cellArr[1].Y += MOVECELL;
			m_cellArr[3].X -= MOVECELL;
			m_cellArr[3].Y += MOVECELL;
			if (m_col == 14) { shiftEsLeft(); }
			m_col++;
			break;
		case 2:		//pointing right rotating down
			m_rotation++;
			m_row++;
			
			m_esHeight = MOVECELL * 2;
			m_cellArr[0].X -= MOVECELL * 2;
			m_cellArr[0].Y -= MOVECELL * 2;
			m_cellArr[1].X -= MOVECELL;
			m_cellArr[1].Y -= MOVECELL;
			m_cellArr[3].X += MOVECELL;
			m_cellArr[3].Y += MOVECELL;
			if (m_col == 0) { shiftEsRight(); }
			m_col--;
			break;
		case 3:		//pointing down rotating left
			m_rotation++;
			m_row--;
			m_esHeight = MOVECELL * 3;
			m_cellArr[0].X += MOVECELL * 2;
			m_cellArr[1].X += MOVECELL;
			m_cellArr[1].Y -= MOVECELL;
			m_cellArr[3].X -= MOVECELL;
			m_cellArr[3].Y -= MOVECELL;
			if (m_col == 14) { shiftEsLeft(); }
			m_col++;
			break;
		case 4:		//pointing left rotating up
			m_rotation = 1;
			m_row++;
			m_esHeight = MOVECELL * 2;
			m_cellArr[0].X -= MOVECELL * 2;
			m_cellArr[0].Y += MOVECELL * 2;
			m_cellArr[1].X -= MOVECELL;
			m_cellArr[1].Y += MOVECELL;
			m_cellArr[3].X += MOVECELL;
			m_cellArr[3].Y -= MOVECELL;
			// If on the far right col, move shape left 1 pos
			//if (m_col == 15) { shiftEsLeft(); }
			m_col--;
			break;
		default:
			break;
		}
	}
	// esOffGrid()
	bool dx4_win2d::Es::esOffGrid(void)
	{
		switch (m_rotation)
		{
		case 1:
		case 2: return (m_cellArr[3].Y >= FLOOR_POS) ? true : false; break;
		case 3: return (m_cellArr[1].Y >= FLOOR_POS) ? true : false; break;
		case 4: return (m_cellArr[2].Y >= FLOOR_POS) ? true : false; break;
		default:
			break;
		}
		return false;
	}
	void dx4_win2d::Es::putInNext(void)
	{
		for (size_t i = 0; i < BOXCELLS; i++)
		{
			m_cellArr[i].X += MOVECELL * NEXT_COL;
			m_cellArr[i].Y += MOVECELL * NEXT_ROW;
		}
	}
}