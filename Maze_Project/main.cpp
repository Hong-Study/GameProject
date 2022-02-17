
#include <QtWidgets/QApplication>
#include <QtWidgets/qgraphicsScene>
#include <QtWidgets/QgraphicsView>                  // ±×·¡ÇÈ ºä
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

    Player* player = new Player(1, 1,"HOng");
    QGraphicsView view;
    view.setMinimumHeight(600);
    view.setMinimumWidth(600);

    Menu menu(&size, player);
    view.setScene(&menu);
    view.show();
    return a.exec();
}

// »èÁ¦°¡ ¶ä.
