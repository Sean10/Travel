//#ifndef ihead
#include "ihead.h"
//#endif
#include "mapwidget.h"
#include "mainwindow.h"

extern int ReqNum;//旅客的数量
extern int cityNum, routeNum;//城市和交通路线的数量
extern int tRoutesNum;//初始化当前需要经过的路线
extern int path[20];//路径数组
extern Route buff[200];//存储路径缓冲区
extern Block mat[maxCity+2][maxCity+2];
extern City city[maxCity+2];
extern int minMoney;
extern int tMoney;
extern int tStart;//旅客的出发时间
extern Tour* hTour;
extern Tour* curTour;
extern int flag[maxCity+2];//暴力搜索的标记数组
extern int pathlen;//路径长度
extern float minTime;
extern clock_t zeroTime;//系统零点定时
extern clock_t currentTime;//系统临时计时变量

extern Tour *tTour;
//extern QWidget *mapRearl;

mapWidget::mapWidget(QWidget *parent)
    : QWidget(parent)
{
    //mapRearl = new QWidget;
    //this->setObjectName("Map");
    //QPixmap map(":/map.jpg");
    //this->setFixedSize(500,400);
    //this->setStyleSheet("#Map{border-image:url(:/map.jpg);}");
    //this->setStyleSheet("#Map{border-image:url(:/map.jpg);}");
    this->setAutoFillBackground(true);

    QTimer *paintmstimer;
    paintmstimer = new QTimer;
    paintmstimer->start(1000/60);
    QObject::connect(paintmstimer, SIGNAL(timeout()), this, SLOT(update()));
    //QPalette palette = this->palette();
    //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/map.jpg")));

    //this->(palette);
   // mapBackground
}

mapWidget::~mapWidget()
{
;
}

void mapWidget::paintEvent(QPaintEvent *)
{
    QPainter mapBackground(this);
    QPixmap pngBackground;
    pngBackground.load(":/map.jpg");
    mapBackground.scale(1,1);
    mapBackground.setRenderHint(QPainter::Antialiasing, true);
    mapBackground.drawPixmap(0,0,1103,827,pngBackground);



    QPainter mapLocation(this);
    //Widget *fatherPtr = (Widget *)parentWidget();
    //if (fatherPtr->currentTraveler != -1)
    //{
    mapLocation.scale(1,1);
    mapLocation.setRenderHint(QPainter::Antialiasing, true);
    //mapLocation.translate(250,200);
    //mapLocation.setViewport(0,0,500,400);
    //mapLocation.drawRect(250,200,10,10);
    //mapLocation.drawPixmap(setPointPos(), QPixmap(":/location.png"));
    mapLocation.drawPixmap(setPointPos(),QPixmap(":/location.png"));
    //mapLocation.set
    //}
}

QPointF mapWidget::setPointPos()
{
    //Widget *fatherPtr = (Widget *)parentWidget();
    static QPointF pointPos;
    switch(tTour->currentState.stateCase)
    {
    case 0:
        pointPos = getCityCorner(CityToNum(tTour->startin));
    case 1:
        pointPos = (getCityCorner(tTour->currentState.currentRoute.destID)
                    -getCityCorner(tTour->currentState.currentRoute.startID))*tTour->currentState.percent
                +getCityCorner(tTour->currentState.currentRoute.startID);
    case 2:
        pointPos = getCityCorner(tTour->currentState.currentRoute.startID);
    case 3:
        pointPos = getCityCorner(CityToNum(tTour->destin));
    default:
        qDebug() << "PointPos is in error\n";
    }

    return pointPos;
}

QPointF mapWidget::getCityCorner(int city)
{
    int x, y;
    switch (city)
    {
    case 0:
        x = 765;
        y = 317;
        break;
    case 1:
        x = 860;
        y = 492;
        break;
    case 2:
        x = 707;
        y = 701;
        break;
    case 3:
        x = 783;
        y = 552;
        break;
    case 4:
        x = 861;
        y = 289;
        break;
    case 5:
        x = 738;
        y = 530;
        break;
    case 6:
        x = 566;
        y = 518;
        break;
    case 7:
        x = 523;
        y = 651;
        break;
    case 8:
        x = 564;
        y = 440;
        break;
    case 10:
        x = 698;
        y = 388;
        break;
    }

    return QPointF(x, y);
}

int mapWidget::CityToNum(QString city)
{

    if(city == "Beijing")
        return 0;
    else if(city == "Shanghai")
        return 1;
    else if(city == "Guangzhou")
        return 2;
    else if(city == "Nanchang")
        return 3;
    else if(city == "Shenyang")
        return 4;
    else if(city == "Wuhan")
        return 5;
    else if(city == "Chengdu")
        return 6;
    else if(city == "Kunming")
        return 7;
    else if(city == "Lanzhou")
        return 8;
    else if(city == "Taiyuan")
        return 9;
}
