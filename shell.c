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
extern char* getuserinput (int *ret);
int ext_str (int *loop_count,char *c,int ret,char *user_buf);

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

		int loop_count = 0;
		int last_flag = 0;
		//printf("ret1 = %d\n",ret1);
		int first_flag = 0;
		ext_str (&loop_count,c,ret,user_buf);
		/*while(c[loop_count] != 0)
		{
			if (first_flag == 0 && c[loop_count] == '/')
				first_flag = loop_count;
			else if (first_flag > 0 && c[loop_count] == '/')
				last_flag = loop_count;
			//printf("last_flag = %d\n",last_flag);
			//printf("first_flag = %d\n",first_flag);
			if (c[loop_count] == ':')
			{
				int tmp_n = loop_count - last_flag;
				//printf("tmp_n = %d\n",tmp_n);
				//printf("%c\n",c[loop_count]);
				int tmp_n1 = loop_count;
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
				//printf("first_flag = %d loop_count = %d ret2 = %d\n",first_flag,loop_count,ret2);
				if (ret2)
				{
					free(tmp_c);
					tmp_n = loop_count - first_flag + 1;
					tmp_n1 = loop_count;
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
					first_flag = 0;
					break;
				}
			}
			loop_count = loop_count + 1;
			//printf("内loop_count = %d\n",loop_count);
		}*/
		//printf("外loop_count = %d\n",loop_count);
	}
	return 0;
}
