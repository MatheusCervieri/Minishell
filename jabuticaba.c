# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

int    main(int argc, char **argv, char **envp)
{
	int fd = open("./testblabla.txt", O_RDWR);
    char *buf = calloc(sizeof(char), 101);
	read(fd, buf, 100);
	
	printf("%s \n", buf);
    printf("wtf");
	close(fd);
}