#include "ihead.h"
#include "mainwindow.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//class Running;

int tMoney;
int tStart;//旅客出发时间
int pathlen;
Tour* hTour;
int minMoney;
float minTime;
Tour *curTour;
int flag[maxCity+2];
int ReqNum;//旅客的数量
clock_t currentTime;//系统临时计时变量
float currentHour;//系统计时(以小时为单位）
int cityNum, routeNum;//城市和交通路线的数量
clock_t zeroTime;//系统零点定时
int tRoutesNum;//初始化当前需要经过的路线
int path[20];//路径数组
Route buff[200];//存储路径缓冲区
Block mat[maxCity+2][maxCity+2];
City city[maxCity+2];
QFile *logFile;
QTextStream *out;
//extern void running();

int req, response;

void init(){
    ReqNum = 0;
    minMoney = 0x3f3f3f3f;//初始化最小金额
    minTime = 0x3f3f3f3f;//初始化最少时间
    tMoney = 0;//初始化当前金额


    hTour = (Tour*)malloc(sizeof(Tour));//旅客状态链
    curTour = NULL;
    memset(mat, 0, sizeof(mat));

    //printf("---------------------Tourist Information Inquiry System-------------------------\n");
    //printf("\n\n-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|Welcome!-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-\n\n");

    //printf("请输入要导入的地图文件：\n");
    //char getMap[30];
    //scanf("%s", getMap);
    //FILE *sourceData = fopen(":/transportData.txt", "r");//改成固定地图文件


    QFile sourceData(":/transportData.txt");
    if(!sourceData.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open the file by reading";
        return;
    }


    QTextStream in(&sourceData);


    //fscanf(sourceData, "%d", &cityNum);
    in >> cityNum >> endl;
    qDebug() << cityNum;
    for(int i = 1; i <= cityNum; i++)
    {
        //fscanf(sourceData, "%s%f%f", city[i].cityN    ame, &city[i].x, &city[i].y);
        in >> city[i].cityName >> city[i].x >> city[i].y >> endl;
        qDebug() << city[i].cityName << city[i].x << city[i].y;
    }
    //cout <<"aaa"<<endl;
    //fscanf(sourceData, "%d", &routeNum);
    in >> routeNum >> endl;
    //int q = 0;
    while(routeNum--)
    {
        Route temp;
        int i1, j1;
        //char buff2[30];
        QString buff2;//, tstartin[30], tdestin[30], tid[30];
        //fscanf(sourceData, "%s%s%s%s%d%f%f%d", buff2, temp.id, temp.startin, temp.destin, &temp.price, &temp.timeSpan, &temp.firstExpressTime, &temp.interval);
        in >> buff2 >> temp.id >> temp.startin >> temp.destin >> temp.price >> temp.timeSpan >> temp.firstExpressTime >> temp.interval >> endl;

        for(int i = 1; i <= cityNum; i++)
        {
            if(!QString::compare(temp.startin, city[i].cityName))
               i1 = i;
            if(!QString::compare(temp.destin, city[i].cityName))
               j1 = i;
        }
        mat[i1][j1].routesNum++;
        if(!QString::compare(buff2, "car"))
           temp.Transport = 1;
        else if(!QString::compare(buff2, "train"))//修改成else if
           temp.Transport = 2;
        else if(!QString::compare(buff2, "flight"))
           temp.Transport = 3;

        mat[i1][j1].rt[mat[i1][j1].routesNum].startID = i1;
        mat[i1][j1].rt[mat[i1][j1].routesNum].destID = j1;
        mat[i1][j1].rt[mat[i1][j1].routesNum] = temp;
    }
    //fclose(sourceData);
    //sourceData = NULL;
    sourceData.close();
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    init();
    zeroTime = clock();//系统零点时刻定时
    Widget *win = new Widget;

    QSplashScreen *splash = new QSplashScreen(QPixmap(":/img/splash.png"));
    splash->setDisabled(true); //禁用用户的输入事件响应
    splash->show();

    splash->showMessage(QObject::tr("正在启动中...."),Qt::AlignBottom|Qt::AlignRight,Qt::black);

    QElapsedTimer *splashTimer = new QElapsedTimer;
    splashTimer->start();
    while(splashTimer->elapsed() < (1000))
    {
         QCoreApplication::processEvents();
    }
    //QSplashScreen splash_2(QMovie(":/img/splash.gif"));

    //QLabel *label = new QLabel();
    //QMovie *mov = new QMovie(":/1.gif");
    //label->setMovie(mov);
    //mov->start();
      //  label->show();

    splash->finish(win);

    //QThread *ThreadID2;
    //ThreadID2 = new QThread;

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecFo(codec);

    logFile = new QFile("logFile.txt");
    if(!logFile->open(QIODevice::ReadOnly | QIODevice::Append))
        qDebug() << "could not open the logFile file";
    else
        qDebug() << "open the logFile file";


    //logFile = new ofstream;
    //logFile->open("logFile.txt",ios::out);
    //logFile->open("log.txt");
    //if(!logFile->is_open())
    //{
      //  qDebug() << "Could not open the logFile.txt";
        //return ;
    //}
    //else
      //  qDebug() << "Succeed in opening the logFile";
    //*logFile << unitbuf;

    //if(sourceData == NULL)
    //{
      //  printf("The map file doesn't exist！\n");//change
        //return;
    //}
    out = new QTextStream(logFile);
    //qDebug() << "out(main):" << out << *out;
    *out << "hello" << endl;
    win->show();

    delete splash;
    delete splashTimer;
    //logFile->close();

    qDebug() << "win have been shown;";
    return a.exec();
}
