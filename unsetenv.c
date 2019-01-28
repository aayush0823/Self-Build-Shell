#include "function.h"
int unset_env(char** args)
{
	if(args[1] == NULL){
		fprintf(stderr, "NO VARIABLE TO UNSET\n");
		return 1;
	}

	if(unsetenv(args[1])!=0)
		perror("Error: ");
	return 1;
}