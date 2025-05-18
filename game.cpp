#include "game.h"

game::game(QWidget *parent)
    : QMainWindow(parent)

{   //set title
    setWindowTitle("Five Chess");

    //set size of window
    setMinimumSize(1000,800);
    setMaximumSize(1000,800);

    //set botton
    QPushButton *button_start = new QPushButton(this);
    button_start->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    button_start->setGeometry(QRect(785,100,200,50));
    button_start->setText("game mode");


    //the label
    QLabel *label = new QLabel(this);
    label->setText("Five Chess v1.0");
    label->setGeometry(785,700,200,50);
    label->setStyleSheet("color : black ; font-size:22px");

    // select botton
    game_model = 1;
    selectModelGroup = new QButtonGroup(this);

    //PVC
    QRadioButton *pvc = new QRadioButton("PVC",this);
    selectModelGroup->addButton(pvc,1);
    pvc->setStyleSheet("font:Bold;font-size:24px;color:black");
    pvc->setGeometry(825,200,100,30);
    connect(pvc,SIGNAL(clicked()),this,SLOT(SelecRadio()));

    //PVP
    QRadioButton *pvp = new QRadioButton("PVP",this);
    selectModelGroup->addButton(pvp,2);
    pvp->setStyleSheet("font:Bold;font-size:24px;color:black");
    pvp->setGeometry(825,300,100,30);
    connect(pvp,SIGNAL(clicked()),this,SLOT(SelecRadio()));

    //default PVC
    pvc->setChecked(true);


    // start and over button
    flags = 0;
    button = new QPushButton(this);
    button->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    button->setGeometry(QRect(785,400,200,50));
    button->setText("game start");
    connect(button,SIGNAL(clicked()),this,SLOT(operat()));


    //regrat
    while(!stak.empty())
    {
        stak.pop();
    }
    QPushButton *back_button=new QPushButton(this);
    back_button->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    back_button->setGeometry(QRect(785,490,200,50));
    back_button->setText("regrat");
    connect(button,SIGNAL(clicked()),this,SLOT(back()));


    //get mouse message
    setMouseTracking(true);
    lock = 1;
    memset(chessboard,0,sizeof(chessboard)); // disopse the chessboard



}

game::~game()
{

}
//dir is the direvtion ; offset is the type of piece
int game::getPointAt(QPoint p,int dir, int offset)
{
    return 0;
}

// judge who win
void game::iswin_yh(int x,int y)
{

}

// jude is over
int game::isover_yh(QPoint p)
{
    return 0;
}

// get the piece location of user
void game::person_yh(QMoveEvent *e)
{

}

//get the piece location of ai
void game::ai()
{

}

//the brain of ai
int game::assese(QPoint noew,int me)
{
    return 0;
}

//paint
void game::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //
    p.setRenderHint(QPainter::Antialiasing,true);

    //paint the chessboard

    //the blackbround color
    QBrush brush;
    brush.setColor(QColor(213,176,141));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);

    //
    QPen pen = p.pen();
    p.setPen(pen);
    p.drawRect(30,30,740,740);

    //the line
    pen.setColor(Qt::black);
    pen.setWidth(1);
    p.setPen(pen);
    for(int i = 0; i < 15; i++)
    {
        p.drawLine(50,50+i*50,750,50+i*50);
        p.drawLine(50+i*50,50,50+i*50,750);

    }

    // draw five dots
    brush.setColor(Qt::black);
    p.setBrush(brush);
    p.drawEllipse(195,195,10,10);
    p.drawEllipse(595,195,10,10);
    p.drawEllipse(195,595,10,10);
    p.drawEllipse(595,595,10,10);
    p.drawEllipse(395,395,10,10);
}

//mouse moves
void game::mouseMoveEvent(QMouseEvent *e)
{

}

//mouse click
void game::mousePressEvent(QMouseEvent *e)
{

}

void game::operat()
{

}
void game::SelectRadio()
{

}
void game::back()
{

}
