#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

char in_pw[10];		// ��û �� ���ɽ� ���� üũ �佺���� 

struct data{
	int check, num_lot, lot[5];
	char pw[25], lot_temp[15];
};

data stu[31000];	// ����ü, �л� 

int input_pw();		// �н����� �Է� 
int check_pw();		// �н����� Ȯ�� 
int input_file();
int add();
int keynum();

int main()
{
	int i, type, a;
	
	input_file();
	
	while(1)
	{
		type=check_pw();
		switch(type)
		{
			case 1:
				add();
				break;
			default :
				break;
		}
		
		break;
	}

	check_pw() == 1 ? printf("code\n") : printf("end");
	
	printf("%d %s %d ", stu[1].check, stu[1].pw, stu[1].num_lot);
	for(i=1; i<=stu[1].num_lot; i++) printf("%d ", stu[1].lot[i]);
	printf("\n");
	
	return 0;
}

int input_pw()
{
	int a, i, j;		//	a : keycode input
	for(i=0; i<10; i++) in_pw[i] = NULL;
	i=0;
	
	printf("password >> ");
	while(1)
	{
		a=getch();
		if(a == 13) break;
		if(a == 8) in_pw[i--] = NULL;
		else in_pw[i++]=a;
		if(i < 0) i=0;
		system("cls");
		printf("password >> ");
		for(j=1; j<=i; j++) printf("* ");
	}
	
	return 0;
}

int check_pw()
{
	system("cls");
	while(1)
	{
		input_pw();
		if(strcmp(in_pw, "add") == 0) return 1;
		if(strcmp(in_pw, "end") == 0) return 2;
		system("cls");
		printf("��й�ȣ�� ���� �ʽ��ϴ�.\n");
	}
	
	return 0;
}

int input_file()
{
	int i, j;
	
	freopen("student.txt", "r", stdin);
	
	for(i=1; i<=31000; i++)
	{
		scanf("%d %s %d", &stu[i].check, stu[i].pw, &stu[i].num_lot);
		for(j=1; j<=stu[i].num_lot; j++) scanf("%s", stu[i].lot_temp);
	}
	
	fclose(stdin);
	return 0;
}

int add()
{
	int gra, cla, num, a, stu_num, f=0;		//grade, class, number	
r_a:
	system("cls");
	if(f == 1) printf("���Է�\n");
	printf("�г� \n>> ");
	gra=keynum();
	printf("�� : \n>> ");
	cla=keynum();
	printf("��ȣ : \n>> ");
	num=keynum();
	
	printf("%d�� %d�� %d��\nȮ��(Y/N)... ", gra, cla, num);
	while(1)
	{
		a=getch();
		if(a == 121) break;
		else if(a == 110) {
			f=1;
			goto r_a;
		}
	}
	
	system("cls");
	
	stu_num = gra*10000 + cla*100 + num;
	printf("%d\n", stu_num);
	getch();
	
	return 0;
}

int keynum()
{
	int a, n=0;
	while(1)
	{
		a=getch();
		if(a == 13) break;
		if(a == 8) {
			n/=10;
		}
		if(48 <= a && a <= 57) n=n*10+(a-48);
		system("cls");
		printf(">> %d", n);
	}
	system("cls");
	return n;
}
