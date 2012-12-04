#include "apue.h"

int glob = 6;
char buf[] = "a write to stdout\n";

int
main ()
{
  int var;
  volatile pid_t pid, pid2;

var = 88;
  printf ("before vfork\n");

  if (((pid = vfork ()) < 0))
    err_sys ("vfork errir");
  else if (pid == 0)
    {
      glob++;
      var++;
      printf ("pid = %d, glob = %d,var =%d\n", getpid (), glob, var);
      _exit (0);
    }

  printf ("pid = %d, glob = %d,var =%d\n", getpid (), glob, var);
  exit (0);
}
