#ifndef PVE_H
#define PVE_H

#include <QMainWindow>
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
#include <QRadioButton>
#include <QButtonGroup>
#include <QPalette>
#include <QtDebug>
#include <QLabel>
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>

using namespace std;



class pve : public QWidget
{
    Q_OBJECT
public:
    explicit pve(QWidget *parent = nullptr);
private:
    int player;//if player == even , it is the first player.odd is the second player.
    int moveX,moveY; // the mouse message
    int currentX,currentY;//the last location of piece
    bool lock; // the lock of chessboard
    int flags; // the state of game. 1 == start ,0 == over
    int game_model;//  1 == PVC, 2 == PVP
    int X,Y;
    QPushButton *button;
    QButtonGroup *selectModelGroup;
    QString strWinner;  //dispose the string in qt
    stack<QPoint> stak; // regret the last piece
    bool showpreview;

public:

    int chessboard[15][15];
    // judge who win
    void iswin(int x,int y);


    //paint
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

#endif // PVE_H
