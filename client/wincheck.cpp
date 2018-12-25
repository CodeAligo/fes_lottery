#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

struct data{
	int pw[25], lot[6][5];	//	pw[0] : password length
};

struct data2{
	int num, lot[5], p1, p2, point;
};

int lottery[5], total;
data stu[4001];
data2 student[3800];

int str_sort(data2 *max)
{
	int i, j;
	data2 t;
	for(i=1; i<=total; i++)
	{
		for(j=i+1; j<=total; j++)
		{
			if(max[i].point < max[j].point)
			{
				t=max[i];
				max[i]=max[j];
				max[j]=t;
			}
		}
	}
}

int lotto_input()
{
	FILE *fi = fopen("lottery.txt", "r");
	fscanf(fi, "%d %d %d %d", &lottery[1], &lottery[2], &lottery[3], &lottery[4]);
	fclose(fi);
}

int student_input()			// 추후에 간략히. 최적화 
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

int main()
{
	lotto_input();
	student_input();
	
	int i, j, k, a;
	
	a=0;
	for(i=1000; i<=4000; i++)				// student 배열로 이동 
	{
		for(j=1; j<=stu[i].lot[0][0]; j++) 
		{
			student[++a].num = i;
			for(k=1; k<=4; k++) student[a].lot[k] = stu[i].lot[j][k];
		}
	}
	
	for(k=1; k<=total; k++)			// 일치 확인 
	{
		for(i=1; i<=4; i++)
			for(j=i; j<=4; j++)
				if(lottery[i] == student[k].lot[j]) {
					student[k].p1++;
					if(i==j) student[k].p2++;
				}
		student[k].point = student[k].p1*2 + student[k].p2;
	}
	
	for(i=1; i<=4; i++) printf("%d ", lottery[i]);
	printf("\n");
	str_sort(student);
	for(i=1; i<=total; i++) printf("%3d : %2d %2d %2d %2d  - %d %d\n", student[i].num, student[i].lot[1], student[i].lot[2], student[i].lot[3], student[i].lot[4], student[i].p1, student[i].p2);
	getch();
	getch();
	return 0;
}
