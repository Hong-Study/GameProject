#pragma once

#include <QtWidgets/qgraphicsitem>
#include <QtWidgets/qgraphicsScene>
#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <qgraphicsview.h>
#include <QKeyEvent>

#include <vector>
#include <qdebug.h>
#include <random>
#include "Items.h"
#include "Player.h"

class Board : public QGraphicsScene {
private:
	QGraphicsRectItem _root;
	std::vector<std::vector<Item*>> _items;

	enum class TileType {
		Empty,
		Wall,
		USER = 2
	};
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	struct Node {
		TileType type;
		bool came;
	};
	int directions[4] = {
			Direction::UP,
			Direction::DOWN,
			Direction::LEFT,
			Direction::RIGHT
	};
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	Node** _board;

	void GenerateByBinaryTree();				// 초기 맵 설정
	void RecursiveBackTraing(int y, int x);		// Maze Algorithm
	void shuffleArray(int* array, int size);
	int inRange(int y, int x);

	int _size;
	Player* _player;

public:
	Board(int size, Player* player);
	~Board();
	void addItem(int row, int colum);					//아이템 추가
	void removeItem(int row, int colum);				//아이템 삭제
	void moveItem(Item* item, int toRow, int toColum);	//아이템 교환
	void moveCharcter(int x0, int y0, int x1, int y1);
	void keyPressEvent(QKeyEvent* event);
	bool check(int x, int y);							//벽인지 확인
	/*class PressEvent {
	public:
		virtual void PlayerMoveEvent() = 0;
	};*/
};

