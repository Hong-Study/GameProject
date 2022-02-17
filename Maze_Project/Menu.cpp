#include "Menu.h"
#include <qdebug.h>

#include <string>
void Menu::show()
{
	_view->setScene(this);
	_view->show();
}

Menu::Menu(QGraphicsView* view)
	: _view(view)
{
	_view->setMinimumHeight(600);
	_view->setMinimumWidth(600);

	QGraphicsScene::setSceneRect(0, 0, 600, 600);
	QGraphicsScene::addWidget(&_button);
	QGraphicsScene::addWidget(&_input1);
	QGraphicsScene::addWidget(&_input2);

	_input1.setGeometry(view->minimumWidth() / 2 - 120, view->minimumHeight() / 2 - 100, 100, 20);
	_input2.setGeometry(view->minimumWidth() / 2 + 20, view->minimumHeight() / 2 - 100, 100, 20);
	_button.setGeometry(view->minimumWidth()/2-50 , view->minimumHeight()/2-50, 100, 20);
	_button.setText("Start");		//한국어 쓰면 에러남.

	QGraphicsScene::connect(&_button, SIGNAL(clicked()), this, SLOT(btn_click()));
	
	show();
}

void Menu::btn_click() {
	qDebug() << "Working";
	_size = _input1.text().toInt();
	_player = new Player(1,1,_input2.text());
	board = new Board(_size, _player);
	qDebug() << _size << " : " << _player->X();

	_view->setMinimumHeight(_size * 31);
	_view->setMinimumWidth(_size * 31);
	_view->setMaximumHeight(_size * 31);
	_view->setMaximumWidth(_size * 31);

	_view->setScene(board);
	_view->update();
}