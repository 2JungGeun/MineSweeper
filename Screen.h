#pragma once
#include"Utils.h"
#include"InputSystem.h"
class Screen
{
	int m_cols;
	int m_rows;
	char* m_map;
	int m_flagNum;
	InputSystem& m_input;

	bool isClickedMap(Position pos)
	{
		if (pos.x < m_rows - 1 && pos.y < m_cols)
			return true;
		return false;
	}

public:
	Screen(int cols, int rows, InputSystem& input) : m_cols(cols), m_rows(rows), m_map(new char[cols * rows + 1]), m_flagNum(0), m_input(input) {
		Borland::Initialize();
		clear();
	}
	virtual ~Screen() {
		delete[] m_map;
	}

	int posToOffset(int x, int y) { return x + y * m_rows; }
	char getShape(int offset) { return m_map[offset]; }
	void setShape(int offset, char shape) { m_map[offset] = shape; }
	void clear() {
		memset(m_map, '-', m_cols * m_rows);
		for (int i = 1; i <= m_cols; i++)
		{
			m_map[i * m_rows - 1] = '\n';
		}
		m_map[m_cols * m_rows] = '\0';
	}

	void screenContol(Position pos) {
		if (m_input.getKeyDown(0x46)) {
			int offset = posToOffset(pos.x, pos.y);
			if (m_map[offset] == '-') {
				m_map[offset] = 'X';
				m_flagNum++;
			}
			else if (m_map[offset] == 'X') {
				m_map[offset] = '-';
				m_flagNum--;
			}
		}
		else if (m_input.getMouseButtonDown(1))
		{
			Position mousePos = m_input.getMousePosition();
			if (isClickedMap(pos))
			{
				int offset = posToOffset(mousePos.x, mousePos.y);
				if (m_map[offset] == '-') {
					m_map[offset] = 'X';
					m_flagNum++;
				}
				else if (m_map[offset] == 'X') {
					m_map[offset] = '-';
					m_flagNum--;
				}
			}
		}
	}

	void render() {
		Borland::GotoXY(0, 0);
		printf("%s", m_map);
	}
};

