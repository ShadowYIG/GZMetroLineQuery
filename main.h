#define MAXKEYERR 3
#define MaxVertexNum 500
#define MAXEXITNUM 20 
#define MAXTRANNUM 5
#define MAXSTATIONSUM 40
#define MAXLINESUM 30
#define ADMINPWD "123456" 
#define MAXSTANUM 20
#ifndef MAIN_H
#define MAIN_H
 
#ifdef __cplusplus
extern "C" {
#endif
typedef struct{
	int adnum;
	char exitname[100];//xx出口 
	char exitad[MAXSTANUM][100];//地名数组 
}exitinfo;

typedef struct{
	int lineno;//线路编号 
	int stationid;//站点编号 
	int stageseq;//站点顺序 
	int exitsum;//出口数 
	int x;//绘图时使用的坐标 
	int y;
	double longitude;//经度 
	double latitude;//纬度
	int transfer[MAXTRANNUM];//换乘站  
	char namecn[50];//站点中文名
	char nameen[50];//站点英文名 
	char startonetime[8];//上行首班车时间 
	char starttwotime[8];//下行首班车时间 
	char endonetime[8];//上行末班车时间 
	char endtwotime[8];//下行末班车时间 
//	lineinfo line;
	exitinfo exitdata[MAXEXITNUM];//出口数组 	
}stationinfo;


typedef struct{
	int number;//线路编号，线路文件名 
	int lineno;//线路号 
	int averageintervaltime;//平均班次间隔时间 
	int lastmodifytime;//线路开通时间 
	int stationsum;//站点数 
	char linecn[30];//线路中文名 
	char lineen[30];//线路英文名 
	char start[50];//始发站
	char end[50]; //终点站 
	char color[10];//8位线路颜色代码 
	char color1[10];//颜色代码 
	stationinfo station[MAXSTATIONSUM];
}lineinfo;




typedef struct EdgeNode{
	double weight;//距离权值 	
}Edge,Edgearc[MaxVertexNum][MaxVertexNum];


typedef struct{
	int vexnum,arcnum;
	stationinfo data[MaxVertexNum];
	Edgearc arcs;
}Graph;


void mylogin(void); 
void ModifyInfoMenu(int opt); 
void menu(int opt);
void quit(void); 
#ifdef  __cplusplus
}
#endif
 
#endif
