#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define MAX_SIZE 255

void FileRead(FILE *ptr){
	char buffer[MAX_SIZE];
	while(fgets(buffer,MAX_SIZE,ptr)){
		printf("%s",buffer);
	}
	printf("\n");
}


int main(int argc, char *argv[]){
	if(argc<2){
		fprintf(stderr,"Too few arguments!\nUsage: ./my-cat [file1] [file2]....[fileN]\n");
		exit(0);
	}
	FILE *fileptr;
	for(int i=0;i<argc-1;i++){
		if((fileptr=fopen(argv[i+1],"r"))==NULL){
			printf("Error in file opening: %s\n", strerror(errno));
			exit(1);
		}
		FileRead(fileptr);
		fclose(fileptr);
	}
	return 0;
}
