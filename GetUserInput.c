#include<stdio.h>
#include <unistd.h>

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
	p = user_buf;
	return p;
}
