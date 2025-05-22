#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
    : QWidget{parent}
{
    //set title
    setWindowTitle("Five Chess");
    //set size of window
    setMinimumSize(600,400);
    setMaximumSize(600,400);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(140, 140, 140));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    //set botton_pvp
    QPushButton *button_pvp = new QPushButton(this);
    button_pvp->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    button_pvp->setGeometry(QRect(200,175,200,50));
    button_pvp->setText("PVP");
    connect(button_pvp, &QPushButton::clicked, [this]() {
        memset(pvp.chessboard,0,sizeof(pvp.chessboard)); // disopse the chessboard
        pvp.show();
    });


    //set botton_pve
    QPushButton *button_pve = new QPushButton(this);
    button_pve->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    button_pve->setGeometry(QRect(200,250,200,50));
    button_pve->setText("PVE");
    connect(button_pve, &QPushButton::clicked, [this]() {
        memset(ai.chessboard,0,sizeof(ai.chessboard)); // disopse the chessboard
        ai.show();
    });

    //the label
    QLabel *label = new QLabel(this);
    label->setText("Welcome!");
    label->setGeometry(185,50,260,50);
    label->setStyleSheet("color : black ; font-size:56px");

}
void mainwindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//mouse moves
void mainwindow::mouseMoveEvent(QMouseEvent *e)
{

}

//mouse click
void mainwindow::mousePressEvent(QMouseEvent *e)
{

}

void mainwindow::operat()
{

}
void mainwindow::SelectRadio()
{

}
void mainwindow::back()
{

}
