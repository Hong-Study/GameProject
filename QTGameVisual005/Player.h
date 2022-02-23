#pragma once
#include<conio.h>
#include<iostream>
#include <qstring.h>

class Player {
private:
	int _x;
	int _y;
	int _winx;
	int _winy;
	int _Check_Trap;
	int visionItem = 10 - _size * 2;
	QString _name;

public:
	Player(int x, int y, int Check_Trap, QString name)
		: _x(x)
		, _y(y)
		, _Check_Trap(Check_Trap)
		, _name(name)
		, _winx(0)
		, _winy(0) {}

	int X() const {
		return _x;
	}
	int Y() const {
		return _y;
	}
	void set_X(int x) {
		_x = x;
	}
	void set_Y(int y) {
		_y = y;
	}
	void set_winX(int x) {
		_winx = x;
	}
	void set_winY(int y) {
		_winy = y;
	}
	void set_Name(const QString name) {
		_name = name;
	}
	bool visionItemCount() {
		if (visionItem-- <= 0)
			return false;
		return true;
	}
	bool Check() {
		if (_Check_Trap-- <= 0)
			return false;
		return true;
	}
	bool Victory_Chekc() {
		if (_x == _winx && _y == _winy)
			return true;
		return false;
	}
};