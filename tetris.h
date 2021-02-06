#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include "Es.h"


// Has all 5 shape headers and mastershapes.h
namespace dx4_win2d
{
	class GameColors
	{
	public:
		GameColors() 
		{
	
		};
		~GameColors() {};

	private:
	
	};

	////////////////////////////////////////////
	class StatusWindow//////////////////////////
	{///////////////////////////////////////////
	public:
		StatusWindow()
		{
			m_statusWindow.X = 600;
			m_statusWindow.Y = 325;
			m_statusWindow.Width = 300;
			m_statusWindow.Height = 500;
		};
		~StatusWindow() {};
		Windows::Foundation::Rect getStatusWindow(void) { return m_statusWindow; }
	private:
		Windows::Foundation::Rect m_statusWindow;
	};
	////////////////////////////////////////////
	class NextWindow//////////////////////////
	{///////////////////////////////////////////
	public:
		NextWindow()
		{
			m_nextWindow.X = 600;
			m_nextWindow.Y = 100;
			m_nextWindow.Width = 200;
			m_nextWindow.Height = 200;
		};
		~NextWindow() {};
		Windows::Foundation::Rect getNextWindow(void) { return m_nextWindow; }
	private:
		Windows::Foundation::Rect m_nextWindow;
	};

	////////////////////////////////////////////
	class GameOver//////////////////////////
	{///////////////////////////////////////////
	public:
		GameOver()
		{
			m_gameOverWindow.X = 600;
			m_gameOverWindow.Y = 100;
			m_gameOverWindow.Width = 300;
			m_gameOverWindow.Height = 200;
		};
		~GameOver() {};
		Windows::Foundation::Rect getGameOverWindow(void) { return m_gameOverWindow; }
	private:
		Windows::Foundation::Rect m_gameOverWindow;
	};

	//////////////////////////////////////////////////////////////////////////
	class Totals // Window for running score & totals ////////////////////////
	{////////////////////////////////////////////////////////////////////////
	public:
		Totals()
		{
			m_totalsWindow.X = 600;
			m_totalsWindow.Y = 325;
			m_totalsWindow.Width = 200;
			m_totalsWindow.Height = 375;
		};
		~Totals() {};
		Windows::Foundation::Rect getTotalsWindow(void) { return m_totalsWindow; }
	private:
		Windows::Foundation::Rect m_totalsWindow;
	};
	//////////////////////////////////////////
	class GameBorder//////////////////////////
	{/////////////////////////////////////////
	public:
		GameBorder()
		{
			m_gameBorder.X = FLOOR_START;
			m_gameBorder.Y = 100;
			m_gameBorder.Width = 404;
			m_gameBorder.Height = 600;
		}
		~GameBorder() {};
		Windows::Foundation::Rect getGameBorder(void) { return m_gameBorder; }
	private:
		Windows::Foundation::Rect m_gameBorder;
	};
	//////////////////////////////////////////////////////////////////
	class FilledRow // Rectangle around a filled up row////////////////
	{/////////////////////////////////////////////////////////////////////
	public:
		FilledRow(int row)
		{
			m_filledRow.X = FLOOR_START;
			m_filledRow.Y = (float)FLOOR_POS - (MOVECELL * (row +1));
			m_filledRow.Width = 400;
			m_filledRow.Height = MOVECELL + 2;
		};
		~FilledRow() {};
		void setX(float x) { m_filledRow.X = x; }
		void setY(float y) { m_filledRow.Y = y; }
	
		Windows::Foundation::Rect getFilledRow(void) { return m_filledRow; }
	private:
		Windows::Foundation::Rect m_filledRow;
	};
	////////////////////////////////////////////////////////////////////////////////////////////////
	class Shapes // Shapes class represents collection of set shapes on the bottom of screen.///////
	{///////////////////////////////////////////////////////////////////////////////////////////////
	public:
		Shapes() // Constructor
		{
			m_numOfBoxes = 0;
			m_numOfTees = 0;
			m_numOfBars = 0;
			m_numOfEs = 0;
			m_numOfEls = 0;
			m_moveCell = 25; // set cell size
			// initialize gameGrid to 0;
			for (int i = 0; i < ROWS; i++)
				for (int j = 0; j < COLS; j++)
					m_gameGrid[i][j] = 0;
		}
		~Shapes()  // Destructor
		{
			//if (m_boxArr != nullptr)delete[] m_boxArr; if (m_teeArr != nullptr) delete[] m_teeArr;
		};
		
		// Boxes
		void setNumOfBoxes(int num) { m_numOfBoxes = num; }
		int getNumOfBoxes() { return m_numOfBoxes; }
		void addToBoxes() { ++m_numOfBoxes; }
		void markBoxInGrid(Box & currentBox);
		
		// Tees
		void setNumOfTees(int num) { m_numOfTees = num; }
		int getNumOfTees() { return m_numOfTees; }
		void addToTees() { ++m_numOfTees; }
		void markTeeInGrid(TEE & currentTee);
		
		// Bars
		void setNumOfBars(int num) { m_numOfBars = num; }
		int getNumOfBars() { return m_numOfBars; }
		void addToBars() { ++m_numOfBars; }
		void markBarInGrid(Bar & currentBar);

		// Es
		void setNumOfEs(int num) { m_numOfEs = num; }
		int getNumOfEs() { return m_numOfEs; }
		void addToEs() { ++m_numOfEs; }
		void markEsInGrid(Es & currentEs);

		// Els
		void setNumOfEls(int num) { m_numOfEls = num; }
		int getNumOfEls() { return m_numOfEls; }
		void addToEls() { ++m_numOfEls; }
		void markElInGrid(El & currentEl);

		// ROW stuf
		bool checkRow(int rowToCheck);
		void shiftGameGridDown1Row(int row);
		int getGridPosition(int x, int y) { return m_gameGrid[x][y]; }
	private:
		int m_gameGrid[ROWS][COLS];
		int m_moveCell; // value to move cell (25)
		int m_numOfBoxes;
		int m_numOfTees;
		int m_numOfBars;
		int m_numOfEs;
		int m_numOfEls;
	};
}

#endif // !TETRIS_H