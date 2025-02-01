#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>

char* getuserinput (int *ret)
{
	char user_buf[255];
	char *p;
	(*ret) = read(0,user_buf,255);
	if((*ret) == -1)
	{
		printf("u_read\n");
	}
	user_buf[(*ret) - 1] = 0;
	p = (char *)malloc((*ret) * sizeof(char));
	int n = 0;
	while (user_buf[n] == 0)
	{
		p[n] = user_buf[n];
		n = n + 1;
	}
	p = user_buf;
	return p;
}
