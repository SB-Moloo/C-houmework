#include<stdio.h>
#include<windows.h>

//�������� 
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
	int student[31];      //ѧ�� 31�����������30���ˣ���Ҫ��-1����λ�� 
	int score[31];        //����
	int k = 0;            //��¼¼���������ֵΪ����-1��������ű�
	int menunumb = 0;
	int sum = 0;
	int *point = 0;       //23-25����������ѧ��
	int empty = 0;
	point = &empty;
	double average = 0.0;
	int freeze;           //�����ӳٵı���	
//�˵���������ӡ�˵���
	Menu(); 
	scanf("%d",&menunumb);
	printf("\n");
//����������ŵ��ú����� 
	while(menunumb != 0)
	{
		switch(menunumb)
		{
		case 1:	k = InputRecord(student, score, point);
				while(k == 0)   //��ֹδ����ѧ�źͳɼ���ɳ������ 
				{
					printf("��������ѧ�źͳɼ�\n");
					k = InputRecord(student, score, point);
				}
				break;
		case 2:	sum = Calculate(score,k);
				printf("�ܷ�Ϊ��%d\n",sum);
				average = sum/(k+1.0);
				printf("ƽ����Ϊ��%f\n",average);
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
				printf("�ܷ�Ϊ��%d\n",sum);
				average = sum/(k+1.0);
				printf("ƽ����Ϊ��%f\n",average);
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
		//�ӳ���ʾ�˵� 
		for(freeze=0;freeze<=500000000;freeze++);
		//���һ������ѡ����
		Menu(); 
		scanf("%d",&menunumb);
		printf("\n");
	}
	system("pause");
	return 0;
	
}

void Menu()
{
	printf("1.Input record(����ѧ�źͳɼ�)\n");
	printf("2.Calculate total and average score of course(�����ܳɼ���ƽ����)\n");
	printf("3.Sort in descending order by score(�������гɼ�)\n");
	printf("4.Sort in ascending order by number(�������гɼ�)\n");
	printf("5.Search by number(ͨ��ѧ�Ų��ҳɼ�)\n");
	printf("6.Statistic analysis(�ɼ�����)\n");
	printf("7.List record(�г����гɼ�)\n");
	printf("8.Find top1(��ѯ��һ��)\n");
	printf("0.Exit(�˳�)\n");
	printf("��ʾ������\"-1\"����¼��ɼ���ѧ��\n"); 
	printf("���ݲ˵���Ӧ�����ѡ���ܣ�\n");
}

int InputRecord(int a[],int b[], int *point)
{
	int i = *point;
	int k = 0;
	for(;i<30;i++)
	{
		printf("������ѧ�ţ�");
		scanf("%d",&a[i]);
		printf("������ɼ���"); 
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

//ѧ���ɼ��Ӵ�С���У����n=1�ʹ�ӡ��� 
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
	printf("ѧ��\t\t\t�ɼ�\n");
		for(i=0;i<=k;i++)
		{
			printf("%d\t\t\t",student[i]);
			printf("%d\n",score[i]);
		}
	}
}

//ѧ����Ŵ�С�������У����n=1�ʹ�ӡ��� 
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
		printf("ѧ��\t\t\t�ɼ�\n");
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
	printf("�������ѯ��ѧ��:");
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
					printf("����Ϊ��%d\n",mid+1);
					printf("�ɼ�Ϊ��%d\n",record);
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
	printf("ѧ��\t\t\t");
	printf("�ɼ�\n");
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
	printf("����������%d\n",a);
	printf("������ʣ�%.2f%%\n",count);
	count = 0;
	count = (b/(k+1.0))*100;
	printf("����������%d\n",b);
	printf("���ñ��ʣ�%.2f%%\n",count);
	count = 0;
	count = (c/(k+1.0))*100;
	printf("�е�������%d\n",c);
	printf("�еȱ��ʣ�%.2f%%\n",count);
	count = 0;
	count = (d/(k+1.0))*100;
	printf("����������%d\n",d);
	printf("������ʣ�%.2f%%\n",count);
	count = 0;
	count = (e/(k+1.0))*100;
	printf("������������%d\n",e);
	printf("��������ʣ�%.2f%%\n",count);
	
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

