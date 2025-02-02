#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>

int main()
{
	char *tmp = (char *)malloc(255 * sizeof(char));
	chdir("/home/sili");
	getcwd(tmp,255);
	printf("%s\n",tmp);
	return 0;
}
