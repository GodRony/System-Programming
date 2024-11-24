#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fp;
	char tmpname[L_tmpnam];
	char template[] = "/tmp/senutemp.XXXXXX";
	int fd;

	if((fp = tmpfile()) == NULL){
		perror("tmpfile");
		exit(1);
	}
	printf("Success to make temporary file with tmpfile(3) function\n");
	system("ls /tmp");

	fputs("This is contents of the tmpfile\n\n",fp);
	rewind(fp);
	while(fgets(tmpname,sizeof(tmpname),fp) != NULL){
		fputs(tmpname,stdout);
	}
	fclose(fp);

	if((fd = mkstemp(template)) == -1){
		perror("mkstemp");
		exit(1);
	}
	write(fd,"This is contents of the tmpfile",32);

	printf("Success to make temporary file with mkstemp(3) function\n");
	printf("tempfile name : %s\n",template);
	system("ls /tmp");
	close(fd);

	return 0;
}
