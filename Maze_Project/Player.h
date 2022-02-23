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
	int _show_map;
	QString _name;

public:
	Player(int x, int y, int size, QString name) 
		: _x(x)
		, _y(y)
		, _Check_Trap(size*2)
		, _name(name) 
		, _show_map(size)
		, _winy(0){}

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
	void set_winX(int x) {
		_winx = x;
	}
	void set_winY(int y) {
		_winy = y;
	}
	void set_Name(const QString name) {
		_name = name;
	}
	int left_Check() {
		if (_Check_Trap == 0)
			return 0;
		return _Check_Trap;
	}
	int left_show() {
		if (_show_map == 0)
			return 0;
		return _show_map;
	}
	bool Check() {
		if (_Check_Trap-- <= 0)
			return false;
		return true;
	}
	bool Show_Mape() {
		if (_show_map-- <= 0)
			return false;
		return true;
	}
	bool Victory_Chekc() {
		if (_x == _winx && _y == _winy)
			return true;
		return false;
	}
};