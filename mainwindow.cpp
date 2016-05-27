#include "mainwindow.h"
#include "ihead.h"
#include "mapwidget.h"
//#ifndef running
//#include "running.h"

//class Running;

int Dijkstra1(int i, int j);
void Dijkstra2(int i, int j, Tour *tTour);
void Dijkstra3(int i, int j, Tour *tTour);
QString NumToCity(int);
void AddPassenger(QString passengerName);

Tour* tTour = new Tour;

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
extern Tour* hTour;//旅客结点的链表头结点
extern Tour* curTour;//旅客结点的链表尾结点
extern int flag[maxCity+2];//暴力搜索的标记数组
extern int pathlen;//路径长度
extern float minTime;
extern clock_t zeroTime;//系统零点定时
extern clock_t currentTime;//系统临时计时变量
extern int req;
//extern float restrainTime;

float tTime;
float tminTime = (float)0x3f3f3f3f;
float calTime;//模拟时间
float tcurTime;//临时计时变量1
float tcalTime;//临时计时变量2
Route buff2[200];//临时路径缓冲区
int tcurMon;//临时金额计数变量
int passSeq[12];//中间经过城市的标号
float restrainTime;//限时最小金额的时间限制条件
//QWidget *mapRearl;
mapWidget *mapReal;
//Tour* tTour = (Tour*)malloc(sizeof(Tour));
QMutex Mutex;


Widget::Widget(QStackedWidget *parent)
    : QStackedWidget(parent)
{

    setWindowTitle("Travel Query Search System V1.1");
    qDebug() << "Init Widget succeed";
    QIcon exeIcon(":/icon.ico");
    this->setWindowIcon(exeIcon);


    //connect(ThreadID2,SIGNAL(started()),this,SLOT(running));


    //QThread *ThreadID1;
    //ThreadID1 = new QThread;
    //QObject execute;
    //ThreadID1->start();
    //execute.moveToThread(ThreadID1);
    //connect(ThreadID1,SIGNAL(started()),this,SLOT(execute()));
    QTimer *timerRun = new QTimer;
    //timerRun->moveToThread(ThreadID2);
    QObject::connect(timerRun,SIGNAL(timeout()),this,SLOT(running()));
    timerRun->start(10000);


    //setFixedSize(720, 540);
    CreateFirstPage();
    CreateSecondPage();
    CreateThirdPage();
    CreateFourthPage();
    CreateFifthPage();
    CreateSecond2Page();
    CreateThird2Page();
    CreateFourth2Page();
    CreateSecond3Page();
    CreateThird3Page();
    CreateFourth3Page();

}

Widget::~Widget()
{

}

void Widget::CreateFirstPage()
{

    label = new QLabel(tr("欢迎使用旅行模拟系统V1.1"));
    labelHint = new QLabel(tr("请在以下功能中选择使用"));

    layoutLeft = new QHBoxLayout;
    layoutLeft->addWidget(labelHint);

    buttonRoute = new QPushButton(tr("查询并制定旅行路线"));
    buttonState = new QPushButton(tr("查询用户状态"));
    buttonPlanChange = new QPushButton(tr("改变用户计划"));

    connect(buttonRoute,SIGNAL(clicked()),this,SLOT(trans2()));
    connect(buttonState,SIGNAL(clicked(bool)),this,SLOT(trans2_2()));
    connect(buttonPlanChange,SIGNAL(clicked(bool)),this,SLOT(trans2()));
    /* 改变计划策略直接采用制定界面 */

    firstLayout = new QVBoxLayout;
    firstLayout->addWidget(label);
    firstLayout->addLayout(layoutLeft);
    firstLayout->addWidget(buttonRoute);
    firstLayout->addWidget(buttonState);
    firstLayout->addWidget(buttonPlanChange);

    //setFixedHeight(sizeHint().height());

    firstWidget = new QWidget;
    firstWidget->setLayout(firstLayout);
    this->addWidget(firstWidget);

    layout = new QVBoxLayout;
    layout->addWidget(this);

    zeroTime = clock();//系统零点时刻定时
    memset(buff, 0, sizeof(buff));
}

void Widget::CreateSecondPage()
{
    /* int fro, to;//起始城市的标号
    int inq;//选择服务策略
    int passNum;
    Tour* tTour = (Tour*)malloc(sizeof(Tour));*/
    //Tour *tTour = new Tour;


    labelHint2 = new QLabel(tr("请输入您的旅行计划"));

    QLabel *labelTourName;
    labelTourName = new QLabel(tr("姓名:"));

    lineTourName = new QLineEdit;
    labelTourName->setBuddy(lineTourName);

    //connect(lineTourName, SIGNAL(textChanged(QString)), this, SLOT(AddPassenger(text())));


    labelStarting = new QLabel(tr("起点:"));
    //lineStarting = new QLineEdit;
    lineStarting = new QComboBox;
    qDebug() << cityNum;
    for(int i = 0; i < cityNum; i++)
        lineStarting->addItem(NumToCity(i));

    labelStarting->setBuddy(lineStarting);

    // 添加在终点中去除已选的起点
    labelDestination = new QLabel(tr("终点:"));
    lineDestination = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineDestination->addItem(NumToCity(i));


    //connect(lineStarting, SIGNAL(currentIndexChanged(QString)), this, SLOT(SettingStarting(currentIndex())));
    //connect(lineDestination,SIGNAL(currentIndexChanged(QString)), this, SLOT(SettingDestination(currentIndex())));

    labelDestination->setBuddy(lineDestination);

    QComboBox *cityPassing1;
    cityPassing1 = new QComboBox;
    //cityPassing->

    QHBoxLayout *secondLayoutName;
    secondLayoutName = new QHBoxLayout;
    secondLayoutName->addWidget(labelTourName);
    secondLayoutName->addStretch();
    secondLayoutName->addWidget(lineTourName);
    secondLayoutName->addStretch();
    //secondLayoutName->addStretch();
    secondLayoutName->addStretch();

    secondLayout1 = new QHBoxLayout;
    secondLayout1->addWidget(labelStarting);
    secondLayout1->addWidget(lineStarting);
    secondLayout1->addWidget(labelDestination);
    secondLayout1->addWidget(lineDestination);

    QPushButton *addStopoverCity;
    addStopoverCity = new QPushButton(tr("添加停留城市"));
    passNum = 0;

    connect(addStopoverCity, SIGNAL(clicked(bool)),this,SLOT(AddStopoverCityAndTime()));

    //labelHint3 = new QLabel(tr("Please input the stopover cities:"));
    labelStopoverCity2_1 = new QLabel(tr("停留城市:"));
    lineStopoverCity2_1 = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineStopoverCity2_1->addItem(NumToCity(i));
    labelStopoverCity2_1->setBuddy(lineStopoverCity2_1);

    labelStopoverTime2_1 = new QLabel(tr("停留时长:"));
    lineStopoverTime2_1 = new QSpinBox();
    lineStopoverTime2_1->setRange(0,24);
    lineStopoverTime2_1->setValue(0);
    labelStopoverTime2_1->setBuddy(lineStopoverTime2_1);
    //connect(lineStopoverCity2_1, SIGNAL(currentIndexChanged(QString)),this,SLOT(SettingStopoverCity(1,currentIndex());));
    lineStopoverCity2_1->setEnabled(false);
    lineStopoverTime2_1->setEnabled(false);

    //第二个途经城市
    labelStopoverCity2_2 = new QLabel(tr("停留城市:"));
    lineStopoverCity2_2 = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineStopoverCity2_2->addItem(NumToCity(i));
    labelStopoverCity2_2->setBuddy(lineStopoverCity2_2);

    labelStopoverTime2_2 = new QLabel(tr("停留时长:"));
    lineStopoverTime2_2 = new QSpinBox();
    lineStopoverTime2_2->setRange(0,24);
    lineStopoverTime2_2->setValue(0);
    labelStopoverTime2_2->setBuddy(lineStopoverTime2_2);
    //connect(lineStopoverCity2_2, SIGNAL(currentIndexChanged(QString)),this,SLOT(SettingStopoverCity(2,currentIndex())));
    lineStopoverCity2_2->setEnabled(false);
    lineStopoverTime2_2->setEnabled(false);

    labelStopoverCity2_3 = new QLabel(tr("停留城市:"));
    lineStopoverCity2_3 = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineStopoverCity2_3->addItem(NumToCity(i));
    labelStopoverCity2_3->setBuddy(lineStopoverCity2_3);

    labelStopoverTime2_3 = new QLabel(tr("停留时长:"));
    lineStopoverTime2_3 = new QSpinBox();
    lineStopoverTime2_3->setRange(0,24);
    lineStopoverTime2_3->setValue(0);
    labelStopoverTime2_3->setBuddy(lineStopoverTime2_3);
    //connect(lineStopoverCity2_3, SIGNAL(currentIndexChanged(QString)),this,SLOT(SettingStopoverCity(3,currentIndex())));
    lineStopoverCity2_3->setEnabled(false);
    lineStopoverTime2_3->setEnabled(false);


    labelStopoverCity2_4 = new QLabel(tr("停留城市:"));
    lineStopoverCity2_4 = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineStopoverCity2_4->addItem(NumToCity(i));
    labelStopoverCity2_4->setBuddy(lineStopoverCity2_4);

    labelStopoverTime2_4 = new QLabel(tr("停留时长:"));
    lineStopoverTime2_4 = new QSpinBox();
    lineStopoverTime2_4->setRange(0,24);
    lineStopoverTime2_4->setValue(0);
    labelStopoverTime2_4->setBuddy(lineStopoverTime2_4);
    //connect(lineStopoverCity2_4, SIGNAL(currentIndexChanged(QString)),this,SLOT(SettingStopoverCity(4,currentIndex())));
    lineStopoverCity2_4->setEnabled(false);
    lineStopoverTime2_4->setEnabled(false);


    labelStopoverCity2_5 = new QLabel(tr("停留城市:"));
    lineStopoverCity2_5 = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineStopoverCity2_5->addItem(NumToCity(i));
    labelStopoverCity2_5->setBuddy(lineStopoverCity2_5);

    labelStopoverTime2_5 = new QLabel(tr("停留时长:"));
    lineStopoverTime2_5 = new QSpinBox();
    lineStopoverTime2_5->setRange(0,24);
    lineStopoverTime2_5->setValue(0);
    labelStopoverTime2_5->setBuddy(lineStopoverTime2_5);
    //connect(lineStopoverCity2_5, SIGNAL(currentIndexChanged(QString)),this,SLOT(SettingStopoverCity(5,currentIndex())));
    lineStopoverCity2_5->setEnabled(false);
    lineStopoverTime2_5->setEnabled(false);


    labelStopoverCity2_6 = new QLabel(tr("停留城市:"));
    lineStopoverCity2_6 = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineStopoverCity2_6->addItem(NumToCity(i));
    labelStopoverCity2_6->setBuddy(lineStopoverCity2_6);

    labelStopoverTime2_6 = new QLabel(tr("停留时长:"));
    lineStopoverTime2_6 = new QSpinBox();
    lineStopoverTime2_6->setRange(0,24);
    lineStopoverTime2_6->setValue(0);
    labelStopoverTime2_6->setBuddy(lineStopoverTime2_6);
    //connect(lineStopoverCity2_6, SIGNAL(currentIndexChanged(QString)),this,SLOT(SettingStopoverCity(6,currentIndex());));
    lineStopoverCity2_6->setEnabled(false);
    lineStopoverTime2_6->setEnabled(false);


    labelStopoverCity2_7 = new QLabel(tr("停留城市:"));
    lineStopoverCity2_7 = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineStopoverCity2_7->addItem(NumToCity(i));
    labelStopoverCity2_7->setBuddy(lineStopoverCity2_7);

    labelStopoverTime2_7 = new QLabel(tr("停留时长:"));
    lineStopoverTime2_7 = new QSpinBox();
    lineStopoverTime2_7->setRange(0,24);
    lineStopoverTime2_7->setValue(0);
    labelStopoverTime2_7->setBuddy(lineStopoverTime2_7);
    //connect(lineStopoverCity2_7, SIGNAL(currentIndexChanged(QString)),this,SLOT(SettingStopoverCity(7,currentIndex())));
    lineStopoverCity2_7->setEnabled(false);
    lineStopoverTime2_7->setEnabled(false);


    labelStopoverCity2_8 = new QLabel(tr("停留城市:"));
    lineStopoverCity2_8 = new QComboBox;
    for(int i = 0; i < cityNum; i++)
        lineStopoverCity2_8->addItem(NumToCity(i));
    labelStopoverCity2_8->setBuddy(lineStopoverCity2_8);

    labelStopoverTime2_8 = new QLabel(tr("停留时长:"));
    lineStopoverTime2_8 = new QSpinBox();
    lineStopoverTime2_8->setRange(0,24);
    lineStopoverTime2_8->setValue(0);
    labelStopoverTime2_8->setBuddy(lineStopoverTime2_8);
    //connect(lineStopoverCity2_8, SIGNAL(currentIndexChanged(QString)),this,SLOT(SettingStopoverCity(8,currentIndex())));
    lineStopoverCity2_8->setEnabled(false);
    lineStopoverTime2_8->setEnabled(false);

    go3 = new QPushButton(tr("下一步"));
    connect(go3,SIGNAL(clicked()),this,SLOT(trans3()));

    back1 = new QPushButton(tr("返回"));
    connect(back1,SIGNAL(clicked()),this,SLOT(trans1()));

    layoutButtonGoBack2 = new QHBoxLayout;
    layoutButtonGoBack2->addStretch();
    layoutButtonGoBack2->addWidget(go3);
    layoutButtonGoBack2->addWidget(back1);

    secondLayout2_1 = new QHBoxLayout;
    secondLayout2_1->addWidget(labelStopoverCity2_1);
    secondLayout2_1->addWidget(lineStopoverCity2_1);
    secondLayout2_1->addWidget(labelStopoverTime2_1);
    secondLayout2_1->addWidget(lineStopoverTime2_1);

    secondLayout2_2 = new QHBoxLayout;
    secondLayout2_2->addWidget(labelStopoverCity2_2);
    secondLayout2_2->addWidget(lineStopoverCity2_2);
    secondLayout2_2->addWidget(labelStopoverTime2_2);
    secondLayout2_2->addWidget(lineStopoverTime2_2);

    secondLayout2_3 = new QHBoxLayout;
    secondLayout2_3->addWidget(labelStopoverCity2_3);
    secondLayout2_3->addWidget(lineStopoverCity2_3);
    secondLayout2_3->addWidget(labelStopoverTime2_3);
    secondLayout2_3->addWidget(lineStopoverTime2_3);

    secondLayout2_4 = new QHBoxLayout;
    secondLayout2_4->addWidget(labelStopoverCity2_4);
    secondLayout2_4->addWidget(lineStopoverCity2_4);
    secondLayout2_4->addWidget(labelStopoverTime2_4);
    secondLayout2_4->addWidget(lineStopoverTime2_4);

    secondLayout2_5 = new QHBoxLayout;
    secondLayout2_5->addWidget(labelStopoverCity2_5);
    secondLayout2_5->addWidget(lineStopoverCity2_5);
    secondLayout2_5->addWidget(labelStopoverTime2_5);
    secondLayout2_5->addWidget(lineStopoverTime2_5);

    secondLayout2_6 = new QHBoxLayout;
    secondLayout2_6->addWidget(labelStopoverCity2_6);
    secondLayout2_6->addWidget(lineStopoverCity2_6);
    secondLayout2_6->addWidget(labelStopoverTime2_6);
    secondLayout2_6->addWidget(lineStopoverTime2_6);

    secondLayout2_7 = new QHBoxLayout;
    secondLayout2_7->addWidget(labelStopoverCity2_7);
    secondLayout2_7->addWidget(lineStopoverCity2_7);
    secondLayout2_7->addWidget(labelStopoverTime2_7);
    secondLayout2_7->addWidget(lineStopoverTime2_7);

    secondLayout2_8 = new QHBoxLayout;
    secondLayout2_8->addWidget(labelStopoverCity2_8);
    secondLayout2_8->addWidget(lineStopoverCity2_8);
    secondLayout2_8->addWidget(labelStopoverTime2_8);
    secondLayout2_8->addWidget(lineStopoverTime2_8);

    secondLayout = new QVBoxLayout;
    secondLayout->addLayout(secondLayoutName);
    secondLayout->addWidget(label);
    secondLayout->addWidget(labelHint2);
    secondLayout->addLayout(secondLayout1);
    secondLayout->addWidget(addStopoverCity);
    secondLayout->addLayout(secondLayout2_1);
    secondLayout->addLayout(secondLayout2_2);
    secondLayout->addLayout(secondLayout2_3);
    secondLayout->addLayout(secondLayout2_4);
    secondLayout->addLayout(secondLayout2_5);
    secondLayout->addLayout(secondLayout2_6);
    secondLayout->addLayout(secondLayout2_7);
    secondLayout->addLayout(secondLayout2_8);


    secondLayout->addLayout(layoutButtonGoBack2);

    secondWidget = new QWidget;
    secondWidget->setLayout(secondLayout);
    this->addWidget(secondWidget);

}

void Widget::CreateThirdPage()
{
    labelChooseStrategy = new QLabel(tr("请选择旅行计划策略:"));
    strategyValue = new QRadioButton(tr("最少消费策略"));
    strategyValue->setChecked(true);
    inq = 1;
    strategyTime = new QRadioButton(tr("最短时间策略"));
    strategyValueTime = new QRadioButton("限时最少消费策略");
    lineStrategyValueTime = new QSpinBox;
    lineStrategyValueTime->setRange(0,72);
    lineStrategyValueTime->setValue(0);
    //strategyValueTime->set();//wait for adding the lineEdit.
    connect(strategyValue,SIGNAL(toggled(bool)),this,SLOT(SettingStrategy1()));
    connect(strategyTime, SIGNAL(toggled(bool)),this,SLOT(SettingStrategy2()));
    connect(strategyValueTime,SIGNAL(toggled(bool)),this,SLOT(SettingStrategy3()));

    go4 = new QPushButton(tr("下一步"));
    connect(go4,SIGNAL(clicked()),this,SLOT(trans4()));

    back2 = new QPushButton(tr("返回"));
    connect(back2,SIGNAL(clicked(bool)),this,SLOT(trans2()));

    layoutButtonGoBack3 = new QHBoxLayout;
    layoutButtonGoBack3->addStretch();
    layoutButtonGoBack3->addWidget(go4);
    layoutButtonGoBack3->addWidget(back2);

    QHBoxLayout *layoutStrategyValueTime;
    layoutStrategyValueTime = new QHBoxLayout;
    layoutStrategyValueTime->addWidget(strategyValueTime);
    layoutStrategyValueTime->addWidget(lineStrategyValueTime);
    layoutStrategyValueTime->addStretch();

    layoutStrategy = new QVBoxLayout;
    layoutStrategy->addWidget(labelChooseStrategy);
    layoutStrategy->addWidget(strategyValue);
    layoutStrategy->addWidget(strategyTime);
    layoutStrategy->addLayout(layoutStrategyValueTime);
    layoutStrategy->addWidget(lineStrategyValueTime);
    layoutStrategy->addLayout(layoutButtonGoBack3);

    thirdWidget = new QWidget;
    thirdWidget->setLayout(layoutStrategy);
    this->addWidget(thirdWidget);
    connect(go4,SIGNAL(clicked()),this,SLOT(trans4()));
    connect(back2,SIGNAL(clicked()),this,SLOT(trans2()));
}

void Widget::CreateFourthPage()
{
    labelOrder = new QLabel(tr("According to your travel plan and chosen strategy, "
                               "the route calculated is as following:"));

    textContent = new QTextEdit;

    buttonConfirm = new QPushButton(tr("Confirm the Order"));
    buttonCancel = new QPushButton(tr("Cancel the order"));

    connect(buttonConfirm,SIGNAL(clicked()),this,SLOT(Confirm()));
    connect(buttonCancel,SIGNAL(clicked()),this,SLOT(trans3()));

    layoutButtonConfirm = new QHBoxLayout;
    layoutButtonConfirm->addStretch();
    layoutButtonConfirm->addWidget(buttonConfirm);
    layoutButtonConfirm->addWidget(buttonCancel);

    fourthLayout = new QVBoxLayout;
    fourthLayout->addWidget(labelOrder);
    fourthLayout->addWidget(textContent);
    fourthLayout->addStretch();//wait for add commands;
    fourthLayout->addLayout(layoutButtonConfirm);

    fourthWidget = new QWidget;
    fourthWidget->setLayout(fourthLayout);
    this->addWidget(fourthWidget);
}

void Widget::CreateFifthPage()
{
    textOrderConfirmed = new QTextEdit;

    buttonReturn = new QPushButton(tr("&Save and Return to Home Page"));
    connect(buttonReturn, SIGNAL(clicked(bool)), this, SLOT(trans1()));

    layoutButtonReturn = new QHBoxLayout;
    layoutButtonReturn->addStretch();
    layoutButtonReturn->addWidget(buttonReturn);

    fifthLayout = new QVBoxLayout;
    fifthLayout->addWidget(textOrderConfirmed);
    fifthLayout->addStretch();
    fifthLayout->addLayout(layoutButtonReturn);

    fifthWidget = new QWidget;
    fifthWidget->setLayout(fifthLayout);
    this->addWidget(fifthWidget);

}


void Widget::CreateSecond2Page()
{
    labelSearchTourist1 = new QLabel(tr("Please input the tourist's number you want to search:"));

    lineSearchTourist1 = new QLineEdit;
    labelSearchTourist1->setBuddy(lineSearchTourist1);

    go2_3 = new QPushButton(tr("下一步"));
    connect(go2_3,SIGNAL(clicked(bool)), this,SLOT(trans2_3()));

    back1_1 = new QPushButton;
    back1_1->setText(tr("返回"));
    connect(back1_1,SIGNAL(clicked(bool)),this,SLOT(trans1()));//here may risk of repeating

    layoutButtonGoBack2_3 = new QHBoxLayout;
    layoutButtonGoBack2_3->addStretch();
    layoutButtonGoBack2_3->addWidget(go2_3);
    layoutButtonGoBack2_3->addWidget(back1_1);

    layoutSecond2 = new QVBoxLayout;
    layoutSecond2->addWidget(labelSearchTourist1);
    layoutSecond2->addWidget(lineSearchTourist1);
    layoutSecond2->addLayout(layoutButtonGoBack2_3);

    second2Widget = new QWidget;
    second2Widget->setLayout(layoutSecond2);
    this->addWidget(second2Widget);
}

void Widget::CreateThird2Page()
{
    labelHintTour = new QLabel(tr("Dear No. %d tourist:"));

    textSearchContent = new QTextEdit;


/*
 *
 *Add the chosen information
 *
 */
    go2_4 = new QPushButton(tr("&Enter Real-Time Maps"));
    connect(go2_4,SIGNAL(clicked(bool)), this,SLOT(trans2_4()));

    back2_2 = new QPushButton(tr("返回"));
    connect(back2_2,SIGNAL(clicked(bool)),this,SLOT(trans2_2()));

    layoutButtonGoBack2_4 = new QHBoxLayout;
    layoutButtonGoBack2_4->addStretch();
    layoutButtonGoBack2_4->addWidget(go2_4);
    layoutButtonGoBack2_4->addWidget(back2_2);

    layoutThird2 = new QVBoxLayout;
    layoutThird2->addWidget(labelHintTour);
    layoutThird2->addWidget(textSearchContent);
    layoutThird2->addLayout(layoutButtonGoBack2_4);

    third2Widget = new QWidget;
    third2Widget->setLayout(layoutThird2);
    this->addWidget(third2Widget);

}

void Widget::CreateFourth2Page()
{
    back1_3 = new QPushButton;
    back1_3->setText(tr("返回"));
    connect(back1_3,SIGNAL(clicked(bool)),this,SLOT(trans1()));//here may risk of repeating



    layoutFourth2 = new QVBoxLayout;
    layoutFourth2->addStretch();
    layoutFourth2->addWidget(back1_3);

    //labelLocation = new QLabel;
    //painterLocation(":/location.png");
    //labelLocation->;

    mapReal = new mapWidget;
    //fourth2Widget = new QWidget;
    //mapWidget(fourth2Widget);
    //fourth2Widget->setObjectName("Map");
    //QPixmap map(":/map.jpg");
    //fourth2Widget->setFixedSize(702,505);
    //fourth2Widget->setStyleSheet("#Map{border-image:url(:/map.jpg);}");
    //fourth2Widget->setLayout(layoutFourth2);
    //fourth2Widget->
    mapReal->setLayout(layoutFourth2);
    this->addWidget(mapReal);
}

void Widget::CreateSecond3Page()
{

    labelSearchTourist2 = new QLabel(tr("Please input the tourist's number you want to search:"));

    lineSearchTourist2 = new QLineEdit;
    labelSearchTourist2->setBuddy(lineSearchTourist2);


    go3_3 = new QPushButton(tr("下一步"));
    connect(go3_3,SIGNAL(clicked(bool)), this,SLOT(trans3_3()));

    back1_2 = new QPushButton;
    back1_2->setText(tr("返回"));
    connect(back1_2,SIGNAL(clicked(bool)),this,SLOT(trans1()));//here may risk of repeating


    layoutButtonGoBack3_3 = new QHBoxLayout;
    layoutButtonGoBack3_3->addStretch();
    layoutButtonGoBack3_3->addWidget(go3_3);
    layoutButtonGoBack3_3->addWidget(back1_2);

    layoutSecond3 = new QVBoxLayout;
    layoutSecond3->addWidget(labelSearchTourist2);
    layoutSecond3->addWidget(lineSearchTourist2);
    layoutSecond3->addLayout(layoutButtonGoBack3_3);

    second3Widget = new QWidget;
    second3Widget->setLayout(layoutSecond3);
    this->addWidget(second3Widget);

}

void Widget::CreateThird3Page()
{

    labelHint3 = new QLabel(tr("Please input the stopover cities:"));
    labelStopoverCity = new QLabel(tr("停留城市:"));
    lineStopoverCity = new QLineEdit;
    labelStopoverCity->setBuddy(lineStopoverCity);
    labelStopoverTime = new QLabel(tr("停留时长:"));
    lineStopoverTime = new QLineEdit;
    labelStopoverTime->setBuddy(lineStopoverTime);

    go3_4 = new QPushButton(tr("下一步"));
    connect(go3_4,SIGNAL(clicked()),this,SLOT(trans3_4()));

    back3_2 = new QPushButton(tr("返回"));
    connect(back3_2,SIGNAL(clicked(bool)),this,SLOT(trans3_2()));

    layoutButtonGoBack3_4 = new QHBoxLayout;
    layoutButtonGoBack3_4->addStretch();
    layoutButtonGoBack3_4->addWidget(go3_4);
    layoutButtonGoBack3_4->addWidget(back3_2);

    thirdLayout3 = new QHBoxLayout;
    thirdLayout3->addWidget(labelStopoverCity);
    thirdLayout3->addWidget(lineStopoverCity);
    thirdLayout3->addWidget(labelStopoverTime);
    thirdLayout3->addWidget(lineStopoverTime);

    layoutThird3 = new QVBoxLayout;
    layoutThird3->addWidget(label);
    layoutThird3->addWidget(labelHint2);
    layoutThird3->addLayout(secondLayout1);
    layoutThird3->addWidget(labelHint3);
    layoutThird3->addLayout(thirdLayout3);
    layoutThird3->addLayout(layoutButtonGoBack3_4);


    third3Widget = new QWidget;
    third3Widget->setLayout(layoutThird3);
    this->addWidget(third3Widget);

}

void Widget::CreateFourth3Page()
{
    buttonConfirmReturn = new QPushButton(tr("Confirm the Order"));
    buttonCancelReturn = new QPushButton(tr("Cancel the order"));

    connect(buttonConfirmReturn,SIGNAL(clicked()),this,SLOT(trans1()));//recharge the save function
    connect(buttonCancelReturn,SIGNAL(clicked()),this,SLOT(trans1()));

    layoutButtonConfirmReturn = new QHBoxLayout;
    layoutButtonConfirmReturn->addStretch();
    layoutButtonConfirmReturn->addWidget(buttonConfirmReturn);
    layoutButtonConfirmReturn->addWidget(buttonCancelReturn);

    layoutFourth3 = new QVBoxLayout;
    layoutFourth3->addWidget(labelOrder);
    layoutFourth3->addStretch();//wait for add commands;
    layoutFourth3->addLayout(layoutButtonConfirmReturn);

    fourth3Widget = new QWidget;
    fourth3Widget->setLayout(layoutFourth3);
    this->addWidget(fourth3Widget);
}

void Widget::trans1()
{
    this->setCurrentWidget(firstWidget);
}

void Widget::trans2()
{
    req = 1;
    this->setCurrentWidget(secondWidget);
}

void Widget::trans3()
{
    this->setCurrentWidget(thirdWidget);
}

void Widget::trans4()
{
    this->setCurrentWidget(fourthWidget);
    execute();
}

void Widget::trans5()
{
    this->setCurrentWidget(fifthWidget);
}

void Widget::Confirm()
{
    if(QMessageBox::Yes == QMessageBox::question(this,
                                                 tr("Question"),
                                                 tr("Do you Confirm your order again?"),
                                                 QMessageBox::Yes | QMessageBox::No,
                                                 QMessageBox::Yes))
    {
        ask = 1;
        if(!curTour)
        {
           hTour->nextTour = tTour;
           curTour = tTour;
        }
        else
        {
            curTour->nextTour = tTour;
            curTour = tTour;
        }
        //textOrderConfirmed->clear();
        qDebug() << tr("下单成功，欢迎使用更多功能!\n");
        trans5();


    }
    else
    {
        ask = 0;
        qDebug() << "Bad Done";
    }

}

void Widget::trans2_2()
{
    req = 2;
    this->setCurrentWidget(second2Widget);
}

void Widget::trans2_3()
{
    this->setCurrentWidget(third2Widget);
    execute();
}

void Widget::trans2_4()
{
    //this->setCurrentWidget(fourth2Widget);
    this->setCurrentWidget(mapReal);
}

void Widget::trans3_2()
{
    req = 3;
    this->setCurrentWidget(second3Widget);
}

void Widget::trans3_3()
{
    this->setCurrentWidget(third3Widget);
}

void Widget::trans3_4()
{
    this->setCurrentWidget(fourth3Widget);
}

bool cmp1(const Route &temp1, const Route &temp2)//按金额升序排列
{
    return temp1.price < temp2.price;
}

bool cmp2(const Route &temp1, const Route &temp2)//按时间长短升序排列
{
    return temp1.timeSpan < temp2.timeSpan;
}

int Dijkstra1(int i, int j)//最小金额算法
{
    int curMon, k;
    int final[cityNum+2];
    int inPath[cityNum+2];
    memset(inPath, 0, sizeof(inPath));
    memset(path, 0, sizeof(path));
    inPath[j] = 1;
    for(int v = 1; v <= cityNum; v++)
    {
        final[v] = 0;//全部顶点初始化为位置最短路径
        path[v] = i;
    }
    mat[i][i].minMon = 0;
    final[i] = 1;
    for(int v = 1; v <= cityNum; v++)
    {
        curMon = 0x3f3f3f3f;
        for(int w = 1; w <= cityNum; w++)
        {
            if(!final[w] && mat[i][w].minMon < curMon)
            {
                k = w;
                curMon = mat[i][w].minMon;
                //printf("curMon:%d i:%d w:%d\n", curMon, i, w);
            }
        }
        final[k] = 1;
        for(int w = 1; w <= cityNum; w++)
        {
            //printf("1 curMon:%d i:%d w:%d k:%d %d\n", curMon, i, w, k, mat[i][w].minMon);
            if(!final[w] && (curMon + mat[k][w].minMon < mat[i][w].minMon))
            {
                mat[i][w].minMon = curMon + mat[k][w].minMon;
                //printf("2 curMon:%d i:%d w:%d k:%d %d\n", curMon, i, w, k, mat[i][w].minMon);
                path[w] = k;
            }
        }
    }
    int w = j, n = 1;
    while(path[w] != i)//记录经过的路径条数
    {
        w = path[w];
        n++;
    }
    int tRoutes = tRoutesNum;
    w = j;
    for(int v = tRoutes+n; v > tRoutes; v--)//记录路径
    {
        buff[v] = mat[path[w]][w].rt[1];
        w = path[w];
    }
    tRoutesNum += n;
    return mat[i][j].minMon;
}

void Dijkstra2(int i, int j, Tour *tTour)//最小时间算法，暴力递归回溯
{
    if(tcurTime > minTime)//剪枝
       return;
    flag[i] = 1;
    if(i == j)
    {
        int valid = 1;
        for(int k = 1; k <= tTour->PassingNum; k++)
        {
            if(!flag[passSeq[k]])
            {
                valid = 0;
                break;
            }
        }
        //printf("tcurTime:%f tcurMon:%d pathlen:%d\n", tcurTime, tcurMon, pathlen);
        if(tcurTime <= minTime&& valid)//时间最少，且经过所有指定的中间城市
        {
            for(int l = 1; l <= pathlen; l++)
                buff[l] = buff2[l];

            minTime = tcurTime;//记录时间总和
            tTour->RoutesNum = pathlen;//记录路线长度
        }
        return;
    }
    for(int k = 1; k <= cityNum; k++)
    {
        if(!flag[k])
        {
            int duration = 0;
            flag[k] = 1;
            for(int m = 1; m <= tTour->PassingNum; m++)
            {
                if(k == tTour->passingCity[m].cityNo)
                    duration = tTour->passingCity[m].duration;
            }
            for(int l = 1; l <= mat[i][k].routesNum; l++)
            {
                pathlen++;
                float temp = mat[i][k].rt[l].firstExpressTime;
                while(temp < tcalTime)//计算距离旅客行程开始时间的最近下一班车
                    temp += mat[i][k].rt[l].interval;
                temp = temp-tcalTime+mat[i][k].rt[l].timeSpan+duration;
                buff2[pathlen] = mat[i][k].rt[l];

                tcurTime += temp;
                tcalTime += temp;

                Dijkstra2(k, j, tTour);//递归

                pathlen--;
                tcurTime -= temp;
                tcalTime -= temp;
                flag[k] = 0;
            }
        }
    }
}

void Dijkstra3(int i, int j, Tour *tTour)//限时最小金额策略算法，类似于上面的Dijkstra2函数，只不过加上了时间的限制，然后计算最小金额
{
    //本算法是一个简单的回溯递归加剪枝算法
    qDebug() << "tcurTime:" << tcurTime;
    qDebug() << "restrainTime:" << restrainTime;
    qDebug() << "tcurMon:" << tcurMon;
    qDebug() << "minMoney:" << minMoney;
    if(tcurMon > minMoney || tcurTime > restrainTime)//剪枝
       return;

    flag[i] = 1;
    if(i == j)
    {
        int valid = 1;
        for(int k = 1; k <= tTour->PassingNum; k++)
        {
            if(!flag[passSeq[k]])
            {
                valid = 0;
                break;
            }
        }
        //printf("tcurTime:%f tcurMon:%d pathlen:%d\n", tcurTime, tcurMon, pathlen);
        if(tcurTime <= restrainTime && tcurMon < minMoney && valid)//在限定时间内、金额最小，且经过所有指定的中间城市
        {
            for(int l = 1; l <= pathlen; l++)
                buff[l] = buff2[l];

            tTime = tcurTime;//记录时间总和
            //calTime = tcalTime;//记录本路径当前时间
            tTour->RoutesNum = pathlen;//记录路线长度
            minMoney = tcurMon;//记录最小金额
        }
        return;
    }
    for(int k = 1; k <= cityNum; k++)
    {
        if(!flag[k])
        {
            int duration = 0;
            flag[k] = 1;
            for(int m = 1; m <= tTour->PassingNum; m++)
            {
                if(k == tTour->passingCity[m].cityNo)
                    duration = tTour->passingCity[m].duration;
            }
            for(int l = 1; l <= mat[i][k].routesNum; l++)
            {
                pathlen++;
                float temp = mat[i][k].rt[l].firstExpressTime;
                while(temp < tcalTime)//计算距离旅客行程开始时间的最近下一班车
                    temp += mat[i][k].rt[l].interval;
                temp = temp-tcalTime+mat[i][k].rt[l].timeSpan+duration;
                buff2[pathlen] = mat[i][k].rt[l];

                tcurTime += temp;
                tcalTime += temp;
                tcurMon += mat[i][k].rt[l].price;

                Dijkstra3(k, j, tTour);//递归

                pathlen--;
                tcurTime -= temp;
                tcalTime -= temp;
                tcurMon -= mat[i][k].rt[l].price;
                flag[k] = 0;
            }
        }
    }
}

QString NumToCity(int num)
{
    switch(num)
    {
    case 0: return ("北京");
    case 1: return ("上海");
    case 2: return ("广州");
    case 3: return ("南昌");
    case 4: return ("沈阳");
    case 5: return ("武汉");
    case 6: return ("成都");
    case 7: return ("昆明");
    case 8: return ("兰州");
    case 9: return ("太原");
    }
}

QString NumToCityStr(int num)
{
    switch(num)
    {
    case 0: return ("Beijing");
    case 1: return ("Shanghai");
    case 2: return ("Guangzhou");
    case 3: return ("Nanchang");
    case 4: return ("Shenyang");
    case 5: return ("Wuhan");
    case 6: return ("Chengdu");
    case 7: return ("Kunming");
    case 8: return ("Lanzhou");
    case 9: return ("Taiyuan");
    }
}
/*
void Widget::AddPassenger(QString passengerName)
{
    //tTour->TourName = passengerName;
}

void Widget::SettingStarting(int num)
{
    //tTour->startin = NumToCityStr(num);
}

void Widget::SettingDestination(int num)
{
    //tTour->destin = NumToCityStr(num);
}

void Widget::SettingStopoverCity(int num, int cityNum)
{
    //tTour->passingCity[num].cityName = NumToCityStr(cityNum);
}
*/
void Widget::execute()
{
    loop2:
    qDebug() << "Thread has survived";
    if(req == 1)
    {
        //passNum作为成员变量

        //Tour* tTour = (Tour*)malloc(sizeof(Tour));

        //printf("请输入您的姓名：\n");
        //scanf("%s", tTour->TourName);
        qDebug() << tr("姓名:") << lineTourName->text();
        //qDebug() << tTour->TourName;
        tTour->TourName = lineTourName->text();
        //qDebug() << tTour->TourName;
        //printf("请输入起始城市和目的城市：\n");
        //scanf("%s%s", tTour->startin, tTour->destin);

        tTour->startin = NumToCityStr(lineStarting->currentIndex());
        tTour->destin = NumToCityStr(lineDestination->currentIndex());


        for(int i = 1; i <= cityNum; i++)
        {
            if(!QString::compare(tTour->startin, city[i].cityName,Qt::CaseSensitive))
               fro = i;
            if(!QString::compare(tTour->destin, city[i].cityName,Qt::CaseSensitive))
               to = i;
        }
        //printf("请输入中间经过的城市个数：\n");

        //scanf("%d", &passNum);
        tTour->PassingNum = passNum;
        if(passNum)
        {
            //printf("请输入停留的城市名称以及停留的时间(以小时计)：\n");
            for(int i = 1; i <= passNum; i++)
            {
               //scanf("%s%d", tTour->passingCity[i].cityName, &tTour->passingCity[i].duration);
               tTour->passingCity[i].cityName = GetStopoverCity(i);
               tTour->passingCity[i].duration = GetStopoverTime(i);
               for(int j = 1; j <= cityNum; j++)
               {
                   if(!QString::compare(tTour->passingCity[i].cityName, city[j].cityName,Qt::CaseSensitive))
                   {
                      passSeq[i] = j;
                      tTour->passingCity[i].cityNo = j;
                   }
               }
            }
        }

        sort(passSeq+1, passSeq+passNum+1);
        passSeq[0] = fro;
        passSeq[passNum+1] = to;//将头尾加到路线数组中
        //printf("请输入服务策略：\n");
        //printf("1-最少金额策略\n2-最短时间策略\n3-限时最少金额策略\n");
        loop3:

        if(inq == 1)//最少金额策略
        {
            tTour->service = 1;
            for(int i = 1; i <= cityNum; i++)//刷新地图最小权值,每次计算都要刷新！
               for(int j = 1; j <= cityNum; j++)
               {
                  sort(mat[i][j].rt+1, mat[i][j].rt+mat[i][j].routesNum+1, cmp1);
                  mat[i][j].minMon = mat[i][j].rt[1].price;
                  //qDebug << "mat[" << i << "][" << j << "].minMon = " << mat[i][j].minMon << endl;
               }

            minMoney = 0x3f3f3f3f;
            tMoney = 0;
            tRoutesNum = 0;
            memset(buff, 0, sizeof(buff));

            for(int i = 0; i <= passNum; i++)
                tMoney += Dijkstra1(passSeq[i], passSeq[i+1]);
            //printf("%d %d:%d\n", passSeq[i], passSeq[i+1], tMoney);

            qDebug() << "tMoney:" << tMoney;
            qDebug() << "1minMoney:" << minMoney;

            if(tMoney < minMoney)
            {
                minMoney = tMoney;
                memset(tTour->line, 0, sizeof(tTour->line));

                for(int i = 1; i <= tRoutesNum; i++)
                    tTour->line[i] = buff[i];
                tTour->RoutesNum = tRoutesNum;
            }
            qDebug() << "minMoney:" << minMoney;

            while(next_permutation(passSeq+1, passSeq+passNum+1))
            {
                int not_cheapest = 0;
                tMoney = 0;
                tRoutesNum = 0;
                memset(buff, 0, sizeof(buff));

                for(int i = 0; i <= passNum; i++)
                {
                    if(tMoney > minMoney)//剪枝优化
                    {
                        not_cheapest = 1;
                        break;
                    }
                    tMoney += Dijkstra1(passSeq[i], passSeq[i+1]);
                    //qDebug() << passSeq[i] << passSeq[i+1] <<tMoney;
                }
                if(not_cheapest == 1)
                   continue;//剪枝
                if(tMoney < minMoney)
                {
                    minMoney = tMoney;
                    memset(tTour->line, 0, sizeof(tTour->line));
                    for(int i = 1; i <= tRoutesNum; i++)
                        tTour->line[i] = buff[i];

                    tTour->RoutesNum = tRoutesNum;
                }
                qDebug() << "3minMoney:" << minMoney;
            }
            qDebug() << "minMoney:" << minMoney;

            tTour->startTime = tTour->line[1].firstExpressTime;//最少金额策略将旅客出发时间设置为第一条路线的首发时间
            textContent->setPlainText(tr("系统计算的最少金额路线为：\n"));
            for(int i = 1; i <= tTour->RoutesNum; i++)
               textContent->append(tr("编号 ")+tTour->line[i].id + " " + tTour->line[i].startin+"->"+tTour->line[i].destin+"\n");
            textContent->append(tr("金额为")+QString::number(minMoney)+ tr("元，是否确认订单？"));

            textOrderConfirmed->setPlainText(tr("亲爱的")+lineTourName->text()+tr("顾客, 您的订单已确认。\n "));
            textOrderConfirmed->append(tr("系统计算的最少金额路线为：\n"));
            for(int i = 1; i <= tTour->RoutesNum; i++)
                textOrderConfirmed->append(tr("编号 ")+tTour->line[i].id+tTour->line[i].startin+"->"+tTour->line[i].destin+"\n");
            textOrderConfirmed->append(tr("金额为")+ QString::number(minMoney) + tr("元，是否确认订单？\n"));
            textOrderConfirmed->append(tr("您可以继续查看您的状态和日志.\n感谢您的使用!"));
        }
        else if(inq == 2)//最短时间策略
        {
            tTour->service = 2;
            //printf("请输入您要出发的时间(距离今天凌晨0:00的时间，以小时为单位)：\n");
            //scanf("%f", &tTour->startTime);
            //tStart %= 24;//以24小时为一个航班表循环
            tTour->startTime = 0;
            /* 待追加选择出发时间 */

            for(int i = 1; i <= cityNum; i++)//刷新地图最小权值,每次计算都要刷新！
               for(int j = 1; j <= cityNum; j++)
                  sort(mat[i][j].rt+1, mat[i][j].rt+mat[i][j].routesNum+1, cmp2);

            tRoutesNum = 0;
            minTime = (float)0x3f3f3f3f;
            memset(buff, 0, sizeof(buff));
            memset(buff2, 0, sizeof(buff2));

            tcalTime = tTour->startTime;//初始化模拟时间
            tcurTime = 0;

            Dijkstra2(fro, to, tTour);

            for(int i = 1; i <= tTour->RoutesNum; i++)
               tTour->line[i] = buff[i];

            textContent->setPlainText(tr("系统计算的最少时间路线为：\n"));
            for(int i = 1; i <= tTour->RoutesNum; i++)
               textContent->append(tr("编号 ") +tTour->line[i].id + " " + tTour->line[i].startin + "->" + tTour->line[i].destin);
            textContent->append(tr("时间一共为") + QString::number(minTime) + tr("小时（包括旅游停留时间和等待班车时间），是否确认订单？\n"));

            textOrderConfirmed->setPlainText(tr("亲爱的")+lineTourName->text()+tr("顾客, 您的订单已确认。\n "));
            textOrderConfirmed->append(tr("系统计算的最少时间路线为：\n"));
            for(int i = 1; i <= tTour->RoutesNum; i++)
               textOrderConfirmed->append(tr("编号 ") +tTour->line[i].id+ " " + tTour->line[i].startin + "->" + tTour->line[i].destin);
            textOrderConfirmed->append(tr("时间一共为") + QString::number(minTime) + tr("小时（包括旅游停留时间和等待班车时间），是否确认订单？\n"));
            textOrderConfirmed->append(tr("您可以继续查看您的状态和日志.\n感谢您的使用!"));
        }

        else if(inq == 3)
        {
            tTour->service = 3;
            //printf("请输入您要出发的时间(距离今天凌晨0:00的时间，以小时为单位)：\n");
            //scanf("%f", &tTour->startTime);
            tTour->startTime = 0;
            /* 待选择出发时间 */
            for(int i = 1; i <= cityNum; i++)//刷新地图最小权值,每次计算都要刷新！
               for(int j = 1; j <= cityNum; j++)
                  sort(mat[i][j].rt+1, mat[i][j].rt+mat[i][j].routesNum+1, cmp1);

            loop4://printf("请输入您的限制时间(以小时为单位)：\n");
            //cin >> restrainTime;
            restrainTime = lineStrategyValueTime->value();

            tTime = 0;
            tcurMon = 0;
            tRoutesNum = 0;
            minMoney = 0x3f3f3f3f;
            memset(buff, 0, sizeof(buff));
            memset(buff2, 0, sizeof(buff2));
            calTime = tTour->startTime;//初始化模拟时间

            tcalTime = calTime;
            tcurTime = tTime;

            Dijkstra3(fro, to, tTour);

            for(int i = 1; i <= tTour->RoutesNum; i++)
               tTour->line[i] = buff[i];

            if(minMoney == 0x3f3f3f3f)
            {
                textContent->setPlainText(tr("没有找到限定时间内的路线！请重新输入：\n"));

                goto loop4;
                qDebug() << tr("this is a error4\n");
            }
            else
            {
                textContent->setPlainText(tr("系统计算的限时最少金额路线为：\n"));
                for(int i = 1; i <= tTour->RoutesNum; i++)
                   textContent->append(tr("编号 ") +tTour->line[i].id +" "+ tTour->line[i].startin + "->" + tTour->line[i].destin);
                textContent->append(tr("金额为")+QString::number(minMoney)+ tr("元，总时间（包括等车、中间城市停留时间）为")+QString::number(tTime) + tr("小时（包括旅游停留时间和等待班车时间），是否确认订单？\n"));

                textOrderConfirmed->setPlainText(tr("亲爱的")+lineTourName->text()+tr("顾客, 您的订单已确认。\n "));
                textOrderConfirmed->append(tr("系统计算的限时最少金额路线为：\n"));
                for(int i = 1; i <= tTour->RoutesNum; i++)
                   textOrderConfirmed->append(tr("编号 ") +tTour->line[i].id +" "+ tTour->line[i].startin + "->" + tTour->line[i].destin);
                textOrderConfirmed->append(tr("金额为")+QString::number(minMoney)+ tr("元，总时间（包括等车、中间城市停留时间）为")+QString::number(tTime) + tr("小时（包括旅游停留时间和等待班车时间），是否确认订单？\n"));
                textOrderConfirmed->append(tr("您可以继续查看您的状态和日志.\n\n感谢您的使用!"));
            }
        }
        else
        {
            //printf("输入有误，请重新输入！\n");
            qDebug() << "This is an error3\n";
            goto loop3;
        }
        req = 0;

        //cin >> ask;

    }

    else if(req == 2)//查询旅客状态
    {

        int flag2 = 0;
        //printf("请输入您要查询的名字：\n\n");
        //scanf("%s", tName);
        tName = lineSearchTourist1->text();
        Tour* Srch = hTour->nextTour;
        qDebug() << "No Srch";
        while(Srch)
        {
            qDebug() << "Here is Srch ";
            if(!QString::compare(tName, Srch->TourName, Qt::CaseSensitive))
            {
               flag2 = 1;
               qDebug() << tr("已查询到该名旅客相关的信息，您也可以选择打开地图。\n\n");
               textSearchContent->setPlainText(tr("已查询到该名")+tName+tr("旅客相关的信息，您也可以选择打开地图。"));

               if(Srch->currentState.stateCase == 0)
               {
                   textSearchContent->append(tr("该旅客还没有出发~距离出发还有")+QString::number(Srch->currentState.leftTime)+tr("小时。\n\n"));
               }
               else if(Srch->currentState.stateCase == 1)
               {
                   textSearchContent->append(tr("该旅客出发地为")+Srch->startin+tr("，目的地为")+Srch->destin+tr("，目前在编号为")
                           +Srch->currentState.currentRoute.id+tr("、从")+Srch->currentState.currentRoute.startin
                           +tr("开往")+Srch->currentState.currentRoute.destin+tr("的路线上，距离到达本段目的地还有")
                           +(1-Srch->currentState.percent)*(Srch->currentState.currentRoute.timeSpan)+tr("小时。\n\n"));

               }
               else if(Srch->currentState.stateCase == 2)
               {
                   textSearchContent->append(tr("该旅客目前停留在")+Srch->currentState.currentRoute.destin+tr("\n"));
               }
               else if(Srch->currentState.stateCase == 3)
               {
                   textSearchContent->append(tr("该旅客已经到达目的地")+Srch->destin+tr("，系统将在不久后退出对本旅客的定位，请查询相关日志文件")
                                             +Srch->TourName+tr(".txt。\n\n"));
               }
            }
            Srch = Srch->nextTour;
        }
        if(!flag2)
            textSearchContent->append(tr("未查询到相关旅客信息，请确认是否下单成功或者该旅客已经到站！\n\n"));
    }
    else if(req == 3)//改变旅游计划
    {
        ;
    }
    //goto loop2;
    return ;
}

void Widget::AddStopoverCityAndTime()
{
    passNum++;
    switch(passNum)
    {
    case 1:
        lineStopoverCity2_1->setEnabled(true);
        lineStopoverTime2_1->setEnabled(true);

        break;
    case 2:
        lineStopoverCity2_2->setEnabled(true);
        lineStopoverTime2_2->setEnabled(true);
        break;
    case 3:
        lineStopoverCity2_3->setEnabled(true);
        lineStopoverTime2_3->setEnabled(true);
        break;
    case 4:
        lineStopoverCity2_4->setEnabled(true);
        lineStopoverTime2_4->setEnabled(true);
        break;
    case 5:
        lineStopoverCity2_5->setEnabled(true);
        lineStopoverTime2_5->setEnabled(true);
        break;
    case 6:
        lineStopoverCity2_6->setEnabled(true);
        lineStopoverTime2_6->setEnabled(true);
        break;
    case 7:
        lineStopoverCity2_7->setEnabled(true);
        lineStopoverTime2_7->setEnabled(true);
        break;
    case 8:
        lineStopoverCity2_8->setEnabled(true);
        lineStopoverTime2_8->setEnabled(true);
        break;
    default:
        qDebug() << "AddStopoverCity is error.";
        //passNum = 0;
    }
}

QString Widget::GetStopoverCity(int num)
{
    switch(num)
    {
    case 1:
        return NumToCityStr(lineStopoverCity2_1->currentIndex());
    case 2:
        return NumToCityStr(lineStopoverCity2_2->currentIndex());
    case 3:
        return NumToCityStr(lineStopoverCity2_3->currentIndex());
    case 4:
        return NumToCityStr(lineStopoverCity2_4->currentIndex());
    case 5:
        return NumToCityStr(lineStopoverCity2_5->currentIndex());
    case 6:
        return NumToCityStr(lineStopoverCity2_6->currentIndex());
    case 7:
        return NumToCityStr(lineStopoverCity2_7->currentIndex());
    case 8:
        return NumToCityStr(lineStopoverCity2_8->currentIndex());
    }
}

int Widget::GetStopoverTime(int time)
{
    switch(time)
    {
    case 1:
        return lineStopoverTime2_1->value();
    case 2:
        return lineStopoverTime2_2->value();
    case 3:
        return lineStopoverTime2_3->value();
    case 4:
        return lineStopoverTime2_4->value();
    case 5:
        return lineStopoverTime2_5->value();
    case 6:
        return lineStopoverTime2_6->value();
    case 7:
        return lineStopoverTime2_7->value();
    case 8:
        return lineStopoverTime2_8->value();
    }
}

void Widget::SettingStrategy1()
{
    inq = 1;
}

void Widget::SettingStrategy2()
{
    inq = 2;
}

void Widget::SettingStrategy3()
{
    inq = 3;
    //restrainTime = lineStrategyValueTime->value();
}
/*
void Widget::ConfirmOrder()
{
    if(ask == 1)
    {

    }
    else
    {
        //free(tTour);
        //printf("下单失败，返回上层!\n\n");

    }
}
*/
void Widget::running()//假设10s为一小时，不间断地刷新乘客的信息
{
    //while(1)
    if(1)
    {

        int find = 0;
        //Tour* prev = hTour;
        Tour* p = hTour->nextTour;
        qDebug() << "hTour->nextTour:" << hTour->nextTour;
        while(p)
        {
            currentTime = clock();
            float currentHour = (currentTime-zeroTime)/CLOCKS_PER_SEC;
            currentHour /= 10;//10s等于一小时
            float tempTime = p->startTime;
            float cur = p->line[1].firstExpressTime;
            while(cur < tempTime)
               cur += p->line[1].interval;
            tempTime = cur;
            if(currentHour <= tempTime)
            {
                p->currentState.stateCase = 0;
                p->currentState.leftTime = tempTime-currentHour;
            }
            else if(currentHour > tempTime)
            {
                for(int i = 1; i <= p->RoutesNum; i++)
                {
                    if(i != 1)
                    {
                        cur = p->line[i].firstExpressTime;
                        while(cur < tempTime)
                           cur += p->line[1].interval;
                        tempTime = cur;
                    }

                    tempTime += p->line[i].timeSpan;
                    if(currentHour < tempTime)
                    {
                        find = 1;
                        p->currentState.stateCase = 1;
                        p->currentState.currentRoute = p->line[i];
                        p->currentState.percent = (float)(tempTime-currentHour)/p->line[i].timeSpan;
                        break;
                    }
                    else
                    {
                        for(int j = 1; j <= p->PassingNum; j++)
                        {
                            if(p->line[i].destID == p->passingCity[i].cityNo)
                            {
                                tempTime += p->passingCity[i].duration;
                                if(currentHour < tempTime)
                                {
                                    p->currentState.stateCase = 2;
                                    p->currentState.currentRoute = p->line[i];
                                    find = 1;
                                    break;
                                }
                                break;
                            }
                        }
                    }
                    if(find)
                       break;
                }
                if(currentHour > 0)
                {
                    p->currentState.stateCase = 3;
                    //Sleep(200);//0.2秒后删除改点
                }
            }
            p = p->nextTour;
        }
    }
}
