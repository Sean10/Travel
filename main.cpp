//!!!   QT5


#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *win = new Widget;
    win->show();
    return a.exec();
}
