#include "apue.h"

int glob = 6;
char buf[] = "a write to stdout\n";

int main()
{
	int	var;
       volatile	pid_t	pid,pid2;
	var = 88;
//	setbuf(stdout,NULL);
	if(write(STDOUT_FILENO, buf, sizeof(buf)-1 ) != sizeof(buf)-1 )
		err_sys("write error");
	printf("before fork\n");
	if(((pid = fork()) < 0) )
	err_sys("fork errir");
	else if(pid == 0)
	{
		printf("the pid = fork() returns %d\n",pid);
		glob++;
		var++;
		sleep(10);//the child block itself,when its parent dies after sleep for 2s,the child will be an orphan
			  //then will be adobted by the process init 
	}
	else sleep(2);

	printf("pid = %d, glob = %d,var =%d\n",getpid(),glob,var);
	printf("the pid of parent is getppid = %d\n",getppid());//return the pid of parent of the process
//	printf("the sizeof buf is %d\n",sizeof(buf));
//	printf("the strlen of buf is %d\n",strlen(buf));
	exit(0);
}
