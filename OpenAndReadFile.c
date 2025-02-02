#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define pn "PATH"
int MyOpen ()
{
	int ret;
	ret = open(pn,O_RDONLY);
	return ret;
}

int FileSize (int fd)
{
	int alloc_size = 20;
	int ret;
	int f_tmpsize = 0;
	char *tmp_c;
	while (1)
	{
		tmp_c = (char *)malloc(alloc_size * sizeof(char));
		if (!tmp_c)
			return -1;
		ret = read(fd,tmp_c,alloc_size);
		if (ret == -1)
		{
			free(tmp_c);
			printf("f_read\n");
		}
		else if (ret == alloc_size)
		{
			free(tmp_c);
			f_tmpsize = f_tmpsize + 1;
		}
		else if (ret == 0 )
		{
			free(tmp_c);
			ret = f_tmpsize * alloc_size;
			break;
		}
		else
		{
			free(tmp_c);
			ret = f_tmpsize * alloc_size + ret;
			break;
		}
	}	
	return ret;
}

char* MyRead (int size,int fd)
{
	//printf("%d,%d\n",size,fd);
	char *c;
	c = (char *)malloc(size * sizeof(char));
	lseek(fd,0,SEEK_SET);
	read(fd,c,size);
	c[size - 1] = 0;
	close(fd);
	return c;
}
