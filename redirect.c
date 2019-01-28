#include "function.h"
char inputfile[100];
char outputfile[100];
void redirect(char **args,int inp,int outp,int outpa)
{
	char *com[100];
	int ignore=0;
	int point=0;
	for(int i=0;args[i]!=NULL;i++)
	{
		if(strcmp(args[i],">")==0 || strcmp(args[i],">>")==0)
		{
			ignore=1;
			if(args[i+1]!=NULL)
				strcpy(outputfile,args[i+1]);
			else
				printf("NO OUTPUT FILE SPECIFIED\n");
		}
		else if(strcmp(args[i],"<")==0)
		{
			ignore=1;
			if(args[i+1]!=NULL)
				strcpy(inputfile,args[i+1]);
			else
				printf("NO INPUT FILE SPECIFIED\n");
		}
		if(!ignore)
			com[point++]=args[i];
	}
	com[point]=NULL;
	if(inp)
	{
		int ii=dup(0);
		int input = open(inputfile,O_RDONLY);
		dup2(input,0);
		close(input);
		int oo,output;
		if(outp+outpa)
		{
			oo=dup(1);
			if(outp)
				output = open(outputfile,O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				output = open(outputfile,O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(output,1);
			close(output);
		}
		int pid = fork();
		int status;
		pid_t wpid;
		if(pid == 0)
			execvp(com[0],com);
		else
		{
			do {
					wpid = waitpid(pid, &status, WUNTRACED);
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		dup2(ii,0);
		close(ii);
		dup2(oo,1);
		close(oo);
	}
	else
	{
		int oo=dup(1);
		int output;
		if(outp)
			output = open(outputfile,O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			output = open(outputfile,O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(output,1);
		close(output);
		int pid = fork();
		int status;
		pid_t wpid;
		if(pid == 0)
			execvp(com[0],com);
		else
		{
			do {
					wpid = waitpid(pid, &status, WUNTRACED);
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		dup2(oo,1);
		close(oo);
	}
	return;
}