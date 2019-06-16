#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "utility.h"
#include "main.h"
#include "UserFun.h"
#include "AdminFun.h"
#include "AdminFunModi.h"
#define __STDC_WANT_LIB_EXT1__ 1
Graph G;
lineinfo L[MAXLINESUM];
int MaxLine;
int MaxStation;

/*初始化*/
void init(){
	
	int i=0,j=0,k=0,r=0,lineNum,stationNum,lineSum,temp,prior,next;
	double templa=0,templng=0;
	char linePath[100],str1[200],str2[200],chNumLine[5],chNumStation[5],chNumExit[5],*pname,*pad,tempch[5],*temp_p,*temp_e;
	char lineInfoPath[100]="data\\lineinfo.ini",buffer[MAXPATH];
//	strcpy(lineInfoPath,GetInfoPath());
//	getcwd(buffer,MAXPATH);
//    sprintf(buffer,"\\lineinfo.ini");
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	for(i=0;i<lineSum;i++){
		itoa(i,chNumLine,10);
		lineinfo *lInfo;
		lInfo=(lineinfo*)malloc(sizeof(lineinfo));
		/*初始化lInfo开始*/
		lInfo->averageintervaltime=0; 
		lInfo->lastmodifytime=0;
		lInfo->lineno=0;
		lInfo->number=0;
		lInfo->stationsum=0;
		lInfo->color[0]='\0';
		lInfo->color1[0]='\0';
		lInfo->end[0]='\0';
		lInfo->linecn[0]='\0';
		lInfo->lineen[0]='\0';
		lInfo->start[0]='\0';
		/*初始化lInfo结束*/ 
		
		BuildPath(GetIniKeyInt(lineInfoPath,chNumLine,"number"),linePath);//对应线路的文件路径获取 
		stationNum=GetIniKeyInt(linePath,"config","stationsum");//对应线路站点数量 
		 
//		printf("%d  ",GetIniKeyInt(lineInfoPath,chNumLine,"number"));
		/*线路信息获取*/
		lInfo->averageintervaltime=GetIniKeyInt(lineInfoPath,chNumLine,"averageintervaltime");
		lInfo->lastmodifytime=GetIniKeyInt(lineInfoPath,chNumLine,"lastmodifytime");
		lInfo->lineno=GetIniKeyInt(lineInfoPath,chNumLine,"lineno");
		lInfo->number=GetIniKeyInt(lineInfoPath,chNumLine,"number");
		if(lInfo->number>MaxLine && lInfo->number!=9999){//实时更新最大线id，方便添加地点 
			MaxLine=lInfo->number;
		}
		lInfo->stationsum=GetIniKeyInt(linePath,"config","stationsum");
		strcpy(lInfo->color,GetIniKeyString(lineInfoPath,chNumLine,"color"));
		strcpy(lInfo->color1,GetIniKeyString(lineInfoPath,chNumLine,"numcolor"));
		strcpy(lInfo->linecn,GetIniKeyString(lineInfoPath,chNumLine,"linecn"));
		strcpy(lInfo->lineen,GetIniKeyString(lineInfoPath,chNumLine,"lineen"));
		strcpy(lInfo->start,GetIniKeyString(linePath,"config","startone"));
		strcpy(lInfo->end,GetIniKeyString(linePath,"config","starttow"));
		/*站点信息获取*/
		for(j=0;j<stationNum;j++){//站点信息 
			stationinfo *sInfo;
			exitinfo *eInfo;
			sInfo=(stationinfo*)malloc(sizeof(stationinfo));
			eInfo=(exitinfo*)malloc(sizeof(exitinfo));
			/*初始化sInfo开始*/
			sInfo->exitsum=0;
			sInfo->lineno=0;
			sInfo->latitude=0; 
			sInfo->longitude=0;
			sInfo->stageseq=0;
			sInfo->stationid=0;
			for(k=0;k<MAXTRANNUM;k++){
				sInfo->transfer[k]=0;
			}
			
			sInfo->x=0;
			sInfo->y=0;
			sInfo->endonetime[0]='\0';
			sInfo->endtwotime[0]='\0';
			sInfo->namecn[0]='\0';
			sInfo->nameen[0]='\0';
			sInfo->startonetime[0]='\0';
			sInfo->starttwotime[0]='\0';
			for(k=0;k<MAXEXITNUM;k++){//设定出口数量最大为20，超过需要修改这里 
				sInfo->exitdata[k].exitname[0]='\0';
				for(int r=0;r<MAXEXITNUM;r++){
					sInfo->exitdata[k].exitad[r][0]='\0';
				}	
			}
			/*初始化sInfo结束*/

			itoa(j,chNumStation,10);			
			strcpy(sInfo->endonetime,GetIniKeyString(linePath,chNumStation,"endone"));
			strcpy(sInfo->endtwotime,GetIniKeyString(linePath,chNumStation,"endtow"));
			strcpy(sInfo->nameen,GetIniKeyString(linePath,chNumStation,"nameen"));
			strcpy(sInfo->namecn,GetIniKeyString(linePath,chNumStation,"namecn"));
			strcpy(sInfo->startonetime,GetIniKeyString(linePath,chNumStation,"startone"));
			strcpy(sInfo->starttwotime,GetIniKeyString(linePath,chNumStation,"starttow"));
			
			sInfo->stationid=GetIniKeyInt(linePath,chNumStation,"stationid");
			sInfo->exitsum=GetIniKeyInt(linePath,chNumStation,"exitsum");
			sInfo->lineno=GetIniKeyInt(linePath,chNumStation,"lineno");
			sInfo->longitude=atof(GetIniKeyString(linePath,chNumStation,"longitude"));
			sInfo->latitude=atof(GetIniKeyString(linePath,chNumStation,"latitude"));
			sInfo->stageseq=GetIniKeyInt(linePath,chNumStation,"stageseq");			
			sInfo->x=GetIniKeyInt(linePath,chNumStation,"x");
			sInfo->y=GetIniKeyInt(linePath,chNumStation,"y");
			if(sInfo->stationid>MaxStation){//实时更新最大站id，方便添加地点 
				MaxStation=sInfo->stationid;
			}
//			printf("%d.%s   ",sInfo->stationid,sInfo->namecn);
//			if(j%8==0){
//				printf("\n");
//			}
			
			/*站点出口信息获取*/ 
			strcpy(str1,GetIniKeyString(linePath,chNumStation,"exitname"));
			strcat(str1,"|");
			pname=strtok_s(str1, "|",&temp_p);
			k=0;
			while(pname){//此处未作站点最大数判断，后续有时间增加 
				k++;
				itoa(k,chNumExit,10);
				strcpy(sInfo->exitdata[k-1].exitname,pname);
				pname=strtok_s(NULL, "|",&temp_p);
				strcpy(str2,GetIniKeyString(linePath,chNumStation,chNumExit));
				strcat(str2,"|");
				pad=strtok_s(str2, "|",&temp_e);
				r=0;
				sInfo->exitdata[k-1].adnum=0;
				while(pad){
					strcpy(sInfo->exitdata[k-1].exitad[r++],pad);
					sInfo->exitdata[k-1].adnum++;
					pad=strtok_s(NULL, "|",&temp_e);
				}
			}
			/*站点出口信息获取end*/ 
			
			/*站点换乘信息获取*/ 
			
			strcpy(str1,GetIniKeyString(linePath,chNumStation,"transfer"));
			pname=strtok(str1, "|");
			k=0;
			while(pname){//此处未作站点最大数判断，后续有时间增加 	
				if(atoi(pname)!=0 && atoi(pname)!=lInfo->number && k<MAXTRANNUM){
					sInfo->transfer[k]=atoi(pname);
					k++;
				}
				pname=strtok(NULL, "|");
			}
			
			/*站点换乘信息获取end*/ 
			
			lInfo->station[j]=*sInfo;//将站点信息赋值到线路 
			
			if(sInfo->stationid<MaxVertexNum && G.data[sInfo->stationid].stationid==0){//将站点赋值到图信息头 
				G.vexnum++; 
				G.data[sInfo->stationid]=*sInfo;
				
			}
			/*构造站点邻接矩阵*/
			
			if(GetIniKeyInt(linePath,tempch,"prior")==0 || GetIniKeyInt(linePath,tempch,"next")==0){//判断是否存在前驱或后继，增加站点用 
				if(j+1<=stationNum){
					itoa(j+1,tempch,10);
					temp=GetIniKeyInt(linePath,tempch,"stationid");
					templa=atof(GetIniKeyString(linePath,tempch,"latitude"));
					templng=atof(GetIniKeyString(linePath,tempch,"longitude"));
					if(templa==0){//做是否无经纬度的判断，如果无则与站点同经纬度 
						templa=sInfo->latitude;
					} 
					if(templng==0){
						templng=sInfo->longitude;
					}
					if(G.arcs[sInfo->stationid][temp].weight==0){//矩阵对称赋值 
						G.arcs[sInfo->stationid][temp].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					if(G.arcs[temp][sInfo->stationid].weight==0){
						G.arcs[temp][sInfo->stationid].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					
					
					
				}
				if(j-1>=0){
					itoa(j-1,tempch,10);
					temp=GetIniKeyInt(linePath,tempch,"stationid");
					templa=atof(GetIniKeyString(linePath,tempch,"latitude"));
					templng=atof(GetIniKeyString(linePath,tempch,"longitude"));
					if(templa==0){//做是否无经纬度的判断，如果无则与站点同经纬度 
						templa=sInfo->latitude;
					} 
					if(templng==0){
						templng=sInfo->longitude;
					}
					if(G.arcs[sInfo->stationid][temp].weight==0){//矩阵对称赋值
						G.arcs[sInfo->stationid][temp].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					if(G.arcs[temp][sInfo->stationid].weight==0){
						G.arcs[temp][sInfo->stationid].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
				}	
				
			}else{//存在则执行这里 
				itoa(j,tempch,10);
				prior=GetIniKeyInt(linePath,tempch,"priorstation");
				next=GetIniKeyInt(linePath,tempch,"nextstation");
				templa=atof(GetIniKeyString(linePath,tempch,"latitude"));
				templng=atof(GetIniKeyString(linePath,tempch,"longitude"));
				if(prior!=0 && prior<MaxVertexNum){
					if(templa==0){//做是否无经纬度的判断，如果无则赋值广州CBD珠江新城经纬度 
						templa=23.119293;
					} 
					if(templng==0){
						templng=113.321206;
					}
					if(G.arcs[sInfo->stationid][prior].weight==0){//矩阵对称赋值
						G.arcs[sInfo->stationid][prior].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					if(G.arcs[prior][sInfo->stationid].weight==0){
						G.arcs[prior][sInfo->stationid].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
				}
				
				
				if(next!=0 && next<MaxVertexNum){
					if(templa==0){//做是否无经纬度的判断，如果无则赋值广州CBD珠江新城经纬度 
						templa=23.119293;
					} 
					if(templng==0){
						templng=113.321206;
					}
					if(G.arcs[sInfo->stationid][next].weight==0){//矩阵对称赋值
						G.arcs[sInfo->stationid][next].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
					if(G.arcs[next][sInfo->stationid].weight==0){
						G.arcs[next][sInfo->stationid].weight=get_distance(sInfo->latitude,sInfo->longitude,templa,templng);
						G.arcnum++;
					}
				}
				
			}
	
		}
		L[i]=*lInfo;
	}
	
	printf("顶点数：%d,边数：%d",G.vexnum,G.arcnum);
	
}

/*主菜单*/ 
void menu(int opt){
	char ch;
	system("cls");
	if(opt==1){//用户模式 
		printf("\t\t\t\t|————————————————————|\n");
		printf("\t\t\t\t|     【 欢迎使用地铁信息查询系统 】     |\n");
		printf("\t\t\t\t|               ");
		color(2);
		printf("【用户模式】");
		color(7);
		printf("             |\n");
		printf("\t\t\t\t|   1.路线查询                           |\n");
		printf("\t\t\t\t|   2.站点信息查询                       |\n");
//		printf("\t\t\t\t|   3.地图查看                           |\n");
//		printf("\t\t\t\t|   4.票价查询                           |\n");
		printf("\t\t\t\t|   3.票价查询                           |\n");
		printf("\t\t\t\t|   4.线路查看                           |\n");
		printf("\t\t\t\t|                                 q.返回 |\n");
		printf("\t\t\t\t|————————————————————|\n");
		printf("\t\t\t\t请输入序号【  】\b\b\b\b");
		ch=getch();
		printf("%c",ch);
		switch(ch){
			case '1':RouteQuery();break;
			case '2':QuerySiteInformation(1);break;
//			case '3':ViewMap();break;
//			case '4':QueryTicketPrice();break;
			case '3':QueryTicketPrice();break;
			case '4':QueryLine();break;
			case 'q':mylogin();break;
			default:
				color(4);
				printf("\n\t\t\t\t输入错误，1秒后重试\b\b\b");
				color(7);
				Sleep(1000); 
				menu(1);break;
		}
	}else if(opt==2){//管理员模式 
		printf("\t\t\t\t|————————————————————|\n");
		printf("\t\t\t\t|     【 欢迎使用地铁信息查询系统 】     |\n");
		printf("\t\t\t\t|              ");
		color(4);
		printf("【管理员模式】");
		color(7);
		printf("            |\n");
		printf("\t\t\t\t|   1.站点添加                           |\n");
		printf("\t\t\t\t|   2.站点删除                           |\n");
		printf("\t\t\t\t|   3.线路添加                           |\n");
		printf("\t\t\t\t|   4.线路删除                           |\n");
		printf("\t\t\t\t|   5.线路站点添加                       |\n");
		printf("\t\t\t\t|   6.线路信息修改                       |\n");
		printf("\t\t\t\t|   7.站点信息修改                       |\n");
		printf("\t\t\t\t|                                 q.返回 |\n");
		printf("\t\t\t\t|————————————————————|\n");
		printf("\t\t\t\t请输入序号【  】\b\b\b\b");
		ch=getch();
		printf("%c",ch);
		switch(ch){
			case '1':SiteAddition();break;
			case '2':SiteDeletion();break;
			case '3':LineAddition();break;
			case '4':LineDeletion();break;
			case '5':LineStaAddition();break;
			case '6':ModifyInfoMenu(1);break;
			case '7':ModifyInfoMenu(2);break;
			case 'q':mylogin();break;
			default:
				color(4);
				printf("\n\t\t\t\t输入错误，1秒后重试...");
				color(7);
				Sleep(1000); 
				menu(2);break;
		}
	}
	
}

/*管理员修改菜单*/ 
void ModifyInfoMenu(int opt){//1修改线路信息，2修改站点信息 
	char ch; 
	system("cls");
	if(opt==1){
		printf("\t\t\t\t|————————————————————|\n");
		printf("\t\t\t\t|            【 管理员模式 】            |\n");
		printf("\t\t\t\t|            【线路信息修改】            |\n");
		printf("\t\t\t\t|   1.线路名称修改                       |\n");
		printf("\t\t\t\t|   2.平均等待时间修改                   |\n");
//		printf("\t\t\t\t|   3.线路颜色修改                       |\n");
		printf("\t\t\t\t|                                 q.返回 |\n");
		printf("\t\t\t\t|————————————————————|\n");
		printf("\t\t\t\t请输入序号【  】\b\b\b\b");
		ch=getch();
		printf("%c",ch);
		switch(ch){
			case '1':LineNameModi();break;
			case '2':AverageTimeModi();break;
//			case '3':break;
			case 'q':menu(2);break;
			default:
				color(4);
				printf("\n\t\t\t\t输入错误，1秒后重试...");
				color(7);
				Sleep(1000); 
				ModifyInfoMenu(1);break;
		}
	}else if(opt==2){
		printf("\t\t\t\t|————————————————————|\n");
		printf("\t\t\t\t|            【 管理员模式 】            |\n");
		printf("\t\t\t\t|            【站点信息修改】            |\n");
		printf("\t\t\t\t|   1.站点名称修改                       |\n");
		printf("\t\t\t\t|   2.停始时间修改                       |\n");
		printf("\t\t\t\t|   3.经纬度修改                         |\n");
		printf("\t\t\t\t|   4.站点出口修改                       |\n");
		printf("\t\t\t\t|                                 q.返回 |\n");
		printf("\t\t\t\t|————————————————————|\n");
		printf("\t\t\t\t请输入序号【  】\b\b\b\b");
		ch=getch();
		printf("%c",ch);
		switch(ch){
			case '1':SiteNameModi();break;
			case '2':StoStaTimeModi();break;
			case '3':LaLoModi();break;
			case '4':SiteExitModi();break;
//			case '5':break;
			case 'q':menu(2);break;
			default:
				color(4);
				printf("\n\t\t\t\t输入错误，1秒后重试...");
				color(7);
				Sleep(1000); 
				ModifyInfoMenu(2);break;
		}
	}
	
	
}

/*登陆*/ 
void mylogin(void){
	int input,i,time=1;
	char pr[20],word,ch;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t|————————————————————|\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|     【 欢迎使用地铁信息查询系统 】     |\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|             制作人：谭康鸿             |\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|   ");
	color(2);
	printf("1.用户模式");
	color(7);
	printf("            ");
	color(4);
	printf("2.管理员模式");
	color(7);
	printf("   |\n");
	printf("\t\t\t\t|                 0.退出                 |\n");
	printf("\t\t\t\t|————————————————————|\n");
	printf("\t\t\t\t 请选择模式：【  】\b\b\b\b");
//	scanf("%1d",&input);
	ch=getch(); 
	printf("%c",ch);
	if(ch=='0'){
		printf("\n\t\t\t\t请稍后..."); 
		Sleep(300); 
		quit();
	}else if(ch=='1'){
		printf("\n\t\t\t\t请稍后..."); 
		Sleep(300); 
		menu(1);
	}else if(ch=='2'){
		printf("\n\t\t\t\t请稍后..."); 
		Sleep(300); 
		while(1){
			system("CLS");
			printf("\n\n");
			printf("\t\t\t\t|————————————————————|\n");
			printf("\t\t\t\t|                                        |\n");
			printf("\t\t\t\t|       【 当前模式：管理员模式 】       |\n");
			printf("\t\t\t\t|                                        |\n");
			printf("\t\t\t\t|————————————————————|\n");
			printf("\t\t\t\t 请输入密码：");
			i=0;
			while((word=getch())!='\r') 
			{
	            if(word=='\b' && i>0) 
				{
	                printf("\b \b");                 /*'\b'后面跟了一个空格' '来替换了最后一个字符*/
	                --i;
	            }
	            else if(word!='\b') 
				{
	                pr[i++]=word;
	                printf("*");
	            }
			}
	        pr[i]='\0';
			if(strcmp(pr,ADMINPWD)==0)
			{
				color(2);
				printf("\n\t\t\t\t 【密码正确!】\n");
				color(7);
				Sleep(500);
				system("CLS");
				break;
			}
			else
			{
				if(time>=MAXKEYERR){
//					system("CLS");
					color(4);
					printf("\n\t\t\t【密码错误】次数超过 %d 次",MAXKEYERR);
					printf("\n\t\t\t2秒后返回主界面...");
					Sleep(1000);
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b1秒后返回主界面...");
					color(7);
					Sleep(1000);
					system("CLS");
					time=0;
					mylogin();
					break;
				}
				time++;
				color(4);
				printf("\n\t\t\t\t 【密码有误!】\n");
				printf("\n\t\t\t\t 还有2秒可以重新输入密码...");
				Sleep(1000);
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b1秒可以重新输入密码...");
				color(7);
				Sleep(1000);
				system("CLS");
				
			}
		}
		menu(2);
	}else{
		color(4);
		printf("\n\t\t\t\t【输入错误】1秒后重试\b\b");
		color(7);
		Sleep(1000);
		mylogin();
	}
	
}

void quit(void){
	system("cls");
	printf("\t\t\t\t|————————————————————|\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|                感谢使用                |\n");
	printf("\t\t\t\t|         【 地铁信息查询系统 】         |\n");
	printf("\t\t\t\t|   （Metro Information Query System）   |\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|                                        |\n");
	printf("\t\t\t\t|            Made By 谭康鸿              |\n");
	printf("\t\t\t\t|————————————————————|\n");
}

int main(void) {
	
	MaxLine=0;
	MaxStation=0;
	G.arcnum=0;
	G.vexnum=0;
	for(int i=0;i<MaxVertexNum;i++){
		for(int j=0;j<MaxVertexNum;j++){
			G.arcs[i][j].weight=0;
			for(int k=0;k<MAXEXITNUM;k++){
				G.data[i].exitdata[j].exitad[k][0]='\0';	
			}
			G.data[i].exitdata[j].exitname[0]='\0';
		}
		G.data[i].endonetime[0]='\0';
		G.data[i].endtwotime[0]='\0';
		G.data[i].namecn[0]='\0';
		G.data[i].nameen[0]='\0';
		G.data[i].startonetime[0]='\0';
		G.data[i].starttwotime[0]='\0';
		G.data[i].exitsum=0;
		G.data[i].latitude=0;
		G.data[i].lineno=0;
		G.data[i].longitude=0;
		G.data[i].stageseq=0;
		G.data[i].stationid=0;
		for(int k=0;k<MAXTRANNUM;k++){
			G.data[i].transfer[k]=0;
		}	
		G.data[i].x=0;
		G.data[i].y=0;
//		G.data[i].line.color[0]='\0';
//		G.data[i].line.color1[0]='\0';
//		G.data[i].line.end[0]='\0';
//		G.data[i].line.linecn[0]='\0';
//		G.data[i].line.lineen[0]='\0';
//		G.data[i].line.start[0]='\0';
//		G.data[i].line.averageintervaltime=0;
//		G.data[i].line.lastmodifytime=0;
//		G.data[i].line.lineno=0;
//		G.data[i].line.number=0;
//		G.data[i].line.stationsum=0;
		
	}


	init();
	
	mylogin();
	return 0;
}
