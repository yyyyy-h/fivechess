#include "rinking.h"

Rinking::Rinking(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    layout->addWidget(textEdit);

    // 加载文件
    QString filePath= "ranking.txt";
    if (!loadFile(filePath)) {
        textEdit->setPlainText("无法加载文件: " + filePath);
    }

    // 设置窗口标题和大小
    setWindowTitle("Ranking");
    resize(600, 400);
}

bool Rinking::loadFile(const QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        textEdit->setPlainText(in.readAll());
        file.close();
        return true;
    }
    return false;
}


void Rinking::openFile()
{
    QString filePath = "ranking.txt";

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        textEdit->setPlainText(in.readAll());
        file.close();
    }
    else {
        // 如果文件不存在，创建一个空文件
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.close();
            textEdit->setPlainText("已创建新文件。");
        }
        else {
            QMessageBox::critical(this, "错误", "无法打开或创建文件: " + file.errorString());
        }
    }
}
