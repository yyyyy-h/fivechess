#ifndef GAME_H
#define GAME_H

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

using namespace std;


class game : public QMainWindow
{
    Q_OBJECT

public:
    game(QWidget *parent = nullptr);
    ~game();

private:
    int chessboard[15][15];
    int player;//if player == even , it is the first player.odd is the second player.
    int moveX,moveY; // the mouse message
    int currentX,currentY;//the last location of piece
    bool lock; // the lock of chessboard
    int flags; // the state of game. 0 == start ,1 == over
    int game_model;//  1 == PVC, 2 == PVP
    QPushButton *button;
    QButtonGroup *selectModelGroup;
    QString strWinner;  //dispose the string in qt
    stack<QPoint> stak; // regret the last piece


public:
    // update the chessboard
    void update_chaessboard_yh(int x,int y);

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
    void iswin_yh(int x,int y);

    // jude is over
    int isover_yh(QPoint p);

    // get location of user
    void person_yh(QMoveEvent *e);

    //get AI
    void ai();

    //the brain of ai
    int assese(QPoint noew,int me);

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

};
#endif // GAME_H
