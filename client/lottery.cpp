#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

char in_pw[10];		// 신청 및 수령시 직원 체크 페스워드 

struct data{
	int check, lot[6][5];
	char pw[25];
};

data stu[31000];	// 구조체, 학생 

int input_pw();		// 패스워드 입력 
int check_pw();		// 패스워드 확인 
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

//	check_pw() == 1 ? printf("code\n") : printf("end");
	
	printf("%d %s ", stu[1].check, stu[1].pw);
	for(i=1; i<=stu[1].check; i++) printf("%d %d %d %d", stu[1].lot[i][1], stu[1].lot[i][2], stu[1].lot[i][3], stu[1].lot[i][4]);
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
		printf("check\n");
		input_pw();
		if(strcmp(in_pw, "add") == 0) return 1;
		if(strcmp(in_pw, "end") == 0) return 2;
		system("cls");
		printf("비밀번호가 옳지 않습니다.\n");
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

int add()
{
	int gra, cla, num, a, stu_num, f=0;		// grade, class, number	
r_a:
	system("cls");							// 신원 입력 
	if(f == 1) printf("재입력\n");
	printf("학년 \n>> ");
	gra=keynum();
	printf("반 : \n>> ");
	cla=keynum();
	printf("번호 : \n>> ");
	num=keynum();
	
	printf("%d반 %d반 %d번\n확인(Y/N)... ", gra, cla, num);
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
											// 비밀번호 입력
	if(stu[stu_num].check == 0) {
		
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
		system("cls");
		printf(">> %d", n);
	}
	system("cls");
	return n;
}
