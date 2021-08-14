#include <stdio.h>
#include <windows.h>
#include <string.h>

//函数声明 
void Menu();
int InputRecord(long int a[],float b[], char c[][31], int *point);
int Calculate(float b[], int i);
void Search(long int student[],float score[], char name[][31], int k);
int ListRecord(long int student[], float score[], char name[][31], int k);
void Analyze(float score[], int k);
void FindMax(long int student[], float score[], char name[][31], int k);
int SelectionSort(long int student[], float score[], char name[][31], int k, int (*Compare)(float a, float b));
int Ascending(float a, float b);
int Descending(float a, float b);
void ExchangeFloat(float *x, float *y);
void ExchangeLong(long int *x, long int *y);
void WaitingTime();
int NumbDescending(long int a, long int b);
int NumbSelectionSort(long int student[], float score[], char name[][31], int k, int (*Compare)(long int a, long int b));
void ExchangeChar(char name[][31], int present, int record);
void NamelistInOrder(long int student[], float score[], char name[][31], int k);
int DicStrcmp(char *small, char *big);
void NameSearch(long int student[], float score[], char name[][31], int k);

int main(void)
{
	long int student[31];      //学号 31个，如果输入30个人，需要给-1留个位置 
	float score[31];        //分数
	char name[31][31];
	int k = 0;            //记录录入的人数，值为人数-1，即数组脚标
	int menunumb = 0;
	int sum = 0;
	int *point = 0;       //从此到下第三行，用来续加学生
	int empty = 0;
	point = &empty;
	double average = 0.0;
	int freeze;           //用来延迟的变量	
//菜单函数，打印菜单。
	Menu(); 
	scanf("%d",&menunumb);
	printf("\n");
//根据输入序号调用函数。 
	while(menunumb != 0)
	{
		switch(menunumb)
		{
		case 1:	k = InputRecord(student, score, name, point);
				while(k == 0)   //防止未输如学号和成绩造成程序出错 
				{
					printf("请先输入学号和成绩或至少输入两名同学的数据\n");
					k = InputRecord(student, score, name, point);
				}
				break;
		case 2:	sum = Calculate(score,k);
				printf("总分为：%d\n",sum);
				average = sum/(k+1.0);
				printf("平均分为：%f\n",average);
				printf("\n");
				break;
		case 3:	SelectionSort(student, score, name, k, Descending);
				printf("\n");
				break;
		case 4:	SelectionSort(student, score, name, k, Ascending);
				printf("\n");
				break;
		case 5:	Search(student, score, name, k);
				break;
		case 6:	Analyze(score, k);
				printf("\n");
				break;
		case 7:	sum = ListRecord(student, score, name, k);
				printf("总分为：%d\n",sum);
				average = sum/(k+1.0);
				printf("平均分为：%f\n",average);
				printf("\n");
				break;
		case 8:	FindMax(student, score, name, k);
				printf("\n");
				break;
		case 9:	NamelistInOrder(student, score, name, k);
				printf("\n");
				break;
		case 10:NameSearch(student, score, name, k);
				printf("\n");
				break;
		case 0: exit(0);
		}
		if(menunumb<0 || menunumb >11)
		{
			printf("Wrong input!Try againg!\n");
			printf("\n");
		}
		//延迟显示菜单 
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
	printf("1.Input record(输入学号和成绩)\n");
	printf("2.Calculate total and average score of course(计算总成绩和平均分)\n");
	printf("3.Sort in descending order by score(降序排列成绩)\n");
	printf("4.Sort in ascending order by number(升序排列成绩)\n");
	printf("5.Search by number(通过学号查找成绩)\n");
	printf("6.Statistic analysis(成绩分析)\n");
	printf("7.List record(列出所有成绩)\n");
	printf("8.Find top1(查询第一名)\n");
	printf("9.Sort in dictionary order by name(按字典顺序排列名字)\n");
	printf("10.Search by name(按名字查询)\n");
	printf("0.Exit(退出)\n");
	printf("提示：输入\"-1\"结束录入成绩或学号\n"); 
	printf("根据菜单相应序号来选择功能：\n");
}

int InputRecord(long int a[],float b[], char c[][31], int *point)
{
	int i = *point;
	int k = 0;
	for(;i<30;i++)
	{
		printf("请输入学号：");
		scanf("%ld",&a[i]);
		if(a[i] != -1)
		{
			printf("请输入姓名：");
			scanf("%s",c[i]);
			printf("请输入成绩："); 
			scanf("%f",&b[i]);
		}
		else
		{
			b[i] = -1;
		}
		if((a[i] == -1)||(b[i] == -1))
		{
			printf("\n");
			break;
		}
		k = i;
	}
	*point = k + 1;
	return k;
}

int Calculate(float b[],int i)
{
	int a;
	int sum = 0;
	double average = 0;
	for(a=0;a<=i;a++)
	{
		sum += b[a];
	}
	return sum;
}

int SelectionSort(long int student[], float score[], char name[][31], int k, 
					int (*Compare)(float a, float b))
{
	int next = 0;
	int present;
	int record;
	for(present = 0;present <= k; present++)
	{
		record = present;
		for(next = present + 1; next <= k; next++)
		{
			if((*Compare)(score[next], score[record]))
			{
				record = next;
			}						
		}
		if(record != present)
		{
			ExchangeFloat(&score[present], &score[record]);
			ExchangeLong(&student[present], &student[record]);
			ExchangeChar(name, present, record);
		}
		
	}
}

int NumbSelectionSort(long int student[], float score[], char name[][31], int k,
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
			ExchangeFloat(&score[present], &score[record]);
			ExchangeLong(&student[present], &student[record]);
			ExchangeChar(name, present, record);
		}
		
	}
}

int Ascending(float a, float b)
{
	return (a < b);
}

int Descending(float a, float b)
{
	return (a > b);
}

int NumbDescending(long int a, long int b)
{
	return (a > b);
}

//按姓名的字典顺序排出成绩表
void NamelistInOrder(long int student[], float score[], char name[][31], int k)
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
			ExchangeFloat(&score[present], &score[record]);
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

void Search(long int student[],float score[], char name[][31], int k)
{
	int high=k,mid,low= 0;
	long stu_numb;
	int count = 0;
	int recordscore = 0;
	printf("请输入查询的学号:");
	scanf("%ld",&stu_numb);
	printf("\n");
	NumbSelectionSort(student, score, name, k, NumbDescending);
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
			recordscore = score[mid];
			SelectionSort(student, score, name, k, Descending);
			while(low <= high)
			{
				mid = (high+low)/2;
				if(recordscore < score[mid])
				{
					low = mid + 1;
				}
				else if(recordscore > score[mid])
				{
					high = mid - 1;
				}
				else
				{
					printf("排名为：%d\n", mid+1);
					printf("成绩为：%f\n", score[mid]);
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

void NameSearch(long int student[], float score[], char name[][31], int k)
{
	int i;
	int j;
	int judge = 0;
	int count = 0;
	char a[31];
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
		printf("学号\t\t\t");
		printf("姓名\t\t\t");
		printf("成绩\n");
		printf("%d\t\t\t",student[count]);
		printf("%s\t\t\t",name[count]);
		printf("%f\n",score[count]);
	}
	else
	{
		printf("Not found!\n");
	}
}

int ListRecord(long int student[],float score[], char name[][31], int k)
{
	int i;
	int sum = 0;
	printf("学号\t\t\t");
	printf("姓名\t\t\t");
	printf("成绩\n");
	for(i=0;i<=k;i++)
	{
		printf("%d\t\t\t",student[i]);
		printf("%s\t\t",name[i]);
		printf("%f\n",score[i]);
	}
	printf("\n");
	sum = Calculate(score,k);
	return sum;
}

void Analyze(float score[],int k)
{
	int a=0,b=0,c=0,d=0,e=0;
	double count = 0.0;
	int i;
	for(i=0;i<=k;i++)
	{
		if(score[i]>=90 && score[i]<=100)
		{
			a++;
		}
		else if(score[i]>=80 && score[i]<=89)
		{
			b++;
		}
		else if(score[i]>=70 && score[i]<=79)
		{
			c++;
		}
		else if(score[i]>=60 && score[i]<=69)
		{
			d++;
		}
		else if(score[i]>=0 && score[i]<=59)
		{
			e++;
		}
	}
	count = (a/(k+1.0))*100;
	printf("优秀人数：%d\n",a);
	printf("优秀比率：%.2f%%\n",count);
	count = 0;
	count = (b/(k+1.0))*100;
	printf("良好人数：%d\n",b);
	printf("良好比率：%.2f%%\n",count);
	count = 0;
	count = (c/(k+1.0))*100;
	printf("中等人数：%d\n",c);
	printf("中等比率：%.2f%%\n",count);
	count = 0;
	count = (d/(k+1.0))*100;
	printf("及格人数：%d\n",d);
	printf("及格比率：%.2f%%\n",count);
	count = 0;
	count = (e/(k+1.0))*100;
	printf("不及格人数：%d\n",e);
	printf("不及格比率：%.2f%%\n",count);
	
}

void FindMax(long int student[], float score[], char name[][31], int k)
{
	SelectionSort(student, score, name, k, Descending);
	printf("Top 1 is:\nNumb %d\t\tScore %f\n",student[0],score[0]);
}

void ExchangeLong(long int *x, long int *y)
{
	long int z;
	z = *x;
	*x = *y;
	*y = z;
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

