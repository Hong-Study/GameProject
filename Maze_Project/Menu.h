#pragma once

#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qgraphicsview.h>
#include "Player.h"

class Menu : public QGraphicsScene{
	Q_OBJECT

private:
	int* _size;
	Player* _player;
	//QGraphicsRectItem _root;
	QPushButton _button;

public:
	Menu(int* size, Player* player);
	
private slots:
	void btn_click();
};