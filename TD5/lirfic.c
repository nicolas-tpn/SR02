#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

	int fd;
	int tab1[10]={11,22,33,44,55,66,77,88,99,1000};
	int tab2[10];

	fd=open("titi.dat",O_RDWR,0666);
	read (fd,tab2,10*sizeof(int));
	close(fd);
	for (int i=0;i<10;i++) printf("%d,%d\n",tab2[i],tab1[i]);

	return 0;

} 
