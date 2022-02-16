#pragma once

#include <QtWidgets/qgraphicsitem>
#include <QtWidgets/qgraphicsScene>
#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <qgraphicsview.h>
#include <QKeyEvent>

#include <vector>
#include <qdebug.h>
#include "Items.h"
#include "Player.h"

class Board : public QGraphicsView{
private:
	QGraphicsScene* _scene;
	QGraphicsRectItem _root;

	std::vector<std::vector<Item*>> _items;

	enum class TileType {
		Empty,
		Wall,
		USER = 2
	};
	enum class Move {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	TileType** _board;
	int _size;
	Player* _player;

public:
	Board(QGraphicsScene* _scene, int size, Player* player);
	~Board();
	void addItem(int row, int colum);					//아이템 추가
	void GenerateByBinaryTree();						//미로 알고리즘
	void removeItem(int row, int colum);				//아이템 삭제
	void moveItem(Item* item, int toRow, int toColum);	//아이템 교환
	void moveCharcter(int x0, int y0, int x1, int y1);
	void PlayerMoveEvent();
	bool check(int x, int y);							//벽인지 확인

protected:
	virtual void keyPressEvent(QKeyEvent* Key) override;
};