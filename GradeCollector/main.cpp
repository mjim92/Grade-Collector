#include "mainwindow.h"
#include <QApplication>
/**
 * @brief Grade Collector GameBoard
 * @author Miguel Jimenez Spring 2015 PIC 10C Class.
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
