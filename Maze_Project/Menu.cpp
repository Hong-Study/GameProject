#include "Menu.h"
#include <qdebug.h>

#include <string>
void Menu::show()
{
	_view->setScene(this);
	_view->show();
}

void Menu::Menu_Setting(int width, int height)
{
	QGraphicsScene::addWidget(&_button);

	QGraphicsScene::addWidget(&_Size_Input);
	QGraphicsScene::addWidget(&_Size_Label);

	QGraphicsScene::addWidget(&_Name_Input);
	QGraphicsScene::addWidget(&_Name_Label);

	_Size_Input.setGeometry(width / 2 - 120, height / 2 - 50, 100, 20);
	_Name_Input.setGeometry(width / 2 + 20, height / 2 - 50, 100, 20);

	_button.setGeometry(width / 2 - 50, height / 2, 100, 20);
	_button.setText("Start");		//한국어 쓰면 에러남.

	_Size_Label.setGeometry(width / 2 - 120, height / 2 - 70, 100, 20);
	_Size_Label.setText("Size Input");
	_Size_Label.setAlignment(Qt::AlignCenter);

	_Name_Label.setGeometry(width / 2 + 20, height / 2 - 70, 100, 20);
	_Name_Label.setText("Name Input");
	_Name_Label.setAlignment(Qt::AlignCenter);
	QGraphicsScene::connect(&_button, SIGNAL(clicked()), this, SLOT(btn_click()));
}

void Menu::Windows_Setting(int width, int height)
{
	_view->setMinimumHeight(height);
	_view->setMinimumWidth(width);

	_view->setMaximumHeight(height);
	_view->setMaximumWidth(width);
}

Menu::Menu(QGraphicsView* view)
	: _view(view)
{
	Windows_Setting(300, 300);
	Menu_Setting(_view->minimumWidth(), _view->minimumHeight());
	show();
}

void Menu::btn_click() {
	qDebug() << "Working";
	_size = _Size_Input.text().toInt();
	_player = new Player(1,1, _Name_Input.text());
	board = new Board(_size, _player);
	qDebug() << _size << " : " << _player->X();

	Windows_Setting(_size * 31, _size * 31);
	_view->setScene(board);
	_view->update();
}