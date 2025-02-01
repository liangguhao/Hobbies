#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int ext_str (int *loop_count,char *c,int ret,char *user_buf)
{
	int last_flag = 0;
	int first_flag = 0;
	while(c[*loop_count] != 0)
	{
		if (first_flag == 0 && c[*loop_count] == '/')
			first_flag = *loop_count;
		else if (first_flag > 0 && c[*loop_count] == '/')
			last_flag = *loop_count;
		if (c[*loop_count] == ':')
		{
			int tmp_n = *loop_count - last_flag;
			int tmp_n1 = *loop_count;
			int tmp_n2 = tmp_n;
			char *tmp_c;
			tmp_c = (char *)malloc(tmp_n * sizeof(char));
			while ((tmp_n - 1) != 0)
			{
				tmp_c[tmp_n - 2] = c[tmp_n1 - 1];
				tmp_n = tmp_n - 1;
				tmp_n1 = tmp_n1 - 1;
			}
			tmp_c[tmp_n2 - 1] = 0;
			int ret2 = 1;
			while(tmp_n2 != 0)
			{
				if ((tmp_c[tmp_n2 - 1] - user_buf[ret - 1]) == 0)
					;
				else
					ret2 = 0;
				tmp_n2 = tmp_n2 - 1;
				ret = ret - 1;
			}
			if (ret2)
			{
				free(tmp_c);
				tmp_n = *loop_count - first_flag + 1;
				tmp_n1 = *loop_count;
				tmp_n2 = tmp_n;
				tmp_c = (char *)malloc(tmp_n * sizeof(char));
				while ((tmp_n - 1) != 0)
				{
					tmp_c[tmp_n - 2] = c[tmp_n1 - 1];
					tmp_n = tmp_n - 1;
					tmp_n1 = tmp_n1 - 1;
				}
				tmp_c[tmp_n2 - 1] = 0;
				pid_t fork_ret = fork();
				if(fork_ret == 0)
				{
					execve(tmp_c,0,0);
					return 0;
				}
				else
				{
					siginfo_t info;
					waitid(P_PID,fork_ret,&info,WEXITED);
				}
			}
			else
			{
				free(tmp_c);
				first_flag = 0;
				break;
			}
		}
	*loop_count = *loop_count + 1;
	}
}
