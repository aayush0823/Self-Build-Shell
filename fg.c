#include "function.h"

int fg(char **args,int total)
{

	if(args[1]==NULL)
        {
                fprintf(stderr, "INVALID COMMAND\n");
                return 1;
        }
        int jbid = atoi(args[1]);
        int point=0;
        int cal=0;
        for(int i=0;i<total;i++)
        {
                if(backg[i].flag==1 || backg[i].flag==0)
                        point++;
                if(point==jbid)
                        cal=i;
        }
        if(jbid > point)
        {
                fprintf(stderr, "No such Process Exists\n");
                return 1;
        }

	pid_t wpid;
	printf("%s\n",backg[cal].command);
	int status;
	kill(backg[cal].pid,SIGCONT);
		backg[cal].flag=-1;
	do {
		wpid = waitpid(backg[cal].pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));  

	return 1;
}