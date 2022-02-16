#pragma once
#include <iostream>
#include <random>
#include <time.h>
#include "Player.h"

class Board :public Player::EventListner{
private:
	enum class TileType {
		Empty,
		Wall,
		USER = 2
	};

	TileType** _board;
	int _size;
	Player* _player;
public:
	Board() = delete;
	Board(int size,Player* player);
	~Board();
	void GenerateByBinaryTree();
	void println(bool m);
	void moveCharcter(int x0, int y0, int x1, int y1);
	bool check(int x, int y);
	virtual void PlayerMoveEvent();
	
};