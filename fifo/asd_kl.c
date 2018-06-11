#include "asd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])          /* a számot a parancssorban adjuk meg */
{
  	int fd, fd1;                            /* kliens- és szerverfifo */
	char s[15];
	char buf[1024];
 	azon t;
 	int n;
  	if (argc != 3)                          /* nincs megadva argumentum, hiba */
  	{
  		printf("hasznalat: kliens <keresett szo> <katalogus>\n");
    		exit(1);
  	}
  	sprintf(s, "fifo_%d", getpid());        /* meghat. a fifonevet a pid segítségével */
  	mkfifo(s, S_IFIFO|0666);                /* létrehoz egy kliensfifot */
  	fd = open("szerverfifo", O_WRONLY);
  	t.pid = getpid();                       /* a küldendő adatok */
  	strcpy(t.szo,argv[1]);
  	strcpy(t.katalogus,argv[2]);
  	write(fd, &t, sizeof(t));              /* küldi a szervernek */
	if(!strcmp(t.szo,"exit")==0 && !strcmp(t.katalogus,"exit")==0){
		fd1 = open(s, O_RDONLY);
		n=read(fd1,buf,1024);
  		while(n>0){
			write(1,buf,n);
			n=read(fd1,buf,1024);
		}
	}
  	
 	close(fd1);
  	unlink(fd1);                            /* kliensfifo törlése */
  	exit(0);
}
