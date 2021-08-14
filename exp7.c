#include<stdio.h>
#include<windows.h>

//函数声明 
void Menu();
int InputRecord(int a[], int b[], int *point);
int Calculate(int b[], int i);
void HtoL_OrderScore(int student[], int score[], int k, int n);
void Exchange(int student[], int score[], int a, int i);
void LtoH_OrderStudent(int student[], int score[], int k, int n);
void Search(int student[], int score[], int k);
int ListRecord(int student[], int score[], int k);
void Analyze(int score[], int k);
void FindMax(int student[], int score[], int k);

int main(void)
{
	int student[31];      //学号 31个，如果输入30个人，需要给-1留个位置 
	int score[31];        //分数
	int k = 0;            //记录录入的人数，值为人数-1，即数组脚标
	int menunumb = 0;
	int sum = 0;
	int *point = 0;       //23-25行用来续加学生
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
		case 1:	k = InputRecord(student, score, point);
				while(k == 0)   //防止未输如学号和成绩造成程序出错 
				{
					printf("请先输入学号和成绩\n");
					k = InputRecord(student, score, point);
				}
				break;
		case 2:	sum = Calculate(score,k);
				printf("总分为：%d\n",sum);
				average = sum/(k+1.0);
				printf("平均分为：%f\n",average);
				printf("\n");
				break;
		case 3:	HtoL_OrderScore(student, score, k, 1);
				printf("\n");
				break;
		case 4:	LtoH_OrderStudent(student, score, k, 1);
				printf("\n");
				break;
		case 5:	Search(student, score, k);
				break;
		case 6:	Analyze(score, k);
				printf("\n");
				break;
		case 7:	sum = ListRecord(student, score, k);
				printf("总分为：%d\n",sum);
				average = sum/(k+1.0);
				printf("平均分为：%f\n",average);
				printf("\n");
				break;
		case 8:	FindMax(student, score, k);
				printf("\n");
				break;
		case 0: exit(0);
		}
		if(menunumb<0 || menunumb >8)
		{
			printf("Wrong input!Try againg!\n");
			printf("\n");
		}
		//延迟显示菜单 
		for(freeze=0;freeze<=500000000;freeze++);
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
	printf("0.Exit(退出)\n");
	printf("提示：输入\"-1\"结束录入成绩或学号\n"); 
	printf("根据菜单相应序号来选择功能：\n");
}

int InputRecord(int a[],int b[], int *point)
{
	int i = *point;
	int k = 0;
	for(;i<30;i++)
	{
		printf("请输入学号：");
		scanf("%d",&a[i]);
		printf("请输入成绩："); 
		scanf("%d",&b[i]);
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

int Calculate(int b[],int i)
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

//学生成绩从大到小排列，如果n=1就打印结果 
void HtoL_OrderScore(int student[],int score[],int k,int n)
{
	int i;
	int j;
	int c,d;
	int a = 0;
	for(i=0;i<=k;i++)
	{
		a = i;
		for(j=i+1;j<=k;j++)
		{
			if(score[j] > score[a])
			{
				a = j;
			}
		}
		if(a != i)
		{
			Exchange(student,score,a,i);
		}
	}
	if(n == 1)
	{
	printf("学号\t\t\t成绩\n");
		for(i=0;i<=k;i++)
		{
			printf("%d\t\t\t",student[i]);
			printf("%d\n",score[i]);
		}
	}
}

//学生序号从小到大排列，如果n=1就打印结果 
void LtoH_OrderStudent(int student[],int score[],int k,int n)
{
	int i;
	int j;
	int c,d;
	int a = 0;
	for(i=0;i<=k;i++)
	{
		a = i;
		for(j=i+1;j<=k;j++)
		{
			if(student[j] < student[a])
			{
				a = j;
			}
		}
		if(a != i)
		{
			Exchange(student,score,a,i);
		}
	}
	if(n == 1)
	{
		printf("学号\t\t\t成绩\n");
		for(i=0;i<=k;i++)
		{
			printf("%d\t\t\t",student[i]);
			printf("%d\n",score[i]);
		}
	}
}

void Search(int student[],int score[],int k)
{
	int high=k,mid,low= 0;
	long stu_numb;
	int record;
	int count = 0;
	printf("请输入查询的学号:");
	scanf("%d",&stu_numb);
	printf("\n");
	LtoH_OrderStudent(student,score,k,0);
	while(low<=high)
	{
		mid = (high+low)/2;
		if(stu_numb<student[mid])
		{
			high = mid - 1;
		}
		else if(stu_numb>student[mid])
		{
			low = mid + 1;
		}
		else
		{
			count = 1;
			record = score[mid];
			HtoL_OrderScore(student,score,k,0);
			low = 0;
			high = k;
			while(low<=high)
			{
				mid = (high+low)/2;
				if(record<score[mid])
				{
				low = mid + 1;
				}
				else if(record>score[mid])
				{
				high = mid - 1;
				}
				else
				{
					printf("排名为：%d\n",mid+1);
					printf("成绩为：%d\n",record);
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

int ListRecord(int student[],int score[],int k)
{
	int i;
	int sum = 0;
	printf("学号\t\t\t");
	printf("成绩\n");
	for(i=0;i<=k;i++)
	{
		printf("%d\t\t\t",student[i]);
		printf("%d\n",score[i]);
	}
	printf("\n");
	sum = Calculate(score,k);
	return sum;
}

void Analyze(int score[],int k)
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

void FindMax(int student[], int score[], int k)
{
	HtoL_OrderScore(student,score,k,0);
	printf("Top 1 is:\nNumb %d   Score %d\n",student[0],score[0]);
}

void Exchange(int student[31],int score[31],int a,int i)
{
	int c,d;
	c = score[i];
	score[i] = score[a];
	score[a] = c;
	d = student[i];
	student[i] = student[a];
	student[a] = d;
}

