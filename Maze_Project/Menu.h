#pragma once

#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qpushbutton.h>
#include <qgraphicsview.h>
#include <qlineedit.h>

#include "Player.h"
#include "Board.h"

class Menu : public QGraphicsScene{
	Q_OBJECT
private:
	int _size;
	Player* _player;
	QGraphicsView* _view;
	Board* board;
	
public:
	Menu(QGraphicsView* view);
	void show();

private slots:
	void btn_click();

private:
	QLineEdit _input1;
	QLineEdit _input2;
	QPushButton _button;
};