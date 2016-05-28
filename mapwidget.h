#ifndef MAPWIDGET
#define MAPWIDGET

#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QPointF>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QPixmap>

class mapWidget : public QWidget
{
    Q_OBJECT
public:
    mapWidget(QWidget *parent = 0);
    //void paintEvent(QPaintEvent*);
    ~mapWidget();
    QPointF setPointPos();
    QPixmap setPointGraph();
    QPointF getCityCorner(int);
    int CityToNum(QString);
public slots:
    void paintEvent(QPaintEvent *);
protected:
private:


};

#endif
