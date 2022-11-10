#pragma once
#include"Utils.h"
#include"Screen.h"
#include<cstdlib>
#include<ctime>
#include"InputSystem.h"

#define MINENUM 13

class Mine
{
	char* m_mineMap;
	int m_mineIndex[MINENUM];
	int m_cols;
	int m_rows;
	bool m_isGameover;
	bool m_isGameClear;
	Screen* m_screen;
	InputSystem& m_input;

	void clear()
	{
		memset(m_mineMap, '0', m_cols * m_rows);
		for (int i = 1; i <= m_cols; i++)
		{
			m_mineMap[i * m_rows - 1] = '\n';
		}
		m_mineMap[m_cols * m_rows] = '\0';
	}
	void mineAroundNum()
	{
		for (int i = 0; i < MINENUM; i++)
		{
			aroundMineCount(m_mineIndex[i]);
		}
	}
	void aroundMineCount(int index)
	{
		int max = m_cols * m_rows - 1;
		if ((index - m_rows - 1) >= 0 && m_mineMap[index - m_rows - 1] != '\n' && m_mineMap[index - m_rows - 1] != '*')
			m_mineMap[index - m_rows - 1]++;

		if ((index - m_rows) >= 0 && m_mineMap[index - m_rows] != '\n' && m_mineMap[index - m_rows] != '*')
			m_mineMap[index - m_rows]++;

		if ((index - m_rows + 1) >= 0 && m_mineMap[index - m_rows + 1] != '\n' && m_mineMap[index - m_rows + 1] != '*')
			m_mineMap[index - m_rows + 1]++;

		if ((index - 1) >= 0 && m_mineMap[index - 1] != '\n' && m_mineMap[index - 1] != '*')
			m_mineMap[index - 1]++;

		if ((index + 1) < max && m_mineMap[index + 1] != '\n' && m_mineMap[index + 1] != '*')
			m_mineMap[index + 1]++;

		if ((index + m_rows - 1) < max && m_mineMap[index + m_rows - 1] != '\n' && m_mineMap[index + m_rows - 1] != '*')
			m_mineMap[index + m_rows - 1]++;

		if ((index + m_rows) < max && m_mineMap[index + m_rows] != '\n' && m_mineMap[index + m_rows] != '*')
			m_mineMap[index + m_rows]++;

		if ((index + m_rows + 1) < max && m_mineMap[index + m_rows + 1] != '\n' && m_mineMap[index + m_rows + 1] != '*')
			m_mineMap[index + m_rows + 1]++;
	}
	void screenMapToMineMap(int offset) {
		if (m_screen->getShape(offset) == '-')
		{
			m_screen->setShape(offset, m_mineMap[offset]);
			if (m_mineMap[offset] == '0')
				decisionAroundMine(offset);
		}
	}
	void decisionAroundMine(int offset)
	{
		int max = m_cols * m_rows - 1;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (offset + (i * m_rows) + j >= 0 && offset + (i * m_rows) + j < max)
					screenMapToMineMap(offset + (i * m_rows) + j);
			}
	}
	bool isClickedMap(Position pos)
	{
		if (pos.x < m_rows - 1 && pos.y < m_cols)
			return true;
		return false;
	}
	void gameClear()
	{
		int max = m_cols * m_rows - 1;
		for (int i = 0; i < max; i++)
		{
			if (m_mineMap[i] != '*')
				if (m_mineMap[i] != m_screen->getShape(i))
					return;
		}
		m_isGameClear = true;
	}
public:
	Mine(int cols, int rows, Screen* screen, InputSystem& input) :m_cols(cols), m_rows(rows),
		m_mineMap(new char[cols * rows + 1]), m_screen(screen), m_isGameover(false), m_input(input) {

		Borland::Initialize();
		clear();
		int count = 0;
		int max = cols * rows - 1;
		while(count < MINENUM)
		{
			int index = rand() % max;
			if (getShape(index) == '0')
			{
				setShape(index, '*');
				m_mineIndex[count] = index;
				count++;
			}
		}
		mineAroundNum();
	}
	virtual ~Mine() { delete[] m_mineMap; }

	char getShape(int index) {
		return m_mineMap[index];
	}

	void setShape(int index, char shape) {
		m_mineMap[index] = shape;
	}

	bool getIsGameover() { return m_isGameover; }
	bool getIsGameClear() { return m_isGameClear; }
	
	
	void mineControl(Position pos)
	{
		if (m_input.getKeyDown(0x52)) {
			int offset = m_screen->posToOffset(pos.x, pos.y);
			if (m_screen->getShape(offset) == '-' && m_mineMap[offset] == '*')
			{
				m_isGameover = true;
			}
			screenMapToMineMap(offset);
			gameClear();
		}
		else if (m_input.getMouseButtonDown(0))
		{
			Position mousePos = m_input.getMousePosition();
			if (isClickedMap(mousePos))
			{
				int offset = m_screen->posToOffset(mousePos.x, mousePos.y);
				if (m_screen->getShape(offset) == '-' && m_mineMap[offset] == '*')
				{
					m_isGameover = true;
				}
				screenMapToMineMap(offset);
				gameClear();
			}
		}
	}
	void render()
	{
		Borland::GotoXY(0, COLS + 3);
		printf("%s\n", m_mineMap);
		printf("Number of mines %d", MINENUM);
	}
};

