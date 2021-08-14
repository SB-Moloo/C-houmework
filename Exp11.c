#include <stdio.h>
#include <windows.h>
#include <string.h>

//函数声明 
void Menu();
int InputRecord(long int a[],double b[][7], char c[][31], int *point, int coursenumb);
void CalculateEveryCourse(double score[][7], double sumc[], double averagec[], int i, int coursenumb);
void CalculateEveryStudent(double score[][7], double sums[], double averages[], int i , int coursenumb);
void Search(long int student[],double *pscore[],
			double *paverages[], double *psums[31], int coursenumb,
			char name[][31], int k);
int ListRecord(long int student[],double *pscore[], double *paverages[],
				double *psums[], double averagec[], double sumc[],
				char name[][31], int coursenumb, int k);
void Analyze(double score[][7], int coursenumb, int k);
int SelectionSort(long int student[], double *pscore[31], double *paverages[],
					double *psums[], char name[][31], int k, int coursenumb,
					int (*Compare)(double a, double b));
int Ascending(double a, double b);
int Descending(double a, double b);
void ExchangePoint(double *x, double *y, int coursenumb);
void ExchangeFloat(float *x, float *y);
void ExchangeLong(long int *x, long int *y);
void WaitingTime();
int NumbAscending(long int a, long int b);
int NumbDescending(long int a, long int b);
int NumbSelectionSort(long int student[], double *pscore[], double *paverages[],
						double *psums[], char name[][31], int k, int coursenumb,
						int (*Compare)(long int a, long int b));
void ExchangeChar(char name[][31], int present, int record);
void NamelistInOrder(long int student[], double *pscore[], double *paverages[],
						double *psums[], char name[][31], int k, int coursenumb);
int DicStrcmp(char *small, char *big);
void NameSearch(long int student[], double *pscore[],
				double *paverages[], double *psums[], int coursenumb, 
				char name[][31], int k);

int main(void)
{
	long int student[31];      //学号 31个，如果输入30个人，需要给-1留个位置 
	double score[31][7] = {0};        //分数
	double *pscore[31];
	int tool = 0;
	for(tool=0 ; tool<31 ; tool++)
	{
		pscore[tool] = score[tool];
	}
	char name[31][31];
	int k = 0;            //记录录入的人数，值为人数-1，即数组脚标
	int menunumb = 0;
	double sumc[6] = {0};
	double averagec[6] = {0};
	double sums[31] = {0};
	double *psums[31];
	for(tool=0 ; tool<31 ; tool++)
	{
		psums[tool] = &sums[tool];
	}
	double averages[31] = {0};
	double *paverages[31];
	for(tool=0 ; tool<31 ; tool++)
	{
		paverages[tool] = &averages[tool];
	}
	int *point = 0;       //从此到下第三行，用来续加学生
	int empty = 0;
	point = &empty;
	int freeze;           //用来延迟的变量	
	int coursenumb = 7;
	while(coursenumb > 6)
	{
		printf("请输入课程的数量(最多6门)：");
		scanf("%d", &coursenumb);
	}
	printf("----------------------------------------\n");
//菜单函数，打印菜单。
	Menu(); 
	scanf("%d",&menunumb);
	printf("\n");
//根据输入序号调用函数。 
	while(menunumb != 0)
	{
		switch(menunumb)
		{
		case 1:	k = InputRecord(student, score, name, point, coursenumb);
				while(k == 0)   //防止未输如学号和成绩造成程序出错 
				{
					printf("请先输入学号和成绩或至少输入两名同学的数据\n");
					k = InputRecord(student, score, name, point, coursenumb);
				}
				break;
		case 2:	CalculateEveryCourse(score,sumc,averagec,k,coursenumb);
				printf("\n");
				break;
		case 3:	CalculateEveryStudent(score,sums,averages,k,coursenumb);
				printf("\n");
				break;
		case 4:	SelectionSort(student, pscore, paverages, psums, name, k, coursenumb, Descending);
				printf("\n");
				break;
		case 5:	SelectionSort(student, pscore, paverages, psums, name, k, coursenumb, Ascending);
				printf("\n");
				break;
		case 6:	NumbSelectionSort(student, pscore, paverages, psums, name, k, coursenumb, NumbAscending);
				printf("\n");
				break;
		case 7:	NamelistInOrder(student, pscore, paverages, psums, name, k, coursenumb);
				printf("\n");
				break;
		case 8:	Search(student, pscore, paverages, psums, coursenumb, name, k);
				printf("\n");
				break;
		case 9:	NameSearch(student, pscore, paverages, psums, coursenumb, name, k);
				printf("\n");
				break;
		case 10:Analyze(score, coursenumb, k);
				printf("\n");
				break;
		case 11:ListRecord(student, pscore, paverages,
							psums, averagec, sumc,
							name, coursenumb, k);
				printf("\n");
				break;
		case 0: exit(0);
		}
		if(menunumb<0 || menunumb >11)
		{
			printf("Wrong input!Try againg!\n");
			printf("\n");
		}
		//分割线 
		printf("----------------------------------------\n");
		//最后一步，再选择功能
		Menu(); 
		scanf("%d",&menunumb);
		printf("\n");
	}
	system("pause");
	return 0;
	
}

void Menu()
{
	printf("1.录入每个学生的学号、姓名和各科考试成绩\n");
	printf("2.计算每门课程的总分和平均分\n");
	printf("3.计算每个学生的总分和平均分\n");
	printf("4.按每个学生的总分由高到低排出名次表\n");
	printf("5.按每个学生的总分由低到高排出名次表\n");
	printf("6.按学号由小到大排出成绩表\n");
	printf("7.按姓名的字典顺序排出成绩表\n");
	printf("8.按学号查询学生排名及其各科考试成绩\n");
	printf("9.按姓名查询学生排名及其各科考试成绩\n");
	printf("10.各科成绩分析\n");
	printf("11.输出每个学生的成绩\n");
	printf("0.Exit(退出)\n");
	printf("提示：输入\"-1\"结束录入成绩或学号\n"); 
	printf("根据菜单相应序号来选择功能：\n");
}

int InputRecord(long int a[],double b[][7], char c[][31], int *point, int coursenumb)
{
	int i = *point;
	int k = 0;
	int m;
	for(;i<30;i++)
	{
		printf("请输入学号：");
		scanf("%ld",&a[i]);
		if(a[i] != -1)
		{
			printf("请输入姓名：");
			scanf("%s",c[i]);
			for(m=0 ; m<coursenumb ; m++)
			{
				printf("请输入课程%d成绩：",m+1); 
				scanf("%lf",&b[i][m]);
			}
		}
		if((a[i] == -1))
		{
			printf("\n");
			break;
		}
		k = i;
	}
	*point = k + 1;
	return k;
}

//计算每门课程的总成绩 
void CalculateEveryCourse(double score[][7], double sumc[], double averagec[], int i , int coursenumb)
{
	int a;
	int b;
	for(b=0; b<coursenumb; b++)
	{
		for(a=0; a<=i ; a++)
		{
			sumc[b] += score[a][b];
		}
	}
	for(b=0 ; b<coursenumb; b++)
	{
		averagec[b] = sumc[b]/(i+1);
	}
}

//计算每名学生的总成绩 
void CalculateEveryStudent(double score[][7], double sums[], double averages[], int i , int coursenumb)
{
	int a;
	int b;
	for(a=0; a<=i ; a++)
	{
		for(b=0; b<coursenumb; b++)
		{
			sums[a] += score[a][b];
		}
		averages[a] = sums[a]/coursenumb;
	}
}

//按每个学生的总成绩排序 
int SelectionSort(long int student[], double *pscore[31], double *paverages[],
					double *psums[], char name[][31], int k, int coursenumb,
					int (*Compare)(double a, double b))
{
	int next = 0;
	int present;
	int record;
	for(present = 0;present <= k; present++)
	{
		record = present;
		for(next = present + 1; next <= k; next++)
		{
			if((*Compare)(*(psums[next]), *(psums[record])))
			{
				record = next;
			}						
		}
		if(record != present)
		{
			ExchangePoint(psums[present], psums[record], coursenumb);
			ExchangePoint(paverages[present], paverages[record], coursenumb);
			ExchangePoint(pscore[present], pscore[record], coursenumb);
			ExchangeLong(&student[present], &student[record]);
			ExchangeChar(name, present, record);
		}
		
	}
}

//按学号排序 
int NumbSelectionSort(long int student[], double *pscore[], double *paverages[],
						double *psums[], char name[][31], int k, int coursenumb,
						int (*Compare)(long int a, long int b))
{
	int next = 0;
	int present;
	int record;
	for(present = 0;present <= k; present++)
	{
		record = present;
		for(next = present + 1; next <= k; next++)
		{
			if((*Compare)(student[next], student[record]))
			{
				record = next;
			}						
		}
		if(record != present)
		{
			ExchangePoint(pscore[present], pscore[record], coursenumb);
			ExchangePoint(psums[present], psums[record], coursenumb);
			ExchangePoint(paverages[present], paverages[record], coursenumb);
			ExchangeLong(&student[present], &student[record]);
			ExchangeChar(name, present, record);
		}
		
	}
}

int Ascending(double a, double b)
{
	return (a < b);
}

int Descending(double a, double b)
{
	return (a > b);
}

int NumbAscending(long int a, long int b)
{
	return (a < b);
}

int NumbDescending(long int a, long int b)
{
	return (a > b);
}

//按姓名的字典顺序排出成绩表
void NamelistInOrder(long int student[], double *pscore[], double *paverages[],
						double *psums[], char name[][31], int k, int coursenumb)
{
	int present = 0;
	int j = 0;
	int record = 0;
	for(; present <= k; present++)
	{
		record= present;
		for(j = present + 1; j <= k; j++)
		{
			if((DicStrcmp(name[j], name[record])<0))
			{
				record = j;
			}
		}
		if(record != present)
		{
			ExchangePoint(pscore[present], pscore[record], coursenumb);
			ExchangePoint(paverages[present], paverages[record], coursenumb);
			ExchangePoint(psums[present], psums[record], coursenumb);
			ExchangeLong(&student[present], &student[record]);
			ExchangeChar(name, present, record);
		}
	}
}

//按字典顺序比大小，不区分大小写 
int DicStrcmp(char *small, char *big)
{
	
	int i;
	int length;
	length = (strlen(small)<strlen(big))?(strlen(small)):(strlen(big));
	for(i = 0; i < length; i++)
	{
		if((small[i] == big[i]) || (small[i] == big[i]+32) || (big[i] == small[i]+32))
		{
		continue;
		}
		else if((small[i] < 91) && (big[i] < 91))
		{
			if(small[i] < big[i])
			{
				return -1;
			}
			else if(small[i] > big[i])
			{
				return 1;
			}
		}
		else if((small[i] > 96) && (big[i] > 96))
		{
			if(small[i] < big[i])
			{
				return -1;
			}
			else if(small[i] > big[i])
			{
				return 1;
			}
		}
		else if((small[i] > 96) && (big[i] < 91))
		{
			if(small[i] < big[i] + 32)
			{
				return -1;
			}
			else if(small[i] > big[i] + 32)
			{
				return 1;
			}
		}
		else if((small[i] < 91) && (big[i] > 96))
		{
			if(small[i] + 32 < big[i])
			{
				return -1;
			}
			else if(small[i] + 32 > big[i])
			{
				return 1;
			}
		}
	}
	return 0;
}


//按学号查找学生成绩和排名（有排名，则成绩降序） 
void Search(long int student[],double *pscore[],
			double *paverages[], double *psums[31], int coursenumb,
			char name[][31], int k)
{
	int high=k,mid,low= 0;
	long stu_numb;
	int count = 0;
	int recordscore = 0;
	int tool;		//工具人参数
	double *ptool;		//工具人指针，用来保存分数的行地址 
	printf("请输入查询的学号:");
	scanf("%ld",&stu_numb);
	printf("\n");
	NumbSelectionSort(student, pscore, paverages, psums, name, k, coursenumb, NumbDescending);
	while(low<=high)
	{
		mid = (high+low)/2;
		if(stu_numb < student[mid])
		{
			low = mid + 1;
		}
		else if(stu_numb > student[mid])
		{
			high = mid - 1;
		}
		else
		{
			count = 1;
			low = 0;
			high = k;
			recordscore = *(psums[mid]);
			SelectionSort(student, pscore, paverages, psums, name, k, coursenumb, Descending);
			while(low <= high)
			{
				mid = (high+low)/2;
				if(recordscore < *(psums[mid]))
				{
					low = mid + 1;
				}
				else if(recordscore > *(psums[mid]))
				{
					high = mid - 1;
				}
				else
				{
					printf("姓名：%s\n学号：%d\n",name[mid],student[mid]);
					printf("排名为：%d\n", mid+1);
					printf("总分为：%f\n", psums[mid]);
					ptool = pscore[mid];
					for(tool=1 ; *pscore[mid]!=0 ; (pscore[mid])++,tool++)
					{
						printf("课程%d的成绩为%f\n",tool,*(pscore[mid]));
					}
					printf("\n");
					break;	
				}
			}
		}
		if(count == 1)
		{
			break;
		}
	}
}

//按名字查找，不区分大小写
void NameSearch(long int student[], double *pscore[],
				double *paverages[], double *psums[], int coursenumb,
				char name[][31], int k)
{
	int i;
	int j;
	int judge = 0;
	int count = 0;
	char a[31];
	int tool;		//工具人参数 
	double *ptool;		//工具人指针，记录score的行地址 
	int high=k,mid,low= 0;	//找排名的变量 
	int recordscore = 0;
	printf("请输入想要查询的名字：");
	scanf("%s", a);
	for(i = 0; i <= k; i++)
	{
		for(j = 0; j <= strlen(name[i])-1; j++)
		{
			if( ((a[j]<91)&&(name[i][j]<91)) || ((a[j]>96)&&(name[i][j]>96)) )
			{
				if( a[j] == name[i][j] )
				{
					judge = 1;
					count = i;
				}
				else
				{
					judge = 0;
					break;
				}
			}
			else if ( (a[j]<91)&&(name[i][j]>96) )
			{
				if( a[j]+32 == name[i][j] )
				{
					judge = 1;
					count = i;
				}
				else
				{
					judge = 0;
					break;
				}
			}
			else if ( (a[j]>96)&&(name[i][j]<91) )
			{
				if( a[j] == name[i][j]+32 )
				{
					judge = 1;
					count = i;
				}
				else
				{
					judge = 0;
					break;
				}
			}
		}
		if(judge == 1)
		{
			break;
		}
	}
	if(judge == 1)
	{
		printf("姓名：%s\n学号：%d\n",name[count],student[count]);
		recordscore = *(psums[count]);
		SelectionSort(student, pscore, paverages, psums, name, k, coursenumb, Descending);
		while(low <= high)
		{
			mid = (high+low)/2;
			if(recordscore < *(psums[mid]))
			{
				low = mid + 1;
			}
			else if(recordscore > *(psums[mid]))
			{
				high = mid - 1;
			}
			else
			{
				printf("排名为：%d\n", mid+1);
				printf("总分为：%f\n", *(psums[mid]));
				ptool = pscore[mid];
				for(tool=1 ; *pscore[mid]!=0 ; (pscore[mid])++,tool++)
				{
					printf("课程%d的成绩为%f\n",tool,*(pscore[mid]));
				}
				break;
			}
			printf("\n");
		}
	}
	else
	{
		printf("Not found!\n");
	}
}

int ListRecord(long int student[],double *pscore[], double *paverages[],
				double *psums[], double averagec[], double sumc[],
				char name[][31], int coursenumb, int k)
{
	int i;
	int tool;
	double *ptool;
	for(i=0;i<=k;i++)
	{
		printf("姓名：%s\n",name[i]);
		printf("学号：%d\n",student[i]);
		printf("总分%.2f\t平均分%.2f\n",*(psums[i]),*(paverages[i]));
		ptool = pscore[i];
		for(tool=1 ; *pscore[i]!=0 ; (pscore[i])++,tool++)
		{
			printf("课程%d的成绩为%.2f\n",tool,*(pscore[i]));
		}
		pscore[i] = ptool;		//将指针指回原行地址
		printf("\n");
	}
	printf("\n");
	for(i=0,tool=1 ; i<coursenumb ; i++,tool++)
	{
		printf("课程%d的总成绩为%.2f,平均分为%.2f\n",tool,sumc[i],averagec[i]);
	}
}

//分析每门课的成绩 
void Analyze(double score[][7], int coursenumb, int k)
{
	int a=0,b=0,c=0,d=0,e=0;
	double count = 0.0;
	int i,j;
	for(j=0 ; j<coursenumb ; j++)
	{
		a=0,b=0,c=0,d=0,e=0;
		for(i=0 ; i<=k ; i++)
		{
			if(score[i][j]>=90 && score[i][j]<=100)
			{
				a++;
			}
			else if(score[i][j]>=80 && score[i][j]<=89)
			{
				b++;
			}
			else if(score[i][j]>=70 && score[i][j]<=79)
			{
				c++;
			}
			else if(score[i][j]>=60 && score[i][j]<=69)
			{
				d++;
			}
			else if(score[i][j]>=0 && score[i][j]<=59)
			{
				e++;
			}
		}
		printf("课程%d的成绩分析：",j+1);
		count = (a/(k+1.0))*100;
		printf("优秀人数：%d\t优秀比率：%.2f%%\n",a,count);
		count = (b/(k+1.0))*100;
		printf("良好人数：%d\t良好比率：%.2f%%\n",b,count);
		count = (c/(k+1.0))*100;
		printf("中等人数：%d\t中等比率：%.2f%%\n",c,count);
		count = (d/(k+1.0))*100;
		printf("及格人数：%d\t及格比率：%.2f%%\n",d,count);
		count = (e/(k+1.0))*100;
		printf("不及格人数：%d\t不及格比率：%.2f%%\n",e,count);
	}
}

void ExchangeLong(long int *x, long int *y)
{
	long int z;
	z = *x;
	*x = *y;
	*y = z;
}

void ExchangePoint(double *x, double *y, int coursenumb)
{
	double z;
	int i;
	for(i=0 ; i<coursenumb ; i++)
	{
		z = *(x+i);
		*(x+i) = *(y+i);
		*(y+i) = z;
	}
}

void ExchangeFloat(float *x, float *y)
{
	float z;
	z = *x;
	*x = *y;
	*y = z;
}

void ExchangeChar(char name[][31], int present, int record)
{
	char p[31] = "";
	strcpy(p, name[present]);
	strcpy(name[present], name[record]);
	strcpy(name[record], p);
}

