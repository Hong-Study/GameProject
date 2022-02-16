#include "Board.h"
#include "Player.h"

Board::Board(int size, Player* player)
	: _size(size)
	, _board(new TileType* [size] {})
	, _player(player)
{
	if (size % 2 == 0)
		return;
	for (int i = 0; i < size; i++) {
		_board[i] = new TileType[size];
	}

	GenerateByBinaryTree();
}
Board::~Board()
{
	for (int i = 0; i < _size; i++) {
		delete _board[i];
	}
	delete _board;
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
				_board[y+1][x] = TileType::Empty;
			}
		}
	}
	_board[_player->Y()][_player->X()] = TileType::USER;
	println(true);
}

void Board::println(bool m)
{
	if (!m)
		system("cls");
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (_board[y][x] == TileType::Wall) 
				std::cout << "��";
			else if(_board[y][x] == TileType::USER)
				std::cout << "��";
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

void Board::moveCharcter(int x0, int y0, int x1, int y1)
{
	TileType tmp = _board[y0][x0];
	_board[y0][x0] = _board[y1][x1];
	_board[y1][x1] = tmp;

	_player->set_X(x1);
	_player->set_Y(y1);
}
bool Board::check(int x, int y) {
	if (TileType::Empty == _board[y][x])
		return true;
	else
		return false;
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
				case static_cast<int>(Player::Move::LEFT):
					if (check(x - 1, y))
						moveCharcter(x, y, x - 1, y);
					break;
				case static_cast<int>(Player::Move::RIGHT):
					if (check(x + 1, y))
						moveCharcter(x, y, x + 1, y);
					break;
				case static_cast<int>(Player::Move::DOWN):
					if (check(x, y+1))
						moveCharcter(x, y, x , y+1);
					break;
				case static_cast<int>(Player::Move::UP):
					if (check(x, y - 1))
						moveCharcter(x, y, x, y-1);
					break;
				}
			}
			println(false);
		}
	}
}