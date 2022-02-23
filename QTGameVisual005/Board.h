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
		Trap,
		Echo
	};
	enum class TileVisible {
		Visible, // �þ� �� ����
		Invisible, // �þ� �� ����
		detectInvisible, // �þ� �� -> �þ� �� ���� - 
	};
	enum class MetaVerse {
		detecting,
		nonDetecting
	};
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
		MetaVerse detecting;
		bool came;
	};
	Node** _board;		//��
	std::vector<std::vector<Item*>> _items;		//������ �̹��� ǥ��(_board�� ���ؼ�)
	QGraphicsRectItem _root;
	Player* _player;
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	int _size;
	int _trap;

public:
	Board::Board(int size, Player* player, int trap);
	void Board::GenerateByBinaryTree();
	Board::~Board();

	void Board::removeItem(int row, int colum);		//������ ����
	void Board::addItem(int row, int colum);		//������ �߰�

	void Board::item1(int y, int x, int directY, int directX);
	void Board::moveCharcter(int y0, int x0, int y1, int x1);	//ĳ���� �̵�
	void Board::moveItem(Item* item, int toRow, int toColum);	//�����

	int Board::check(int y, int x);				//���� ���� �������� �Ǵ�
	void Board::keyPressEvent(QKeyEvent* event);

	void Board::shuffleArray(int* array, int size);		//�� ������ ����
	int Board::inRange(int y, int x);					//�� ������ ���� ����
	void Board::RecursiveBackTraing(int y, int x);		//�� �˰�����

	void Make_Trap();			//Ʈ�� ����
	int rand(int a, int b);		//a~b ���� ���� �μ� ����
	void Setting_Lighting(int y, int x, int size);
};