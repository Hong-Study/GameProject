/********************************************************************************
** Form generated from reading UI file 'QTGameVisual005.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGAMEVISUAL005_H
#define UI_QTGAMEVISUAL005_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTGameVisual005Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTGameVisual005Class)
    {
        if (QTGameVisual005Class->objectName().isEmpty())
            QTGameVisual005Class->setObjectName(QString::fromUtf8("QTGameVisual005Class"));
        QTGameVisual005Class->resize(600, 400);
        menuBar = new QMenuBar(QTGameVisual005Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QTGameVisual005Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTGameVisual005Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QTGameVisual005Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTGameVisual005Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QTGameVisual005Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTGameVisual005Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QTGameVisual005Class->setStatusBar(statusBar);

        retranslateUi(QTGameVisual005Class);

        QMetaObject::connectSlotsByName(QTGameVisual005Class);
    } // setupUi

    void retranslateUi(QMainWindow *QTGameVisual005Class)
    {
        QTGameVisual005Class->setWindowTitle(QCoreApplication::translate("QTGameVisual005Class", "QTGameVisual005", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTGameVisual005Class: public Ui_QTGameVisual005Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGAMEVISUAL005_H
