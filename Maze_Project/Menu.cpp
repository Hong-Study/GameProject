#include "Menu.h"
#include <qdebug.h>

#include <string>
void Menu::show()
{
	_view->setScene(this);
	_view->show();
}

void Menu::Windows_setting(int width, int height){

	_view->setMinimumHeight(height);
	_view->setMinimumWidth(width);

	_view->setMaximumHeight(height);
	_view->setMaximumWidth(width);
}
void Menu::add_Widget() {
	QGraphicsScene::addWidget(&_button);
	QGraphicsScene::addWidget(&_SIZE_INPUT);
	QGraphicsScene::addWidget(&_NAME_INPUT);

	QGraphicsScene::addWidget(&_SIZE_LABEL);
	QGraphicsScene::addWidget(&_NAME_LABEL);

	_SIZE_INPUT.setGeometry(_view->minimumWidth() / 2 - 120, _view->minimumHeight() / 2 - 100, 100, 20);
	_NAME_INPUT.setGeometry(_view->minimumWidth() / 2 + 20, _view->minimumHeight() / 2 - 100, 100, 20);

	_SIZE_LABEL.setText("Size Input");
	_NAME_LABEL.setText("Name Input");

	_SIZE_LABEL.setAlignment(Qt::AlignCenter);
	_NAME_LABEL.setAlignment(Qt::AlignCenter);

	_SIZE_LABEL.setGeometry(_view->minimumWidth() / 2 - 120, _view->minimumHeight() / 2 - 120, 100, 20);
	_NAME_LABEL.setGeometry(_view->minimumWidth() / 2 + 20, _view->minimumHeight() / 2 - 120, 100, 20);
	_button.setGeometry(_view->minimumWidth() / 2 - 50, _view->minimumHeight() / 2 - 50, 100, 20);
	_button.setText("Start");

	QGraphicsScene::connect(&_button, SIGNAL(clicked()), this, SLOT(btn_click()));
}

Menu::Menu(QGraphicsView* view)
	: _view(view)
{
	Windows_setting(250, 250);
			//한국어 쓰면 에러남.

	add_Widget();
	show();
}

void Menu::btn_click() {
	qDebug() << "Working";
	_size = _SIZE_INPUT.text().toInt();
	_player = new Player(1, 1, _NAME_INPUT.text());
	board = new Board(_size, _player);
	qDebug() << _size << " : " << _player->X();
	Windows_setting(_size * 31, _size * 31);

	_view->setScene(board);
	_view->update();
}