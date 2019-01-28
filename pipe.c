#include "function.h"

char **split_pipe_fxn(char *line)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	int pos = 0;
	char **token_storage = malloc( buffer_size * sizeof(char*));
	char *token;
	char *saveptr1;

	if (token_storage == NULL) {
		fprintf(stderr, "Memory Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok_r(line,"|",&saveptr1);
	while (token != NULL) 
	{
		token_storage[pos] = token;
		pos++;

		if (pos >= buffer_size) 
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			token_storage = realloc(token_storage,  buffer_size * sizeof(char*));
			if (token_storage == NULL) {
				fprintf(stderr, "Memory Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok_r(NULL,"|", &saveptr1);
	}

	token_storage[pos] = NULL;
	return token_storage;
}

char **split_line_fxn(char *line)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	int pos = 0;
	char **token_storage = malloc( buffer_size * sizeof(char*));
	char *token;
	char *saveptr1;

	if (token_storage == NULL) {
		fprintf(stderr, "Memory Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok_r(line,TOKEN_DELIM,&saveptr1);
	while (token != NULL) 
	{
		token_storage[pos] = token;
		pos++;

		if (pos >= buffer_size) 
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			token_storage = realloc(token_storage,  buffer_size * sizeof(char*));
			if (token_storage == NULL) {
				fprintf(stderr, "Memory Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok_r(NULL, TOKEN_DELIM, &saveptr1);
	}

	token_storage[pos] = NULL;
	return token_storage;
}

int piping(char ** args)
{
	char command[1000];
	for (int i = 0; i < 1000; ++i)
	{
		command[i]='\0';
		/* code */
	}
	int ii=dup(0);
	int oo=dup(1);

	for(int i=0;args[i]!=NULL;i++)
	{
		// printf("%s\n",args[i]);
		strcat(command,args[i]);
		strcat(command," ");
	}
	// printf("%s\n",command);
	char** cmd=split_pipe_fxn(command);
	int no=0;
	while(cmd[no]!=NULL)
		no++;
	for (int i = 0; i < no-1; ++i)
	{
		char** c=split_line_fxn(cmd[i]);
		// for(int j=0;c[j]!=NULL;j++)
			// printf("%s\n",c[j]);
		int input1=0;
		for(int j=0;c[j]!=NULL;j++)
			if(strcmp(c[j],"<") == 0)
					input1 = j+1;
		if(input1)
		{
			// printf("%s\n",c[input1]);
			int input = open(c[input1],O_RDONLY);
			dup2(input,STDIN_FILENO);
			close(input);
		}
		int pd[2];
		pipe(pd);
		int pid = fork();
		int status;
		pid_t wpid;
		if(pid == 0)
		{
			dup2(pd[1],1);
			if(input1){
						execlp(c[0],c[0],c[2],NULL);
					}
					else
						execvp(c[0],c);
		}
		else
		{
			do {
					wpid = waitpid(pid, &status, WUNTRACED);
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		dup2(pd[0],0);
		close(pd[1]);
	}
	char** c=split_line_fxn(cmd[no-1]);
	int out1=0,app1=0;
		for(int j=0;c[j]!=NULL;j++)
		{
			if(strcmp(c[j],">") == 0)
					out1 = j;
			if(strcmp(c[j],">>") == 0)
					app1 = j;
		}
	int output=1;
		if(out1)
		{
			output = open(c[out1+1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(output,1);
			close(output);
		}
		else if(app1)
		{
			output = open(c[app1+1],O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(output,1);
			close(output);
		}
		char * c1[10];
		int w=0;
		while(c[w]!=NULL && strcmp(c[w],">")!=0 && strcmp(c[w],">>")!=0)
		{
			c1[w]=c[w];
			w++;
		}
		c1[w]=NULL;
	int pid = fork();
		int status;
		pid_t wpid;
		if(pid == 0)
			execvp(c1[0],c1);
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
	return 1;
}