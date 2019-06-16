#ifndef ADMIN_FUN_H
#define ADMIN_FUN_H
Graph G;
lineinfo L[MAXLINESUM];
int  MaxLine;
int MaxStation;
#ifdef __cplusplus
extern "C" {
#endif
int AdminPrintLine(int flag);
void AdminPrintStation(int lNum);
void AdminLineHead(void);
void AdminStationHead(void);
void AdminStationHead2(void);
void AdminStationTail2(void);
void AdminStationTailAllNo(void);
void AdminStationTailNoM(void);
void AdminStationTail(void);
void PrintAddStaInfo(int lNum,int sNum);
int ReturnLineStaSum(int lineNo);
void SiteAddition(void);
int SelectAddres(stationinfo *station,int code,int *lnum,int *snum);
int AdditionWrite(int sid,int lindex);
void SiteDeletion();
void DeleteStaMem(stationinfo station,int code,int LineNum,int stationNum);
int DeleteStaWrite(int sNum,int lindex);
int SelectSta(int i);
int LineStaLink(lineinfo *line);
void LineAddition(void);
int LineAdditionWrite(lineinfo *line);
void LineDeletion(void);
void DeleteLineMem(int lnum);
int DeleteLineWrite(int lnum);
void LineStaAddition(void); 
#ifdef  __cplusplus
}
#endif
 
#endif
