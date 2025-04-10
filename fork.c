#include <stdio.h>
#include <unistd.h>


int gval = 10;
int main()
{
	pid_t pid;
	int lval = 20;
	gval++;
	lval +=5;
	pid = fork();
	if(pid == 0) // if child process
		gval += 2, lval += 2;
	else	//if parent process
		gval -= 2, lval -= 2;
	
	if(pid == 0)
		printf("child process: [%d, %d] \n",gval,lval);
	else
		printf("parent process: [%d, %d] \n",gval,lval);
	return 0;
}

