#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (){

	int i;

	printf ("\nI am exec.c program called by execvp() \n");
	printf ("The pid of exec.c is %ld\n", (long) getpid());
	printf ("Ignored the Ending --- of  the program execDemo.c\n");

	return 0;
}




