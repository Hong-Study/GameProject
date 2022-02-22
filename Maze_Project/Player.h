#pragma once
#include<conio.h>
#include<iostream>
#include <qstring.h>

class Player {
private:
	int _x;
	int _y;
	QString _name;

public:
	Player(int x, int y, QString name) 
		: _x(x)
		, _y(y)
		, _name(name) {}

	int X() const {
		return _x;
	}
	int Y() const{
		return _y;
	}
	void set_X(int x){
		_x = x;
	}
	void set_Y(int y){
		_y = y;
	}
	void set_Name(const QString name) {
		_name = name;
	}
};