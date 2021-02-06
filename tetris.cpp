#include "pch.h"
#include "tetris.h"
///////////////// Class for Set shapes (all the non-moving shapes)
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// SHAPES /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void dx4_win2d::Shapes::shiftGameGridDown1Row(int row)
{
	for (int i = row; i < ROWS - 1; i++) // shift cells down 1 position in game grid
		for (int j = 0; j < COLS; j++)
		{
			m_gameGrid[i][j] = m_gameGrid[i + 1][j];
		}

}

bool dx4_win2d::Shapes::checkRow(int rowToCheck)
{
	bool rowFilled = true;
	for (int j = 0; j < COLS; j++)
	{
		if (m_gameGrid[rowToCheck][j] == 0)
		{
			rowFilled = false;
		}
	}
	return rowFilled;
}

void dx4_win2d::Shapes::markBoxInGrid(Box & currentBox)
{
	m_gameGrid[currentBox.getRow()][currentBox.getCol()] = 1;
	m_gameGrid[currentBox.getRow()][currentBox.getCol() + 1] = 1;
	m_gameGrid[currentBox.getRow() + 1][currentBox.getCol()] = 1;
	m_gameGrid[currentBox.getRow() + 1][currentBox.getCol() + 1] = 1;
}
void dx4_win2d::Shapes::markTeeInGrid(TEE & currentTee)
{
	switch (currentTee.getRotation())
	{
	case 1:
		m_gameGrid[currentTee.getRow()][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 1][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow()][currentTee.getCol() - 1] = 2;
		m_gameGrid[currentTee.getRow()][currentTee.getCol() + 1] = 2;
		break;
	case 2:
		m_gameGrid[currentTee.getRow()][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 1][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 2][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 1][currentTee.getCol() + 1] = 2;
		break;
	case 3:
		m_gameGrid[currentTee.getRow()][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 1][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 1][currentTee.getCol() - 1] = 2;
		m_gameGrid[currentTee.getRow() + 1][currentTee.getCol() + 1] = 2;
		break;
	case 4:
		m_gameGrid[currentTee.getRow()][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 1][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 2][currentTee.getCol()] = 2;
		m_gameGrid[currentTee.getRow() + 1][currentTee.getCol() - 1] = 2;
		break;
	default:
		break;
	}
}
void dx4_win2d::Shapes::markBarInGrid(Bar & currentBar)
{
	switch (currentBar.getRotation())
	{
	case 1: // upright
		m_gameGrid[currentBar.getRow()][currentBar.getCol()] = 3;
		m_gameGrid[currentBar.getRow() + 1][currentBar.getCol()] = 3;
		m_gameGrid[currentBar.getRow() + 2][currentBar.getCol()] = 3;
		m_gameGrid[currentBar.getRow() + 3][currentBar.getCol()] = 3;
		break;
	case 2:// horizontal
		m_gameGrid[currentBar.getRow()][currentBar.getCol()] = 3;
		m_gameGrid[currentBar.getRow()][currentBar.getCol() - 1] = 3;
		m_gameGrid[currentBar.getRow()][currentBar.getCol() + 1] = 3;
		m_gameGrid[currentBar.getRow()][currentBar.getCol() + 2] = 3;
		break;
	default:
		break;
	}
}
void dx4_win2d::Shapes::markEsInGrid(Es & currentEs)
{
	switch (currentEs.getRotation())
	{
	case 1:
		m_gameGrid[currentEs.getRow()][currentEs.getCol()] = 4;
		m_gameGrid[currentEs.getRow() - 1][currentEs.getCol()] = 4;
		m_gameGrid[currentEs.getRow()][currentEs.getCol() + 1] = 4;
		m_gameGrid[currentEs.getRow() +1][currentEs.getCol() + 1] = 4;
		break;
	case 2:
		m_gameGrid[currentEs.getRow()][currentEs.getCol()] = 4;
		m_gameGrid[currentEs.getRow()][currentEs.getCol() +1] = 4;
		m_gameGrid[currentEs.getRow() + 1][currentEs.getCol()] = 4;
		m_gameGrid[currentEs.getRow() + 1][currentEs.getCol() - 1] = 4;
		break;
	case 3:
		m_gameGrid[currentEs.getRow()][currentEs.getCol()] = 4;
		m_gameGrid[currentEs.getRow() + 1][currentEs.getCol()] = 4;
		m_gameGrid[currentEs.getRow()][currentEs.getCol() + 1] = 4;
		m_gameGrid[currentEs.getRow() - 1][currentEs.getCol() + 1] = 4;
		break;
	case 4:
		m_gameGrid[currentEs.getRow()][currentEs.getCol()] = 4;
		m_gameGrid[currentEs.getRow()][currentEs.getCol() -1] = 4;
		m_gameGrid[currentEs.getRow() + 1][currentEs.getCol()] = 4;
		m_gameGrid[currentEs.getRow() + 1][currentEs.getCol() + 1] = 4;
		break;
	default:
		break;
	}
}
void dx4_win2d::Shapes::markElInGrid(El & currentEl)
{
	switch (currentEl.getRotation())
	{
	case 1:
		m_gameGrid[currentEl.getRow()][currentEl.getCol()] = 5;
		m_gameGrid[currentEl.getRow() + 1][currentEl.getCol()] = 5;
		m_gameGrid[currentEl.getRow() -1][currentEl.getCol()] = 5;
		m_gameGrid[currentEl.getRow() -1][currentEl.getCol() + 1] = 5;
		break;
	case 2:
		m_gameGrid[currentEl.getRow()][currentEl.getCol()] = 5;
		m_gameGrid[currentEl.getRow()][currentEl.getCol() -1] = 5;
		m_gameGrid[currentEl.getRow()][currentEl.getCol() +1] = 5;
		m_gameGrid[currentEl.getRow() - 1][currentEl.getCol() - 1] = 5;
		break;
	case 3:
		m_gameGrid[currentEl.getRow()][currentEl.getCol()] = 5;
		m_gameGrid[currentEl.getRow() + 1][currentEl.getCol()] = 5;
		m_gameGrid[currentEl.getRow() + 1][currentEl.getCol() - 1] = 5;
		m_gameGrid[currentEl.getRow() - 1][currentEl.getCol()] = 5;
		break;
	case 4:
		m_gameGrid[currentEl.getRow()][currentEl.getCol()] = 5;
		m_gameGrid[currentEl.getRow() + 1][currentEl.getCol() +1] = 5;
		m_gameGrid[currentEl.getRow()][currentEl.getCol() -1] = 5;
		m_gameGrid[currentEl.getRow()][currentEl.getCol() +1] = 5;
		break;
	default:
		break;
	}
}