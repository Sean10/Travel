#include "ihead.h"
#include "running.h"
using namespace std;

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

Running::Running()//假设10s为一小时，不间断地刷新乘客的信息
{
    while(1)
    {
        int find = 0;
        //Tour* prev = hTour;
        Tour* p = hTour->nextTour;
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

Running::~Running()
{
}
