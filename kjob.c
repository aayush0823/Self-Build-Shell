#include "function.h"

int kjob(char **args,int total)
{
        if(args[1]==NULL || args[2] ==NULL)
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
                fprintf(stderr, "Job number does not exist\n");
                return 1;
        }

        int sig=atoi(args[2]);
        kill(backg[cal].pid,sig);
        if(sig == 9 || sig==15)
                backg[cal].flag=-2;
        else if(sig == 20)
                backg[cal].flag=0;
        else if(sig == 18)
                backg[cal].flag=1;
        return 1;
}