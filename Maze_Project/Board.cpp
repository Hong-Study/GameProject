#include "Board.h"
#include "Consts.h"
#include "Player.h"
#include "Items.h"
#include <random>
#include <qdebug.h>


Board::Board(QGraphicsScene* _scene, int size, Player* player)
	: _scene(_scene)
	, _size(size)
	, _player(player)
	, _board(new TileType*[size])
{
	_scene->addItem(&_root);
	_root.setX(_scene->sceneRect().width() / 2 - (Consts::BOARD_IMAGE_SIZE * Consts::BOARD_LENGTH / 2));		//X��ǥ ����
	_root.setY(_scene->sceneRect().height() / 2 - (Consts::BOARD_IMAGE_SIZE * Consts::BOARD_LENGTH / 2));		//Y��ǥ ����

	if (size % 2 == 0)
		return;

	for (int i = 0; i < size; i++) {
		_board[i] = new TileType[size];
	}
	GenerateByBinaryTree();

	for (int row = 0; row < Consts::BOARD_LENGTH; ++row) {
		std::vector<Item*> rowItems(Consts::BOARD_LENGTH);
		_items.push_back(rowItems);
		for (int colum = 0; colum < Consts::BOARD_LENGTH; ++colum) {
			addItem(row, colum);
		}
	}
}

void Board::GenerateByBinaryTree()
{
	//�ʱ�� ����
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (x % 2 == 0 || y % 2 == 0)
				_board[y][x] = TileType::Wall;
			else
				_board[y][x] = TileType::Empty;
		}
	}
	srand(unsigned(time(NULL)));

	//���� �� �ձ�
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (x % 2 == 0 || y % 2 == 0)
				continue;
			if (y == _size - 2) {
				_board[y][x + 1] = TileType::Empty;
				continue;
			}
			if (x == _size - 2) {
				_board[y + 1][x] = TileType::Empty;
				continue;
			}
			if (rand() % 2 == 0) {
				_board[y][x + 1] = TileType::Empty;
			}
			else {
				_board[y + 1][x] = TileType::Empty;
			}
		}
	}
	_board[_player->Y()][_player->X()] = TileType::USER;
}
Board::~Board()
{
	for (int row = 0; row < _items.size(); ++row) {
		for (int colum = 0; colum < _items[row].size(); ++colum) {
			removeItem(row, colum);
		}
	}
	for (int i = 0; i < _size; i++) {
		delete _board[i];
	}
	delete _board;
}

void Board::removeItem(int row, int colum)
{
	auto* item = _items[row][colum];
	if (item == nullptr)
		return;

	_items[row][colum] = nullptr;
	item->setParentItem(nullptr);
	_scene->removeItem(item);

	delete item;
}
void Board::addItem(int row, int colum)
{
	const std::string& path_wall = Consts::paths[0].c_str();
	const std::string& path_empty = Consts::paths[1].c_str();
	const std::string& path_user = Consts::paths[2].c_str();
	Item* item;
	if(_board[row][colum] == TileType::Wall)
		item = new Item(path_wall, row, colum, &_root);
	else if(_board[row][colum] == TileType::USER)
		item = new Item(path_user, row, colum, &_root);
	else
		item = new Item(path_empty, row, colum, &_root);

	item->setPos(colum * Consts::BOARD_IMAGE_SIZE, row * Consts::BOARD_IMAGE_SIZE);
	_scene->addItem(item);					//�̸��� ������ Scene�� addItem �Լ���.
	_items[row][colum] = item;
}

void Board::moveCharcter(int x0, int y0, int x1, int y1)
{
	Item* item0 = _items[x0][y0];
	Item* item1 = _items[x1][y1];

	moveItem(item0, x1, y1);
	moveItem(item1, x0, y0);

	_items[x0][y0] = item1;
	_items[x1][y1] = item0;

	

	TileType tmp = _board[y0][x0];
	_board[y0][x0] = _board[y1][x1];
	_board[y1][x1] = tmp;

	_player->set_X(x1);
	_player->set_Y(y1);
}

void Board::moveItem(Item* item, int toRow, int toColum)
{
	item->setRow(toRow);
	item->setColum(toColum);
	item->setPos(toColum * Consts::BOARD_IMAGE_SIZE, toRow * Consts::BOARD_IMAGE_SIZE);

	_items[toRow][toColum] = item;
}

bool Board::check(int x, int y) {
	if (TileType::Empty == _board[y][x])
		return true;
	else
		return false;
}

void Board::keyPressEvent(QKeyEvent* Key)
{
	qDebug() << "���� �۵���";
	
	switch (Key->key()) {
	case Qt::Key_Up:
		qDebug() << "Up";
		break;
	case Qt::Key_Down:
		qDebug() << "Down";
		break;
	case Qt::Key_Left:
		qDebug() << "Left";
		break;
	case Qt::Key_Right:
		qDebug() << "Right";
		break;
	}
}

void Board::PlayerMoveEvent()
{
	char c;
	int x;
	int y;
	for (;;) {
		if (_kbhit()) {        //Ű���� �Է� Ȯ�� (true / false)
			c = _getch();      // ����Ű �Է½� 224 00�� ������ �Ǳ⿡ �տ� �ִ� �� 224�� ����
			if (c == -32) {    // -32�� �ԷµǸ�
				c = _getch();  // ���� �Է°��� �Ǻ��Ͽ� �����¿� ���
				x = _player->X();
				y = _player->Y();
				switch (c) {
				case static_cast<int>(Move::LEFT):
					if (check(x - 1, y))
						moveCharcter(x, y, x - 1, y);
					break;
				case static_cast<int>(Move::RIGHT):
					if (check(x + 1, y))
						moveCharcter(x, y, x + 1, y);
					break;
				case static_cast<int>(Move::DOWN):
					if (check(x, y + 1))
						moveCharcter(x, y, x, y + 1);
					break;
				case static_cast<int>(Move::UP):
					if (check(x, y - 1))
						moveCharcter(x, y, x, y - 1);
					break;
				}
			}
		}
	}
}