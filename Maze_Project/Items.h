#pragma once
#pragma once

#include <string>
#include <QtWidgets/QgraphicsPixmapItem>
#include <qtimeline.h>

class Item : public QGraphicsPixmapItem, public QObject {
	class EventListener;
public:
	Item(const std::string& path, int row, int colum, QGraphicsItem* parent);
	std::string path() const;
	int row() const;
	int colum() const;

	void setRow(int row);
	void setColum(int colum);

private:
	const std::string _path;
	int _row;
	int _colum;
	QPointF _pressPos;
};