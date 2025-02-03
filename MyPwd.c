#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>

int mypwd(void)
{
	char *tmp = NULL;
	tmp = (char *)malloc(500 * sizeof(char));
	if (!getcwd(tmp,500))
	{
		printf("error: pwd\n");
		return -1;
	}
	printf("%s\n",tmp);
	free(tmp);
}
