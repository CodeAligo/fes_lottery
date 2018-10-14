#include <stdio.h>

int main()
{
	freopen("student.txt", "w", stdout);
	for(int i=1; i<=4000; i++) printf("0 0\n");
}
