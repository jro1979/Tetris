#pragma once
#ifndef RECT_H
#define RECT_H



class Cell
{
public:
	Cell(int topL, int topR, int botL, int botR);
	~Cell();
	void setTopLeft(int num) { m_topLeft = num; }
	void setTopRight(int num) { m_topRight = num; }
	void setBotLeft(int num) { m_botLeft = num; }
	void setBotRight(int num) { m_botRight = num; }
	int getTopLeft(void) { return m_topLeft; }
	int getTopRight(void) { return m_topRight; }
	int getBotLeft() { return m_botLeft; }
	int getBotRight() { return m_botRight; }
private:
	int m_topLeft;
	int m_topRight;
	int m_botLeft;
	int m_botRight;
};




#endif // !RECT_H

