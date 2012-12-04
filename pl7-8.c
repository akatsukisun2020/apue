#include"apue.h"

#if defined(BSD) || defined(MACOS)

#include<sys/time.h>
#define FMT "%1011d	"
#else 
#define FMT "%101d	"

#endif

#include <sys/resource.h>
#define doit(name) pr_limits(#name, name)

static void pr_limits(char *,int);

int main()
{
	printf("Program List 7-8\n");
	doit(RLIMIT_CORE);
	doit(RLIMIT_CPU);
	doit(RLIMIT_DATA);
	doit(RLIMIT_FSIZE);
	doit(RLIMIT_DATA);
	doit(RLIMIT_MEMLOCK);
	exit(0);
}

static void pr_limits(char *name,int resource)
{
	struct rlimit limit;

	if(getrlimit(resource, &limit) < 0)
		err_sys("getrlimit error for %s",name);
	printf("%s",name);
	if(limit.rlim_cur == RLIM_INFINITY)
		printf("(infinite)	");
	else
		printf(FMT, limit.rlim_cur);
	
	if(limit.rlim_max == RLIM_INFINITY)
		printf("(infinite)	");
	else
		printf(FMT,limit.rlim_max);
	
	putchar((int)'\n');
}

