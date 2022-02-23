#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qgraphicseffect.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <qstring.h>
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
		Trap
	};
	enum class TileVisible {
		Visible, // �þ� �� ����
		Invisible, // �þ� �� ����
		detectInvisible, // �þ� �� ���� -> �� ���� �ٲ�
		alreadyVisible // �þ� �� ���� -> �� �������� �̹� �ٲ� ����
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
		bool came;
	};
	Node** _board;		// �̴ϸ�
	std::vector<std::vector<Item*>> _items;		//������ ����
	QGraphicsRectItem _root;
	Player* _player;
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	int _size;
	int _trap;

	QPushButton victory;
	QLabel UI;
	QString UI_Text;
private slots:
	void btn_click();

public:
	Board::Board(int size, Player* player,int trap);
	void Board::GenerateByBinaryTree();
	Board::~Board();

	void Board::removeItem(int row, int colum);		//������ ����
	void Board::addItem(int row, int colum);		//������ �߰�

	void Board::moveCharcter(int y0, int x0, int y1, int x1);	//ĳ���� �̵�
	void Board::moveItem(Item* item, int toRow, int toColum);	//�����

	int Board::check(int y, int x);				//���� ���� �������� �Ǵ�
	void Board::keyPressEvent(QKeyEvent* event);

	void Board::shuffleArray(int* array, int size);		//�� ������ ����
	int Board::inRange(int y, int x);					//�� ������ ���� ����
	void Board::RecursiveBackTraing(int y, int x);		//�� �˰���
	
	void Make_Trap();			//Ʈ�� ����
	int rand(int a, int b);		//a~b ���� ���� �μ� ����
	void Setting_Lighting(int y, int x, bool m);
	void usingItem1(int y, int x);
	void new_Setting(int y, int x, bool m);
};