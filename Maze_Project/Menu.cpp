#include "Menu.h"
#include <qdebug.h>
Menu::Menu(int* size, Player* player)
	: _size(size)
	, _player(player)
{
	QGraphicsScene::setSceneRect(0, 0, 600, 600);
	QGraphicsScene::addWidget(&_button);
	_button.setGeometry(QGraphicsScene::sceneRect().width() , QGraphicsScene::sceneRect().height(), 100, 20);
	_button.setText("Start");		//한국어 쓰면 에러남.
	QGraphicsScene::connect(&_button, SIGNAL(clicked()), this, SLOT(btn_click()));
}

void Menu::btn_click() {
	*_size = 11;
}