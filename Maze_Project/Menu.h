#pragma once

#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qpushbutton.h>
#include <qgraphicsview.h>
#include <qlineedit.h>
#include <qlabel.h>

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
	void Menu_Setting(int width, int height);
	void Windows_Setting(int width, int height);

private:
	QLineEdit _Size_Input;
	QLabel _Size_Label;

	QLineEdit _Name_Input;
	QLabel _Name_Label;

	QPushButton _button;
};