#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define MAX_SIZE 255

unsigned int testFunc(unsigned int number){
	if(number==0) return 0;
	if(number==1) return 1;
	return (number % 2) +10*testFunc(number/2);
}

int CharToInt(int c, int multiplier){
	unsigned int proxy;
	char proxychar[8];
	proxy=testFunc( c);
	sprintf(proxychar, "%d", proxy);
	//printf("as a binary :%d and cahr:%s \n",proxy, proxychar);
	if(proxy==0){
		return 0;
	}	
	int returnvalue=0,test=0;
	for(int i=0;i<8;i++){
		if(proxychar[7-i]==0){
			test=i;
		}
		if(proxychar[7-i]=='1'){
			
			returnvalue+=pow(2,i-test-1);
	//		printf("return value middleee:%d\n",returnvalue);		
		}
	}
	/*
	int loop=0;
	while(proxychar[loop]!=0){
		if(proxychar[loop]=='1'){
			returnvalue+=pow(2,loop+multiplier*8);
		}
		//printf("%d\n",loop);
		loop++;
	}*/
	//printf("value returned %d\n",returnvalue);
	return returnvalue;
}

int GetNumberFromBinary(char binary[5]){
	int value=0;
	for(int i=0;i<4;i++ ){
		value+=CharToInt((int)binary[i],i);
	}
	return value;
}

void BinaryFileRead(FILE *fptr){
	char buffer[5];
	int i=0, loop=0;
	while(fread(buffer,sizeof(buffer),1,fptr)==1){
		//printf("from Buffed: %c  number: %d\n",buffer[4], buffer[0]);
		for(i=0;i<GetNumberFromBinary(buffer);i++){
			printf("%c",buffer[4]);
		}
		
		loop++;
	}
	
}


int main(int argc, char *argv[]){
	FILE *fptr;
	if((fptr=fopen(argv[argc-1],"rb"))==NULL){
		fprintf(stderr,"Error reading file: %s",strerror(errno));
		exit(1);
	}
	//printf("reading file\n");
	BinaryFileRead(fptr);
	fclose(fptr);
}
