
#include <QtWidgets/QApplication>
#include <QtWidgets/qgraphicsScene>
#include <QtWidgets/QgraphicsView>                  // ±×·¡ÇÈ ºä
#include <qpushbutton.h>
#include <qwidget.h>

#include "Menu.h"
#include "Board.h"
#include "Player.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    int size = 11;
    QString str = "Maze-Game";
    a.setApplicationDisplayName(str);

    QGraphicsView view;
    Menu menu(&view);
    return a.exec();
}

// »èÁ¦°¡ ¶ä.
