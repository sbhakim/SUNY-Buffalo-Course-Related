#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	
	char *args[]={"./exec", NULL};

	printf ("The pid of execDemo is %ld\n", (long) getpid());
	
	execvp (args[0], args);
	

	/* All statements are ignored after execvp() call as this whole process(execDemo.c) is replaced by another process (EXEC.c)*/

	printf ("\n-----Ending------\n");
	

	return 0;
}
