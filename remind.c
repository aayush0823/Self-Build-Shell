#include "function.h"
int remind(char **args)
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		printf("\033[0;32mCannot Create Child Process\033[0m\n");
	}
	else if(pid==0)
	{
		sleep(atoi(args[1]));
		int j=3;
		char message[10000];
		strcpy(message,args[2]);
		while(args[j]!=NULL)
		{
			strcat(message,args[j++]);
		}
		printf("\n\033[0;31mReminder:\033[0m %s\n",message);
	}
	else
	{
		printf("REMINDER SET\n");
	}
	return 1;
}