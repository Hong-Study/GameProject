
#include <QtWidgets/QApplication>
#include <QtWidgets/qgraphicsScene>
#include <QtWidgets/QgraphicsView>                  // ±×·¡ÇÈ ºä

#include <qlabel.h>
#include "Board.h"
#include "Player.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    /*QString str = "Hello";
    a.setApplicationDisplayName(str);*/

    QGraphicsScene scene;
    Player* player = new Player(1, 1, "HongJiHyun");
    Board board(&scene, 31, player);
    QGraphicsView view(&scene);
    
    view.setMaximumHeight(1000);
    view.setMaximumWidth(1000);
    view.showMaximized();

    return a.exec();
}

// »èÁ¦°¡ ¶ä.
