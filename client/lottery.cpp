#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

char in_pw[10];		// 신청 및 수령시 직원 체크 페스워드 

struct data{
	int num, lot_n=0, lot[5];
	char pw[25];
};

data stu[31000];	// 구조체, 학생 

int input_pw();		// 패스워드 입력 
int check_pw();		// 패스워드 확인 
int input_file();

int main()
{

	input_file();
	
/*	while(1)
	{
		switch(check_pw())
			case 1:
				
			default :
				break;
	}*/

	check_pw() == 1 ? printf("code\n") : printf("end");
	
	printf("%d %s %d %d %d %d\n", stu[1].num, stu[1].pw, stu[1].lot[0], stu[1].lot[1], stu[1].lot[2], stu[1].lot[3]);
	
	return 0;
}

int input_pw()
{
	int a, i, j;		//	a : keycode input
	for(i=0; i<10; i++) in_pw[i] = NULL;
	
	i=0;
	while(1)
	{
		a=getch();
		if(a == 13) break;
		if(a == 8) {
			system("cls");
			in_pw[i--] = NULL;
			for(j=1; j<=i; j++) printf("* ");
		}
		printf("* ");
		in_pw[i++]=a;
	}
	
	return 0;
}

int check_pw()
{
	system("cls");
	while(1)
	{
		printf(">> ");
		input_pw();
		if(strcmp(in_pw, "code") == 0) return 1;
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
		scanf("%d %s %d", &stu[i].num, stu[i].pw, &stu[i].lot_n);
	}
	fclose(stdin);
	
	return 0;
}
