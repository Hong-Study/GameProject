#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qgraphicseffect.h>

#include <qgraphicsview.h>
#include <iostream>
#include "item.h"
#include "Player.h"

class Board : public QGraphicsScene {
private:
	enum class TileType {
		Wall,
		Empty,
		USER,
		Trap
	};
	enum class TileVisible {
		Visible, // 시야 내 구간
		Invisible, // 시야 외 구간
		noVisible, // 시야 내 -> 시야 외 구간 - (길)
		//nonVisible // 시야 내 -> 시야 외 구간 - (벽)
	};
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	struct Node {
		TileType type;
		TileVisible tipe;
		bool came;
	};
	Node** _board;		//맵
	std::vector<std::vector<Item*>> _items;		//실질적 이미지 표현(_board를 통해서)
	QGraphicsRectItem _root;
	Player* _player;
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	int _size;
	int _trap;
	
public:
	Board::Board(int size, Player* player,int trap);
	void Board::GenerateByBinaryTree();
	Board::~Board();

	void Board::removeItem(int row, int colum);		//아이템 삭제
	void Board::addItem(int row, int colum);		//아이템 추가

	void Board::moveCharcter(int y0, int x0, int y1, int x1);	//캐릭터 이동
	void Board::moveItem(Item* item, int toRow, int toColum);	//도우미

	int Board::check(int y, int x);				//도로 인지 함정인지 판단
	void Board::keyPressEvent(QKeyEvent* event);

	void Board::shuffleArray(int* array, int size);		//맵 생성시 셔플
	int Board::inRange(int y, int x);					//맵 생성시 내부 제한
	void Board::RecursiveBackTraing(int y, int x);		//맵 알고리즘
	
	void Make_Trap();			//트랩 생성
	int rand(int a, int b);		//a~b 안의 랜덤 인수 생성
	void Setting_Lighting(int y, int x);
};