#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef  struct Shell
{
	int cd_n;
	char cd[2];
}
shell;

extern int MyOpen(void);
extern int FileSize(int fd);
extern char* MyRead(int size,int fd);
extern char* getuserinput (int *ret);
extern int CompareString(int *tmp_n2,int *ret,char *tmp_c,char *user_buf);
extern int ext_str (int *loop_count,char *c,int ret,char *user_buf);

int main ()
{
	shell myshell = {2,{'c','d'}};
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

	while(1)
	{
		char *user_buf = getuserinput(&ret);
		printf("user_buf = %s\n",user_buf);
		if (user_buf[0] == 'c')
		{
			if (user_buf[1] == 'd')
			{
				if (user_buf[2] == ' ')
				{
					int tmp_n = 3;
					int loop_n = 0;
					char *tmp = NULL;
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
					chdir(tmp);
					free(tmp);
				}
			}
		}
		int loop_count = 0;
		int last_flag = 0;
		int first_flag = 0;
		ext_str (&loop_count,c,ret,user_buf);
		free(user_buf);
	}
	return 0;
}
