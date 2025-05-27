#include "game.h"
#include "mainwindow.h"
#include <QApplication>

#include <bits/stdc++.h>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow mai;
    mai.show();
    return a.exec();
}
