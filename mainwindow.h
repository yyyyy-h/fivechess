#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "game.h"
#include "pve.h"
#include"rinking.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
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
    Rinking a;
    QVBoxLayout *layout;
    QTextEdit *textEdit;  // 显示文件内容
public:


    void paintEvent(QPaintEvent *);


public  slots:
    //在 Qt 里，slots 是类的特殊成员函数，能够和信号进行连接。当对应的信号被发射时，槽函数就会被调用。

signals:
};

#endif // MAINWINDOW_H
