#include "function.h"
void bgreturn(char ** args ,int in)
{
	int status;
	pid_t wpid;
	wpid=waitpid(-1,&status,WNOHANG);
	if(wpid)
	{
		if(WIFEXITED(status))
		{
			for(int i=0;i<in;i++)
			{
				if(backg[i].pid == wpid && backg[i].flag==1)
				{
					printf("[%d]+ Done\t\t\t%s pid %d\n",backg[i].pid,backg[i].command,wpid);
					backg[i].flag=-1;
				}
			}
		}
	}
	for(int i=0;i<in;i++)
	{
		if(backg[i].flag==-2)
		{
			printf("Process\t%s killed with pid %d\n",backg[i].command,backg[i].pid);
			backg[i].flag=-1;
		}
	}
	return;
}