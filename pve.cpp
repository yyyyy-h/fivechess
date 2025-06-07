#include "pve.h"

pve::pve(QWidget *parent)
    : QWidget{parent}
{

    username = "";


    //preview
    showpreview = false;

    moveX = 0;
    moveY = 0;
    X = -1;
    Y = -1;

    flags = 0;

    //set title
    setWindowTitle("Five Chess- pve");

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
    button->setText("game start");
    connect(button,SIGNAL(clicked()),this,SLOT(operat()));


    //set username
    sign = new QPushButton(this);
    sign->setStyleSheet("font:Bold;font-size:24px;color:white;background-color:rgb(30,144,255);border:2px;border-radius:10px;padding:2px 4px;");
    sign->setGeometry(QRect(785,100,200,50));
    sign->setText("sign in");
    connect(sign,SIGNAL(clicked()),this,SLOT(Setname()));
    bool connected = connect(sign, &QPushButton::clicked, this, &pve::Setname);
    qDebug() << "信号槽连接状态:" << (connected ? "成功" : "失败");


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
    memset(chessboard,0,sizeof(chessboard)); // disopse the chessboard

    scoreMapVec.clear();
    for(int i = 0; i < 15; i++)
    {
        vector<int>linScores;
        for(int j = 0; j < 15; j++)
        {
            linScores.push_back(0);
            scoreMapVec.push_back(linScores);
        }
    }

    playerFlag = true;
}

void pve::newchessboard()
{
    memset(chessboard,0,sizeof(chessboard)); // disopse the chessboard
    aix = -1;
    aiy =-1;
    player = 1;
}
bool pve::modifyPointsInFile(const QString &fileName, const QString &playerName, int pointsToAdd) {
    QString tempFileName = fileName + ".temp";
    QFile inputFile(fileName);
    QFile outputFile(tempFileName);

    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开原文件:" << fileName;
        return false;
    }

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法创建临时文件:" << tempFileName;
        inputFile.close();
        return false;
    }

    QTextStream in(&inputFile);
    QTextStream out(&outputFile);
    bool found = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpression re(QString(R"(^\d+\s+player\s+%1\s+(\d+)\s+points$)").arg(playerName));
        QRegularExpressionMatch match = re.match(line);

        if (match.hasMatch()) {
            // 获取当前分数并转换为整数
            int currentPoints = match.captured(1).toInt();
            // 计算新分数（原分数 + pointsToAdd）
            int newPoints = currentPoints + pointsToAdd;
            // 替换为新分数
            QString newLine = line.replace(match.captured(1), QString::number(newPoints));
            out << newLine << "\n";
            found = true;
            qDebug() << "玩家" << playerName << "分数从" << currentPoints << "增加到" << newPoints;
        } else {
            out << line << "\n";
        }
    }

    inputFile.close();
    outputFile.close();

    if (!found) {
        QFile::remove(tempFileName);
        qDebug() << "未找到玩家:" << playerName;
        return false;
    }

    if (QFile::exists(fileName)) {
        if (!QFile::remove(fileName)) {
            qDebug() << "无法删除原文件:" << fileName;
            return false;
        }
    }

    if (!QFile::rename(tempFileName, fileName)) {
        qDebug() << "无法重命名临时文件:" << tempFileName;
        return false;
    }

    qDebug() << "文件修改成功:" << fileName;
    return true;
}
// judge who win
void pve::iswin(int x,int y)
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
                QMessageBox::information(this,"over","user is winner");


                flags =0;

                modifyPointsInFile("ranking.txt",username,200);
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
                    QMessageBox::information(this,"over","AI is winner");


                    flags =0;
                }
            }
        }

}


//paint
void pve::paintEvent(QPaintEvent *)
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

void pve::calculateScore()
{
    int personnum = 0;
    int botnum = 0;
    int emptynum = 0;

    scoreMapVec.clear();
    scoreMapVec.resize(15, vector<int>(15, 0));

    for(int x = 0;x < 15;x++)
    {
        for(int y = 0; y < 15; y++)
        {
            if(x > 0&& y > 0&& chessboard[x][y] == 0)
            {
                for(int j = -1;j <= 1;j++)
                {
                    for(int i = -1;i <= 1;i++)
                    {
                        int px =0;
                        int py =0;
                        personnum = 0;
                        botnum = 0;
                        emptynum = 0;

                        if(!(j == 0&&i == 0))
                            {
                                //每个方向延伸4子
                                //对玩家黑子从正反两方面评分
                            for(int a = 1;a <= 4 ;a++)
                                {
                                    if(x + a * j > 0 && x + a * j < 15 && y + a * i > 0 && y + a * i < 15 && chessboard[x + a * j][y + a * i] == 1)
                                {
                                    personnum++;
                                        px =x + a * j;
                                        py=y + a * i;
                                    }
                                    else if((x + a * j > 0 && x + a * j < 15 && y + a * i > 0 && y + a * i < 15 && chessboard[x + a * j][y + a * i] == 0)&&(x + (a+1) * j > 0 && x +(a+1) * j < 15 && y + (a+1) * i > 0 && y + (a+1)  * i < 15 && chessboard[x + (a+1)  * j][y + (a+1)  * i] == 1))
                                    {
                                        emptynum++;
                                    }
                                    else
                                        break;
                            }
                            for(int a = 1;a <= 4;a++)
                            {
                                if(x - a * j > 0 && x - a * j < 15 && y - a * i > 0 && y - a * i < 15 && chessboard[x - a * j][y - a * i] == 1)
                                {
                                    personnum++;
                                }
                                else if((x - a * j > 0 && x - a * j < 15 && y - a * i > 0 && y - a * i < 15 && chessboard[x - a * j][y - a * i] == 0)&&(x - (a-1) * j > 0 && x - (a-1) * j < 15 && y - (a-1) * i > 0 && y - (a-1) * i < 15 && chessboard[x - (a-1) * j][y - (a-1) * i] == 1))
                                {
                                    emptynum++;
                                }
                                else
                                    break;
                            }



                            if(personnum == 1)
                            {
                                if(!(fabs(x-px)==0&&fabs(y-py)==0))
                                scoreMapVec[x][y] += 30/fabs(x-px)+30/fabs(y-py);

                            }
                            else if(personnum == 2)
                            {
                                if(emptynum == 1)
                                    scoreMapVec[x][y] += 40;
                                else if(emptynum >= 2)
                                    scoreMapVec[x][y] += 60;
                            }
                            else if(personnum == 3)
                            {
                                //优先级不同
                                if(emptynum == 1)
                                {if(!(fabs(x-px)==0&&fabs(y-py)==0))
                                        scoreMapVec[x][y] += 1000/fabs(x-px)+1000/fabs(y-py);}
                                else if(emptynum == 2){
                                    if(!(fabs(x-px)==0&&fabs(y-py)==0))
                                        scoreMapVec[x][y] += 9100/fabs(x-px)+9100/fabs(y-py);}

                            }
                            else if(personnum == 4)
                                scoreMapVec[x][y] += 10100;

                            //进行清空
                            emptynum = 0;
                            //对AI进行评分
                            for(int a = 1;a <= 4;a++)
                            {
                                if(x + a * j > 0 && x + a * j < 15 && y + a * i > 0 && y + a * i < 15 && chessboard[x + a * j][y + a * i] == 2)
                                {
                                    botnum++;
                                }
                                else if((x + a * j > 0 && x + a * j < 15 && y + a * i > 0 && y + a * i < 15 && chessboard[x + a * j][y + a * i] == 0)&&(x + (a+1) * j > 0 && x +(a+1) * j < 15 && y + (a+1) * i > 0 && y + (a+1)  * i < 15 && chessboard[x + (a+1)  * j][y + (a+1)  * i] == 2))
                                {
                                    emptynum++;
                                }
                                else
                                    break;
                            }
                            for(int a = 1;a <= 4;a++)
                            {
                                if(x - a * j > 0 && x - a * j < 15 && y - a * i > 0 && y - a * i < 15 && chessboard[x - a * j][y - a * i] == 2)
                                {
                                    botnum++;
                                }
                                else if((x - a * j > 0 && x - a * j < 15 && y - a * i > 0 && y - a * i < 15 && chessboard[x - a * j][y - a * i] == 0)&&(x - (a-1) * j > 0 && x - (a-1) * j < 15 && y - (a-1) * i > 0 && y - (a-1) * i < 15 && chessboard[x - (a-1) * j][y - (a-1) * i] == 2))
                                {
                                    emptynum++;
                                }
                                else
                                    break;
                            }
                            if(botnum == 0)
                                scoreMapVec[x][y] += 5;
                            else if(botnum == 1)
                                scoreMapVec[x][y] += 10;
                            else if(botnum == 2)
                            {
                                if(emptynum == 1)
                                    scoreMapVec[x][y] += 250;
                                else if(emptynum == 2)
                                    scoreMapVec[x][y] += 350;
                            }
                            else if(botnum == 3)
                            {
                                //优先级不同
                                if(emptynum == 1)
                                    scoreMapVec[x][y] += 755;
                                else if(emptynum == 2)
                                    scoreMapVec[x][y] += 800;
                            }
                            else if(botnum == 4)
                                scoreMapVec[x][y] += 20000;
                            }
                    }
                }
            }
        }
    }
}

void pve::actionByAI()
{
    int clickx;
    int clicky;
    //计算评分
    calculateScore();
    //找出最大评分位置
    int maxscore = 0;
    vector<pair<int,int>>maxPoints;
    for(int x = 1;x < 15;x++)
    {
        for(int y = 1;y < 15;y++)
        {
            //前提坐标为空
            if(chessboard[x][y] == 0)
            {
                if(scoreMapVec[x][y] > maxscore)
                {
                    maxPoints.clear();
                    maxscore = scoreMapVec[x][y];
                    maxPoints.push_back(make_pair(x,y));
                }
                else if(scoreMapVec[x][y] == maxscore)
                    maxPoints.push_back(make_pair(x,y));
            }
        }
    }
    srand((unsigned)time(0));
    int index = rand()%maxPoints.size();
    pair<int,int>pointPair = maxPoints.at(index);
    clickx = pointPair.first;
    clicky = pointPair.second;
    chessboard[clickx][clicky] = 2;
    iswin(clickx,clicky);
    update();
}

//mouse moves
void pve::mouseMoveEvent(QMouseEvent *e)
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
void pve::mousePressEvent(QMouseEvent *e)
{
    // 只处理左键点击
    if (e->button() != Qt::LeftButton)
        return;

    if(flags==0)
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


    // 记录落子位置用于悔棋
    int tx  = X;
    int ty  = Y;
    stak.push(QPoint(tx, ty));

    // 检查胜负
    iswin(X,Y);


    // 如果是人机对战模式，且轮到AI
    if(flags!=0)
    {
    actionByAI();
    }
    // 重绘界面
    update();
}
void pve::operat()
{
    flags = 1;
    player = 1;
    newchessboard();
}
void pve::SelectRadio()
{

}
void pve::Setname()
{
    bool ok;
    QString name = QInputDialog::getText(
        this,                  // 父窗口指针
        "输入名称",            // 对话框标题
        "请输入你的名称:",      // 提示文本
        QLineEdit::Normal,     // 输入模式（普通文本）
        "",                    // 默认文本
        &ok                    // 用于判断用户是否点击了"确定"
        );

    if (ok && !name.isEmpty()) {
        // 用户点击了"确定"且输入不为空
        // 处理获取到的名称（例如保存到成员变量或显示在界面上）
        qDebug() << "用户输入的名称是:" << name;
        username = name;  // 假设你有一个设置玩家名称的函数
        qDebug() << "名称是:" << name;
    }
}
void pve::back()
{

}
