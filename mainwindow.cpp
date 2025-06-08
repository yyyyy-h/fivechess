#include "mainwindow.h"
#include "QStyleOption"
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

        pvp.newchessboard();
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


    //set botton_ranking
    QPushButton *button_ranking = new QPushButton(this);
    button_ranking->setStyleSheet("font:Bold;font-size:15px;color:black;background-color:rgb(255,255,255);border:2px;border-radius:0px;padding:2px 4px;");
    button_ranking->setGeometry(QRect(0,0,50,50));
    button_ranking->setText("rank");
    connect(button_ranking, &QPushButton::clicked, [this]() {


        a.show();
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


