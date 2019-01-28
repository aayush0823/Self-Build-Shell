#include "function.h"
int jobs(char ** args,int total)
{
	int point=1;
	for(int i=0;i<total;i++)
	{
		if(backg[i].flag==1)
		{
			printf("[%d]  %s  %s[%d]\n",point,"Running",backg[i].command,backg[i].pid);
			point++;
		}
		if(backg[i].flag==0)
		{
			printf("[%d]  %s  %s[%d]\n",point,"Stopped",backg[i].command,backg[i].pid);
			point++;
		}
	}
	return 1;
}