#include "Board.h"
#include "Player.h"

#include <>

Board::Board(int size, Player* player)
	: _size(size)
	, _board(new Node* [size] {})
	, _player(player)
{
	if (_size % 2 == 0)
		return;
	for (int i = 0; i < size; i++) {
		_board[i] = new Node[size];
	}
	GenerateByBinaryTree();
	println(true);
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
	for (int y = 0; y < _size; y++) {

		for (int x = 0; x < _size; x++) {
			if (x % 2 == 0 || y % 2 == 0) {
				_board[y][x].type = TileType::Wall;
			}
			else {
				_board[y][x].type = TileType::Empty;
				_board[y][x].came = false;
			}
			_board[y][x].tipe = TileVisible::Invisible;//������� �Ⱥ��̰� ����
		}
	}
	RecursiveBackTraing(1, 1);
	_board[1][1].type = TileType::USER;
}

void Board::shuffleArray(int* array, int size) {
	int i, r, temp;
	for (i = 0; i < (size - 1); ++i)
	{
		r = i + (rand() % (size - i));
		temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
}
void Board::RecursiveBackTraing(int y, int x) {
	int r, nx, ny;
	int directions[4] = {
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
void Board::println(bool m)
{
	if (!m)
		system("cls");
	int a, b;
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (_board[y][x].tipe == TileVisible::Visible) {//������ �̺�Ʈ ��, �þ߿� ���Դ� ����(������ ����)��
				if (_board[y][x].type == TileType::Empty)//������� ��쿡��
					_board[y][x].tipe = TileVisible::noVisible;//1���������� ����
				else                                      //���� ��쿡��
					_board[y][x].tipe = TileVisible::nonVisible;//2���������κ���
															//(�������� ������ ���̶� ���̶� ����)
			}
			if (_board[y][x].type == TileType::USER) {
				a = y, b = x;
			}//������ġ a,b�� ����
		}
	}
	double c, d;
	for (int i = 0; i < 360; i++) {
		c = (double)a + 0.5, d = (double)b + 0.5;
		while (true) {
			c += sin(i) / 100;
			d += cos(i) / 100;
			_board[(int)c][(int)d].tipe = TileVisible::Visible;
			if (_board[(int)c][(int)d].type == TileType::Wall) {
				_board[(int)c][(int)d].tipe = TileVisible::Visible;
				break;
			}
		}//���� ��ġ �������� 360���� 1���� ���ư��鼭 ����, 0.1ĭ�� ������ �����ϸ鼭
		//������ ��� ������ �� �� �ִ� ����(Visible)�� �����ϰ�
		//���� ������ ���� visible�� �ٲٸ鼭 ��������
		//(360�� �ݺ�)

		//������ �������� �ϴ� �˰��� �������µ�
		//�Ϻ������� ����ȵǰų� �Ⱥ������ϴ°����� ���̰��ϴ� ������
		//��� ���淡 �����߾��..
	}

	//#include <QAmbientLightReading> ����
	// �������� ���Ҽ��ֱ淡 �Ÿ������� ������(0~5)�� �ҷ��µ�
	// ������ ���Ƽ� �׷��� �ȶ߱淡.. �ϴ� �Ʒ��ɷ� ǥ���߾��
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (_board[y][x].type == TileType::Wall) {//���϶�
				if (_board[y][x].tipe == TileVisible::Visible) // �þ߹������� ��
					std::cout << "��";
				else if (_board[y][x].tipe == TileVisible::nonVisible)// �þ߹��� ���� �� //(2������)
					std::cout << "��";
				else                                            //�� ���� ��� ��
					std::cout << "��";
			}
			else if (_board[y][x].type == TileType::USER) {  // ������ġ
				std::cout << "��";
			}
			else {//�̵����ɰ����� ��
				if (_board[y][x].tipe == TileVisible::Visible)// �þ߹��� �� �̵� ���� ����
					std::cout << "  ";
				else if (_board[y][x].tipe == TileVisible::noVisible)   //(1������)
					std::cout << "��";//�þ߹����� �� �� �̻� ������ �̵� ����
				else
					std::cout << "��";//�þ߹��� ���� �̵� ����
			}
		}
		std::cout << std::endl;
	}
}

void Board::moveCharcter(int x0, int y0, int x1, int y1)
{
	TileType tmp = _board[y0][x0].type;
	_board[y0][x0].type = _board[y1][x1].type;
	_board[y1][x1].type = tmp;

	_player->set_X(x1);
	_player->set_Y(y1);
}
bool Board::check(int x, int y) {
	if (TileType::Empty == _board[y][x].type)
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
		if (_kbhit()) {
			c = _getch();
			if (c == -32) {
				c = _getch();
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
					if (check(x, y + 1))
						moveCharcter(x, y, x, y + 1);
					break;
				case static_cast<int>(Player::Move::UP):
					if (check(x, y - 1))
						moveCharcter(x, y, x, y - 1);
					break;
				}
			}
			println(false);
		}
	}
}