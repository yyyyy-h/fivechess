#include "game.h"

game::game(QWidget *parent)
    : QMainWindow(parent)

{
    //preview
    showpreview = false;

    moveX = 0;
    moveY = 0;
    X = -1;
    Y = -1;

    flags = 0;

    //set title
    setWindowTitle("Five Chess- pvp");

    //set size of window
    setMinimumSize(1000,800);
    setMaximumSize(1000,800);

    //set botton
    //QPushButton *button_start = new QPushButton(this);
    //button_start->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    //button_start->setGeometry(QRect(785,100,200,50));
    //button_start->setText("game mode");


    //the label
    QLabel *label = new QLabel(this);
    label->setText("Five Chess v1.0");
    label->setGeometry(785,700,200,50);
    label->setStyleSheet("color : black ; font-size:22px");

    // select botton
    game_model = 1;



    // start and over button
    button = new QPushButton(this);
    button->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    button->setGeometry(QRect(785,400,200,50));
    button->setText("game (re)start");
    connect(button,SIGNAL(clicked()),this,SLOT(operat()));


    //regrat
    while(!stak.empty())
    {
        stak.pop();
    }
    QPushButton *back_button=new QPushButton(this);
    back_button->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    back_button->setGeometry(QRect(785,490,200,50));
    back_button->setText("regret");
    connect(back_button, &QPushButton::clicked, this, &game::back);



    //get mouse message
    setMouseTracking(true);
    memset(chessboard,0,sizeof(chessboard)); // disopse the chessboard



}

game::~game()
{

}

void game::newchessboard()
{
    memset(chessboard,0,sizeof(chessboard)); // disopse the chessboard
    player = 1;
}
//dir is the direvtion ; offset is the type of piece
int game::getPointAt(QPoint p,int dir, int offset)
{
    return 0;
}

// judge who win
void game::iswin(int x,int y)
{
    int directions[4][2] =
    {
        {1,0},
        {0,1},
        {1,1},
        {1,-1},
    };
    if(chessboard[x][y] == 1)
    {
    for(int direct = 0;direct < 4;direct++)
    {
        int a = 1;

        for(int i = 1;i < 5;i++)
        {
            int nextx = x + directions[direct][0] * i;
            int nexty = y + directions[direct][1] * i;

            if((nextx >= 0 && nextx < 15) && (nexty >= 0 && nexty < 15) && chessboard[nextx][nexty] == 1)
            {
                a++;
            }
            else{break;}
        }
        for(int i = 1;i < 5;i++)
        {
            int nextx = x - directions[direct][0] * i;
            int nexty = y - directions[direct][1] * i;

            if((nextx >= 0 && nextx < 15) && (nexty >= 0 && nexty < 15) && chessboard[nextx][nexty] == 1)
            {
                a++;
            }
            else{break;}
        }

        if(a >= 5)
        {
            QMessageBox::information(this,"over","black is winner");


            flags =0;
        }
    }

    }

    else if(chessboard[x][y] == 2)
    {
        for(int direct = 0;direct < 4;direct++)
        {
            int a = 1;

            for(int i = 1;i < 5;i++)
            {
                int nextx = x + directions[direct][0] * i;
                int nexty = y + directions[direct][1] * i;

                if((nextx >= 0 && nextx < 15) && (nexty >= 0 && nexty < 15) && chessboard[nextx][nexty] == 2)
                {
                    a++;
                }
                else{break;}
            }
            for(int i = 1;i < 5;i++)
            {
                int nextx = x - directions[direct][0] * i;
                int nexty = y - directions[direct][1] * i;

                if((nextx >= 0 && nextx < 15) && (nexty >= 0 && nexty < 15) && chessboard[nextx][nexty] == 2)
                {
                    a++;
                }
                else{break;}
            }

            if(a >= 5)
            {
                QMessageBox::information(this,"over","white is winner");


                flags =0;
            }
        }
    }

}

// jude is over
int game::isover(QPoint p)
{
    return 0;
}

// get the piece location of user
void game::person(QMoveEvent *e)
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

    //draw chessboard
    for(int i = 0 ;i <15;i++)
    {
        for(int j = 0 ; j < 15 ;j++)
        {
            if(chessboard[i][j]==1)
            {
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(29+i*50,29+j*50,42,42);
            }
            else if(chessboard[i][j]==2)
            {
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawEllipse(29+i*50,29+j*50,42,42);
            }
        }
    }

    //preview
    if(showpreview) {
        QPen pen(Qt::gray, 2, Qt::DashLine);
        p.setPen(pen);

        // 根据当前玩家设置不同颜色的预览
        QBrush brush(QColor(0, 0, 0, 100) ); // 预览

        p.setBrush(brush);

        p.drawEllipse(moveX-20, moveY-20 , 40, 40);
    }


}

//mouse moves
void game::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();


    if((x < 50 || x > 750 || y < 50 || y > 750)||flags==0) {
        showpreview = false;
    }
    else
    {
        showpreview  = true;
    }


    bool found = false;
    if(showpreview)
    {
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            int gridX = 50 + j * 50;
            int gridY = 50 + i * 50;

            // 计算鼠标与当前交叉点的距离
            int dx = x - gridX;
            int dy = y - gridY;
            int distance = dx * dx + dy * dy;

            // 如果距离小于阈值（例如25像素），认为是这个交叉点
            if(distance < 25*25) {
                moveX = gridX;
                moveY = gridY;
                X = j;
                Y = i;
                found = true;
                break;
            }
        }
        if(found) break; // 找到后跳出外层循环
    }
    }

    update();
}


//mouse click
void game::mousePressEvent(QMouseEvent *e)
{
    if(flags==0)
    {
        return;
    }
    // 只处理左键点击
    if (e->button() != Qt::LeftButton)
        return;

    int x = e->x();
    int y = e->y();

    // 检查点击是否在棋盘范围内
    if (x < 50 || x > 750 || y < 50 || y > 750)
        return;

    // 将点击位置映射到最近的棋盘交叉点


    // 检查该位置是否已经有棋子
    if (chessboard[X][Y] != 0)
        return;

    // 放置棋子（1表示黑棋，2表示白棋）
    chessboard[X][Y] = player;

    iswin(X,Y);

    // 切换玩家
    player = (player == 1) ? 2 : 1;

    //记录落子位置和玩家
    stak.push(QPoint(X, Y));
    playerStack.push(player); // 压入当前玩家（1或2）

    // 重绘界面
    update();
}

void game::operat()
{
    flags = 1;
    newchessboard();
}
void game::SelectRadio()
{

}
void game::back()
{
    if (stak.empty()) return; // 无棋可悔

    // 取出最后一步的位置和玩家
    QPoint lastPos = stak.top();

    // 清空棋盘位置
    chessboard[lastPos.x()][lastPos.y()] = 0;

    // 弹出栈顶元素（撤销最后一步）
    stak.pop();
    playerStack.pop();

    // 恢复玩家到上一步（例如：上一步是玩家1落子，悔棋后当前玩家应变回玩家1）
    player =(player == 1) ? 2 : 1;

    update(); // 重绘界面
}
