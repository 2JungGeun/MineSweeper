#pragma once
#include"Utils.h"
#include"InputSystem.h"
class Player
{
	Position m_pos;
	char m_shape;
	InputSystem& m_input;
public:
	Player(int x, int y, InputSystem& input) : m_pos(x, y), m_shape('P'), m_input(input) {}

	Position getPos() { return m_pos; }
	char getShape() { return m_shape; }

	void render()
	{
		Borland::GotoXY(m_pos.x, m_pos.y);
		printf("%c", m_shape);
	}

	void playerControl() {
		
		if (m_input.getKeyDown(0x57)) {
			if (m_pos.y < 1) return;
			m_pos.y--;
		}
		else if (m_input.getKeyDown(0x41)) {
			if (m_pos.x < 1) return;
			m_pos.x--;
		}
		else if (m_input.getKeyDown(0x53)) {
			if (m_pos.y > COLS - 2) return;
			m_pos.y++;
		}
		else if (m_input.getKeyDown(0x44)) {
			if (m_pos.x > ROWS - 3) return;
			m_pos.x++;
		}
	}
};

