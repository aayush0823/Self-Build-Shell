#include "function.h"
int echo(char **args)
{
	if(args[1] == NULL)
	{
		printf("\n");
		return 1;
	}
	int i=1;
	while(args[i]!=NULL)
	{
		if(args[i][0] == '\"' || args[i][0] == '\'')
		{
			int x = strlen(args[i]); 
			if(args[i][x-1] == '\"' || args[i][x-1] == '\'')
				for(int j=1;j<x-1;j++)
					printf("%c",args[i][j]);
			else
				for(int j=1;j<x;j++)
					printf("%c",args[i][j]);
			printf(" ");
		}
		else if(args[i][0]=='$')
		{
			int l=strlen(args[i]);
			char sub[l];
			for(int j=0;j<l-1;j++)
				sub[j]=args[i][j+1];
			sub[l-1]='\0';
			const char* str=getenv(sub);
			if(str != NULL)
				printf("%s",str);
			else
				printf(" ");
		}
		else
			printf("%s ",args[i]);
		i++;
	}
	printf("\n");
	return 1;
}