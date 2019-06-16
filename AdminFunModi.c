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

extern Graph G;
extern lineinfo L[MAXLINESUM];
extern int  MaxLine;
extern int MaxStation;
/*线路修改输出头*/
void AdminModiLHead(void){
	color(7);
	system("cls");
	printf("\t\t\t\t| ——————————————————————— |\n");
	printf("\t\t\t\t|                 ");
	color(2);
	printf("【 管理员模式 】");
	color(7);
	printf("               |\n");
	printf("\t\t\t\t|                   【线路修改】                 |\n");
	printf("\t\t\t\t|                                                |\n"); 
}

/*站点修改输出头*/
void AdminModiSHead(void){
	color(7);
	system("cls");
	printf("\t\t\t\t| ——————————————————————— |\n");
	printf("\t\t\t\t|                 ");
	color(2);
	printf("【 管理员模式 】");
	color(7);
	printf("               |\n");
	printf("\t\t\t\t|                   【站点修改】                 |\n");
	printf("\t\t\t\t|                                                |\n");
}

/*修改输出尾*/
void AdminModiTail(void){
	printf("\t\t\t\t|                                                |\n");
	printf("\t\t\t\t| ——————————————————————— |\n");
	
}

/*线路修改线路选择*/
int LineModi(void){
	int LineNum,code=1,nrindex=0,lineSum;
	char lch[5],sch[5],lineName[50]; 
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	AdminModiLHead(); 
	AdminModiTail();
	AdminLineHead();
	nrindex=AdminPrintLine(1);
	AdminStationTail();
	while(1){
		if(code==1){
			printf("\t\t\t\t请输入要修改的线路序号：【  】\b\b\b\b");
			color(9);
			scanf("%s",&lch); 
			color(7);
			if(strcmp(sch,"q")==0){
				ModifyInfoMenu(1);break;
			}else if(strcmp(sch,"m")==0){
				menu(2);break;
			}else{
				LineNum=atoi(lch);
				if(nrindex<LineNum){
					LineNum++;
				}
				color(7);
				code=2;break;
			}
			while(LineNum<=0 && LineNum-1>=lineSum){
				color(4);
				printf("\t\t\t\t输入错误\n");
				color(7);
				printf("\t\t\t\t请重新输入要修改的线路序号：【  】\b\b\b\b");
				color(9);
				scanf("%s",&lch); 
				color(7);
				if(strcmp(sch,"q")==0){
					ModifyInfoMenu(1);break;
				}else if(strcmp(sch,"m")==0){
					menu(2);break;
				}else{
					LineNum=atoi(lch);
					if(nrindex<LineNum){
						LineNum++;
					}
					color(7);
					code=2;break;
				}
				
			}
			
		}
		if(code==2){
			break;
		} 
	}
	if(code==2){
		return LineNum-1;
	}
	return -1;
	
}

/*线路名称修改*/
void LineNameModi(void){
	int lindex=-1,trueInput=0,enname=0;
	char title[5],key[50],value[100],linename[30];
	char lineInfoPath[100]="data\\lineinfo.ini";
	lindex=LineModi();
	if(lindex==-1){
		color(4);
		printf("\t\t\t\t【选择失败】"); 
		color(7);
		ModifyInfoMenu(1);
		return;
	}
	color(7);printf("\t\t\t\t请输入该线路中文名称：");
	color(9);scanf("%s",&linename); 
	color(7);printf("\t\t\t\t你确定要将");
	color(6);printf("【%s】",L[lindex].linecn);
	color(7);printf("更改为");
	color(2);printf("【%s】",linename);
	color(7);printf("吗？[y/n]【  】\b\b\b\b"); 
	color(9);char ch=getch();
	printf("%c",ch); 
	trueInput=0;
	while(!trueInput){
		switch(ch){
			case 'y':
			case 'Y':
				color(7);printf("\n\t\t\t\t修改中，请稍后....");
				trueInput=1;
				strcpy(L[lindex].linecn,linename);
				itoa(lindex,title,10);
				if(PutIniKeyString(lineInfoPath,title,"linecn",linename)!=EOF){
					color(2);printf("\n\t\t\t\t【修改成功】");
				}else{		
					color(4);printf("\n\t\t\t\t【修改失败】");
				}
				break;
			case 'n':
			case 'N':	
				ModifyInfoMenu(1);trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	color(7);printf("\n\t\t\t\t请问你需要修改该线路英文名称吗？[y/n]【  】\b\b\b\b");
	trueInput=0;
	while(!trueInput){
		switch(ch){
			case 'y':
			case 'Y':
				enname=1;break;
			case 'n':
			case 'N':	
				trueInput=1;enname=0;break;
			default:
				enname=0;
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	if(enname==1){
		color(7);printf("\t\t\t\t请输入该线路英文名称：");
		color(9);scanf("%s",&linename); 
		color(7);printf("\t\t\t\t你确定要将");
		color(6);printf("【%s】",L[lindex].lineen);
		color(7);printf("更改为");
		color(2);printf("【%s】",linename);
		color(7);printf("吗？[y/n]【  】\b\b\b\b"); 
		color(9);char ch=getch();
		printf("%c",ch); 
		trueInput=0;
		while(!trueInput){
			switch(ch){
				case 'y':
				case 'Y':
					color(7);printf("\n\t\t\t\t修改中，请稍后....");
					trueInput=1;
					strcpy(L[lindex].lineen,linename);
					itoa(lindex,title,10);
					if(PutIniKeyString(lineInfoPath,title,"lineen",linename)!=EOF){
						color(2);printf("\n\t\t\t\t【修改成功】");
						color(7);printf("\n\t\t\t\t输入任意字符返回主菜单：【  】\b\b\b\b");
						ch=getch();
						menu(2);
					}else{		
						color(4);printf("\n\t\t\t\t【修改失败】");
						color(7);printf("\n\t\t\t\t输入任意字符返回主菜单：【  】\b\b\b\b");
						ch=getch();
						menu(2);
					}
					break;
				case 'n':
				case 'N':	
					trueInput=1;break;
				default:
					trueInput=0;
					color(4);
					printf("\n\t\t\t\t【输入错误】\n");
					color(7);break;
				
			}	
		}
	}
	color(7);printf("\n\t\t\t\t输入任意字符返回主菜单：【  】\b\b\b\b");
	ch=getch();
	ModifyInfoMenu(1);

}

/*线路平均发车时间修改*/
void AverageTimeModi(void){
	int lindex=-1,trueInput=0,averagetime=0;
	char title[10];
	char lineInfoPath[100]="data\\lineinfo.ini";
	lindex=LineModi();
	if(lindex==-1){
		color(4);
		printf("\t\t\t\t【选择失败】"); 
		color(7);
		ModifyInfoMenu(1);
		return;
	}
	color(7);printf("\t\t\t\t请输入该线路平均等待时间：  分钟\b\b\b\b\b");
	color(9);scanf("%d",&averagetime); 
	color(7);printf("\t\t\t\t你确定要将");
	color(6);printf("【%d分钟】",L[lindex].averageintervaltime);
	color(7);printf("更改为");
	color(2);printf("【%d分钟】",averagetime);
	color(7);printf("吗？[y/n]【  】\b\b\b\b"); 
	color(9);char ch=getch();
	printf("%c",ch); 
	trueInput=0;
	while(!trueInput){
		switch(ch){
			case 'y':
			case 'Y':
				color(7);printf("\n\t\t\t\t修改中，请稍后....");
				trueInput=1;
				L[lindex].averageintervaltime=averagetime*60;
				itoa(lindex,title,10);
				if(PutIniKeyInt(lineInfoPath,title,"averageintervaltime",averagetime*60)!=EOF){
					color(2);printf("\n\t\t\t\t【修改成功】");
				}else{		
					color(4);printf("\n\t\t\t\t【修改失败】");
					
				}
				break;
			case 'n':
			case 'N':	
				trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	color(7);printf("\n\t\t\t\t输入任意字符返回主菜单：【  】\b\b\b\b");
	ch=getch();
	ModifyInfoMenu(1);
}

/*站点修改站点选择*/
void StationModi(int *lindex,int *sindex){
	int code=1,LineNum=-1,stationNum=-1,lineSum=0;
	char sch[5],lch[5];
	char lineInfoPath[100]="data\\lineinfo.ini";
	lineSum=GetIniKeyInt(lineInfoPath,"config","linesum");
	AdminModiSHead(); 
	AdminModiTail();
	while(1){
		if(code==1){
			system("cls");
			AdminModiSHead(); 
			AdminModiTail();
			AdminLineHead();
			AdminPrintLine(0);
			AdminStationTailNoM();
			printf("\t\t\t\t请输入线路序号：【  】\b\b\b\b");
			color(9);
			scanf("%s",&lch); 
			color(7);
			if(strcmp(lch,"q")==0){
				ModifyInfoMenu(2);break;
			}else{
				LineNum=atoi(lch);
				*lindex= LineNum-1; 
				color(7);
				code=2;
			}
			while(LineNum<=0 && LineNum-1>=lineSum){
				color(4);
				printf("\t\t\t\t输入错误\n");
				color(7);
				printf("\t\t\t\t请重新输入线路序号：【  】\b\b\b\b");
				color(9);
				scanf("%s",&lch); 
				color(7);
				if(strcmp(sch,"q")==0){
					menu(2);break;
				}else{
					LineNum=atoi(lch);
					*lindex= LineNum-1; 
					color(7);
					code=2;break;
				} 
				
			}
			
		}
		
		
		if(code==2){
			system("cls");
			AdminModiSHead(); 
			AdminModiTail();
			AdminStationHead(); 
			AdminPrintStation(LineNum-1);
			AdminStationTail();
			printf("\t\t\t\t请输入修改的站点序号：【  】\b\b\b\b");
			color(9);
			scanf("%s",&sch); 
			if(strcmp(sch,"q")==0){
				code=1;
				continue;
			}else if(strcmp(sch,"m")==0){
				menu(2);break;
			}else{
				stationNum=atoi(sch);
				*sindex=stationNum-1;
				code=3;
			}
			color(7);
			while(stationNum<=0 && stationNum>=L[LineNum-1].stationsum){
				color(4);
				printf("\t\t\t\t输入错误\n");
				color(7);
				printf("\t\t\t\t请重新输入修改的站点序号：【  】\b\b\b\b");
				color(9);
				scanf("%s",sch); 
				if(strcmp(sch,"q")==0){
					code=1;
					continue;
				}else if(strcmp(sch,"m")==0){
					menu(2);break;
				}else{
					stationNum=atoi(sch);
					*sindex=stationNum-1;
					code=3;break;
				}
				
			}
			
		}
		if(code==3){
			break;
		}
		
	}

	
}

/*站点名称修改*/
void SiteNameModi(void){
	int lindex=-1,sindex=-1,enname=0,trueInput=0;
	char stationname[50],title[50];
	char linePath[100];
	StationModi(&lindex,&sindex);
	if(lindex==-1 && sindex==-1){
		color(4);
		printf("\t\t\t\t【选择失败】"); 
		color(7);
		ModifyInfoMenu(2);return;
	}
	color(7);printf("\t\t\t\t请输入该线路中文名称：");
	color(9);scanf("%s",&stationname); 
	color(7);printf("\t\t\t\t你确定要将");
	color(6);printf("【%s】",L[lindex].station[sindex].namecn);
	color(7);printf("更改为");
	color(2);printf("【%s】",stationname);
	color(7);printf("吗？[y/n]【  】\b\b\b\b"); 
	color(9);char ch=getch();
	printf("%c",ch); 
	trueInput=0;
	while(!trueInput){
		switch(ch){
			case 'y':
			case 'Y':
				color(7);printf("\n\t\t\t\t修改中，请稍后....");
				trueInput=1;
				strcpy(L[lindex].station[sindex].namecn,stationname);
				strcpy(G.data[L[lindex].station[sindex].stationid].namecn,stationname);
				itoa(L[lindex].number,title,10);
				BuildPath(L[lindex].number,linePath);
				itoa(sindex,title,10);
				if(PutIniKeyString(linePath,title,"namecn",stationname)!=EOF){
					color(2);printf("\n\t\t\t\t【修改成功】");
				}else{		
					color(4);printf("\n\t\t\t\t【修改失败】");
				}
				trueInput=1;break;
			case 'n':
			case 'N':	
				trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	color(7);printf("\n\t\t\t\t请问你需要修改该站点英文名称吗？[y/n]【  】\b\b\b\b");
	trueInput=0;
	while(!trueInput){
		switch(ch){
			case 'y':
			case 'Y':
				enname=1;break;
			case 'n':
			case 'N':	
				trueInput=1;enname=0;break;
			default:
				enname=0;
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	if(enname==1){
		color(7);printf("\t\t\t\t请输入该站点英文名称：");
		color(9);scanf("%s",&stationname); 
		color(7);printf("\t\t\t\t你确定要将");
		color(6);printf("【%s】",L[lindex].station[sindex].nameen);
		color(7);printf("更改为");
		color(2);printf("【%s】",stationname);
		color(7);printf("吗？[y/n]【  】\b\b\b\b"); 
		color(9);char ch=getch();
		printf("%c",ch); 
		trueInput=0;
		while(!trueInput){
			switch(ch){
				case 'y':
				case 'Y':
					color(7);printf("\n\t\t\t\t修改中，请稍后....");
					trueInput=1;
					strcpy(L[lindex].station[sindex].nameen,stationname);
					strcpy(G.data[L[lindex].station[sindex].stationid].nameen,stationname);
					BuildPath(L[lindex].number,linePath);
					itoa(sindex,title,10);
					if(PutIniKeyString(linePath,title,"nameen",stationname)!=EOF){
						color(2);printf("\n\t\t\t\t【修改成功】");
					}else{		
						color(4);printf("\n\t\t\t\t【修改失败】");
					}
					trueInput=1;break;
				case 'n':
				case 'N':	
					trueInput=1; break;
				default:
					trueInput=0;
					color(4);
					printf("\n\t\t\t\t【输入错误】\n");
					color(7);break;
				
			}	
		}
	}
	color(7);printf("\n\t\t\t\t输入任意字符返回主菜单：【  】\b\b\b\b");
	ch=getch();
	ModifyInfoMenu(2);
	
}

/*站点始发时间终点时间修改*/
void StoStaTimeModi(void){
	int lindex=-1,sindex=-1,trueInput=0;
	char title[50],time1[50],time2[50];
	char linePath[100];
	StationModi(&lindex,&sindex);
	if(lindex==-1 && sindex==-1){
		color(4);
		printf("\t\t\t\t【选择失败】"); 
		color(7);
		ModifyInfoMenu(2);return;
	}
	color(7);printf("\t\t\t\t请输入该站点上行始发时间：");
	color(9);scanf("%s",&time1); 
	color(7);printf("\t\t\t\t请输入该站点上行终点时间：");
	color(9);scanf("%s",&time2); 
	color(7);printf("\t\t\t\t你确定要将\n\t\t\t\t上行始发时间");
	color(6);printf("【%s】",L[lindex].station[sindex].startonetime);
	color(7);printf("更改为");
	color(2);printf("【%s】",time1);
	color(7);printf("\n\t\t\t\t上行终点时间");
	color(6);printf("【%s】",L[lindex].station[sindex].endonetime);
	color(7);printf("更改为");
	color(2);printf("【%s】",time2);
	color(7);printf("吗？[y/n]【  】\b\b\b\b"); 
	color(9);char ch=getch();
	printf("%c",ch); 
	trueInput=0;
	while(!trueInput){
		switch(ch){
			case 'y':
			case 'Y':
				color(7);printf("\n\t\t\t\t修改中，请稍后....");
				trueInput=1;
				strcpy(L[lindex].station[sindex].startonetime,time1);
				strcpy(L[lindex].station[sindex].endonetime,time2);
				strcpy(G.data[L[lindex].station[sindex].stationid].startonetime,time1);
				strcpy(G.data[L[lindex].station[sindex].stationid].endonetime,time2);
				itoa(L[lindex].number,title,10);
				BuildPath(L[lindex].number,linePath);
				itoa(sindex,title,10);
				if(PutIniKeyString(linePath,title,"startone",time1)!=EOF && PutIniKeyString(linePath,title,"endone",time2)!=EOF){
					color(2);printf("\n\t\t\t\t【修改成功】");
				}else{		
					color(4);printf("\n\t\t\t\t【修改失败】");
				}
				trueInput=1;break;
			case 'n':
			case 'N':	
				trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	color(7);printf("\t\t\t\t请输入该站点下行始发时间：");
	color(9);scanf("%s",&time1); 
	color(7);printf("\t\t\t\t请输入该站点下行终点时间：");
	color(9);scanf("%s",&time2); 
	color(7);printf("\t\t\t\t你确定要将\n\t\t\t\t下行始发时间");
	color(6);printf("【%s】",L[lindex].station[sindex].starttwotime);
	color(7);printf("更改为");
	color(2);printf("【%s】",time1);
	color(7);printf("\n\t\t\t\t下行终点时间");
	color(6);printf("【%s】",L[lindex].station[sindex].endtwotime);
	color(7);printf("更改为");
	color(2);printf("【%s】",time2);
	color(7);printf("吗？[y/n]【  】\b\b\b\b"); 
	color(9);ch=getch();
	printf("%c",ch); 
	trueInput=0;
	while(!trueInput){
		switch(ch){
			case 'y':
			case 'Y':
				color(7);printf("\n\t\t\t\t修改中，请稍后....");
				trueInput=1;
				strcpy(L[lindex].station[sindex].starttwotime,time1);
				strcpy(L[lindex].station[sindex].starttwotime,time2);
				strcpy(G.data[L[lindex].station[sindex].stationid].starttwotime,time1);
				strcpy(G.data[L[lindex].station[sindex].stationid].starttwotime,time2);
				itoa(L[lindex].number,title,10);
				BuildPath(L[lindex].number,linePath);
				itoa(sindex,title,10);
				if(PutIniKeyString(linePath,title,"starttow",time1)!=EOF && PutIniKeyString(linePath,title,"endtow",time2)!=EOF){
					color(2);printf("\n\t\t\t\t【修改成功】");
				}else{		
					color(4);printf("\n\t\t\t\t【修改失败】");
				}
				trueInput=1;break;
			case 'n':
			case 'N':	
				trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	color(7);printf("\n\t\t\t\t输入任意字符返回主菜单：【  】\b\b\b\b");
	ch=getch();
	ModifyInfoMenu(2);
}

/*站点经纬度修改*/
void LaLoModi(void){
	int lindex=-1,sindex=-1,trueInput=0;
	char title[50],chla[30],chlo[30];
	double la,lo;
	char linePath[100];
	StationModi(&lindex,&sindex);
	if(lindex==-1 && sindex==-1){
		color(4);
		printf("\t\t\t\t【选择失败】"); 
		color(7);
		ModifyInfoMenu(2);return;
	}
	color(7);printf("\t\t\t\t请输入该站点经度(如：113.321206)：");
	color(9);scanf("%lf",&lo); 
	color(7);printf("\t\t\t\t请输入该站点纬度(如：23.119293)：");
	color(9);scanf("%lf",&la); 
	color(7);printf("\t\t\t\t你确定要将");
	color(6);printf("【经度：%.6lf  纬度：%.6lf】",L[lindex].station[sindex].longitude,L[lindex].station[sindex].latitude);
	color(7);printf("\n\t\t\t\t更改为");
	color(2);printf("【经度：%.6lf  纬度：%.6lf】",lo,la);
	color(7);printf("吗？[y/n]【  】\b\b\b\b"); 
	color(9);char ch=getch();
	printf("%c",ch); 
	trueInput=0;
	while(!trueInput){
		switch(ch){
			case 'y':
			case 'Y':
				color(7);printf("\n\t\t\t\t修改中，请稍后....");
				trueInput=1;
				L[lindex].station[sindex].longitude=lo;
				L[lindex].station[sindex].latitude=la;
				G.data[L[lindex].station[sindex].stationid].longitude=lo;
				G.data[L[lindex].station[sindex].stationid].latitude=la;
				sprintf(chlo,"%.6lf",lo);
				sprintf(chla,"%.6lf",la);
				itoa(L[lindex].number,title,10);
				BuildPath(L[lindex].number,linePath);
				itoa(sindex,title,10);
				if(PutIniKeyString(linePath,title,"longitude",chlo)!=EOF && PutIniKeyString(linePath,title,"latitude",chla)!=EOF){
					color(2);printf("\n\t\t\t\t【修改成功】");
				}else{		
					color(4);printf("\n\t\t\t\t【修改失败】");
				}
				trueInput=1;break;
			case 'n':
			case 'N':	
				trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	color(7);printf("\n\t\t\t\t输入任意字符返回主菜单：【  】\b\b\b\b");
	ch=getch();
	ModifyInfoMenu(2);
}

/*输出出口信息*/
void printexit(exitinfo exitdata[],int exitsum){
	char temp[200],temp1[200],temp2[200];
	int flag=0;
	printf("\t\t\t| —————————————————————————————————|\n");
	printf("\t\t\t|                                                                   |\n");
	if(exitsum!=0){
		printf("\t\t\t|                           ");
		color(2);
		printf("【 出口信息 】");
		color(7);
		printf("                          |\n");
	}
	for(int i=0;i<exitsum;i++){
		if(exitdata[i].exitname!=""){
			sprintf(temp,"【%s】",exitdata[i].exitname);
			printf("\t\t\t|\t%-60s|\n",temp);
			flag=0;
			temp[0]='\0';
			for(int j=0;j<=exitdata[i].adnum;j++){
				if(j==0){
					printf("\t\t\t|\t");
				}
				strcpy(temp2,exitdata[i].exitad[j]);
				if(strlen(temp)+strlen(temp2)>=55){//下一行
					if(strlen(temp2)>55){
						if(temp!=""){
							printf("%-60s|\n\t\t\t|\t",temp);
						}
						strncpy(temp,temp2,55);
						printf("%-60s|\n\t\t\t|\t",temp);
						strcpy(temp,temp2+55);
						if(j==exitdata[i].adnum-1){
							printf("%-60s|\n",temp);
						}else{
								strcat(temp,"、");
						}
					}else{
						printf("%-60s|\n\t\t\t|\t",temp);
						strcpy(temp,temp2);
						if(j==exitdata[i].adnum-1){
							printf("%-60s|\n",temp);
						}else{
								strcat(temp,"、");
						}
					}
				}else{
					strcat(temp,temp2);
					if(j==exitdata[i].adnum-1){
						printf("%-60s|\n",temp);
					}else{
						strcat(temp,"、");
					}
					
				}				
			}
		}
	}
	printf("\t\t\t|                                                                   |\n");
	printf("\t\t\t| —————————————————————————————————|\n");
}

/*站点出口信息修改*/
void SiteExitModi(void){
	int lindex=-1,sindex=-1,trueInput=0;
	char ch;
	exitinfo exit[MAXEXITNUM];
	for(int i=0;i<MAXEXITNUM;i++){
		exit[i].exitname[0]='\0';
	}
	int exitsum;
	char title[50];
	double la,lo;
	char linePath[100];
	StationModi(&lindex,&sindex);
	if(lindex==-1 && sindex==-1){
		color(4);
		printf("\t\t\t\t【选择失败】"); 
		color(7);
		ModifyInfoMenu(2);return;
	}
	printf("\t\t\t\t请输入站点出口数量：");
	color(9);
	scanf("%d",&exitsum); 
	color(7);
	for(int i=0;i<exitsum;i++){
		printf("\t\t\t\t请输入第%d个出口名称(例：A出口)：",i+1);
		color(9);
		scanf("%s",&exit[i].exitname);
		color(7);
		printf("\t\t\t\t请输入该出口地点数量：");
		color(9);
		scanf("%d",&exit[i].adnum); 
		color(7);
		for(int j=0;j<exit[i].adnum;j++){
			printf("\t\t\t\t请输入第%d个地点(例：广州商学院)：",j+1);
			color(9);
			scanf("%s",&exit[i].exitad[j]);
			color(7);
		}
		
	}
	color(7);printf("\t\t\t\t你确定要将\n");
	printexit(L[lindex].station[sindex].exitdata,L[lindex].station[sindex].exitsum);
	color(7);printf("\n\t\t\t\t更改为\n");
	printexit(exit,exitsum);
	while(!trueInput){
		color(7);printf("\n\t\t\t\t[y/n]【  】\b\b\b\b"); 
		color(9);ch=getch();
		printf("%c",ch); 
		color(7);
		trueInput=0;
		switch(ch){
			case 'y':
			case 'Y':
				L[lindex].station[sindex].exitsum=exitsum;			
				G.data[L[lindex].station[sindex].stationid].exitsum=exitsum;
				memcpy(&(G.data[L[lindex].station[sindex].stationid].exitdata),&exit,sizeof(exit)+1);
				memcpy(&(L[lindex].station[sindex].exitdata),&exit,sizeof(exit)+1);
				color(7);printf("\n\t\t\t\t修改中，请稍后....");
				if(writeexit(lindex,sindex)!=EOF){
					color(2);printf("\n\t\t\t\t【修改成功】");
				}else{		
					color(4);printf("\n\t\t\t\t【修改失败】");
				}
				trueInput=1;break;
			case 'n':
			case 'N':	
				trueInput=1;break;
			default:
				trueInput=0;
				color(4);
				printf("\n\t\t\t\t【输入错误】\n");
				color(7);break;
			
		}	
	}
	color(7);printf("\n\t\t\t\t输入任意字符返回主菜单：【  】\b\b\b\b");
	ch=getch();
	ModifyInfoMenu(2);
	
}

/*站点出口信息写入文件*/
int writeexit(int lindex,int sindex){
	char exitsta1[300],exitsta[300];
	char ich[10],temp[200],temp1[200];
	char linePath[100],title[50];
	int i=0;
	itoa(L[lindex].number,title,10);
	BuildPath(L[lindex].number,linePath);
	itoa(sindex,title,10);
	exitsta1[0]='\0';
	exitsta[0]='\0';
	temp[0]='\0';
	temp1[0]='\0';
	while(L[lindex].station[sindex].exitdata[i].exitname[0]!='\0'){
		sprintf(temp1,"|%s",L[lindex].station[sindex].exitdata[i].exitname);
		strcat_s(temp,sizeof(temp),temp1);
		exitsta[0]='\0';
		exitsta1[0]='\0';
		for(int k=0;k<L[lindex].station[sindex].exitdata[i].adnum;k++){
			sprintf(exitsta1,"|%s",L[lindex].station[sindex].exitdata[i].exitad[k]);
			strcat_s(exitsta,sizeof(temp),exitsta1);
		}
		itoa(i+1,ich,10);
		PutIniKeyString(linePath,title,ich, exitsta);
		i++;
	}
	PutIniKeyInt(linePath,title,"exitsum", L[lindex].station[sindex].exitsum);
	return PutIniKeyString(linePath,title,"exitname", temp);
	
}
