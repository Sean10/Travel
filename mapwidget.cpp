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
    this->setFixedSize(612,502);
    //this->setStyleSheet("#Map{border-image:url(:/map.jpg);}");
    //this->setStyleSheet("#Map{border-image:url(:/map.jpg);}");
    this->setAutoFillBackground(false);

    QTimer *painttimer;
    painttimer = new QTimer;
    QThread *ThreadTimer1 = new QThread;
    painttimer->moveToThread(ThreadTimer1);
    painttimer->start(1000);
    //QObject::connect(painttimer, SIGNAL(timeout()), this, SLOT(update()));
    QObject::connect(painttimer, SIGNAL(timeout()), this, SLOT(paintEvent()));
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
    pngBackground.load(":/img/map.png");
    mapBackground.scale(1,1);
    mapBackground.setWindow(0,0,612,502);
    mapBackground.setRenderHint(QPainter::Antialiasing, true);
    mapBackground.drawPixmap(0,0,612,502,pngBackground);

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
    mapLocation.drawPixmap(setPointPos(),setPointGraph());
    //mapLocation.set




    update();
    //}
}

QPixmap mapWidget::setPointGraph()
{

    //qDebug() << "transport:" << tTour->currentState.currentRoute.Transport;
    if(tTour->currentState.stateCase != 1)
        return QPixmap(":/img/location.png");

    switch(tTour->currentState.currentRoute.Transport)
    {
    case 1:
        return QPixmap(":/img/car.ico");
    case 2:
        return QPixmap(":/img/train.ico");
    case 3:
        return QPixmap(":/img/plane.ico");
    default:
        qDebug() << "transport is wrong;";
        return QPixmap(":/img/location.png");
    }
}

QPointF mapWidget::setPointPos()
{
    //Widget *fatherPtr = (Widget *)parentWidget();
    static QPointF pointPos;
    switch(tTour->currentState.stateCase)
    {
    case 0:
        pointPos = getCityCorner(CityToNum(tTour->startin));
        break;
    case 1:
        double x,y;
        //pointPos = (getCityCorner(CityToNum(tTour->currentState.currentRoute.destin))\
                    -getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)))*(qreal)tTour->currentState.percent\
                +getCityCorner(CityToNum(tTour->currentState.currentRoute.startin));
        if(getCityCorner(CityToNum(tTour->currentState.currentRoute.destin)).x()\
                -getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).x())
            x = ((getCityCorner(CityToNum(tTour->currentState.currentRoute.destin)).x())
                    -(getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).x()))*(qreal)tTour->currentState.percent
                +(getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).x());
        else
            x = (getCityCorner(CityToNum(tTour->currentState.currentRoute.destin)).x()
                    -getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).x())*(1-(qreal)tTour->currentState.percent)
                +getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).x();

        if(getCityCorner(CityToNum(tTour->currentState.currentRoute.destin)).y()\
                -getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).y())
            y = (getCityCorner(CityToNum(tTour->currentState.currentRoute.destin)).y()
                    -getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).y())*(qreal)tTour->currentState.percent
                +getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).y();
        else
            y = (getCityCorner(CityToNum(tTour->currentState.currentRoute.destin)).y()
                    -getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).y())*(1-(qreal)tTour->currentState.percent)
                +getCityCorner(CityToNum(tTour->currentState.currentRoute.startin)).y();

        pointPos.setX(x);
        pointPos.setY(y);
        qDebug() << "percent:" << tTour->currentState.percent;
        qDebug() << "destID:" << tTour->currentState.currentRoute.destin;
        qDebug() << "startID:" << tTour->currentState.currentRoute.startin;
        //qDebug() << "destX, destY:" << getCityCorner(tTour->currentState.currentRoute.destID);
                    //getCityCorner(tTour->currentState.currentRoute.destID).y;
        //qDebug() << "startX, startY:" << getCityCorner(tTour->currentState.currentRoute.startID);//.x <<\
                  //  getCityCorner(tTour->currentState.currentRoute.startID).y;
        break;
    case 2:
        pointPos = getCityCorner(CityToNum(tTour->currentState.currentRoute.destin));
        break;
    case 3:
        pointPos = getCityCorner(CityToNum(tTour->destin));
        break;
    default:
        qDebug() << "PointPos is in error\n";
    }
        qDebug() << "State:" << tTour->currentState.stateCase;
        qDebug() << "x,y:" << pointPos;
    return pointPos;
}

QPointF mapWidget::getCityCorner(int city)
{
    int x, y;
    switch (city)
    {
    case 1:
        x = 382 - 15* 1 ;
        y = 189 - 39* 1 ;
        break;
    case 2:
        x = 439 - 15* 1 ;
        y = 261 - 39* 1 ;
        break;
    case 3:
        x = 331 - 15* 1 ;
        y = 394 - 39* 1 ;
        break;
    case 4:
        x = 256 - 15* 1 ;
        y = 297 - 39* 1 ;
        break;
    case 5:
        x = 529 - 15* 1 ;
        y = 176 - 39* 1 ;
        break;
    case 6:
        x = 305 - 15* 1 ;
        y = 282 - 39* 1 ;
        break;
    case 7:
        x = 189 - 15* 1 ;
        y = 245 - 39* 1 ;
        break;
    case 8:
        x = 151 - 15* 1 ;
        y = 306 - 39* 1 ;
        break;
    case 9:
        x = 154 - 15* 1 ;
        y = 182 - 39* 1 ;
        break;
    case 10:
        x = 323 - 15* 1 ;
        y = 210 - 39* 1 ;
        break;
    default:
        qDebug() << "pos is wrong:";
    }

    return QPointF(x, y);
}

int mapWidget::CityToNum(QString city)
{

    if(city == "Beijing")
        return 1;
    else if(city == "Shanghai")
        return 2;
    else if(city == "Guangzhou")
        return 3;
    else if(city == "Nanchang")
        return 4;
    else if(city == "Shenyang")
        return 5;
    else if(city == "Wuhan")
        return 6;
    else if(city == "Chengdu")
        return 7;
    else if(city == "Kunming")
        return 8;
    else if(city == "Lanzhou")
        return 9;
    else if(city == "Taiyuan")
        return 10;
}
