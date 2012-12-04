#include"apue.h"
int main()
{
	printf("Program List 3.1\n");
	if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
		printf("cannot seek\n");
	else printf("seek OK\n");
	exit(0);
}
