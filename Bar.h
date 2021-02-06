#pragma once
#ifndef BAR_H
#define BAR_H

#include "mastershapes.h"

namespace dx4_win2d
{	////////////////////////////////////////////////////////////////////////////////
	//////////////// Bar shape /////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	class Bar
	{
	public:
		Bar()   // Initialize start position to top middle of screen
		{
			for (size_t i = 0; i < BOXCELLS; i++)
			{
				m_cellArr[i].Width = CELLSIZE;
				m_cellArr[i].Height = CELLSIZE;
			}
			m_cellArr[0].X = 300; // bottom 
			m_cellArr[0].Y = 125;

			m_cellArr[1].X = 300; // middle bottom//  PIVOT PIECE
			m_cellArr[1].Y = 100;

			m_cellArr[2].X = 300; // middle top
			m_cellArr[2].Y = 75;

			m_cellArr[3].X = 300; // top
			m_cellArr[3].Y = 50;
			m_col = 8;
			m_rotation = 1;
			m_counter = 0;
			m_row = ROWS - 2;
			m_barHeight = (CELLSIZE + CELLBORDER) * 4;
		}

		~Bar() {};
		void dropBar1(int & speed);
		void shiftBarLeft();
		void shiftBarRight();
		void putInNext(void);
		void rotateBar();
		int getRow() { return m_row; }
		int getCol() { return m_col; }
		int getRotation() { return m_rotation; }
		float getLowPos(void) { return m_cellArr[0].Y + MOVECELL; }
		void addToCounter(int speed) { m_counter += speed; }
		void resetCounter() { m_counter = 0; }
		bool barOffGrid();
		Windows::Foundation::Rect getCell(int pos) { return m_cellArr[pos]; }
	private:
		Windows::Foundation::Rect m_cellArr[BOXCELLS]; // Rect class cell array
		int m_row;
		int m_col;
		int m_rotation;
		int m_counter;
		int m_barHeight;
		int m_cellColor;
		int m_cellBorderColor;
	};
}

#endif // !BAR_H

