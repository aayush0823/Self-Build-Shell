#include "function.h"
int set_env(char ** args){

	if(args[1] == NULL){
		fprintf(stderr, "NO VARIABLE TO SET\n");
		return 1;
	}

	if(getenv(args[1])==NULL || args[2]==NULL) 
		setenv(args[1],"",1);

	setenv(args[1],args[2],1);
	return 1;
}