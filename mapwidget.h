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

class mapWidget : public QWidget
{
    Q_OBJECT
public:
    mapWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    ~mapWidget();
    QPointF setPointPos();
    QPointF getCityCorner(int);
    int CityToNum(QString);
public slots:
protected:
private:


};

#endif
