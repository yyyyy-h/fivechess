#ifndef GAME_H
#define GAME_H

#include <QMainWindow>

#include <QStack>
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


class game : public QMainWindow
{
    Q_OBJECT

public:
    game(QWidget *parent = nullptr);
    ~game();

private:
    int player;//if player == even , it is the first player.odd is the second player.
    int moveX,moveY; // the mouse message
    int currentX,currentY;//the last location of piece
    int flags; // the state of game. 1 == start ,0 == over
    int X,Y;
    QPushButton *button;
    QButtonGroup *selectModelGroup;
    QString strWinner;  //dispose the string in qt
    bool showpreview;
    stack<QPoint> stak; // 记录落子位置
    QStack<int> playerStack; //记录每一步的玩家（1或2）


public:
       int chessboard[15][15];
    // update the chessboard
    void newchessboard();

    //state the eight directions
    QPoint m_dir[8] = {
        QPoint(0,-1),
        QPoint(1,-1),
        QPoint(1,0),
        QPoint(1,1),
        QPoint(0,1),
        QPoint(-1,1),
        QPoint(-1,0),
        QPoint(-1,-1)
    }; // use eight points to express eight directions

    //dir is the direvtion ; offset is the type of piece
    int getPointAt(QPoint p,int dir, int offset);

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
    void back();

};
#endif // GAME_H
