#include "function.h"
void print_prompt()
{
	char hostname[1000],curDir[1000];
	struct passwd * username=getpwuid(getuid());
	gethostname(hostname,sizeof(hostname));
	getcwd(curDir,sizeof(curDir));
	int i=0,flag=0;
	char addPrint[4098];
	if(strlen(curDir)<strlen(home))
	{
		flag=1;
		strcpy(addPrint,curDir);
	}
	while(home[i]!='\0' && flag==0)
	{
		if(home[i]!=curDir[i])
		{
			flag=1;
		}
		i++;
	}
	if(flag == 0 && strlen(curDir)==strlen(home))
	{
		addPrint[0]='~';
		addPrint[1]='\0';
	}
	else if(flag==0)
	{
		int len=1;
		addPrint[0]='~';
		if(curDir[i]!='/')
		{
			addPrint[len++]='/';	
		}
		while(curDir[i]!='\0')
		{
			addPrint[len]=curDir[i];
			i++;
			len++;
		}
		addPrint[len]='\0';
	}
	else if(flag==1)
	{
		strcpy(addPrint,curDir);
	}
	printf("\033[1m\033[34m%s@%s\033[0m:\033[1m\033[32m%s\033[0m\033[1m\033[34m$\033[0m ",username->pw_name,hostname,addPrint);
}