#ifndef PVE_H
#define PVE_H
#include <vector>
#include <QInputDialog>
#include <QFile>
#include <QRegularExpression>
#include "game.h"

using namespace std;

const int AI_THINK_TIME = 700;

class pve : public QWidget
{
    Q_OBJECT
public:
    explicit pve(QWidget *parent = nullptr);
    //存储棋盘棋子情况，空白为0，黑为1，白为-1
    vector<vector<int>>gameMapVec;
    //存储评分情况，作为ai下棋证据
    vector<vector<int>>scoreMapVec;

    int aix;
    int aiy;
    QString username;
    bool playerFlag;
    bool modifyPointsInFile(const QString &fileName, const QString &playerName,  int pointsToAdd);
    void actionByAI();
    void Setname();
private:
    int player;//if player == even , it is the first player.odd is the second player.
    int moveX,moveY; // the mouse message
    int currentX,currentY;//the last location of piece
    int flags; // the state of game. 1 == start ,0 == over
    int game_model;//  1 == PVC, 2 == PVP
    int X,Y;
    QPushButton *button;
    QPushButton *sign;
    QButtonGroup *selectModelGroup;
    QString strWinner;  //dispose the string in qt
    stack<QPoint> stak; // regret the last piece
    bool showpreview;
    QStack<int> playerStack; //记录每一步的玩家（1或2）

public:

    int chessboard[15][15];
    // judge who win

    void newchessboard();

    void iswin(int x,int y);


    //paint
    void paintEvent(QPaintEvent *);

    void calculateScore();

    void evaluateLine(int x, int y, int dx, int dy, int player, int& count, int& empty);

    //mouse moves
    void mouseMoveEvent(QMouseEvent *e);

    //mouse click
    void mousePressEvent(QMouseEvent *e);

public  slots:
    //在 Qt 里，slots 是类的特殊成员函数，能够和信号进行连接。当对应的信号被发射时，槽函数就会被调用。
    //

    void operat();
    void back();
signals:
};

#endif // PVE_H
