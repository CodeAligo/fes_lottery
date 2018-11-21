#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main()
{
	FILE *fp = fopen("student.txt", "w");
	for(int i=1; i<=4000; i++) fprintf(fp, "0 0\n");
	fclose(fp);
	
	printf("¿Ï·á");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(1000);
	printf("!");
	Sleep(500);
	getch();
	return 0;
}
