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
    sortFileByPoints(filePath);
    if (!loadFile(filePath)) {
        qDebug()<<"文件不存在";
    }

    QFile file(filePath);
    // 文件不存在时创建新文件
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::NewOnly)) {
        QTextStream out(&file);
        out << "";
        file.close();
        qDebug() << "已成功创建" << filePath;
    } else {
        // 检查文件是否已存在fileName
        if (file.exists()) {
            qDebug() << "文件已存在，未创建新文件:" << filePath;
        } else {
            qDebug() << "无法创建文件，可能是权限问题或路径无效:" << filePath;

        }
    }


    // 设置窗口标题和大小
    setWindowTitle("Ranking");
    resize(600, 400);
    QString strWinner;  //
}

bool Rinking::loadFile(const QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        textEdit->setPlainText(in.readAll());
        file.close();
        return true;
        update();
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

bool Rinking::sortFileByPoints(const QString &fileName) {
    QString tempFileName = fileName + ".temp";
    QFile inputFile(fileName);
    QFile outputFile(tempFileName);

    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件:" << fileName;
        return false;
    }

    // 存储玩家数据的结构体
    struct PlayerRecord {
        QString name;
        int points;
        QString originalLine; // 保存原始行用于特殊处理
        bool isSpecialLine;   // 是否为特殊行（非玩家记录）

        PlayerRecord() : points(0), isSpecialLine(false) {}
    };

    QList<PlayerRecord> records;
    QTextStream in(&inputFile);

    // 读取所有行并解析玩家数据
    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpression re(R"(^\s*(\d+)\s+player\s+(\S+)\s+(\d+)\s+points$)");
        QRegularExpressionMatch match = re.match(line);

        if (match.hasMatch()) {
            PlayerRecord record;
            record.name = match.captured(2);
            record.points = match.captured(3).toInt();
            record.isSpecialLine = false;
            records.append(record);
        } else if (!line.isEmpty()) {
            // 非记录行（如标题）作为特殊行处理
            PlayerRecord specialRecord;
            specialRecord.originalLine = line;
            specialRecord.isSpecialLine = true;
            records.append(specialRecord);
        }
    }

    inputFile.close();

    // 分离特殊行和玩家记录
    QList<PlayerRecord> specialLines;
    QList<PlayerRecord> playerRecords;

    for (const auto &record : records) {
        if (record.isSpecialLine) {
            specialLines.append(record);
        } else {
            playerRecords.append(record);
        }
    }

    // 对玩家记录按分数排序（降序）
    std::sort(playerRecords.begin(), playerRecords.end(),
              [](const PlayerRecord &a, const PlayerRecord &b) {
                  return a.points > b.points;
              });

    // 写入排序后的内容，重新生成正确的序号
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法创建临时文件:" << tempFileName;
        return false;
    }

    QTextStream out(&outputFile);

    // 先写入特殊行（如标题）
    for (const auto &specialLine : specialLines) {
        out << specialLine.originalLine << "\n";
    }

    // 再写入排序后的玩家记录，使用正确的序号
    int newId = 1;
    for (const auto &player : playerRecords) {
        QString newLine = QString("%1 player %2 %3 points")
        .arg(newId++)
            .arg(player.name)
            .arg(player.points);
        out << newLine << "\n";
    }

    outputFile.close();

    // 替换原文件
    if (QFile::remove(fileName)) {
        if (QFile::rename(tempFileName, fileName)) {
            qDebug() << "文件已按分数排序，序号已重新生成";
            return true;
        } else {
            qDebug() << "无法重命名临时文件";
        }
    } else {
        qDebug() << "无法删除原文件";
    }

    QFile::remove(tempFileName);
    return false;
}
