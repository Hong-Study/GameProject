#include "Board.h"
#include "Consts.h"

#include <random>
#include <qdebug.h>
#include <QKeyEvent>
Board::Board(int size, Player* player, int trap)
	: _size(size)					//후에 사이즈 추가
	, _player(player)
	, _board(new Node* [size])
	, _trap(trap)
{
	QGraphicsScene::addItem(&_root);
	//_root.setX(QGraphicsScene::sceneRect().width() / 2 - (Consts::BOARD_IMAGE_SIZE * _size / 2));		//X좌표 설정
	//_root.setY(QGraphicsScene::sceneRect().height() / 2 - (Consts::BOARD_IMAGE_SIZE * _size / 2));		//Y좌표 설정
	if (_size % 2 == 0)
		return;
	for (int i = 0; i < _size; i++) {
		_board[i] = new Node[_size];
	}
	GenerateByBinaryTree();
	Make_Trap();
	Setting_Lighting(_player->Y(), _player->X(), true);

	for (int row = 0; row < _size; ++row) {
		std::vector<Item*> rowItems(_size);
		_items.push_back(rowItems);
		for (int colum = 0; colum < _size; ++colum) {
			addItem(row, colum);
		}
	}
	for (int y = _size - 2; y > 1; y--) {
		if (_board[y][_size - 2].type == TileType::Empty) {
			_board[y][_size - 1].type = TileType::Empty;
			_player->set_winX(_size - 1);
			_player->set_winY(y);
			break;
		}
	}
	victory.setText("Win!!");
	victory.setGeometry((_size*Consts::BOARD_IMAGE_SIZE) / 2 - 50, (_size * Consts::BOARD_IMAGE_SIZE) / 2 - 15, 120, 30);
	UI.setGeometry(0, _size * Consts::BOARD_IMAGE_SIZE + 10, _size * Consts::BOARD_IMAGE_SIZE, 30);
	UI.setText(UI_Text.sprintf("Delete_Trap : %d\t\t Show_Map : %d", _player->left_Check(), _player->left_show()));
	QGraphicsScene::addWidget(&UI);
	QGraphicsScene::connect(&victory, SIGNAL(clicked()), this, SLOT(btn_click()));
}

void Board::GenerateByBinaryTree()
{
	//초기맵 설정
	for (int y = 0; y < _size; y++) {

		for (int x = 0; x < _size; x++) {
			if (x % 2 == 0 || y % 2 == 0) {
				_board[y][x].type = TileType::Wall;
			}
			else {
				_board[y][x].type = TileType::Empty;
				_board[y][x].came = false;
			}
			_board[y][x].vision = TileVisible::Invisible;//모든지역 안보이게 설정
		}
	}
	RecursiveBackTraing(1, 1);
	_board[1][1].type = TileType::USER;
}

void Board::shuffleArray(int* array, int size) {
	int i, r, temp;
	for (i = 0; i < (size - 1); ++i)
	{
		r = i + (rand(0,4) % (size - i));
		temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
}
void Board::RecursiveBackTraing(int y, int x) {
	int r, nx, ny;
	int directions[5] = {
			Direction::UP,
			Direction::DOWN,
			Direction::LEFT,
			Direction::RIGHT
	};
	_board[y][x].came = true;
	shuffleArray(directions, 4);

	for (r = 0; r < 4; r++) {
		nx = x + DIR[directions[r]][0];
		ny = y + DIR[directions[r]][1];

		if (inRange(ny, nx) && (_board[ny][nx].type == TileType::Empty) && !_board[ny][nx].came) {
			std::cout << "start : " << nx << " : " << ny << std::endl;
			RecursiveBackTraing(ny, nx);
			if (ny != y) {
				_board[(ny + y) / 2][nx].type = TileType::Empty;
			}
			else {
				_board[ny][(nx + x) / 2].type = TileType::Empty;
			}
		}
	}
}
int Board::inRange(int y, int x)
{
	return (y > 0 && y < _size - 1) && (x > 0 && x < _size - 1);
}
Board::~Board()
{
	for (int row = 0; row < _items.size(); ++row) {
		for (int colum = 0; colum < _items[row].size(); ++colum) {
			removeItem(row, colum);
			delete _items[row][colum];
		}		
	}
	for (int i = 0; i < _size; i++) {
		delete _board[i];
	}
	delete _board;
}
void Board::Setting_Lighting(int y, int x, bool m) {
	if (m) {
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (_board[i][j].vision == TileVisible::Visible)
					_board[i][j].vision = TileVisible::detectInvisible;
			}
		}
	}
	_board[y][x].vision = TileVisible::Visible;
	for (int i = 0; i < 4; i++) {
		int directX, directY;
		if (i == 0)
			directX = 1, directY = 0;
		if (i == 1)
			directX = -1, directY = 0;
		if (i == 2)
			directX = 0, directY = 1;
		if (i == 3)
			directX = 0, directY = -1;
		int a = y, b = x;
		a += directY;
		b += directX;
		_board[a + directX][b + directY].vision = TileVisible::Visible;
		_board[a - directX][b - directY].vision = TileVisible::Visible;
		_board[a][b].vision = TileVisible::Visible;
		if (check(y + directY, x + directX)) {
			while (true) {
				a += directY;
				b += directX;
				_board[a + directX][b + directY].vision = TileVisible::Visible;
				_board[a - directX][b - directY].vision = TileVisible::Visible;
				_board[a][b].vision = TileVisible::Visible;
				if (!check(a, b))
					break;
			}
		}
	}
}
void Board::Make_Trap() {
	int x, y;
	
	while (_trap > 0) {
		x = rand(2, _size - 2);
		y = rand(2, _size - 2);
		if (_board[y][x].type == TileType::Empty) {
			if (check(y - 1, x) == 2)
				continue;
			else if (check(y + 1, x) == 2)
				continue;
			else if (check(y, x - 1) == 2)
				continue;
			else if (check(y, x + 1) == 2)
				continue;
			else {
				_board[y][x].type = TileType::Trap;
				_trap--;
			}
		}
	}
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
	const std::string& path_black = Consts::paths[3].c_str();
	const std::string& path_visibleEmpty = Consts::paths[4].c_str();
	const std::string& path_trap = Consts::paths[5].c_str();

	Item* item;
	if (_board[row][colum].vision == TileVisible::Visible) {
		if (_board[row][colum].type == TileType::Wall)
			item = new Item(path_wall, row, colum, &_root);
		else if (_board[row][colum].type == TileType::USER)
			item = new Item(path_user, row, colum, &_root);
		else if (_board[row][colum].type == TileType::Empty)
			item = new Item(path_empty, row, colum, &_root);
		else if (_board[row][colum].type == TileType::Trap)
			item = new Item(path_trap, row, colum, &_root);
	}
	else if (_board[row][colum].vision == TileVisible::detectInvisible) {
		if (_board[row][colum].type == TileType::Wall)
			item = new Item(path_black, row, colum, &_root);
		else if (_board[row][colum].type == TileType::Empty)
			item = new Item(path_visibleEmpty, row, colum, &_root);
		else if (_board[row][colum].type == TileType::Trap)
			item = new Item(path_visibleEmpty, row, colum, &_root);
		_board[row][colum].vision = TileVisible::alreadyVisible;
	}
	else
		item = new Item(path_black, row, colum, &_root);
	
	/*if (_board[row][colum].type == TileType::Wall)
		item = new Item(path_wall, row, colum, &_root);
	else if (_board[row][colum].type == TileType::USER)
		item = new Item(path_user, row, colum, &_root);
	else
		item = new Item(path_empty, row, colum, &_root);*/

	item->setPos(colum * Consts::BOARD_IMAGE_SIZE, row * Consts::BOARD_IMAGE_SIZE +10);
	QGraphicsScene::addItem(item);					//이름이 같지만 Scene의 addItem 함수임.
	_items[row][colum] = item;
}
int Board::rand(int a, int b) {
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(a, b);

	return dis(gen);
}
void Board::moveCharcter(int y0, int x0, int y1, int x1)
{
	if (check(y1, x1) == 2) {
		_board[y1][x1].type = TileType::Empty;
		_board[y1][x1].vision = TileVisible::detectInvisible;
		removeItem(y1, x1);
		addItem(y1, x1);

		while (true) {
			y1 = rand(2, _size - 2);
			x1 = rand(2, _size - 2);
			if (_board[y1][x1].type == TileType::Empty)
				break;
		}
	}
	_board[y1][x1].vision = TileVisible::detectInvisible;
	Item* item0 = _items[y0][x0];
	Item* item1 = _items[y1][x1];

	moveItem(item0, y1, x1);
	moveItem(item1, y0, x0);

	_items[y0][x0] = item1;
	_items[y1][x1] = item0;

	Node tmp = _board[y0][x0];
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

int Board::check(int y, int x) {
	if (TileType::Empty == _board[y][x].type)
		return 1;
	else if (TileType::Trap == _board[y][x].type)
		return 2;
	else
		return 0;
}
void Board::usingItem1(int y, int x) {
	for (int i = 0; i < 4; i++) {
		int directX, directY;
		if (i == 0)
			directX = 1, directY = 0;
		if (i == 1)
			directX = -1, directY = 0;
		if (i == 2)
			directX = 0, directY = 1;
		if (i == 3)
			directX = 0, directY = -1;
		int a = y, b = x;
		if (check(a + directY, b + directX)) {//공기일때
			while (true) {
				if (!check(a + directY, b + directX)) {
					Setting_Lighting(a, b, false);
					break;
				}
				a += directY;
				b += directX;
			}
		}
	}
}

void Board::keyPressEvent(QKeyEvent* event) {
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
			moveCharcter(y, x, y, x - 1);
		break;
	case Qt::Key_Right:
		if (check(y, x + 1))
			moveCharcter(y, x, y, x + 1);
		break;
	case Qt::Key_A:
		if (check(y - 1, x) == 2 && _player->Check()) {
			_board[y - 1][x].type = TileType::Empty;
			removeItem(y - 1, x);
			addItem(y - 1, x);
		}
		else if (check(y + 1, x) == 2 && _player->Check()) {
			_board[y + 1][x].type = TileType::Empty;
			removeItem(y - 1, x);
			addItem(y - 1, x);
		}
		else if (check(y, x - 1) == 2 && _player->Check()) {
			_board[y][x-1].type = TileType::Empty;
			removeItem(y - 1, x);
			addItem(y - 1, x);
		}
		else if (check(y, x + 1) == 2 && _player->Check()) {
			_board[y][x+1].type = TileType::Empty;
			removeItem(y - 1, x);
			addItem(y - 1, x);
		}
	}
	x = _player->X();
	y = _player->Y();
	if (event->key() == Qt::Key_D && _player->Show_Mape()) {
		usingItem1(y, x);
		new_Setting(y, x, false);
	}
	else
		new_Setting(y, x, true);
	if (_player->Victory_Chekc()) {	
		QGraphicsScene::addWidget(&victory);
		music.Play();
	}
	UI.setText(UI_Text.sprintf("Delete_Trap : %d\t\t Show_Map : %d", _player->left_Check(), _player->left_show()));
}
void Board::new_Setting(int y, int x, bool m) {
	Setting_Lighting(y, x, m);
	for (int row = 0; row < _size; ++row) {
		for (int colum = 0; colum < _size; ++colum) {
			if (_board[row][colum].vision == TileVisible::detectInvisible) {
				removeItem(row, colum);
				addItem(row, colum);
			}
			else if (_board[row][colum].vision == TileVisible::Visible) {
				removeItem(row, colum);
				addItem(row, colum);
			}
		}
	}
}
void Board::btn_click() {
	exit(0);
}