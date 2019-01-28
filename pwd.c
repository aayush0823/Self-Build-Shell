#include "function.h"
int pwd()
{
	char p[11000];
	getcwd(p, sizeof(p));
	printf("%s\n", p);
	return 1;
}