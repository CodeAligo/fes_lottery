#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

struct data{
	int check, pw[25], lot[6][5];	//	pw[0] : password length
};

int stu_num, checkpw[25]={0, }, checkpw_s=0;
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

int main()
{
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
		
		for(i=1; i<=3; i++)		// ��й�ȣ üũ 
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
		
		print(13);
		Sleep(10000);
		
		file_output();
		
		print(1);
		mode = input_one();
		
		if(mode == 65 || mode == 97) {
			print(10);
			printf("Lottery");
			//add_num();
			break;
		}
		else if(mode == 66 || mode == 98) {
			print(10);
			printf("PW");
			break;
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
	for(i=1; i<=4000; i++)
	{
		fscanf(fi, "%d %d", &stu[i].check, &stu[i].pw[0]);
		for(j=1; j<=stu[i].pw[0]; j++) fscanf(fi, "%d", &stu[i].pw[j]);
		for(j=1; j<=stu[i].check; j++) fscanf(fi, "%d %d %d %d", &stu[i].lot[1], &stu[i].lot[2], &stu[i].lot[3], &stu[i].lot[4]);
	}
	fclose(fi);
}

int file_output()
{
	FILE *fo = fopen("student.txt", "r+");
	int i, j;
	for(i=1; i<=4000; i++)
	{
		fprintf(fo, "%d ", stu[i].check);
		for(j=0; j<=stu[i].pw[0]; j++) fprintf(fo, "%d ", stu[i].pw[j]);
		for(j=1; j<=stu[i].check; j++) fprintf(fo, "%d %d %d %d ", stu[i].lot[1], stu[i].lot[2], stu[i].lot[3], stu[i].lot[4]);
	}
	fclose(fo);
}

int print(int type)
{
	int i, j;
	
	system("cls");
	printf("[ staff : %s ]\n\n", staff);
	
	switch(type)
	{
		case 1:		//��� �Է� 
			printf("���\n    a. �ζ� �Է�\n    b. �н����� ����\n\n>> ");
			break;
		case 2:		// �α���, �г� �Է� 
			printf("<�α���>\n\n�г� >> ");
			break;
		case 3:		// �α���, �� �Է� 
			printf("<�α���>\n\n�� >> ");
			break;
		case 4:		// �α���, ��ȣ �Է� 
			printf("<�α���>\n\n��ȣ >> ");
			break;
		case 5:		// �α���, ���� Ȯ��
			printf("<�α���>\n\n    �г� : %d\n      �� : %d\n    ��ȣ : %d\n\nȮ��(\'Y\'es/\'N\'o).. ", stu_num/1000, (stu_num%1000)/100, stu_num%100);
			break;
		case 6:		// �ű�, �н����� ���� 
			printf("<�н�����>\n\n�н����� ����\n4�ڸ� �̻�20�ڸ� ������ ���� �Ǵ� �����ڷ� ������ �н����� �Է�\n>> ");
			for(i=1; i<=stu[stu_num].pw[0]; i++) printf("* ");		
			break;
		case 7:		// �α���,  �н����� �Է� 
			printf("<�α���>\n\n\ �н����� >> ");
			for(i=1; i<=checkpw_s; i++) printf("* ");
			break;
		case 8:
			printf("<!!> ��й�ȣ ������ �ʿ��մϴ�");
			Sleep(1000);
			print(10);
			break;
		case 9:
			print(7);
			printf("\n\n<!!> Ʋ�Ƚ��ϴ�.\a\n");
			Sleep(1000);
			break;
		case 10:	// ���� ���� Ȯ�ο� 
			printf("    ");
			for(i=1; i<=4; i++)
			{ 
				Sleep(150);
				printf("��");
			}
			Sleep(500);
			printf("��");
			Sleep(500);
			break;
		case 11:
			print(7);
			printf("\n\n<!!> 3ȸ Ʋ�Ƚ��ϴ�. ��� �� �α��� ȭ������ ���ư��ϴ�.\a\n");
			Sleep(1500);
			print(10);
			break;
		case 12:
			print(7);
			printf("\n\n�α��� Ȯ��.\n");
			Sleep(1000);
			print(10);
			break;
		case 13:	// �ζ� Ȯ�� 
			printf("<�ζ�>\n\n");
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
		case 14: 	// �ζ� �Է� 
			
		default:
			break;
	}
	
}

int input_one()
{
	int a, b;
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
	while(1)
	{
		a = getch();
		if(a == 8) k = k/10;
		else if(a == 13 && k!=0) return k;
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
	
	file_output();
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
		printf("\n\n����Ǿ����ϴ�. %d�� �� �α��� â���� �Ѿ�ϴ�.", i);
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
	
	return f;			// f=1 : �н����� ��ġ, f=0 : �н����� ����ġ  
}
