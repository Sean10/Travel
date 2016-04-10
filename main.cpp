#include "ihead.h"
#include "mainwindow.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

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
int cityNum, routeNum;//城市和交通路线的数量
clock_t zeroTime;//系统零点定时
int tRoutesNum;//初始化当前需要经过的路线
int path[20];//路径数组
Route buff[200];//存储路径缓冲区
Block mat[maxCity+2][maxCity+2];
City city[maxCity+2];

int main(int argc, char *argv[])
{
    ReqNum = 0;
    minMoney = 0x3f3f3f3f;//初始化最小金额
    minTime = 0x3f3f3f3f;//初始化最少时间
    tMoney = 0;//初始化当前金额


    hTour = (Tour*)malloc(sizeof(Tour));//旅客状态链
    curTour = NULL;
    memset(mat, 0, sizeof(mat));

    printf("---------------------Tourist Information Inquiry System-------------------------\n");
    printf("\n\n-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|Welcome!-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-\n\n");

    loop1:printf("请输入要导入的地图文件：\n");
    char getMap[30];
    scanf("%s", getMap);
    FILE *sourceData = fopen(getMap, "r");
    if(sourceData != NULL)
    {
        fscanf(sourceData, "%d", &cityNum);
        for(int i = 1; i <= cityNum; i++)
        {
            fscanf(sourceData, "%s%f%f", city[i].cityName, &city[i].x, &city[i].y);
        }
        //cout <<"aaa"<<endl;
        fscanf(sourceData, "%d", &routeNum);
        int q = 0;
        while(routeNum--)
        {
            Route temp;
            int i1, j1;
            char buff2[30], tstartin[30], tdestin[30], tid[30];
            fscanf(sourceData, "%s%s%s%s%d%f%f%d", &buff2, &temp.id, &temp.startin, &temp.destin, &temp.price, &temp.timeSpan, &temp.firstExpressTime, &temp.interval);

            for(int i = 1; i <= cityNum; i++)
            {
                if(!strcmp(temp.startin, city[i].cityName))
                   i1 = i;
                if(!strcmp(temp.destin, city[i].cityName))
                   j1 = i;
            }
            mat[i1][j1].routesNum++;
            if(!strcmp(buff2, "car"))
               temp.Transport = 1;
            else if(!strcmp(buff2, "train"))//修改成else if
               temp.Transport = 2;
            else if(!strcmp(buff2, "flight"))
               temp.Transport = 3;

            mat[i1][j1].rt[mat[i1][j1].routesNum].startID = i1;
            mat[i1][j1].rt[mat[i1][j1].routesNum].destID = j1;
            mat[i1][j1].rt[mat[i1][j1].routesNum] = temp;
        }
        fclose(sourceData);
        sourceData = NULL;
    }
    else
    {
        printf("您输入的文件不存在，请重新输入！\n");
        goto loop1;
    }

/*
 * 这里的对线程ID赋值是干什么的？
    DWORD ThreadID1 = 1;
    HANDLE hRead1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InputReq, NULL, 0, &ThreadID1);
    DWORD ThreadID2 = 2;
    HANDLE hRead2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Running, NULL, 0, &ThreadID2);//处于不断刷新旅客的状态中
    DWORD ThreadID3 = 3;
    HANDLE hRead3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OutMap, NULL, 0, &ThreadID3);
*/

    QObject *InPutReq = new QObject;
    QThread *ThreadID1;
    InPutReq->moveToThread(ThreadID1);

    QObject *Running = new QObject;
    QThread *ThreadID2;
    Running->moveToThread(ThreadID2);

    QStackedWidget *widget = new QStackedWidget;
    QThread *ThreadID3;
    widget->moveToThread(ThreadID3);

    while(1);
    return 0;


    QApplication a(argc, argv);
    Widget *win = new Widget;
    win->show();
    return a.exec();
}
