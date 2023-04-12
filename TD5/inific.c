#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

	int tab1[10]={11,22,33,44,55,66,77,88,99,1000};
	int i,fd;
	fd = open("titi.dat",O_RDWR|O_CREAT|O_TRUNC,0666);
	write (fd,tab1,10*sizeof(int));
	close(fd);
	return 0;

} 
