//#ifndef ihead
#include "ihead.h"
//#endif
//#ifndef running
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

Running::Running(){
    ;
}



Running::~Running()
{
}
