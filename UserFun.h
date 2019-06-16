#include "main.h"
//#define INFINITE 10000
#ifndef USER_FUN_H
#define USER_FUN_H

Graph G;
lineinfo L[MAXLINESUM];
int  MaxLine;
int MaxStation;
#ifdef __cplusplus
extern "C" {
#endif
//最短路径辅助数组 
typedef struct 
{ 
	int transfer;//换乘权值
	int time;//时间权重 
    double distance; 
    int path[MaxVertexNum]; 
}ArrayNode; 

char* TransferConversion(int num);
void PrintLine();
void PrintStation(int lNum);
void UserStationHead(void);
void UserStationHead2(void);
void UserStationHead3(void);
void UserStationTail(void);
void UserStationTail2(void);
void UserStationTailNoQ(void);
void UserStationTailAllNo(void);
void PrintStationInfo(int lNum,int sNum);
void PrintTicketPice(int from,int to);
int CalculateFares(double distance);
void Dijkstra(int from,int to);
void RouteQuery(void);
void QuerySiteInformation(int flag);
void ViewMap(void);
void QueryTicketPrice(void);
void PrintLineInfo(int lNum);
void QueryLine(void);
#ifdef  __cplusplus
}
#endif
 
#endif
