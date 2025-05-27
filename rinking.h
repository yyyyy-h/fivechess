#ifndef RINKING_H
#define RINKING_H

#include "game.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
class Rinking : public QWidget
{
    Q_OBJECT
public:
    explicit Rinking(QWidget *parent = nullptr);
private:
    QPushButton *button;
    QString strWinner;  //dispose the string in qt
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QTextEdit *textEdit;  // 显示文件内容
    QPushButton *openButton;  // 打开文件按钮
public:
    explicit Rinking(const QString& filePath, QWidget *parent = nullptr);
    bool loadFile(const QString& filePath);
public  slots:
    //在 Qt 里，slots 是类的特殊成员函数，能够和信号进行连接。当对应的信号被发射时，槽函数就会被调用。
    void openFile();
signals:
};

#endif // RINKING_H
