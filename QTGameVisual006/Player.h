#pragma once
#include<conio.h>
#include<iostream>

class Player {
private:
	int _x;
	int _y;
	std::string _name;
public:
	Player(int x, int y, std::string name);
	int X();
	int Y();
	void set_X(int x);
	void set_Y(int y);//플레이어 x,,y좌표

	enum class Move {
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77//움직임
	};
	class EventListner {
	public:
		virtual void PlayerMoveEvent() = 0;
	};
};