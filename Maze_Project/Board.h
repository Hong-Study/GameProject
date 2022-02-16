#pragma once

#include <QtWidgets/qgraphicsitem>
#include <QtWidgets/qgraphicsScene>
#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>

#include <QKeyEvent>

#include <vector>
#include <qdebug.h>
#include "Items.h"
#include "Player.h"

class Board {
private:
	QGraphicsScene* _scene;
	QGraphicsRectItem _root;

	std::vector<std::vector<Item*>> _items;
	//std::mt19937 _gen;                     //�õ� ��(device())���� �Ϸ��� ���� ����. �� �õ尪�� ������ ���� ���� ����. �׷��� �õ尪���� ���Ͽ� ���濩�� Ȯ�� ����

	enum class TileType {
		Empty,
		Wall,
		USER = 2
	};
	enum class Move {
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77
	};

	TileType** _board;
	int _size;
	Player* _player;

public:
	Board(QGraphicsScene* _scene, int size, Player* player);
	~Board();
	void addItem(int row, int colum);
	void GenerateByBinaryTree();
	void removeItem(int row, int colum);
	void moveItem(Item* item, int toRow, int toColum);
	void moveCharcter(int x0, int y0, int x1, int y1);
	bool check(int x, int y);

protected:
	void keyPressEvent(QKeyEvent* event);
	void PlayerMoveEvent();
};