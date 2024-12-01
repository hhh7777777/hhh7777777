
#include "StdAfx.h" 
/*
	Name: 
	Copyright: 
	Author: 
	Date: 13/06/24 23:50
	Description: 
*/

using namespace std;

#include <stdio.h>
#include<iostream>
#include<fstream>
#include <string> 
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <sstream>
#include <mysql.h>
#include <WinSock2.h>


#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"wsock32.lib")

 
#define LEN sizeof(struct scorenode)
#define DEBUG
#define size
#define FrameX 13   		//�������Ͻǵ�X������
#define FrameY 3   			//�������Ͻǵ�Y������
#define Frame_height  20 	//���ڵĸ߶�
#define Frame_width   18 	//���ڵĿ�� 
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "1234"
#define DATABASE "xiaofei"

#define _CRT_SECURE_NO_WARNINGS

  
struct scorenode
{
	int number;/*ѧ��*/
	char name[10];/*����*/
	int xiaofei;/*�������*/
	struct scorenode *next;
};

typedef struct scorenode score;

int n,k;/*n,kΪȫ�ֱ���*/
void gotoxy(int x, int y);//����ƶ���ָ��λ��
int choice;     
void menu();//�˵� 
int people();//װ�� 
MYSQL *mysql = new MYSQL; //mysql����
MYSQL_FIELD *fd;    //�ֶ�������  
char field[32][32];    //���ֶ�����ά����  
MYSQL_RES *res; //����ṹ�������е�һ����ѯ�����  
MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���  
char query[150]; //��ѯ���  
int b_id;//�������ݿ� 

bool QueryDatabase1();
bool ConnectDatabase(); //

char b_name[20];
string in_usl;
score *creat(void);
score *load(score *head);
score *search(score *head);
score *del(score *head);
score *add(score *head,score *stu);
void print(score *head);
int save(score *p1);


 
                                                                                                                                                                                                                                                                                                                                                                                 

/*=========================��ȡ��Ļ���λ��=============================*/ 

void gotoxy(int x, int y)
{
	COORD pos{};
	pos.X = x;  //������
	pos.Y = y;  //������
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ������ɫ���� 
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
	return 0;
}


/*=========================�½��˺���������ݿ�=============================*/
//String����ת�� 
std::string StringFromLPCTSTR(LPCTSTR str) 
{
#ifdef _UNICODE
	int size_str = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, NULL, NULL);

	char* point_new_array = new char[size_str];

	WideCharToMultiByte(CP_UTF8, 0, str, -1, point_new_array, size_str, NULL, NULL);

	std::string return_string(point_new_array);
	delete[] point_new_array;
	point_new_array = NULL;
	return return_string;
#else
	return std::string(str);
#endif
}

/*=========================ע���¼=============================*/
bool ConnectDatabase()
{
	system("cls");
	string username,password,un,pw;
	int number;
    //��ʼ��mysql  
    mysql_init(mysql);
    //����false������ʧ�ܣ�����true�����ӳɹ�  
    if (!(mysql_real_connect(mysql, "localhost", "root", "1234", "xiaofei", 3306, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
    {
        printf("Error connecting to database:%s", mysql_error(mysql));
        return false;
    }
    else
    {
        printf("���ݿ����ӳɹ���Connected...\n");
		strcpy(query,"commit");//����: ��ʱ���ݻ��ڻ�����, Ϊ��ȷ�����, ������commit�ύһ�����һ���ǲ���Ҫ����
        return true;
        
    }
    
}

bool QueryDatabase1(){
	int number; 
	string username,password,un,pw;
        cout<<"�������˺ţ�";
       	cin>>username;	
    	cout<<"���������룺";   	
    	cin>>password;   
	strcpy(query, "select * from users"); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü�����  
    mysql_query(mysql, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������  
    //����0 ��ѯ�ɹ�������1��ѯʧ��  	
    if (mysql_query(mysql, query))    //ִ��SQL���
    {
        printf("Query failed (%s)", mysql_error(mysql));
        return false;
    }
    else
    {
        printf("��ѯ�ɹ���");
		
        //��ȡ�����  
    if (!(res = mysql_store_result(mysql)))   //���sql�������󷵻صĽ����  
    {
        printf("Couldn't get result from %s\n", mysql_error(mysql));
        return false;
    }  
        //��ӡ��������  
    printf("number of dataline returned: %d\n", mysql_affected_rows(mysql));
    while (column = mysql_fetch_row(res))   //����֪�ֶ���������£���ȡ����ӡ��һ��  
    {

        if(column[0]==username&&column[1]==password)
{
	
    printf("�����˺Ŵ��ڣ����Զ���¼�ɹ���\n");  
    printf("\n\n\t ����0�˳���¼��number��:");
    	    scanf("%d",&number);
	    	getchar();
				}
else{
    printf("���˺Ų����ڣ�����������!!");
	 	
		    printf("\n\n\t ����0�˳���¼��number��:");
    	    scanf("%d",&number);
    	    getchar();
			return   QueryDatabase1();
				}

}
}
}
    

/*=========================���������˺�������һ��ָ������ͷ��ָ��=============================*/
score *creat(void)
{
	system("cls");
	score *head;
    score *p1,*p2,*p3,*max;
	int i,j;
    char t[10];
	n=0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ����̨���,������Ļ�ı���ɫ��������ɫ
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
	printf("\n\n\t\t\t����ѧ�����Ѽ�¼\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���	
    p1=p2=p3=(score *)malloc(LEN);/*head=p3; ����һ���µ�Ԫ*/
		printf("\n\n\t    ������ѧ����Ϣ������numberΪ0ʱ��������������\n");
	repeat1: printf("\t    number:");/*����ѧ�ţ�ѧ��Ӧ����0*/
       scanf("%d",&p1->number);
	   printf("\t    name:");
	   scanf("%s",&p1->name);/*����ѧ������*/
	   printf("\t    money:");/*�����������;*/
		scanf("%d",&p1->xiaofei);
		/*����ѧ��Ϊ�ַ���С��0ʱ�����򱨴���ʾ��������ѧ��*/
	while(p1->number<0)
	{
		getchar();
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
		printf("\t    number����С��0������������:");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���		
        scanf("%d",&p1->number);
	}
  
	if(p1->number==0)
		goto end;/*�������ѧ��Ϊ0ʱ��ת��ĩβ��������������*/
	else
	{
		p3=head;
		if(n>0)
		{
			for(i=0;i<n;i++)
			{
				if(p1->number!=p3->number)
					p3=p3->next;
				else
				{
					SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
					printf("\t    number�ظ�������������!\n");
					SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
					goto repeat1;	/*�������ѧ���Ѿ�����ʱ�����򱨴�����ǰ����������*/   
			}
			}
		}
	 }


	while(p1->number!=0)/*�������ѧ�Ų�Ϊ0ʱ��ѭ������ѧ����Ϣ*/
	{
		n=n+1;
		if(n==1)	//��һ������ķ��ڵ�һλ
		{
			head=p1;
		}
		else		//�����������η�ǰ��ĺ���
		{
			p2->next=p1;
		}
		p2=p1;
		p1=(score *)malloc(LEN);
		printf("\t    ������ѧ����Ϣ������numberΪ0ʱ��������������\n");
		repeat2:
		printf("\t    number:");
		scanf("%d",&p1->number);/*����ѧ�ţ�ѧ��Ӧ����0*/

		while(p1->number<0)/*����ѧ��Ϊ�ַ���С��0ʱ�����򱨴���ʾ��������ѧ��*/
		{
			getchar();
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
			printf("\t    number����С��0������������:");
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���			
			scanf("%d",&p1->number);
		}			
		if(p1->number==0)
		{
			goto end;/*�������ѧ��Ϊ0ʱ��ת��ĩβ��������������*/
		}
		else
		{
			p3=head;
			if(n>0)
			{
				for(i=0;i<n;i++)
				{
					if(p1->number!=p3->number)
					{
						p3=p3->next;
					}
					else/*�������ѧ���Ѿ����ڣ����򱨴�����ǰ����������*/
					{
						SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
						printf("\t    number�ظ�������������!\n");
						SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���						
						goto repeat2;    
					}
				}
			}
		}
		printf("\t    name:");
		scanf("%s",&p1->name);/*����ѧ������*/
		printf("\t    money:");
		scanf("%d",&p1->xiaofei);/*�����������; */
	}//����ѭ��
	end: p1=head;
    p3=p1;
	for(i=1;i<n;i++)
    {
		for(j=i+1;j<=n;j++)
		{
			max=p1;
			p1=p1->next;

			if(max->number>p1->number)/*����ǰ�����е����������ʹ֮��ѧ����ƥ��*/
			{
				/*����ǰ�����е�ѧ��ֵ��ʹ��ѧ�Ŵ����Ƶ�����Ľ����*/
				k=max->number;
				max->number=p1->number;
				p1->number=k;
				/*����ǰ�����е�������ʹ֮��ѧ����ƥ��*/
				strcpy(t,max->name); 
				strcpy(max->name,p1->name);
				strcpy(p1->name,t);                           
           }
         }
		max=head;p1=head;/*����ʹmax,pָ������ͷ*/
	}
	p2->next=NULL;/*�����β*/	
	printf("\t    ������ ");  
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
	printf("%d  ",n);
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�Ļ�������ɫ���׵׺��� 
    printf("��ѧ�����Ѽ�¼!\n");
	getch();
    return(head);

}

/*===========================���ļ�����ѧ����¼=================================================*/
score *load(score *head)
{
	system("cls");
	score *p1,*p2;
    int m=0;
    char filepn[10];
	FILE *fp;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ����̨���,������Ļ�ı���ɫ��������ɫ
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
	printf("\n\n\t\t\t���ļ�����ѧ�����Ѽ�¼\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
	printf("\n\n\t\t�������ļ�·�����ļ����ƣ���f:\\mr.txt��:\n\n\t\t\t    ");
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
	scanf("%s",filepn);/*�����ļ�·��������*/
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
	if((fp=fopen(filepn,"r+"))==NULL)
	{
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
		printf("\n\n\t    ���ܴ򿪴��ļ�!\n");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���			
		getch();
		return 0;
	}
	else
	{
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
		p1=(score *)malloc(LEN); /*����һ���µ�Ԫ*/
		fscanf(fp,"%d%s%d\n",&p1->number,p1->name,&p1->xiaofei);
		printf("\t\t-----------------------------------------\n");/*�������*/
		printf("\t\t  | %d\t   | %s\t   | %d\t\n",p1->number,p1->name,p1->xiaofei);		/*�ļ���������ʾ*/
		head=NULL;
		do	
		{
			n=n+1;
			if(n==1)
				head=p1;
			else
				p2->next=p1;
			p2=p1;
			p1=(score *)malloc(LEN);  /*����һ���µ�Ԫ*/
			fscanf(fp,"%d%s%d\n",&p1->number,p1->name,&p1->xiaofei);
			printf("\t\t  | %d\t   | %s\t   | %d\t\n",p1->number,p1->name,p1->xiaofei);			/*�ļ���������ʾ*/			
		}while(!feof(fp));
		p2->next=p1;
		p1->next=NULL;
		n=n+1;
	}
	printf("\t\t-----------------------------------------\n");/*�������*/
	getch();
	fclose(fp);/*�������룬�ر��ļ�*/
	return (head);
}


/*=====================��ѯѧ������=====================================================*/
score *search(score *head)
{
	system("cls");
	int number;
	score *p1,*p2;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ����̨���,������Ļ�ı���ɫ��������ɫ
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
	printf("\n\n\t\t\t��ѯѧ������\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
	printf("\n\n\t  ������Ҫ��ѯ��ѧ��ѧ��,����0�˳���ѯ��number��:");
	scanf("%d",&number);
	getchar();
	while(number!=0)
	{
		if(head==NULL)
		{
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
			printf("\n\t\t ϵͳ�л�û�м�¼���봴����¼!\n");
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
			getchar();
			return(head);
		}
		printf("\t\t---------------------------------------------\n");
		printf("\t\t  | number\t  | name\t  | consume\t \n");
		printf("\t\t---------------------------------------------\n");/*��ӡ�����*/
		p1=head;
		while(number!=p1->number&&p1->next!=NULL)
		{
			p2=p1;
			p1=p1->next;
		}
        if(number==p1->number)
		{
			 printf("\t\t  | %d\t\t  | %s\t\t   |%d\t\n",p1->number,p1->name,p1->xiaofei);
			 printf("\t\t---------------------------------------------\n");

		}/*��ӡ�����*/
        else
		{
			printf("\t\tѧ��Ϊ");
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
			printf(" %d ",number);
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
			printf("��ѧ��������!\n");
		}
		printf("\n\n\t\t������Ҫ��ѯ��ѧ��ѧ�ţ�number��:");
		scanf("%d",&number);
		getchar();
	}
		return(head);
}

/*=======================ɾ��ѧ������================================================*/
score *del(score *head)
{
	system("cls");
	score *p1,*p2;
	int number;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ����̨���,������Ļ�ı���ɫ��������ɫ
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
	printf("\n\n\t\t\tɾ��ѧ������\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
	printf("\n\n\t  ������Ҫɾ����ѧ��ѧ��,����0�˳�ɾ����number��:");
	scanf("%d",&number);
	getchar();
	while(number!=0)/*����ѧ��Ϊ0ʱ�˳�*/
	{

		if(head==NULL)
		{
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
			printf("\n\t\t ϵͳ�л�û�м�¼���봴����¼!\n");
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
			getchar();
			return(head);
		}

		p1=head;

		while(number!=p1->number&&p1->next!=NULL)   /*p1ָ��Ĳ�����Ҫ�ҵ��׽�㣬���Һ��滹�н��*/
		{
			p2=p1;
			p1=p1->next;		/*p1����һ�����*/
		} 
		if(number==p1->number)		/*�ҵ���*/
		{
			if(p1==head)
				head=p1->next;   /*��p1ָ������׽�㣬�ѵض�������ַ����head*/
			else
			
				p2->next=p1->next;   /*������һ������ַ ����ǰһ����ַ*/
				SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//����������ɫ��Ϊī��ɫ
				printf("\n\t\t\tѧ��Ϊ ");
				SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ
				printf("%d",number);
				SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//����������ɫ��Ϊī��ɫ				
				printf(" �ļ�¼��ɾ��!\n");
				SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
				n=n-1;
			
		}
		else
		{
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ
			printf("\n\t\t\tѧ��Ϊ");  /*�Ҳ����ý��*/
			SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
			printf(" %d ",number); 
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ			
			printf("��ѧ��������!\n");  
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
		}
	printf("\n\n\t  ��������Ҫɾ����ѧ��ѧ��,����0�˳�ɾ����number��:");
	scanf("%d",&number);
	getchar();
	}

#ifdef DEBUG
	printf("\n\t\t\t  �Ѿ��˳�ɾ��!\n\n");

#endif
	printf("\t\t    ��ɾ�� ");  
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
	printf("%d  ",n);
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�Ļ�������ɫ���׵׺��� 
    printf("��ѧ�����Ѽ�¼!\n");
	getch();
	return(head);
}


/*==========================���Ӽ�¼===================================================*/
score *add(score *head,score *stu)
{
	system("cls");
	score *p0,*p1,*p2,*p3,*max;
    int i,j;
    char t[10];
	p3=stu=(score *)malloc(LEN);/*����һ���µ�Ԫ*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ����̨���,������Ļ�ı���ɫ��������ɫ
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
	printf("\n\n\t\t\t����ѧ�����Ѽ�¼\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
	repeat4: 
	printf("\n\n\t  ������Ҫ��ӵ�ѧ��ѧ��,����0�˳���number��:");
	scanf("%d",&stu->number);  /*����ѧ�ţ�ѧ��Ӧ����0*/
    while(stu->number<0)/*���������������ѧ��*/
	{
		getchar();
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
		printf("\n\t    number����С��0������������:");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
		scanf("%d",&stu->number);
	}
     /******************************************************/
    if(stu->number==0)/*����0ʱ������������*/
	goto end2;/*�������ѧ��Ϊ0ʱ��ת��ĩβ������׷��*/
	else
	{
		p3=head;
		if(n>0)
		{
			for(i=0;i<n;i++)
			{
				if(stu->number!=p3->number)
					p3=p3->next;
				else    /*�������ѧ���Ѿ����ڣ����򱨴�����ǰ����������*/
				{
					SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
					printf("\n\t    number�ظ�������������!\n");
					SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
					goto repeat4; 
				}
			}
		}
	}

  /******************************************************/
   printf("\t    name:");
   scanf("%s",stu->name);            /*����ѧ������*/
   printf("\t    consuming:");
   scanf("%d",&stu->xiaofei);    
   p1=head;
   p0=stu;
	if(head==NULL)/*��ԭ������Ϊ��ʱ�����׽�㿪ʼ�������*/
	{
	   head=p0;
	   p0->next=NULL;
	}
	else/*ԭ������Ϊ��*/
	{
		if(p1->next==NULL)/*�ҵ�ԭ�������ĩβ*/
		{
			p1->next=p0;
			p0->next=NULL;/*�������¿���Ԫ������*/
		}
		else
		{
			while(p1->next!=NULL)/*��û�ҵ�ĩβ��������*/
			{
				p2=p1;
				p1=p1->next;
			}
			p1->next=p0;
			p0->next=NULL;
		}
	}
	n=n+1;
	p1=head;
	p0=stu;
	for(i=1;i<n;i++)
	{
		for(j=i+1;j<=n;j++)
        {
			max=p1;
			p1=p1->next;
			if(max->number>p1->number) /*����ǰ�����е�ѧ��ֵ��ʹ��ѧ�Ŵ����Ƶ�����Ľ����*/
			{
			k=max->number;
			max->number=p1->number;
			p1->number=k;
        

			strcpy(t,max->name); /*����ǰ�����е�������ʹ֮��ѧ����ƥ��*/
			strcpy(max->name,p1->name);
			strcpy(p1->name,t); /*����ǰ�����е����������ʹ֮��ѧ����ƥ��*/
    
                 
            }
			max=head;
			p1=head;/*����ʹmax,pָ������ͷ*/
		}
	}
	end2:
		printf("\t    ���ڹ��� ");  
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
		printf("%d  ",n);
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�Ļ�������ɫ���׵׺��� 
		printf("��ѧ�����Ѽ�¼!\n");
		getch();
		return(head);
}



 /*=========================��ʾ���м�¼=================================================*/
void print(score *head)
{
	system("cls");
	score *p;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ����̨���,������Ļ�ı���ɫ��������ɫ
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
	printf("\n\n\t\t\t\t��ʾ����ѧ�����Ѽ�¼\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
	if(head==NULL)
	{
        SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
		printf("\n\t\t ϵͳ�л�û�м�¼���봴����¼!\n");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
	
	}else
	{
		SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ 
		printf("\n\t\t����%d��ѧ��\n\n",n);
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//���ı������ɫ��Ϊī��ɫ
		printf("\t\t---------------------------------------------------\n");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ
		printf("\t\t  | number\t|\tname\t|    consume    |\n");
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//���ı������ɫ��Ϊī��ɫ
		printf("\t\t---------------------------------------------------\n");//��ӡ�����
		SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�ָ�������ɫ���׵׺���
		p=head;
		do
		{
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_BLUE);   	//����������ɫ��Ϊ��ɫ

			printf("\t\t     %d\t\t     %s\t      %d\t\n",p->number,p->name,p->xiaofei);
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);   	//���ı������ɫ��Ϊī��ɫ
			printf("\t\t---------------------------------------------------\n");//��ӡ���
			p=p->next;
		}while (p!=NULL);/*��ӡ���*/
		getch();
		
	}
}



/*=============================�����¼���ļ�=========================================*/
 save(score *p1)
{
	FILE *fp;
	if((fp=fopen("D:consume","wb"))==NULL)
	{
		printf("can't open this file!\n");
		return 0;
	}
	else
	{
		while(p1!=NULL)
		{
		fprintf(fp,"%d,%s,%d\t\t\t",p1->number,p1->name,p1->xiaofei);
		p1=p1->next;
		}
		printf("\t\t�ļ�������D:consume!\n");
		getch();
	}
	fclose(fp);
}


/*==================================���˵�===================================================*/
void menu()
{

	system("cls");
	printf("\n\n\n");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ����̨���  
	//printf("\t\t-----------------------------------------\n");	
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);   	//����������ɫ��Ϊ��ɫ 
	printf("\t\t\t   ѧ���������ѹ���ϵͳ\t\t\n\n");
	SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�Ļ�������ɫ���׵׺��� 
	printf("\t\t--------------------------------------------------\n");
	printf("\t\t|\t  1    ����ѧ�����Ѽ�¼                  |\n\n");
	printf("\t\t|\t  2    ��ȡѧ�����Ѽ�¼                  |\n\n");
	printf("\t\t|\t  3    ��ѯѧ�����Ѽ�¼                  |\n\n");
	printf("\t\t|\t  4    ɾ��ѧ�����Ѽ�¼                  |\n\n");
	printf("\t\t|\t  5    ����ѧ�����Ѽ�¼                  |\n\n");
	printf("\t\t|\t  6    ��ʾ���м�¼                      |\n\n");
	printf("\t\t|\t  7    �����¼���ļ�                    |\n\n"); 
	printf("\t\t|\t  0    �˳���ϵͳ                        |\n\n");
	printf("\t\t|------------------------------------------------|\n");
	printf("\t\tchoose(0-7):");
    int people();
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
	gotoxy(90, 5);
	printf("����컨�˶���Ǯ��\n");
	SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	gotoxy(72, 7);
	printf("��������������          ��������������\n");
	gotoxy(72, 8);
	printf("  ������������          ������������\n");
	gotoxy(72, 9);
	printf("   ������������        ������������\n");
	gotoxy(72, 10);
	printf("    ������������      ������������  \n");
	gotoxy(72, 11);
	printf("     ������������    ������������    \n");
	gotoxy(72, 12);
	printf("      ������������������������\n");
	gotoxy(72, 13);
	printf(" ����������������������������������\n");
	gotoxy(75, 14);
	printf("         ��������������\n");
	gotoxy(75, 15);
	printf("         ��������������\n");
	gotoxy(72, 16);
	printf(" ����������������������������������\n");
	gotoxy(75, 17);
	printf("          ������������\n");
	gotoxy(75, 18);
	printf("          ������������\n");
	gotoxy(75, 19);
	printf("          ������������\n"); 
	gotoxy(75, 20);
	printf("          ������������\n");
    gotoxy(75, 21);
	printf("          ������������\n");
	gotoxy(75, 22);
	printf("          ������������\n");
}
/*===============================������================================================*/
main()
{
	system("color f0");			//���ÿ���̨Ϊ�׵׺���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ����̨���
	int num;
	score *head=0,*stu=0;
	int choice;
	ConnectDatabase();
	QueryDatabase1();
	system("pause"); 
	menu();
	gotoxy(30,25); 
	scanf("%d",&num);
	while(1)
	{
		switch(num)
		{  
			case 1: head=creat();break;
			case 2: head=load(head);break;
			case 3: head=search(head);break;
			case 4: head=del(head);break;
			case 5: head=add(head,stu);break;
			case 6: print(head);break;
			case 7: save(head);break;		              	
			case 0: exit(0); 
			default:
				SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|FOREGROUND_RED);//����������ɫ��Ϊ��ɫ
				printf("\t\t   ������0~7֮�����!");
			SetConsoleTextAttribute(handle,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);   	//�Ļ�������ɫ���׵׺���			
			getch();
		}
		menu();
		scanf("%d",&num);
	}
}

