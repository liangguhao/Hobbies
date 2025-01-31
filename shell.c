#include<fcntl.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

#define pn "PATH"

extern int MyOpen(void);
extern int FileSize(int fd);
extern char* MyRead(int size,int fd);
char* getuserinput (int *ret);

int main ()
{
	int fd;
	fd = MyOpen();
	if (fd == -1)
	{
		printf("open\n");
		return -1;
	}
	int ret = FileSize(fd);
	//printf("%d,%d\n",ret,fd);
	if (ret == -1)
	{
		printf("FileSize in malloc\n");
		return -2;
	}
	char *c = NULL;
	c = MyRead(ret,fd);
	if (!c)
	{
		printf("MyRead\n");
		return -3;
	}
	int ret1 = ret;

	while(1)
	{
		write(1,"$ ",2);
		char *user_buf = getuserinput(&ret);
		//printf("user_buf = %s\n",user_buf);

		int u_n = 0;
		int w_n = 0;
		//printf("ret1 = %d\n",ret1);
		int ww_n = 0;
		while(c[u_n] != 0)
		{
			if (ww_n == 0 && c[u_n] == '/')
				ww_n = u_n;
			else if (ww_n > 0 && c[u_n] == '/')
				w_n = u_n;
			//printf("w_n = %d\n",w_n);
			//printf("ww_n = %d\n",ww_n);
			if (c[u_n] == ':')
			{
				int tmp_n = u_n - w_n;
				//printf("tmp_n = %d\n",tmp_n);
				//printf("%c\n",c[u_n]);
				int tmp_n1 = u_n;
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
				//printf("tmp_c = %s\n",tmp_c);
				int ret2 = 1;
				while(tmp_n2 != 0)
				{
					if ((tmp_c[tmp_n2 - 1] - user_buf[ret - 1]) == 0)
						;
					else
						ret2 = 0;
					tmp_n2 = tmp_n2 - 1;
					ret = ret - 1;
					//printf("tmp_n2 = %d\n",tmp_n2);
				}
				//printf("ww_n = %d u_n = %d ret2 = %d\n",ww_n,u_n,ret2);
				if (ret2)
				{
					free(tmp_c);
					tmp_n = u_n - ww_n + 1;
					tmp_n1 = u_n;
					tmp_n2 = tmp_n;
					tmp_c = (char *)malloc(tmp_n * sizeof(char));
					while ((tmp_n - 1) != 0)
					{
						tmp_c[tmp_n - 2] = c[tmp_n1 - 1];
						tmp_n = tmp_n - 1;
						tmp_n1 = tmp_n1 - 1;
					}
					tmp_c[tmp_n2 - 1] = 0;
					//printf("tmp_c = %s\n",tmp_c);
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
					ww_n = 0;
					break;
				}
			}
			u_n = u_n + 1;
			//printf("内u_n = %d\n",u_n);
		}
		//printf("外u_n = %d\n",u_n);
	}
	return 0;
}
