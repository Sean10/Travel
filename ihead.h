#ifndef IHEADER_H
#define IHEADER_H

#endif // IHEADER_H

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<time.h>
#include<malloc.h>
//#include<dos.h>
//#include<windows.h>
//#include<winsock.h>
//#include<winbase.h>
#include<algorithm>

extern int serv;
extern int ReqNum;
extern int currentTime;//初始时间设为某一天早上0:00
const int maxCity = 12;//城市最大数目
const int maxTour = 150;//旅客最大数目
const int maxRoute =  200;//各种航班数目最大值

void ReadData(void);
void InputReq(void);
void Running(void);
void OutMap(void);

typedef struct Route{
    int Transport;//这条路线的交通工具 1为汽车 2为火车 3为飞机
    char id[20];//这个航班的编号,如3376(汽车)、Z66(火车)、CA1076(飞机)
    char *startin;//出发地城市
    char *destin;//目的地城市
    int price;//这条路线的价格
    float timeSpan;//这条路线的时间跨度 (h)
    float firstExpressTime;//这趟航班的首发时间 (h)
    int interval;//每隔多久就发一次航班 (h)
    Route* nextRoute;//出发地相同的下一条航班
}Route, *route; //某一班飞机、火车或汽车路线
extern Route routes[maxRoute];

typedef struct City{
    char *cityName;//城市名称
    float x, y;//城市的地理坐标
    route firstRoute;//从该城市出发的第一条航班
}City, *city;

typedef struct State{
    int stateCase;//0表示还未出发；1表示已出发，在某班飞机或车上；2表示停留在某个城市；3表示到达目的地
    float percent;//在某两个城市之间已走行程占总行程的百分比
    route *currentState;//在某一个航班上
    float leftTime;//在此状态的剩余时间
}State;   //状态结构体

typedef struct PassingCity{
    char *cityName;//城市名称
    int duration;//在某个城市停留的时间，整数
}PassingCity;//途经城市结构体

typedef struct Tour{
    char *TourName;//旅客姓名
    char *startin;//旅客出发地
    char *destin;//旅客目的地
    PassingCity passingCity[12];//停留城市计划
    Tour *nextTour;//下一个旅客的信息
    State currentState;// 该旅客目前所处状态
}Tour;//旅客信息结构体

