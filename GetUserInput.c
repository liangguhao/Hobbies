#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>

char* getuserinput (int *ret)
{
	write(1,"$ ",2);
	char tmp_c[255];
	char *user_buf;
	(*ret) = read(0,tmp_c,255);
	if((*ret) == -1)
	{
		printf("u_read\n");
	}
	tmp_c[(*ret) - 1] = 0;
	//printf("%s\n",tmp_c);
	user_buf = (char *)malloc((*ret) * sizeof(char));
	int n = 0;
	while (tmp_c[n] != 0)
	{
		//printf("%c",tmp_c[n]);
		user_buf[n] = tmp_c[n];
		n = n + 1;
	}
	user_buf[(*ret) - 1] = 0;
	return user_buf;
}
