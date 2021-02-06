#pragma once
#ifndef BOX_H
#define BOX_H

#include "Bar.h"
namespace dx4_win2d
{
	class Box
	{
	public:
		Box()
		{
			for (size_t i = 0; i < BOXCELLS; i++)
			{
				m_cellArr[i].Width = CELLSIZE;
				m_cellArr[i].Height = CELLSIZE;
			}
			m_cellArr[0].X = 275; // top left
			m_cellArr[0].Y = 100;

			m_cellArr[1].X = 300; // top right
			m_cellArr[1].Y = 100;

			m_cellArr[2].X = 275; // bottom left
			m_cellArr[2].Y = 125;

			m_cellArr[3].X = 300; // bottom right
			m_cellArr[3].Y = 125;

			m_row = ROWS - 2;
			m_col = 7;
			m_counter = 0;
			m_boxHeight = (CELLSIZE + CELLBORDER) * 2;
		}
		~Box() {};
		void dropBox1(int & speed);
		Windows::Foundation::Rect getCell(int pos) { return m_cellArr[pos]; }
		void shiftBoxLeft();
		void shiftBoxRight();
		void putInNext(void);
		//float * getLowBarrier(void) {  return **m_lowPos; }
		int getCol() { return m_col; }
		int getRow() { return m_row; }
		int getBoxHeight() { return m_boxHeight; }
		//float getLowPos() { return m_cellArr[2].Y; }
		float getLowPos() { return m_cellArr[2].Y + MOVECELL; }
		void addToCounter(int speed) { m_counter += speed; }
		void resetCounter() { m_counter = 0; }
		bool boxOffGrid();
	private:
		// Windows::Foundation::Rect uses (X, Y, Width, Height) as floats.
		Windows::Foundation::Rect m_cellArr[BOXCELLS]; // Rect class cell array
		int m_col;
		int m_row;
		int m_boxHeight;
		int m_counter;
		int m_cellColor;
		int m_cellBorderColor;
		//float * m_lowPos;
	};

}








#endif // !BOX_H

