#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

struct data{
	int check, pw[25], lot[6][5], pw_l=0;
};

int stu_num, checkpw[25]={0, }, checkpw_s=0;
char staff[30];
data stu[4001];

int file_input();
int print(int type);
int input_one();
int input_num(int type);
int check_student();
int add_num();
int add_pw();
int check_pw();

int main()
{
	printf("<input>\n");
	printf("staff.. ");
	scanf("%s", staff);
	
	file_input();
	
	int mode, i;
	
	while(1)
	{
		check_student();
		
		if(stu[stu_num].pw_l == 0) {
			add_pw();
			check_student();
		}
		
		check_pw(); 
		
		printf("\n");
		for(i=1; i<=stu[stu_num].pw_l; i++) printf("%c", stu[stu_num].pw[i]);
		getch();
		
		print(1);
		mode = input_one();
		if(mode == 0) print(1);
		else if(mode == 65 || mode == 97) {
			print(10);
			add_num();
			break;
		}
		else if(mode == 66 || mode == 98) {
			print(10);
			printf("Lottery");
			break;
		}
		Sleep(1000);
	}
	
	return 0;
}

int file_input()
{
	int i, j;
	freopen("student.txt", "r", stdin);
	for(i=1; i<=4000; i++)
	{
		scanf("%d %d", &stu[i].check, &stu[i].pw[0]);
		for(j=1; j<=stu[i].pw[0]; j++) scanf("%d", &stu[i].pw[j]);
	}
	fclose(stdin);
}

int print(int type)
{
	int i;
	
	system("cls");
	printf("[ staff : %s ]\n\n", staff);
	
	switch(type)
	{
		case 1:		//모드 입력 
			printf("모드\n    a. 로또 입력\n    b. 패스워드 변경\n\n>> ");
			break;
		case 2:		// 로그인, 학년 입력 
			printf("<로그인>\n\n학년 >> ");
			break;
		case 3:		// 로그인, 반 입력 
			printf("<로그인>\n\n반 >> ");
			break;
		case 4:		// 로그인, 번호 입력 
			printf("<로그인>\n\n번호 >> ");
			break;
		case 5:		// 로그인, 최종 확인
			printf("<로그인>\n\n    학년 : %d\n      반 : %d\n    번호 : %d\n\n확인(\'Y\'es/\'N\'o).. ", stu_num/1000, (stu_num%1000)/100, stu_num%100);
			break;
		case 6:		// 신규, 패스워드 설정 
			printf("<패스워드>\n\n패스워드 설정\n4자리 이상의 숫자 또는 영문자로 구성된 패스워드 입력\n>> ");
			for(i=1; i<=stu[stu_num].pw_l; i++) printf("* ");		
			break;
		case 7:		// 로그인,  패스워드 입력 
			printf("<로그인>\n\n\ 패스워드 >> ");
			for(i=1; i<=checkpw_s; i++) printf("* ");
			break;
		case 8:
			printf("<!!> 비밀번호 설정이 필요합니다");
			Sleep(1000);
			print(10);
			break;
		case 10:	// 조건 성립 확인용 
			printf("    ");
			for(i=1; i<=4; i++)
			{ 
				Sleep(150);
				printf("□");
			}
			Sleep(500);
			printf("■");
			Sleep(500);
			break;
		default:
			break;
	}
	
}

int input_one()
{
	int a;
	a = getch();
	if(a == 8) return 0;
	printf("%c", a);
	return a;
}

int input_num(int type)
{
	int a, k=0;
	print(type);
	while(1)
	{
		a = getch();
		if(a == 8) k = k/10;
		else if(a == 13) return k;
		else if(48 <= a && a <= 57) k = k*10 + (a-48);
		print(type);
		k == 0 ? printf(" ") : printf("%d", k);
	}
}

int check_student()
{
	int gra, cla, num, check, f;
	
	while(1)
	{
		f=0;
		gra = input_num(2);
		cla = input_num(3);
		num = input_num(4);
		
		stu_num = gra*1000 + cla*100 + num;
			
		while(1)
		{
			print(5);	
			check = input_one();
			if(check == 89 || check == 121) {
				f = 1;
				break;
			}
			else if(check == 78 || check == 110) break;
		}
		
		if(f) {
			print(10);
			break;
		}
	}
}

int add_num()
{
	
}

int add_pw()
{
	int i, a=0;
	print(6);
	while(1)
	{
		a=getch();
		if(a == 13) break;
		if(a == 8) stu[stu_num].pw_l--;
		else {
			stu[stu_num].pw_l++;
			stu[stu_num].pw[stu[stu_num].pw_l] = a;
		}
		if(stu[stu_num].pw_l <= 0) stu[stu_num].pw_l = 0; 
		print(6);
	}
	
	for(i=3; i>=1; i--)
	{
		print(6);
		printf("\n\n저장되었습니다. %d초 후 로그인 창으로 넘어갑니다.", i);
		Sleep(1000);
	}
	
	
	print(10);
}

int check_pw()
{
	int a;
	
	print(7);
	while(1)
	{
		a = getch();
		if(a == 13) break;
		if(a == 8) checkpw_s--;
		else {
			checkpw_s++;
			checkpw[checkpw_s] = a;
		}
		if(checkpw_s < 0) checkpw_s=0;
		print(7);
	}
	return 0;
}
