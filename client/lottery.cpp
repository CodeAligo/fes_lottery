#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

struct data{
	int check, pw[25], lot[6][5];
};

char staff[30];
data stu[4001];

int file_input();
int print(int type);
int input();

int main()
{
	printf("<input>\n");
	printf("staff.. ");
	scanf("%s", staff);
	
	file_input();
	
	int mode;
	
	print(1);
	
	while(1)
	{
		mode = input();
		if(mode == 0) print(1);
		else if(mode == 65 || mode == 97) {
			printf("Join");
			break;
		}
		else if(mode == 66 || mode == 98) {
			printf("Lottery");
			break;
		}
		
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
	system("cls");
	printf("[ staff : %s ]\n\n", staff);
	
	switch(type)
	{
		case 1: 
			printf("MODE\n    a. Join\n    b. Lottery\n\n>> ");
			break;
		default:
			break;
	}
	
}

int input()
{
	int a;
	a = getch();
	printf("%c", a);
	
	if (a == 13) return a;
	if (a == 8) return 0;
}
