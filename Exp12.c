#include <stdio.h>
#include <windows.h>
#include <string.h>

typedef struct student
{
	long int studentnumb;
	double score[7];
	char name[31];
	double sums;
	double averages;
}STUDENT;

typedef struct course
{
	double sumc;
	double averagec;
}COURSE;

//�������� 
void Menu();
int InputRecord(STUDENT student[31], int *point, int coursenumb);
void CalculateEveryCourse(STUDENT student[31], COURSE course[7], int i , int coursenumb);
void CalculateEveryStudent(STUDENT student[31], int i , int coursenumb);
void Search(STUDENT student[31], int coursenumb, int k);
int ListRecord(STUDENT student[31], COURSE course[7], int coursenumb, int k);
void Analyze(STUDENT student[31], int coursenumb, int k);
int Ascending(double a, double b);
int Descending(double a, double b);
void ExchangeStruct(STUDENT student[31],int present,int record);
int NumbAscending(long int a, long int b);
int NumbDescending(long int a, long int b);
void NamelistInOrder(STUDENT student[31], int k, int coursenumb);
int DicStrcmp(char *small, char *big);
void NameSearch(STUDENT student[31], int coursenumb, int k);
int SelectionSort(STUDENT student[31], int k, int coursenumb,
					int (*Compare)(double a, double b));
int NumbSelectionSort(STUDENT student[31], int k, int coursenumb,
						 int (*Compare)(long int a, long int b));

int main(void)
{
	STUDENT student[31];	//ѧ�� 31�����������30���ˣ���Ҫ��-1����λ�� 
	COURSE course[7];
	int k = 0;            //��¼¼���������ֵΪ����-1��������ű�
	int menunumb = 0;
	int *point = 0;       //�Ӵ˵��¹����У���������ѧ��
	int empty = 0;
	point = &empty;
	int coursenumb = 7;
	while(coursenumb > 6)
	{
		printf("������γ̵�����(���6��)��");
		scanf("%d", &coursenumb);
	}
	printf("----------------------------------------\n");
//�˵���������ӡ�˵���
	Menu(); 
	scanf("%d",&menunumb);
	printf("\n");
//����������ŵ��ú����� 
	while(menunumb != 0)
	{
		switch(menunumb)
		{
		case 1:	k = InputRecord(student, point, coursenumb);
				while(k == 0)   //��ֹδ����ѧ�źͳɼ���ɳ������ 
				{
					printf("��������ѧ�źͳɼ���������������ͬѧ������\n");
					k = InputRecord(student, point, coursenumb);
				}
				break;
		case 2:	CalculateEveryCourse(student, course, k, coursenumb);
				printf("\n");
				break;
		case 3:	CalculateEveryStudent(student, k, coursenumb);
				printf("\n");
				break;
		case 4:	SelectionSort(student, k, coursenumb, Descending);
				printf("\n");
				break;
		case 5:	SelectionSort(student, k, coursenumb, Ascending);
				printf("\n");
				break;
		case 6:	NumbSelectionSort(student, k, coursenumb, NumbAscending);
				printf("\n");
				break;
		case 7:	NamelistInOrder(student, k, coursenumb);
				printf("\n");
				break;
		case 8:	Search(student, coursenumb, k);
				printf("\n");
				break;
		case 9:	NameSearch(student, coursenumb, k);
				printf("\n");
				break;
		case 10:Analyze(student, coursenumb, k);
				printf("\n");
				break;
		case 11:ListRecord(student, course, coursenumb, k);
				printf("\n");
				break;
		case 0: exit(0);
		}
		if(menunumb<0 || menunumb >11)
		{
			printf("Wrong input!Try againg!\n");
			printf("\n");
		}
		//�ָ��� 
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
	printf("1.¼��ÿ��ѧ����ѧ�š������͸��ƿ��Գɼ�\n");
	printf("2.����ÿ�ſγ̵��ֺܷ�ƽ����\n");
	printf("3.����ÿ��ѧ�����ֺܷ�ƽ����\n");
	printf("4.��ÿ��ѧ�����ܷ��ɸߵ����ų����α�\n");
	printf("5.��ÿ��ѧ�����ܷ��ɵ͵����ų����α�\n");
	printf("6.��ѧ����С�����ų��ɼ���\n");
	printf("7.���������ֵ�˳���ų��ɼ���\n");
	printf("8.��ѧ�Ų�ѯѧ������������ƿ��Գɼ�\n");
	printf("9.��������ѯѧ������������ƿ��Գɼ�\n");
	printf("10.���Ƴɼ�����\n");
	printf("11.���ÿ��ѧ���ĳɼ�\n");
	printf("0.Exit(�˳�)\n");
	printf("��ʾ��\t����\"-1\"����¼��ɼ���ѧ��\n\tʹ��4-11��������ʹ��2-3���ܼ���\n\n"); 
	printf("���ݲ˵���Ӧ�����ѡ���ܣ�\n");
}

int InputRecord(STUDENT student[31], int *point, int coursenumb)
{
	int i = *point;
	int k = 0;
	int m;
	for(;i<30;i++)
	{
		printf("������ѧ�ţ�");
		scanf("%ld",&student[i].studentnumb);
		if(student[i].studentnumb != -1)
		{
			printf("������������");
			scanf("%s",student[i].name);
			for(m=0 ; m<coursenumb ; m++)
			{
				printf("������γ�%d�ɼ���",m+1); 
				scanf("%lf",&student[i].score[m]);
			}
		}
		if((student[i].studentnumb == -1))
		{
			printf("\n");
			break;
		}
		k = i;
	}
	*point = k + 1;
	return k;
}

//����ÿ�ſγ̵��ܳɼ�
void CalculateEveryCourse(STUDENT student[31], COURSE course[7], int i , int coursenumb)
{
	int a;
	int b;
	for(b=0; b<coursenumb; b++)
	{
		for(a=0; a<=i ; a++)
		{
			course[b].sumc += student[a].score[b];
		}
	}
	for(b=0 ; b<coursenumb; b++)
	{
		course[b].averagec = course[b].sumc/(i+1);
	}
}

//����ÿ��ѧ�����ܳɼ� 
void CalculateEveryStudent(STUDENT student[31], int i , int coursenumb)
{
	int a;
	int b;
	student[0].sums = 0.0;
	student[0].averages = 0.0; 
	for(a=0; a<=i ; a++)
	{
		for(b=0; b<coursenumb; b++)
		{
			student[a].sums += student[a].score[b];
		}
		student[a].averages = student[a].sums/coursenumb;
	}
}

//��ÿ��ѧ�����ܳɼ����� 
int SelectionSort(STUDENT student[31], int k, int coursenumb,
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
			if((*Compare)(student[next].sums, student[record].sums))
			{
				record = next;
			}						
		}
		if(record != present)
		{
			ExchangeStruct(student, present, record);
		}
		
	}
}

//��ѧ������ 
int NumbSelectionSort(STUDENT student[31], int k, int coursenumb,
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
			if((*Compare)(student[next].studentnumb, student[record].studentnumb))
			{
				record = next;
			}						
		}
		if(record != present)
		{
			ExchangeStruct(student, present, record);
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

//���������ֵ�˳���ų��ɼ���
void NamelistInOrder(STUDENT student[31], int k, int coursenumb)
{
	int present = 0;
	int j = 0;
	int record = 0;
	for(; present <= k; present++)
	{
		record= present;
		for(j = present + 1; j <= k; j++)
		{
			if((DicStrcmp(student[j].name, student[record].name)<0))
			{
				record = j;
			}
		}
		if(record != present)
		{
			ExchangeStruct(student, present, record);
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


//��ѧ�Ų���ѧ���ɼ�������������������ɼ����� 
void Search(STUDENT student[31], int coursenumb, int k)
{
	int high=k,mid,low= 0;
	long stu_numb;
	int count = 0;
	int recordscore = 0;
	int tool;		//�����˲���
	printf("�������ѯ��ѧ��:");
	scanf("%ld",&stu_numb);
	printf("\n");
	NumbSelectionSort(student, k, coursenumb, NumbDescending);
	while(low<=high)
	{
		mid = (high+low)/2;
		if(stu_numb < student[mid].studentnumb)
		{
			low = mid + 1;
		}
		else if(stu_numb > student[mid].studentnumb)
		{
			high = mid - 1;
		}
		else
		{
			count = 1;
			low = 0;
			high = k;
			recordscore = student[mid].sums;
			SelectionSort(student, k, coursenumb, Descending);
			while(low <= high)
			{
				mid = (high+low)/2;
				if(recordscore < student[mid].sums)
				{
					low = mid + 1;
				}
				else if(recordscore > student[mid].sums)
				{
					high = mid - 1;
				}
				else
				{
					printf("������%s\nѧ�ţ�%d\n",student[mid].name,student[mid].studentnumb);
					printf("����Ϊ��%d\n", mid+1);
					printf("�ܷ�Ϊ��%f\n", student[mid].sums);
					for(tool=0 ; tool<coursenumb ; tool++)
					{
						printf("�γ�%d�ĳɼ�Ϊ%f\n",tool+1,student[mid].score[tool]);
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

//�����ֲ��ң������ִ�Сд
void NameSearch(STUDENT student[31], int coursenumb, int k)
{
	int i;
	int j;
	int judge = 0;
	int count = 0;
	char a[31];
	int tool;		//�����˲��� 
	int high=k,mid,low= 0;	//�������ı��� 
	int recordscore = 0;
	printf("��������Ҫ��ѯ�����֣�");
	scanf("%s", a);
	for(i = 0; i <= k; i++)
	{
		for(j = 0; j <= strlen(student[i].name)-1; j++)
		{
			if( ((a[j]<91)&&(student[i].name[j]<91)) || ((a[j]>96)&&(student[i].name[j]>96)) )
			{
				if( a[j] == student[i].name[j] )
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
			else if ( (a[j]<91)&&(student[i].name[j]>96) )
			{
				if( a[j]+32 == student[i].name[j] )
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
			else if ( (a[j]>96)&&(student[i].name[j]<91) )
			{
				if( a[j] == student[i].name[j]+32 )
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
		printf("������%s\nѧ�ţ�%d\n",student[count].name,student[count].studentnumb);
		recordscore = student[count].sums;
		SelectionSort(student, k, coursenumb, Descending);
		while(low <= high)
		{
			mid = (high+low)/2;
			if(recordscore < student[mid].sums)
			{
				low = mid + 1;
			}
			else if(recordscore > student[mid].sums)
			{
				high = mid - 1;
			}
			else
			{
				printf("����Ϊ��%d\n", mid+1);
				printf("�ܷ�Ϊ��%f\n", student[mid].sums);
				for(tool=0; tool<coursenumb; tool++)
				{
					printf("�γ�%d�ĳɼ�Ϊ%f\n",tool+1, student[mid].score[tool]);
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

int ListRecord(STUDENT student[31], COURSE course[7], int coursenumb, int k)
{
	int i;
	int tool;
	for(i=0;i<=k;i++)
	{
		printf("������%s\n",student[i].name);
		printf("ѧ�ţ�%d\n",student[i].studentnumb);
		printf("�ܷ�:%.2f\tƽ����:%.2f\n",student[i].sums, student[i].averages);
		for(tool=0 ; tool < coursenumb; tool++)
		{
			printf("�γ�%d�ĳɼ�Ϊ%.2f\n",tool+1,student[i].score[tool]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0,tool=1 ; i<coursenumb ; i++,tool++)
	{
		printf("�γ�%d���ܳɼ�Ϊ%.2f,ƽ����Ϊ%.2f\n",tool,course[i].sumc,course[i].averagec);
	}
}

//����ÿ�ſεĳɼ� 
void Analyze(STUDENT student[31], int coursenumb, int k)
{
	int a=0,b=0,c=0,d=0,e=0;
	double count = 0.0;
	int i,j;
	for(j=0 ; j<coursenumb ; j++)
	{
		a=0,b=0,c=0,d=0,e=0;
		for(i=0 ; i<=k ; i++)
		{
			if(student[i].score[j]>=90 && student[i].score[j]<=100)
			{
				a++;
			}
			else if(student[i].score[j]>=80 && student[i].score[j]<=89)
			{
				b++;
			}
			else if(student[i].score[j]>=70 && student[i].score[j]<=79)
			{
				c++;
			}
			else if(student[i].score[j]>=60 && student[i].score[j]<=69)
			{
				d++;
			}
			else if(student[i].score[j]>=0 && student[i].score[j]<=59)
			{
				e++;
			}
		}
		printf("�γ�%d�ĳɼ�������",j+1);
		count = (a/(k+1.0))*100;
		printf("����������%d\t������ʣ�%.2f%%\n",a,count);
		count = (b/(k+1.0))*100;
		printf("����������%d\t���ñ��ʣ�%.2f%%\n",b,count);
		count = (c/(k+1.0))*100;
		printf("�е�������%d\t�еȱ��ʣ�%.2f%%\n",c,count);
		count = (d/(k+1.0))*100;
		printf("����������%d\t������ʣ�%.2f%%\n",d,count);
		count = (e/(k+1.0))*100;
		printf("������������%d\t��������ʣ�%.2f%%\n",e,count);
	}
}

void ExchangeStruct(STUDENT student[31], int present, int record)
{
	STUDENT z;
	z = student[present];
	student[present] = student[record];
	student[record] = z; 
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

