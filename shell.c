#include<stdio.h>
#include <stdlib.h>

extern int MyOpen(void);
extern int FileSize(int fd);
extern char* MyRead(int size,int fd);
extern char* getuserinput (int *ret);
extern int ext_str (int *loop_count,char *c,int ret,char *user_buf);
extern void mycd(char *user_buf);

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
		if (user_buf[0] == 'c' && user_buf[1] == 'd')
		{
			/*char *tmp = NULL;
			if (user_buf[2] == '\n')
			{
				tmp = "/home";
				if (chdir(tmp) == -1)
					printf("error:cd\n");
			}
			else if (user_buf[2] == ' ')
			{
				//printf("cd 1\n");
				int tmp_n = 3;
				int loop_n = 1;
				while (user_buf[tmp_n] != '\n')
				{
					tmp_n = tmp_n + 1;
					loop_n = loop_n + 1;
				}
				//printf("2\n");
				tmp = (char *)malloc(loop_n * sizeof(char));
				tmp_n = 3;
				loop_n = 0;
				//printf("3");
				while (user_buf[tmp_n] != '\n')
				{
					tmp[loop_n] = user_buf[tmp_n];
					loop_n = loop_n + 1;
					tmp_n = tmp_n + 1;
				}
				//printf("4");
				tmp[loop_n] = 0;
				chdir(tmp);
				free(tmp);
			}*/
			mycd(user_buf);
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
