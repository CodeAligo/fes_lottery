#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

int d[40];

int main()
{
	FILE *fo = fopen("lottery.txt", "w");
	int i, a;
	srand(time(0));
	for(i=1; i<=4; i++)
	{
		a = rand()%35+1;
		if(d[a] == 1) {
			i--;
			continue;
		}
		d[a]=1;
	}
	
	for(i=1; i<=35; i++) if(d[i]) fprintf(fo, "%d ", i);
	printf("\n\n      ********************************\n      * 로또 번호가 추첨 되었습니다! *\n      ********************************\n\n\n");
	getch();
	fclose(fo);
	return 0;
}
