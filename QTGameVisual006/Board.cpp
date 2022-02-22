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
			_board[y][x].tipe = TileVisible::Invisible;//모든지역 안보이게 설정
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
			if (_board[y][x].tipe == TileVisible::Visible) {//움직임 이벤트 전, 시야에 들어왔던 지역(밝혀진 지역)들
				if (_board[y][x].type == TileType::Empty)//빈공간일 경우에는
					_board[y][x].tipe = TileVisible::noVisible;//1번유형으로 변경
				else                                      //벽일 경우에는
					_board[y][x].tipe = TileVisible::nonVisible;//2번유형으로변경
															//(지나갔던 지역의 벽이랑 길이랑 구분)
			}
			if (_board[y][x].type == TileType::USER) {
				a = y, b = x;
			}//유저위치 a,b에 저장
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
		}//유저 위치 기준으로 360도를 1도씩 돌아가면서 보고, 0.1칸씩 앞으로 전진하면서
		//지나간 모든 지역을 볼 수 있는 지역(Visible)로 지정하고
		//벽에 닿으면 벽을 visible로 바꾸면서 빠져나옴
		//(360번 반복)

		//꼭짓점 기준으로 하는 알고리즘 만들어볼랬는데
		//일부지역이 적용안되거나 안보여야하는곳까지 보이고하는 문제가
		//계속 나길래 포기했어요..
	}

	//#include <QAmbientLightReading> 쓰면
	// 밝기수준을 정할수있길래 거리에따라 밝기수준(0~5)로 할랬는데
	// 버전이 낮아서 그런지 안뜨길래.. 일단 아래걸로 표시했어요
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (_board[y][x].type == TileType::Wall) {//벽일때
				if (_board[y][x].tipe == TileVisible::Visible) // 시야범위내의 벽
					std::cout << "▦";
				else if (_board[y][x].tipe == TileVisible::nonVisible)// 시야범위 밖의 벽 //(2번유형)
					std::cout << "▩";
				else                                            //그 외의 모든 벽
					std::cout << "■";
			}
			else if (_board[y][x].type == TileType::USER) {  // 유저위치
				std::cout << "ㅍ";
			}
			else {//이동가능공간일 때
				if (_board[y][x].tipe == TileVisible::Visible)// 시야범위 내 이동 가능 공간
					std::cout << "  ";
				else if (_board[y][x].tipe == TileVisible::noVisible)   //(1번유형)
					std::cout << "ㅁ";//시야범위에 한 번 이상 들어오면 이동 공간
				else
					std::cout << "■";//시야범위 밖의 이동 공간
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