#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <math.h> 
#include <ctype.h>
#include <direct.h> 
#include <windows.h> 
#include "main.h"
#include "utility.h"

#pragma warning(disable:4996)



/*文件辅助操作*/ 

//去除首尾空格及换行  
void trim_string(char *str){
	char *start, *end;
	int len = strlen(str);
 
	//去掉最后的换行符
	if(str[len-1] == '\n')
	{
		len--;		//字符串长度减一
		str[len] = 0;	//给字符串最后一个字符赋0，即结束符
	}
 
	//去掉两端的空格
	start = str;
	end = str + len -1;
	while(*start && isspace(*start))
		start++;
	while(*end && isspace(*end))
		*end-- = 0;	
	strcpy(str, start);	//把首地址还给str
}

//去除所有空格及末尾换行 
void trim_all_string(char *str){
	char *s, *t;
	int len = strlen(str);
 	int j=0;
	//去掉最后的换行符
	if(str[len-1] == '\n')
	{
		len--;		//字符串长度减一
		str[len] = 0;	//给字符串最后一个字符赋0，即结束符
	}
	s=str;
	t=str;
	while(*t = *s++){
		if(*t!=' ') ++t;
	}
    
}


/*文件操作*/ 

//获取value(string)
char* GetIniKeyString(char* filename, char* title, char* key){
	FILE* fp = NULL;
	int  flag = 0;
	char sTitle[32], * wTmp;
	static char sLine[1024];
	if(key==NULL || title==NULL){
		return "";
	}
	sprintf(sTitle, "[%s]", title);
	if ((fp = fopen(filename, "r"))==NULL) {
		perror("fopen");
		return NULL;
	}
	else {
		while (NULL != fgets(sLine, 1024, fp)) {
			trim_all_string(sLine);
			// 这是注释行
			if (strncmp("//", sLine, 2)==0) continue;
			if (sLine[0]=='#')              continue;

			wTmp = strchr(sLine, '=');
			if ((wTmp!=NULL) && (flag==1)) {
				if (strncmp(key, sLine, wTmp - sLine)==0) { // 长度依文件读取的为准
					sLine[strlen(sLine)] = '\0';
					fclose(fp);
					return wTmp+1;
				}
			}
			else {
				if (strncmp(sTitle, sLine, strlen(sTitle))==0) { // 长度依文件读取的为准
					flag = 1; // 找到标题位置
				}
			}
		}
	}
	fclose(fp);
	return "";
}

//获取value(int)
int GetIniKeyInt(char* filename,char* title, char* key){
	return atoi(GetIniKeyString(filename, title, key));
}

//写入key(string)
int PutIniKeyString(char* filename,char* title,char* key, char* val){
	FILE* fpr, * fpw;
	int  flag = 0,code;
	static char  wTmp[10000], * kTmp, * sTmp1, * sTmp2;
	static char sLine[1024],ysLine[1024], sTitle[32], tmp[1024]; 
	if(key==NULL || title==NULL ||val==NULL){
		return "";
	}
	sprintf(sTitle, "[%s]", title);
	if ((fpr = fopen(filename, "r"))==NULL) {
		fclose(fpr);
		perror("fopen");
		return -1;
	}
	if(wTmp==NULL)  return -1;
	/*
	flag=1 找到title
	flag=2 找到key
	flag=3 找到title，未找到key
	flag=0 均未找到

	*/
	
	sLine[0]='\0';
	wTmp[0]='\0';
	while (fgets(sLine, 1024, fpr) != NULL) {
		trim_all_string(sTitle);
		trim_all_string(sLine);
		if (strncmp(sTitle, sLine, strlen(sLine)) == 0 && sLine[0]!='\0') { // 长度依文件读取的为准
			flag = 1; // 找到标题位置
		}
		if ((kTmp = strchr(sLine, '=')) != NULL) {
			if (flag == 1 && strncmp(key, sLine, strlen(sLine) - strlen(kTmp)) == 0 && sLine[0]!='\0') {
				flag = 2; // 找到key位置 ，并修改
				sprintf(sLine, "%s = %s", key, val);
			}
		}
		
		sTmp1 = strchr(sLine, '[');
		sTmp2 = strchr(sLine, ']');
		if (sTmp1 != NULL && sTmp2 != NULL) {
			if (flag == 1 && sTmp1==sLine &&sTmp2==sLine+strlen(sLine)-1 && strncmp(sTitle, sLine, strlen(sLine) - 1) != 0 && sLine[0]!='\0') {//对应title结束未找到key
				strcpy(tmp,sLine);
				sprintf(sLine, "%s = %s\n%s", key, val, tmp);
				flag = 3;
			}
		}
		sprintf(sLine,"%s\n",sLine); 
		strcat(wTmp, sLine);
	}
	if (flag == 0) {
		sprintf(sLine, "%s\n%s = %s\n", sTitle, key, val);
		strcat(wTmp, sLine);
	}
	if (flag == 1 && fgets(sLine, 1024, fpr) == NULL) {
		sprintf(sLine, "%s = %s\n", key, val);
		strcat(wTmp, sLine);
	}
	fclose(fpr);
	if ((fpw = fopen(filename, "w"))==NULL) {
		fclose(fpw);
		perror("fopen");
		return -1;
	}
	wTmp[strlen(wTmp)] = '\0';
	code=fputs(wTmp, fpw);
	
	
	fclose(fpw);
	return code;// 将临时文件更新到原文件
}


//写入key(int)
int PutIniKeyInt(char* filename, char* title, char* key, int val){
	char sVal[32];
	sprintf(sVal, "%d", val);
	return PutIniKeyString(filename, title, key, sVal);
}

//删除一整节 
int DeleteIniSection(char* filename,char* title){
	FILE* fpr, * fpw;
	int  flag = 0,code;
	static char  wTmp[10000], * kTmp, * sTmp1, * sTmp2;
	static char sLine[1024], sTitle[32], tmp[1024]; 
	if(title==NULL){
		return "";
	}
	sprintf(sTitle, "[%s]", title);
	if ((fpr = fopen(filename, "r"))==NULL) {
		fclose(fpr);
		perror("fopen");
		return -1;
	}
	if(wTmp==NULL)  return -1;
	/*
	flag=1 找到title
	flag=2 title结束 
	*/
	sLine[0]='\0';
	wTmp[0]='\0';
	while (fgets(sLine, 1024, fpr) != NULL) {
		trim_all_string(sTitle);
		trim_all_string(sLine);
		if (strncmp(sTitle, sLine, strlen(sLine)) == 0) { // 长度依文件读取的为准
			flag = 1; // 找到标题位置
			continue;
		}
		sTmp1 = strchr(sLine, '[');
		sTmp2 = strchr(sLine, ']');
		if (sTmp1 != NULL && sTmp2 != NULL) {
			if (flag == 1 && sTmp1==sLine &&sTmp2==sLine+strlen(sLine)-1 && strncmp(sTitle, sLine, strlen(sLine)) != 0 && sLine[0]!='\0') {//对应title结束未找到key
				flag = 2;
			}
		}
		if(flag!=1){
			strcat(wTmp, sLine);
			strcat(wTmp, "\n");
		}
		
	}
	fclose(fpr);
	if ((fpw = fopen(filename, "w"))==NULL) {
		fclose(fpw);
		perror("fopen");
		return -1;
	}
	wTmp[strlen(wTmp)] = '\0';
	code=fputs(wTmp, fpw);
	
	fclose(fpw);
	return code;// 将临时文件更新到原文件
}


//改变title内容 
int ChangeIniTitle(char* filename,char* title,char* Newtitle){
	FILE* fpr, * fpw;
	int  flag = 0,code;
	static char  wTmp[10000], * kTmp, * sTmp1, * sTmp2;
	static char sLine[1024], sTitle[32], tmp[1024],nTitle[32]; 
	if(title==NULL ||Newtitle==NULL){
		return "";
	}
	sprintf(sTitle, "[%s]", title);
	sprintf(nTitle, "[%s]", Newtitle);
	if ((fpr = fopen(filename, "r"))==NULL) {
		fclose(fpr);
		perror("fopen");
		return -1;
	}
	if(wTmp==NULL)  return -1;
	/*
	flag=1 找到title
	flag=2 title结束 
	*/
	sLine[0]='\0';
	wTmp[0]='\0';
	while (fgets(sLine, 1024, fpr) != NULL) {
		trim_all_string(sTitle);
		trim_all_string(nTitle);
		trim_all_string(sLine);
		if (strncmp(sTitle, sLine, strlen(sLine)) == 0 && sLine[0]!='\0') { // 长度依文件读取的为准
			if(flag==0){
				sprintf(sLine,"%s",nTitle); // 找到标题位置
				flag=1;
			}
			
		}
		strcat(wTmp, sLine);
		strcat(wTmp, "\n");
	}
	fclose(fpr);
	if ((fpw = fopen(filename, "w"))==NULL) {
		fclose(fpw);
		perror("fopen");
		return -1;
	}
	wTmp[strlen(wTmp)] = '\0';
	code=fputs(wTmp, fpw);
	
	fclose(fpw);
	return code;// 将临时文件更新到原文件
}



/*经纬度计算距离*/

// 求弧度
double radian(double d){
    return d * PI / 180.0;   //角度1? = π / 180
}

//计算距离
double get_distance(double lat1, double lng1, double lat2, double lng2){
    double radLat1 = radian(lat1);
    double radLat2 = radian(lat2);
    double a = radLat1 - radLat2;
    double b = radian(lng1) - radian(lng2);
    
    double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2) )));
    
    dst = dst * EARTH_RADIUS;
    dst= round(dst * 10000) / 10000;
    return dst;
}

/*其它*/

//时间戳转换时间 
Times stamp_to_standard(int stampTime){
	time_t tick = (time_t)stampTime;
	struct tm tm; 
	char s[100];
	Times standard;
	tm = *localtime(&tick);
	strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
	standard.Year = atoi(s);
	standard.Mon = atoi(s+5);
	standard.Day = atoi(s+8);
	standard.Hour = atoi(s+11);
	standard.Min = atoi(s+14);
	standard.Second = atoi(s+17);
	return standard;
}

//改变字体颜色 
void color(short x) {  
    if(x>=0 && x<=15)//参数在0-15的范围颜色  
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x); 
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  //默认的颜色白色  
} 

//构建目录 
void BuildPath(int num,char *path){
	char linepath[100]={'\0'};
	char chnum[10];
//	strcat(linepath,GetWorkPath());
	strcat(linepath,"data\\line");
	itoa(num,chnum,10);
	strcat(linepath,chnum);
	strcat(linepath,".ini");
	strcpy(path,linepath);
}


