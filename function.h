#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <sys/utsname.h>
#include <termios.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h>
typedef struct arr{
	pid_t pid;
	char command[1000];
	int flag;
}arr;
arr backg[1000];
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIM " \t\r\n\a"
#define CMD_DELIM ";\n"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
int cd(char ** args);
int jobs(char ** args,int total);
void bgreturn(char ** args,int in);
int overkill(char **args,int total);
int pwd();
int fg(char **args,int total);
int echo(char ** args);
int kjob(char **args,int total);
int ls(char ** args,int total);
int pinfo(char ** args,int total);
int lsl(char ** args,int total);
void print_prompt();
int exec(char ** args);
int remind(char **args);
int piping(char ** args);
void redirect(char **args,int inp,int outp,int outpa);
int unset_env(char** args);
int set_env(char** args);
int bg(char **args,int total);
char home[1111];
char previous[1111];