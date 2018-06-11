#include "asd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
  	int hossz, fd, fd1;                            /* szerver- és kliensfifo */
  	char s[15];                             /* kliensfifo neve; pl. fifo_143 */
	char szo[50];
	char katalogus[50];
	char shell[]="./asd1.sh ";
	char buf[1024];
  	azon t;                                 /* küldendő "csomag" */
 	FILE *sh;
  	mkfifo("szerverfifo", S_IFIFO|0666);    /* a szerver létrehozza a saját fifo-ját */
 
  	do                                      /* addig megy, míg 0-t nem küld egy kliens */
  	{
		fd = open("szerverfifo", O_RDONLY);
   	 	read(fd, &t, sizeof(t));              /* szám kiolvasása */
		if(strcmp(t.szo,"exit")!=0 && strcmp(t.katalogus,"exit")!=0){
			strcat(shell,t.szo);
			strcat(shell," ");
			strcat(shell,t.katalogus);
			sh=popen(shell,"r");
			strcpy(shell,"./asd1.sh ");
    			sprintf(s, "fifo_%d", t.pid);
			fd1 = open(s, O_WRONLY);              /* kliensfifo megnyitása írásra */
			while(fgets(buf,1024,sh)){
				hossz=strlen(buf);
				write(fd1,buf,hossz*sizeof(char));		
			}
			pclose(sh);
    			close(fd1);
			close(fd);  			
		}                          /* adatok elküldve, kliensfifo vége */
		else break;
 	}while(1);
  	close(fd);                              /* szerverfifo vége */
 	unlink("szerverfifo");                  /* törli a szerverfifot, hiszen ő hozta létre */
  	exit(0);
}





























