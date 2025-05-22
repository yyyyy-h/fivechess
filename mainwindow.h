#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QWidget>  // windows
#include <QPaintEvent>
#include <QTimer>  //timer
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>  //get mouse message
#include <QPainterPath>
#include <QStyleOption>
#include <QColor>
#include <QBrush>
#include <QMessageBox> //tanchuang
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPalette>
#include <QtDebug>
#include <QLabel>
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>

#include "game.h"
#include "pve.h"
using namespace std;


class mainwindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);
private:
    QPushButton *button;
    QString strWinner;  //dispose the string in qt
    game pvp;
    pve ai;


public:


    void paintEvent(QPaintEvent *);

    //mouse moves
    void mouseMoveEvent(QMouseEvent *e);

    //mouse click
    void mousePressEvent(QMouseEvent *e);

public  slots:
    //在 Qt 里，slots 是类的特殊成员函数，能够和信号进行连接。当对应的信号被发射时，槽函数就会被调用。
    //

    void operat();
    void SelectRadio();
    void back();

signals:
};

#endif // MAINWINDOW_H
