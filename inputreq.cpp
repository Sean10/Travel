#include "ihead.h"
#include "inputreq.h"
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
extern Tour* hTour;//旅客结点的链表头结点
extern Tour* curTour;//旅客结点的链表尾结点
extern int flag[maxCity+2];//暴力搜索的标记数组
extern int pathlen;//路径长度
extern float minTime;
extern clock_t zeroTime;//系统零点定时
extern clock_t currentTime;//系统临时计时变量

float tTime;
float tminTime = (float)0x3f3f3f3f;
float calTime;//模拟时间
float tcurTime;//临时计时变量1
float tcalTime;//临时计时变量2
Route buff2[200];//临时路径缓冲区
int tcurMon;//临时金额计数变量
int passSeq[12];//中间经过城市的标号
float restrainTime;//限时最小金额的时间限制条件

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

InputReq::InputReq()
{
    zeroTime = clock();//系统零点时刻定时
    loop2:int req, response;
    memset(buff, 0, sizeof(buff));
    printf("请选择以下服务:\n");
    printf("1-查询旅游路线\n");
    printf("2-查询旅客状态\n");
    printf("3-变更旅游计划\n");
    scanf("%d", &req);
    if(req == 1)
    {
        int fro, to;//起始城市的标号
        int inq;//选择服务策略
        int passNum;
        Tour* tTour = (Tour*)malloc(sizeof(Tour));
        printf("请输入您的姓名：\n");
        scanf("%s", tTour->TourName);
        printf("请输入起始城市和目的城市：\n");
        scanf("%s%s", tTour->startin, tTour->destin);
        for(int i = 1; i <= cityNum; i++)
        {
            if(!strcmp((char*)tTour->startin, (char*)city[i].cityName))
               fro = i;
            if(!strcmp((char*)tTour->destin, (char*)city[i].cityName))
               to = i;
        }
        printf("请输入中间经过的城市个数：\n");

        scanf("%d", &passNum);
        tTour->PassingNum = passNum;
        if(passNum)
        {
            printf("请输入停留的城市名称以及停留的时间(以小时计)：\n");
            for(int i = 1; i <= passNum; i++)
            {
               scanf("%s%d", tTour->passingCity[i].cityName, &tTour->passingCity[i].duration);
               for(int j = 1; j <= cityNum; j++)
               {
                   if(!strcmp((char*)tTour->passingCity[i].cityName, (char*)city[j].cityName))
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
        printf("请输入服务策略：\n");
        printf("1-最少金额策略\n2-最短时间策略\n3-限时最少金额策略\n");
        loop3:cin >> inq;

        if(inq == 1)//最少金额策略
        {
            tTour->service = 1;
            for(int i = 1; i <= cityNum; i++)//刷新地图最小权值,每次计算都要刷新！
               for(int j = 1; j <= cityNum; j++)
               {
                  sort(mat[i][j].rt+1, mat[i][j].rt+mat[i][j].routesNum+1, cmp1);
                  mat[i][j].minMon = mat[i][j].rt[1].price;
                  //printf("mat[%d][%d].minMon = %d\n", i, j, mat[i][j].minMon);
               }

            minMoney = 0x3f3f3f3f;
            tMoney = 0;
            tRoutesNum = 0;
            memset(buff, 0, sizeof(buff));

            for(int i = 0; i <= passNum; i++)
                tMoney += Dijkstra1(passSeq[i], passSeq[i+1]);
            //printf("%d %d:%d\n", passSeq[i], passSeq[i+1], tMoney);

            if(tMoney < minMoney)
            {
                minMoney = tMoney;
                memset(tTour->line, 0, sizeof(tTour->line));

                for(int i = 1; i <= tRoutesNum; i++)
                    tTour->line[i] = buff[i];
                tTour->RoutesNum = tRoutesNum;
            }
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
                    //printf("%d %d:%d\n", passSeq[i], passSeq[i+1], tMoney);
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
            }
            tTour->startTime = tTour->line[1].firstExpressTime;//最少金额策略将旅客出发时间设置为第一条路线的首发时间
            printf("系统计算的最少金额路线为：\n");
            for(int i = 1; i <= tTour->RoutesNum; i++)
               printf("编号 %s %s -> %s\n", tTour->line[i].id, tTour->line[i].startin,  tTour->line[i].destin);
            printf("金额为 %d 元，是否确认订单？\n1-是\t2-否\n", minMoney);
        }
        else if(inq == 2)//最短时间策略
        {
            tTour->service = 2;
            printf("请输入您要出发的时间(距离今天凌晨0:00的时间，以小时为单位)：\n");
            scanf("%f", &tTour->startTime);
            //tStart %= 24;//以24小时为一个航班表循环

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

            printf("系统计算的最少时间路线为：\n");
            for(int i = 1; i <= tTour->RoutesNum; i++)
               printf("编号 %s %s -> %s\n", tTour->line[i].id, tTour->line[i].startin,  tTour->line[i].destin);
            printf("时间一共为 %.1f 小时（包括旅游停留时间和等待班车时间），是否确认订单？\n1-是\t2-否\n", minTime);
        }

        else if(inq == 3)
        {
            tTour->service = 3;
            printf("请输入您要出发的时间(距离今天凌晨0:00的时间，以小时为单位)：\n");
               scanf("%f", &tTour->startTime);
            for(int i = 1; i <= cityNum; i++)//刷新地图最小权值,每次计算都要刷新！
               for(int j = 1; j <= cityNum; j++)
                  sort(mat[i][j].rt+1, mat[i][j].rt+mat[i][j].routesNum+1, cmp1);

            loop4:printf("请输入您的限制时间(以小时为单位)：\n");
            cin >> restrainTime;

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
                printf("没有找到限定时间内的路线！请重新输入：\n");
                goto loop4;
            }
            else
            {
                printf("系统计算的限时最少金额路线为：\n");
                for(int i = 1; i <= tTour->RoutesNum; i++)
                   printf("编号 %s %s -> %s\n", tTour->line[i].id, tTour->line[i].startin,  tTour->line[i].destin);
                printf("金额为 %d 元，总时间（包括等车、中间城市停留时间）为 %.1f 小时，是否确认订单？\n1-是\t2-否\n", minMoney, tTime);
            }
        }
        else
        {
            printf("输入有误，请重新输入！\n");
            goto loop3;
        }
        int ask;
        cin >> ask;
        if(ask == 1)
        {
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
            printf("下单成功，欢迎使用更多功能!\n\n");
        }
        else
        {
            free(tTour);
            printf("下单失败，返回上层!\n\n");
        }
    }

    else if(req == 2)//查询旅客状态
    {
        char tName[30];
        int flag2 = 0;
        printf("请输入您要查询的名字：\n\n");
        scanf("%s", tName);
        Tour* Srch = hTour->nextTour;
        while(Srch)
        {
            if(!strcmp((char*)tName, (char*)Srch->TourName))
            {
               flag2 = 1;
               printf("已查询到该名旅客相关的信息，您也可以选择打开地图。\n\n");
               if(Srch->currentState.stateCase == 0)
               {
                  printf("该旅客还没有出发~距离出发还有%.1f小时。\n\n", Srch->currentState.leftTime);
               }
               else if(Srch->currentState.stateCase == 1)
               {
                  printf("该旅客出发地为%s，目的地为%s，目前在编号为%s、从%s开往%s的路线上，距离到达本段目的地还有%.1f小时。\n\n",
                  Srch->startin, Srch->destin, Srch->currentState.currentRoute.id, Srch->currentState.currentRoute.startin ,
                  Srch->currentState.currentRoute.destin, (1-Srch->currentState.percent)*(Srch->currentState.currentRoute.timeSpan));
               }
               else if(Srch->currentState.stateCase == 2)
               {
                  printf("该旅客目前停留在%s。\n", Srch->currentState.currentRoute.destin);
               }
               else if(Srch->currentState.stateCase == 3)
                  printf("该旅客已经到达目的地%s，系统将在不久后退出对本旅客的定位，请查询相关日志文件%s.txt。\n\n",
                  Srch->destin, Srch->TourName);
            }
            Srch = Srch->nextTour;
        }
        if(!flag2)
            printf("未查询到相关旅客信息，请确认是否下单成功或者该旅客已经到站！\n\n");
    }
    else if(req == 3)//改变旅游计划
    {
        ;
    }
    goto loop2;
    return ;
}


InputReq::~InputReq()
{;
}
