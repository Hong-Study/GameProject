#include "Board.h"
#include "Consts.h"
#include <random>
#include <qdebug.h>
#include <QKeyEvent>
Board::Board(int size, Player* player)
	: _size(size)					//후에 사이즈 추가
	, _player(player)
	, _board(new TileType*[size])
{
	QGraphicsScene::addItem(&_root);
	//_root.setX(QGraphicsScene::sceneRect().width() / 2 - (Consts::BOARD_IMAGE_SIZE * _size / 2));		//X좌표 설정
	//_root.setY(QGraphicsScene::sceneRect().height() / 2 - (Consts::BOARD_IMAGE_SIZE * _size / 2));		//Y좌표 설정

	if (_size % 2 == 0)
		return;
	
	for (int i = 0; i < _size; i++) {			
		_board[i] = new TileType[_size];
	}
	GenerateByBinaryTree();
	for (int row = 0; row < _size; ++row) {
		std::vector<Item*> rowItems(_size);
		_items.push_back(rowItems);
		for (int colum = 0; colum < _size; ++colum) {
			addItem(row, colum);
		}
	}
}

void Board::GenerateByBinaryTree()
{
	//초기맵 설정
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (x % 2 == 0 || y % 2 == 0)
				_board[y][x] = TileType::Wall;
			else
				_board[y][x] = TileType::Empty;
		}
	}
	srand(unsigned(time(NULL)));

	//랜덤 길 뚫기
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
	QGraphicsScene::removeItem(item);

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
	QGraphicsScene::addItem(item);					//이름이 같지만 Scene의 addItem 함수임.
	_items[row][colum] = item;
}

void Board::moveCharcter(int y0, int x0, int y1, int x1)
{
	Item* item0 = _items[y0][x0];
	Item* item1 = _items[y1][x1];

	moveItem(item0, y1, x1);
	moveItem(item1, y0, x0);

	_items[y0][x0] = item1;
	_items[y1][x1] = item0;

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

bool Board::check(int y, int x) {
	if (TileType::Empty == _board[y][x])
		return true;
	else
		return false;
}

void Board::keyPressEvent(QKeyEvent* event) {
	qDebug() << "Good Working";
	auto x = _player->X();
	auto y = _player->Y();
	switch (event->key()) {
	case Qt::Key_Up:
		if (check(y - 1, x))
			moveCharcter(y, x, y - 1, x);
		break;
	case Qt::Key_Down:
		if (check(y + 1, x))
			moveCharcter(y, x, y + 1, x);
		break;
	case Qt::Key_Left:
		if (check(y, x - 1))
			moveCharcter(y, x, y, x-1);
		break;
	case Qt::Key_Right:
		if (check(y, x + 1))
			moveCharcter(y, x, y, x+1);
		break;
	}
}