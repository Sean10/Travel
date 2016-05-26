#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<time.h>
#include<malloc.h>
#include<algorithm>
#include <QString>
#include <iomanip>
using namespace std;

const int maxCity = 10;//城市最大数目
const int maxTour = 150;//旅客最大数目
const int maxRoute = 200;//各种航班数目最大值



void ReadData(void);
//void InputReq(void);
void Running(void);
void OutMap(void);
void init(void);

typedef struct Route{
    int Transport;//这条路线的交通工具 1为汽车 2为火车 3为飞机
    char id[20];//这个航班的编号,如3376(汽车)、Z66(火车)、CA1076(飞机)
    //QString id;
    char startin[30];//出发地城市
    //QString startin;
    //QString destin;
    char destin[30];//目的地城市
    int startID, destID;//出发城市和目的城市的编号
    int price;//这条路线的价格
    float timeSpan;//这条路线的时间跨度 (h)
    float firstExpressTime;//这趟航班的首发时间 (h)
    int interval;//每隔多久就发一次航班 (h),超过一天时间重新开始
}Route; //某一班飞机、火车或汽车路线

typedef struct Block{
    int routesNum;//这两个城市之间的路线条数
    Route rt[8];//这两个城市之间的路线
    int minMon;//两点之间最小金额
}Block;//邻接矩阵格子

typedef struct City{
    //char cityName[30];//城市名称
    QString cityName;
    float x, y;//城市的地理坐标
}City;

typedef struct State{
    int stateCase;//0表示还未出发；1表示已出发，在某班飞机或车上；2表示停留在某个城市；3表示到达目的地
    float percent;//表示旅客在某个分进程中进展的百分比
    Route currentRoute;//在某一个航班上
    float leftTime;//在此状态的剩余时间
}State;   //状态结构体

typedef struct PassingCity{
    //char cityName[30];//城市名称
    QString cityName;
    int cityNo;//城市的编号
    int duration;//在某个城市停留的时间，整数, 以小时计
}PassingCity;//途经城市结构体

typedef struct Tour{
    int service;//服务策略 1-最小金额 2-最短时间 3-限时最短时间策略
    float startTime;//该名旅客开始旅行的时间
    float nowTime;//该名旅客已经出发的时间
    //char TourName[30];//旅客姓名
    QString TourName;
    QString startin;
    QString destin;
    //char startin[30];//旅客出发地
    //char destin[30];//旅客目的地
    int PassingNum;//旅客停留的城市数目
    PassingCity passingCity[12];//停留城市计划
    int RoutesNum;//存储路线计划数目
    Route line[200];//存储系统分配的路线
    Tour *nextTour;//下一个旅客的信息
    State currentState;// 该旅客目前所处状态
}Tour;//旅客信息结构体


