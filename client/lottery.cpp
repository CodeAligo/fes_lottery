#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

using namespace std;

struct data{
	int pw[25], lot[6][5];	//	pw[0] : password length
};

int stu_num, checkpw[25]={0, }, checkpw_s=0, add_n=0, total=0, time;
char staff[30];
data stu[4001];

int file_input();
int file_output();
int print(int type);
int input_one();
int input_num(int type);
int check_student();
int add_num();
int add_pw();
int check_pw();
int add_cipher(int n);

int main()
{
	printf("<input>\n");
	printf("time.. ");
	scanf("%d", &time); 
	system("cls");
	printf("<input>\n");
	printf("staff.. ");
	scanf("%s", staff);
	
	file_input();
	
	int mode, i, log_con;
	char a;
	
	while(1)
	{
		log_con=0;
		while(1)
		{
			check_student();
			if(stu[stu_num].pw[0] == 0) add_pw();
			else break;
		}
		file_output();
		
		for(i=1; i<=3; i++)		// 비밀번호 체크 
		{
			if(check_pw()) {
				log_con = 1;
				print(12);
				break;
			}
			else print(9);
			Sleep(1000);
		}
		if(log_con == 0) {
			print(11);
			continue; 
		}	
		
/*		printf("\n");
		for(i=1; i<=stu[stu_num].pw[0]; i++) printf("%c", stu[stu_num].pw[i]);
		printf("\n");
		for(i=1; i<=checkpw_s; i++) printf("%c", checkpw[i]);
		getch();*/
		
		file_output();
		
		print(1);
		mode = input_one();
		
		if(mode == 65 || mode == 97) {
			print(10);
			print(13);
			printf("\n	다음으로 넘어가려면 아무 키나 누르세요.");
			getch();
			add_n=0;
			add_num();
		}
		else if(mode == 66 || mode == 98) {
			print(10);
			printf("PW");
		}
		else print(1);
		
		file_output();
		Sleep(1000);
	}
	
	return 0;
}

int file_input()
{
	FILE *fi = fopen("student.txt", "r");
	int i, j;
	fscanf(fi, "%d", &total);
	for(i=1; i<=4000; i++)
	{
		fscanf(fi, "%d %d", &stu[i].lot[0][0], &stu[i].pw[0]);
		for(j=1; j<=stu[i].pw[0]; j++) fscanf(fi, "%d", &stu[i].pw[j]);
		for(j=1; j<=stu[i].lot[0][0]; j++) fscanf(fi, "%d %d %d %d", &stu[i].lot[j][1], &stu[i].lot[j][2], &stu[i].lot[j][3], &stu[i].lot[j][4]);
	}
	fclose(fi);
}

int file_output()
{
	FILE *fo = fopen("student.txt", "w");
	int i, j;
	fprintf(fo, "%d\n", total);
	for(i=1; i<=4000; i++)
	{
		fprintf(fo, "%d ", stu[i].lot[0][0]);
		for(j=0; j<=stu[i].pw[0]; j++) fprintf(fo, "%d ", stu[i].pw[j]);
		for(j=1; j<=stu[i].lot[0][0]; j++) fprintf(fo, "%d %d %d %d ", stu[i].lot[j][1], stu[i].lot[j][2], stu[i].lot[j][3], stu[i].lot[j][4]);
		fprintf(fo, "\n");
	}
	fclose(fo);
}

int print(int type)
{
	int i, j;
	
	if(type == 15) {
		printf("\n");
		for(i=add_n+2; i<=4; i++) printf("  (%d) : \n", i);
		return 0;
	}
	
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
			printf("<패스워드>\n\n패스워드 설정\n4자리 이상  20자리 이하의 숫자 또는 영문자로 구성된 패스워드 입력\n>> ");
			for(i=1; i<=stu[stu_num].pw[0]; i++) printf("* ");		
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
		case 9:
			print(7);
			printf("\n\n<!!> 틀렸습니다.\a\n");
			Sleep(1000);
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
		case 11:
			print(7);
			printf("\n\n<!!> 3회 틀렸습니다. 잠시 후 로그인 화면으로 돌아갑니다.\a\n");
			Sleep(1500);
			print(10);
			break;
		case 12:
			print(7);
			printf("\n\n로그인 확인.\n");
			Sleep(1000);
			print(10);
			break;
		case 13:	// 로또 확인 
			printf("<로또>\n\n");
			if(stu[stu_num].lot[0][0] == 0) printf("\n	등록된 로또가 없습니다.\n\n\n");
			
			for(i=1; i<=stu[stu_num].lot[0][0]; i++)
			{
				printf("  [ %d ]\n", i);
				printf("  =========================\n");
				printf("  ");
				for(j=1; j<=4; j++) printf("|  %d  ", j);
				printf("|\n");
				printf("  -------------------------\n");
				printf("  ");
				for(j=1; j<=4; j++) stu[stu_num].lot[i][j]<10?printf("| %2d  ", stu[stu_num].lot[i][j]):printf("| %3d ", stu[stu_num].lot[i][j]);
				printf("|\n");
				printf("  =========================\n\n\n");
			}
			break;
		case 14: 	// 로또 입력 
			printf("<로또>\n\n");
			for(i=1; i<=add_n; i++) printf("  (%d) : %d\n", i, stu[stu_num].lot[stu[stu_num].lot[0][0]+1][i]);
			printf("  (%d) : ", add_n+1);
			break;
		case 16:	// 로또 에러 
			printf("<로또>\n\n");
			for(i=1; i<=add_n; i++) printf("  (%d) : %d\n", i, stu[stu_num].lot[stu[stu_num].lot[0][0]+1][i]);
			for(i=add_n+1; i<=4; i++) printf("  (%d) : \n", i);
			printf("\n\n	<!!> 번호 형식이 잘못 되었습니다.\a\n");
			break;
		case 17:	// 로또 최대 
			printf("<로또>\n\n\n	<!!> 로또를 5개 구매하셨습니다.\n	  최대 개수만큼 구매하여 더 이상 구매 하실 수 없습니다.\n\n");
			break;
		default:
			break;
	}
	
}

int input_one()
{
	int a;
	while(1)
	{
		a = getch();
		if((65 <= a && a <= 90) || (97 <= a && a <= 122)) return a;
	}
}

int input_num(int type)
{
	int a, k=0;
	print(type);
	if(type == 14) print(15);
	while(1)
	{
		a = getch();
		if(a == 8) k = k/10;
		else if(a == 13 && k!=0) return k;
		else if(48 <= a && a <= 57) k = k*10 + (a-48);
		print(type);
		k == 0 ? printf(" ") : printf("%d", k);
		if(type == 14) print(15);
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
	int a, i, j, f=1, t, codea=0, codeb=0;
	if(stu[stu_num].lot[0][0] == 5) {
		for(i=3; i>=1; i--)
		{
			print(17);
			printf("%d초 후 로그인 창으로 넘어갑니다.", i);
			Sleep(1000);
		}
	}
	print(14);
	print(15);
	while(1)
	{
		a = input_num(14);
		if(a == 0) {
			f=0;
			break;
		}
		else if(0 > a || a > 35) print(16);
		else stu[stu_num].lot[stu[stu_num].lot[0][0]+1][++add_n] = a;
		Sleep(500);
		if(add_n == 4) break;
	}
	
	for(i=1; i<=4; i++)
	{
		for(j=i; j<=4; j++)
		{
			if(stu[stu_num].lot[stu[stu_num].lot[0][0]+1][i] > stu[stu_num].lot[stu[stu_num].lot[0][0]+1][j]) { 
				t = stu[stu_num].lot[stu[stu_num].lot[0][0]+1][i]; 
				stu[stu_num].lot[stu[stu_num].lot[0][0]+1][i] = stu[stu_num].lot[stu[stu_num].lot[0][0]+1][j];
				stu[stu_num].lot[stu[stu_num].lot[0][0]+1][j] = t;
				
			}
		}
	}
	
	for(i=1; i<=4; i++){
		if(stu[stu_num].lot[stu[stu_num].lot[0][0]+1][i] == stu[stu_num].lot[stu[stu_num].lot[0][0]+1][i-1]) {
			
			add_n = 0;
			printf("\n\n	두 개 이상의 숫자가 같으면 안됩니다!\a\n");
			Sleep(1000);
			add_num();
			return 0;
		}
	}
	
	if(f) {
		stu[stu_num].lot[0][0]++;
		total++;
		file_output();
	
		codea = (stu_num/1000)*100000 + ((stu_num/100)%10)*1000 + add_cipher(add_cipher(stu_num))*100 + stu_num%100 ;
		printf("        code A : %d.%d\n        code B : ", codea, total);
		for(i=1; i<=4; i++) 
		{
			if(stu[stu_num].lot[stu[stu_num].lot[0][0]][i] < 10) printf("0");
			printf("%d", stu[stu_num].lot[stu[stu_num].lot[0][0]][i]);
			codeb += (add_cipher(stu[stu_num].lot[stu[stu_num].lot[0][0]][i])*(9-i));
		}
		codeb += (time * 4);
		codeb = (11-(((codeb/7)+(codeb%7))%11))%10;
		printf("%d%d", time, codeb);
		
		printf("\n\n\n    아무 키를 누르십시오.");
		getch();
	}
	
	for(i=3; i>=1; i--)
	{
		print(13);
		printf("%d초 후 로그인 창으로 넘어갑니다.", i);
		Sleep(1000);
	}
	
	return 0;
}

int add_pw()
{
	int i, a=0;
	print(6);
	while(1)
	{
		a=getch();
		if(a == 13) break;
		if(a == 8) stu[stu_num].pw[0]--;
		else {
			stu[stu_num].pw[0]++;
			stu[stu_num].pw[stu[stu_num].pw[0]] = a;
		}
		if(stu[stu_num].pw[0] <= 0) stu[stu_num].pw[0] = 0; 
		print(6);
	}
	
	for(i=3; i>=1; i--)
	{
		print(6);
		printf("\n\n저장되었습니다. %d초 후 로그인 창으로 넘어갑니다.", i);
		Sleep(1000);
	}
	
	file_output();
	print(10);
}

int check_pw()
{
	int a, i, f=0;
	checkpw_s = 0;
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
	
	for(i=1; i<=stu[stu_num].pw[0]; i++)
	{
		if(checkpw[i] == stu[stu_num].pw[i]) f=1;
		else {
			f=0;
			break;
		}
	}
	
	return f;			// f=1 : 패스워드 일치, f=0 : 패스워드 불일치  
}

int add_cipher(int n)
{
	int a = 0;
	while(1)
	{
		a+=(n%10);
		n/=10;
		if(n == 0) break;
	}
	return a;
}
