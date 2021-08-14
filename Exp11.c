#include <stdio.h>
#include <windows.h>
#include <string.h>

//�������� 
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
	long int student[31];      //ѧ�� 31�����������30���ˣ���Ҫ��-1����λ�� 
	double score[31][7] = {0};        //����
	double *pscore[31];
	int tool = 0;
	for(tool=0 ; tool<31 ; tool++)
	{
		pscore[tool] = score[tool];
	}
	char name[31][31];
	int k = 0;            //��¼¼���������ֵΪ����-1��������ű�
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
	int *point = 0;       //�Ӵ˵��µ����У���������ѧ��
	int empty = 0;
	point = &empty;
	int freeze;           //�����ӳٵı���	
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
		case 1:	k = InputRecord(student, score, name, point, coursenumb);
				while(k == 0)   //��ֹδ����ѧ�źͳɼ���ɳ������ 
				{
					printf("��������ѧ�źͳɼ���������������ͬѧ������\n");
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
	printf("��ʾ������\"-1\"����¼��ɼ���ѧ��\n"); 
	printf("���ݲ˵���Ӧ�����ѡ���ܣ�\n");
}

int InputRecord(long int a[],double b[][7], char c[][31], int *point, int coursenumb)
{
	int i = *point;
	int k = 0;
	int m;
	for(;i<30;i++)
	{
		printf("������ѧ�ţ�");
		scanf("%ld",&a[i]);
		if(a[i] != -1)
		{
			printf("������������");
			scanf("%s",c[i]);
			for(m=0 ; m<coursenumb ; m++)
			{
				printf("������γ�%d�ɼ���",m+1); 
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

//����ÿ�ſγ̵��ܳɼ� 
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

//����ÿ��ѧ�����ܳɼ� 
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

//��ÿ��ѧ�����ܳɼ����� 
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

//��ѧ������ 
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

//���������ֵ�˳���ų��ɼ���
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
void Search(long int student[],double *pscore[],
			double *paverages[], double *psums[31], int coursenumb,
			char name[][31], int k)
{
	int high=k,mid,low= 0;
	long stu_numb;
	int count = 0;
	int recordscore = 0;
	int tool;		//�����˲���
	double *ptool;		//������ָ�룬��������������е�ַ 
	printf("�������ѯ��ѧ��:");
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
					printf("������%s\nѧ�ţ�%d\n",name[mid],student[mid]);
					printf("����Ϊ��%d\n", mid+1);
					printf("�ܷ�Ϊ��%f\n", psums[mid]);
					ptool = pscore[mid];
					for(tool=1 ; *pscore[mid]!=0 ; (pscore[mid])++,tool++)
					{
						printf("�γ�%d�ĳɼ�Ϊ%f\n",tool,*(pscore[mid]));
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
void NameSearch(long int student[], double *pscore[],
				double *paverages[], double *psums[], int coursenumb,
				char name[][31], int k)
{
	int i;
	int j;
	int judge = 0;
	int count = 0;
	char a[31];
	int tool;		//�����˲��� 
	double *ptool;		//������ָ�룬��¼score���е�ַ 
	int high=k,mid,low= 0;	//�������ı��� 
	int recordscore = 0;
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
		printf("������%s\nѧ�ţ�%d\n",name[count],student[count]);
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
				printf("����Ϊ��%d\n", mid+1);
				printf("�ܷ�Ϊ��%f\n", *(psums[mid]));
				ptool = pscore[mid];
				for(tool=1 ; *pscore[mid]!=0 ; (pscore[mid])++,tool++)
				{
					printf("�γ�%d�ĳɼ�Ϊ%f\n",tool,*(pscore[mid]));
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
		printf("������%s\n",name[i]);
		printf("ѧ�ţ�%d\n",student[i]);
		printf("�ܷ�%.2f\tƽ����%.2f\n",*(psums[i]),*(paverages[i]));
		ptool = pscore[i];
		for(tool=1 ; *pscore[i]!=0 ; (pscore[i])++,tool++)
		{
			printf("�γ�%d�ĳɼ�Ϊ%.2f\n",tool,*(pscore[i]));
		}
		pscore[i] = ptool;		//��ָ��ָ��ԭ�е�ַ
		printf("\n");
	}
	printf("\n");
	for(i=0,tool=1 ; i<coursenumb ; i++,tool++)
	{
		printf("�γ�%d���ܳɼ�Ϊ%.2f,ƽ����Ϊ%.2f\n",tool,sumc[i],averagec[i]);
	}
}

//����ÿ�ſεĳɼ� 
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

