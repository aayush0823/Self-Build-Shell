#include "function.h"

int bg(char **args,int total)
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

        kill(backg[cal].pid,18);
        backg[cal].flag=1;
        return 1;
}