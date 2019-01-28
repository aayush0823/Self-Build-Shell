#include "function.h"
int in=0;
int ppid;
char commandp[100];
char ** command_storage;
void loop();
void split_command(char *line)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	int pos = 0;
	command_storage = malloc( buffer_size * sizeof(char*));
	char *token;
	char *saveptr1;

	if (command_storage == NULL) {
		fprintf(stderr, "Memory Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line,";\n");
	while (token != NULL) 
	{
		command_storage[pos] = token;
		pos++;

		if (pos >= buffer_size) 
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			command_storage = realloc(command_storage,  buffer_size * sizeof(char*));
			if (command_storage == NULL) {
				fprintf(stderr, "Memory Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL,";\n");
	}
	command_storage[pos] = NULL;
	return;
}
char ** token_storage;
void split_line(char *line)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	int pos = 0;
	token_storage = malloc( buffer_size * sizeof(char*));
	char *token;
	char *saveptr1;

	if (token_storage == NULL) {
		fprintf(stderr, "Memory Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line," \n");
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
		token = strtok(NULL," \n");
	}
	token_storage[pos] = NULL;
	return;
}


void assign(int status[],int new[])
{
	int input=0,output=0,append=0,pipes=0;
	for(int i=0;token_storage[i]!=NULL;i++)
	{
		if(strcmp(token_storage[i],">")==0)
			output=1;
		else if(strcmp(token_storage[i],">>")==0)
			append=1;
		else if(strcmp(token_storage[i],"<")==0)
			input=1;
		else if(strcmp(token_storage[i],"|")==0)
			pipes=1;
	}
	if(pipes)
	{
		status[0]=1;
		piping(token_storage);
		new[0]=1;
	}
	else if(input+output+append)
		{
			status[0]=1;
			redirect(token_storage,input,output,append);
			new[0]=1;
		}
	else if (strcmp(token_storage[0],"pwd")==0)
		{
			status[0]=pwd();
			new[0]=1;
		}
	else if (strcmp(token_storage[0],"echo")==0)
		{
			status[0]=echo(token_storage);
			new[0]=1;
		}
	else if (strcmp(token_storage[0],"exit")==0 || strcmp(token_storage[0],"quit")==0)
		{
			overkill(token_storage,in);
			status[0]=0;
			new[0]=1;
		}
	else if(strcmp(token_storage[0],"ls")==0)
		{
			status[0]=ls(token_storage,in);
			new[0]=1;
		}
	else if(strcmp(token_storage[0],"cd")==0)
		{
			status[0]=cd(token_storage);
			new[0]=1;
		}
	else if(strcmp(token_storage[0],"pinfo")==0)
		{
			status[0]=pinfo(token_storage,in);
			new[0]=1;
		}
	else if(strcmp(token_storage[0],"remindme")==0)
		{
			status[0]=remind(token_storage);
			new[0]=1;
		}
	else if(strcmp(token_storage[0],"setenv")==0)
		{
			status[0]=set_env(token_storage);
			new[0]=1;
		}
	else if(strcmp(token_storage[0],"unsetenv")==0)
		{
			status[0]=unset_env(token_storage);
			new[0]=1;
		}
	else if(strcmp(token_storage[0],"jobs")==0)
		{
			status[0]=jobs(token_storage,in);
			new[0]=1;
		}
	else if(strcmp(token_storage[0],"kjob")==0)
		{
			status[0]=kjob(token_storage,in);
			new[0]=1;
		}
		else if(strcmp(token_storage[0],"bg")==0)
		{
			status[0]=bg(token_storage,in);
			new[0]=1;
		}
		else if(strcmp(token_storage[0],"fg")==0)
		{
			status[0]=fg(token_storage,in);
			new[0]=1;
		}
		else if(strcmp(token_storage[0],"overkill")==0)
		{
			status[0]=overkill(token_storage,in);
			new[0]=1;
		}
	else
		{
			pid_t cpid,wpid;
			int i=0;
			int bg=0,status;
			for(i=0;token_storage[i]!=NULL;i++);
				i--;
			if(strcmp(token_storage[i],"&")==0)
			{
				bg=1;
				token_storage[i]=NULL;
			}
			cpid = fork();
			if(cpid==0)
			{
				i = execvp(token_storage[0],token_storage);
    			if(i < 0) {
        		printf("%s: %s\n", token_storage[0], "command not found");
        			exit(1);        
    			}   
			}
			else
			{
				if(!bg){
					ppid=cpid;
					do {
						wpid = waitpid(cpid, &status, WUNTRACED);
					} 
					while (!WIFEXITED(status) && !WIFSIGNALED(status));
					ppid = 0;
				strcpy(commandp,token_storage[0]);
				}
				else
				{
					backg[in].pid=cpid;
					strcpy(backg[in].command,token_storage[0]);
					backg[in].flag=1;
					in++;
				}
				bg=0;
				
			}
			new[0]=1;
		}
		free(token_storage);
}
void SIGTSTP_handler(int signal_num)
{
	if(ppid){
		if(kill(ppid,SIGTSTP));
		{
			backg[in].pid = ppid;
			strcpy(backg[in].command,commandp);
			backg[in].flag = 0;
			printf("Process Stopped %s with PID[%d]\n",backg[in].command,backg[in].pid);
			in++;
			ppid=0;
			fflush(stdout);
			loop();
		}
		return;
	}
		signal(signal_num, SIG_IGN);
		printf("\n");
		print_prompt();
		fflush(stdout);
		signal(signal_num, SIGTSTP_handler);
}
void  SIGINT_handler(int signal_num)
{	
	if(ppid){
		kill(ppid,SIGINT);
			return;
	}
		signal(signal_num, SIG_IGN);
		printf("\n");
		print_prompt();
		fflush(stdout);
		signal(signal_num, SIGINT_handler);
}

void loop(){
	char *line;
	int status[1];
	status[0]=1;
	int new[1];
	new[0]=1;
	do{
		bgreturn(token_storage,in);
		if(new[0]==1)
		{
			print_prompt();
			ssize_t line_size=0;
			getline(&line,&line_size,stdin);
			new[0]=0;
		}
		if(strcmp(line,"\n")==0)
		{
			new[0]=1;
			continue;
		}
		split_command(line);
		for(int i=0;command_storage[i]!=NULL;i++)
		{
			split_line(command_storage[i]);
			assign(status,new);
		}
		fflush(stderr);
	}
	while(status[0]);
}
int main(int argc, char** argv){
	signal(SIGINT,SIGINT_handler);
	signal(SIGTSTP,SIGTSTP_handler);
	getcwd(home,sizeof(home));
	loop();
	fflush(stderr);
	return 0;
}