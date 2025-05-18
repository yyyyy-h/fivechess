#include "game.h"

#include <QApplication>

#include <QWidget>  // windows
#include <QPaintEvent>
#include <QTimer>  //timer
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>  //get mouse message
#include <QPainterPath>
#include <QColor>
#include <QBrush>
#include <QMessageBox> //tanchuang
#include <QPushButton>
#include <QButtonGroup>
#include <QPalette>
#include <QtDebug>
#include <QLabel>
#include <bits/stdc++.h>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game w;
    w.show();
    return a.exec();
}
