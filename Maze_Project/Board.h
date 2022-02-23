#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qgraphicseffect.h>
#include <QtWidgets/qpushbutton.h>
#include <iostream>

#include "item.h"
#include "Player.h"

class Board : public QGraphicsScene {
	Q_OBJECT
private:
	enum class TileType {
		Wall,
		Empty,
		USER,
		Trap,
		Echo
	};
	enum class TileVisible {
		Visible, // 시야 내 구간
		Invisible, // 시야 외 구간
		detectInvisible, // 시야 내 구간 -> 외 구간 바뀜
	};
	/*enum class MetaVerse {
		detecting,
		nonDetecting
	};*/
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		skill1
	};
	struct Node {
		TileType type;
		TileVisible vision;
		//MetaVerse detecting;
		bool came;
	};
	Node** _board;		// 미니맵
	std::vector<std::vector<Item*>> _items;		//실질적 보드
	QGraphicsRectItem _root;
	Player* _player;
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	int _size;
	int _trap;

	QPushButton victory;

private slots:
	void btn_click();

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