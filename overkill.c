#include "function.h"
int overkill(char **args,int total)
{
	for(int i=0;i<total;i++)
	{
		kill(backg[i].pid,15);
			backg[i].flag=-1;
	}
	return 1;
}