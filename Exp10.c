#include <stdio.h>
#include <windows.h>
#include <string.h>

//�������� 
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
	long int student[31];      //ѧ�� 31�����������30���ˣ���Ҫ��-1����λ�� 
	float score[31];        //����
	char name[31][31];
	int k = 0;            //��¼¼���������ֵΪ����-1��������ű�
	int menunumb = 0;
	int sum = 0;
	int *point = 0;       //�Ӵ˵��µ����У���������ѧ��
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
		case 1:	k = InputRecord(student, score, name, point);
				while(k == 0)   //��ֹδ����ѧ�źͳɼ���ɳ������ 
				{
					printf("��������ѧ�źͳɼ���������������ͬѧ������\n");
					k = InputRecord(student, score, name, point);
				}
				break;
		case 2:	sum = Calculate(score,k);
				printf("�ܷ�Ϊ��%d\n",sum);
				average = sum/(k+1.0);
				printf("ƽ����Ϊ��%f\n",average);
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
				printf("�ܷ�Ϊ��%d\n",sum);
				average = sum/(k+1.0);
				printf("ƽ����Ϊ��%f\n",average);
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
		//�ӳ���ʾ�˵� 
		printf("----------------------------------------\n");
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
	printf("9.Sort in dictionary order by name(���ֵ�˳����������)\n");
	printf("10.Search by name(�����ֲ�ѯ)\n");
	printf("0.Exit(�˳�)\n");
	printf("��ʾ������\"-1\"����¼��ɼ���ѧ��\n"); 
	printf("���ݲ˵���Ӧ�����ѡ���ܣ�\n");
}

int InputRecord(long int a[],float b[], char c[][31], int *point)
{
	int i = *point;
	int k = 0;
	for(;i<30;i++)
	{
		printf("������ѧ�ţ�");
		scanf("%ld",&a[i]);
		if(a[i] != -1)
		{
			printf("������������");
			scanf("%s",c[i]);
			printf("������ɼ���"); 
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

//���������ֵ�˳���ų��ɼ���
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

//���ֵ�˳��ȴ�С�������ִ�Сд 
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
	printf("�������ѯ��ѧ��:");
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
					printf("����Ϊ��%d\n", mid+1);
					printf("�ɼ�Ϊ��%f\n", score[mid]);
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
	printf("��������Ҫ��ѯ�����֣�");
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
		printf("ѧ��\t\t\t");
		printf("����\t\t\t");
		printf("�ɼ�\n");
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
	printf("ѧ��\t\t\t");
	printf("����\t\t\t");
	printf("�ɼ�\n");
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

