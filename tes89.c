#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <signal.h>


void quit(int signo)
{
	printf("signo: %d\n", signo);
}

void main(void) 
{ 
    FILE *fp; 
    pid_t pid; 
    struct  sigaction  act;
  //  exit(-1); 
    act.sa_handler = quit; 
    act.sa_flags   = 0; 
    sigemptyset(&act.sa_mask); 
    sigaction(SIGTERM,&act,NULL); 
    sigaction(SIGHUP,&act,NULL); 
    sigaction(SIGINT,&act,NULL); 
    sigaction(SIGQUIT,&act,NULL); 
    sigaction(SIGUSR1,&act,NULL); 
    sigaction(SIGUSR2,&act,NULL); 
for (;;) { 
      sleep(3); 
    } 
  } 
