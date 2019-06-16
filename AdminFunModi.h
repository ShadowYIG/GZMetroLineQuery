#ifndef ADMIN_FUN_MODI_H
#define ADMIN_FUN_MODI_H

Graph G;
lineinfo L[MAXLINESUM];
int  MaxLine;
int MaxStation;
#ifdef __cplusplus
extern "C" {
#endif
void AdminModiLHead(void); 
void AdminModiSHead(void);
void AdminModiTail(void);
int LineModi(void);
void LineNameModi(void);
void AverageTimeModi(void);
void StationModi(int *lindex,int *sindex);
void SiteNameModi(void);
void StoStaTimeModi(void);
void LaLoModi(void);
void printexit(exitinfo exitdata[],int exitsum);
void SiteExitModi(void);
int writeexit(int lindex,int sindex);
#ifdef  __cplusplus
}
#endif
 
#endif
