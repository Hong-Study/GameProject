#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Maze_Project.h"

class Maze_Project : public QMainWindow
{
    Q_OBJECT

public:
    Maze_Project(QWidget *parent = Q_NULLPTR);

private:
    Ui::Maze_ProjectClass ui;
};
