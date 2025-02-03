#include<stdio.h>
#include <stdlib.h>

extern int MyOpen(void);
extern int FileSize(int fd);
extern char* MyRead(int size,int fd);
extern char* getuserinput (int *ret);
extern int ext_str (int *loop_count,char *c,int ret,char *user_buf);
extern int mycd(char *user_buf);
extern int mypwd(void);
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

	while(1)
	{
		char *user_buf = getuserinput(&ret);
		//printf("1 user_buf = %s",user_buf);
		if (user_buf[0] == '\n' || user_buf[0] == 0)
		{
			free(user_buf);
			continue;
		}
		if (user_buf[0] == 'c' && user_buf[1] == 'd')
		{
			if(!mycd(user_buf))
			{
				free(user_buf);
				continue;
			}
		}
		if (user_buf[0] == 'p' && user_buf[1] == 'w' && user_buf[2] == 'd' || user_buf[3] == '\n')
		{
			if (!mypwd())
			{
				free(user_buf);
				continue;
			}
		}
		int loop_count = 0;
		int last_flag = 0;
		int first_flag = 0;
		user_buf[ret - 1] = 0;
		ext_str (&loop_count,c,ret,user_buf);
		free(user_buf);
	}
	return 0;
}
