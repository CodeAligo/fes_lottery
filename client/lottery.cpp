#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

char in_pw[10], staff[25];		// ��û �� ���ɽ� ���� üũ �佺���� 

struct data{
	int check, lot[6][5];
	char pw[25], pw_t[25];	// password, password_temp
};

data stu[31000];	// ����ü, �л� 

int clr()
{
	system("cls");
	printf("[staff : %s]\n\n", staff);
}
 
int input_pw(char k[]);		// �н����� �Է� 
int check_pw();		// �н����� Ȯ�� 
int input_file();
int add_lot();
int keynum();
int add_pw(int stu_num);

int main()
{
	int i, type;
	
	printf("staff\n>> ");
	scanf("%s", staff);
	clr();
	
	input_file();
	
	while(1)
	{
		type=check_pw();
		
		switch(type)
		{
			case 1:
				add_lot();
				break;
			default :
				break;
		}
		
		break;
	}

//	check_pw() == 1 ? printf("code\n") : printf("end");
	
	printf("\n");
	
	return 0;
}

int input_pw(char k[])
{
	int a, i, j;		//	a : keycode input
	for(i=0; i<strlen(k); i++) k[i] = NULL;
	i=0;
	
	printf("password >> ");
	while(1)
	{
		a=getch();
		if(a == 13) break;
		if(a == 8) k[i--] = NULL;
		else k[i++]=a;
		if(i <= 0) i=0;
		clr();
		printf("password >> ");
		for(j=1; j<=i; j++) printf("* ");
	}
	
	return 0;
}

int check_pw()
{
	clr();
	while(1)
	{
		printf("check\n");
		input_pw(in_pw);
		if(strcmp(in_pw, "add") == 0) return 1;
		if(strcmp(in_pw, "signup") == 0) return 2;
		if(strcmp(in_pw, "change") == 0) return 3;
		if(strcmp(in_pw, "end") == 0) return 4;
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
		scanf("%d %s", &stu[i].check, stu[i].pw);
		for(j=1; j<=stu[i].check; j++) scanf("%d %d %d %d", &stu[i].lot[i][1], &stu[i].lot[i][2], &stu[i].lot[i][3], &stu[i].lot[i][4]);
	}
	
	fclose(stdin);
	return 0;
}

int add_lot()
{
	int gra, cla, num, a, stu_num, f=0, i;		// grade, class, number	
	do {
		clr();							// �ſ� �Է� 
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
			if(a == 121) f=0;
			else if(a == 110) f=1;
			if(a == 121 || a == 110) break;
		}
		
	} while(f == 1);
	
	clr();
	
	stu_num = gra*10000 + cla*100 + num;
	printf("%d\n", stu_num);
											// ��й�ȣ �Է�
	if(stu[stu_num].check == 0) {
		printf("����� �ʿ��մϴ�.\n========================\n");
		add_pw(stu_num);
	}
	
	clr();
	input_pw(stu[stu_num].pw_t);
	clr();
	
	if(strcmp(stu[stu_num].pw, stu[stu_num].pw_t) == 0) {
		a = ++stu[stu_num].check;
		for(i=1; i<=4; i++)	{
			printf("�ζ� : ");
			stu[stu_num].lot[a][i] = keynum();
		}
		clr(); 
		printf("%d�г� %d�� %d�� \n>>%3d %3d %3d %3d", gra, cla, num, stu[stu_num].lot[a][1], stu[stu_num].lot[a][2], stu[stu_num].lot[a][3], stu[stu_num].lot[a][4]);
	}
	
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
		clr();
		printf(">> %d", n);
	}
	clr();
	return n;
}

int add_pw(int stu_num)
{
	printf("\n��й�ȣ ����\n");
	while(1)
	{
		input_pw(stu[stu_num].pw_t);
		printf("\n��й�ȣ ��Ȯ��...\n");
		input_pw(stu[stu_num].pw);
	
		if(strcmp(stu[stu_num].pw, stu[stu_num].pw_t) == 0) {
			printf("\nȮ��\n");
			break;
		}
		clr();
		if(strcmp(stu[stu_num].pw, stu[stu_num].pw_t) != 0) printf("\n��ġ���� ����, �缳��...\n");
	}
	
	return 0;
}
