#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

char pass[10];

struct data{
	int stu, lot[5];
	char pass[25];
};

int in_pass();

int main()
{
	data stu[31000];
	int i, j, con, t;
	char in[100];
	FILE *fp = fopen("student.txt", "r");
	
	if(fp == NULL) {
		fprintf(stdout, "파일을 열지 못했습니다.");
		getch();
		exit(1);
	}
	
	for(i=1; i<=31000; i++)
	{
		fscanf(fp, "%[^\n]s", in);
		con=t=0;
		for(j=0; j<strlen(in); j++)
		{
			if(in[j+1] == ' '){
				switch(con)
				{
					case 0:
						stu[i].stu = t;
						break;
					case 3:
						stu[i].lot[con-3] = t;
				}
			}
		}
	}

	fclose(fp);
	
	system("cls");
	while(1)
	{
		printf(">> ");
		in_pass();
		if(strcmp(pass, "code") == 0) {
			printf("%s", pass);		// 후에 변경 필요 
			break;
		}
		if(strcmp(pass, "end") == 0){
			printf("%s", pass);		// 후에 변경 필요
			break;
		}
		system("cls");
		printf("비밀번호가 옳지 않습니다.\n");
	}

	return 0;
}

int in_pass()
{
	int a, i;
	for(i=0; i<10; i++) pass[i] = NULL;
	i=0;
	while(1)
	{
		a=getch();
		if(a==13) break;
		printf(" *");
		pass[i++]=a;
	}
	return 0;
}
