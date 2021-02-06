#pragma once
#ifndef EL_H
#define EL_H
#include "Tee.h"
namespace dx4_win2d
{
	//////////////// El shape /////////////////////////////////////////////////////
	class El
	{
	public:
		El()   // Initialize start position to top middle of screen
		{
			for (size_t i = 0; i < BOXCELLS; i++)
			{
				m_cellArr[i].Width = CELLSIZE;
				m_cellArr[i].Height = CELLSIZE;
			}
			m_cellArr[0].X = 325; // bottom right
			m_cellArr[0].Y = 125;

			m_cellArr[1].X = 300; // bottom left
			m_cellArr[1].Y = 125;

			m_cellArr[2].X = 300; // middle
			m_cellArr[2].Y = 100;

			m_cellArr[3].X = 300; // top 
			m_cellArr[3].Y = 75;
			m_col = 8;
			m_rotation = 1;
			m_counter = 0;
			m_row = ROWS - 2;
			m_elHeight = (CELLSIZE + CELLBORDER) * 2;
		}

		~El() {};
		void dropEl1(int & speed);
		void shiftElLeft();
		void shiftElRight();
		void putInNext();
		void rotateEl();
		int getRow() { return m_row; }
		int getCol() { return m_col; }
		int getRotation() { return m_rotation; }
		float getLowPos(void) { return m_cellArr[0].Y + MOVECELL; }
		void addToCounter(int speed) { m_counter += speed; }
		void resetCounter() { m_counter = 0; }
		bool elOffGrid();
		Windows::Foundation::Rect getCell(int pos) { return m_cellArr[pos]; }
	private:
		Windows::Foundation::Rect m_cellArr[BOXCELLS]; // Rect class cell array
		int m_row;
		int m_col;
		int m_rotation;
		int m_counter;
		int m_elHeight;
		int m_cellColor;
		int m_cellBorderColor;
	};

}






#endif // !EL_H

