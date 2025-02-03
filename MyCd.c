#include <stdlib.h>
#include <unistd.h>
#include<stdio.h>


void mycd(char *user_buf)
{
	char *tmp = NULL;
	if (user_buf[2] == '\n')
	{
		tmp = "/home";
		if (chdir(tmp) == -1)
			printf("error:cd\n");
	}
	else if (user_buf[2] == ' ')
	{
		int tmp_n = 3;
		int loop_n = 1;
		while (user_buf[tmp_n] != '\n')
		{
			tmp_n = tmp_n + 1;
			loop_n = loop_n + 1;
		}
		tmp = (char *)malloc(loop_n * sizeof(char));
		tmp_n = 3;
		loop_n = 0;
		while (user_buf[tmp_n] != '\n')
		{
			tmp[loop_n] = user_buf[tmp_n];
			loop_n = loop_n + 1;
			tmp_n = tmp_n + 1;
		}
		tmp[loop_n] = 0;
		chdir(tmp);
		free(tmp);
	}
}
