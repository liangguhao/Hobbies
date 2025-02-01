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
	}
	return 0;
}
