#pragma once
#include <iostream>
#include <random>
#include <time.h>
#include "Player.h"

class Board :public Player::EventListner {
private:
	int _size;
	Player* _player;

public:
	Board() = delete;
	Board(int size, Player* player);
	~Board();

	void println(bool m);
	void moveCharcter(int x0, int y0, int x1, int y1);
	bool check(int x, int y);

	virtual void PlayerMoveEvent();

private:
	enum class TileType {
		Empty,
		Wall,
		USER = 2
	};//타일을 공간, 벽, 유저 3개로 나눔
	enum class TileVisible {
		Visible, // 시야 내 구간
		Invisible, // 시야 외 구간
		noVisible, // 시야 내 -> 시야 외 구간 - (길)
		nonVisible // 시야 내 -> 시야 외 구간 - (벽)
	};
	enum class sight {
		sight = false
	};
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN//움직임 감지
	};
	struct Node {
		TileType type;
		TileVisible tipe; // 시야관련
		bool came;// 타일타입, 캠
	};
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	Node** _board;// 이동공간(?)


	void GenerateByBinaryTree();	// 초기 맵 설정
	void RecursiveBackTraing(int start_X, int start_Y);		// Maze Algorithm
	void shuffleArray(int* array, int size);
	int inRange(int y, int x);
};