//references

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define MAX_SIZE 255

//used to find binary form as an long long of a specific number
unsigned long long testFunc(unsigned long long number){
	if(number==0) return 0;
	if(number==1) return 1;
	return (number % 2) +10*testFunc(number/2);
}

int BinaryPointFndr(char binary[32]){
	int x=0;
	while(binary[x]!=0)x++;
	return x;
}

void TurningIntoBinary(int consecutive, char character){
	unsigned char buffer[5];
	int binpoint, binpointproxy=0;
	//int test;
	char binary[32];
	for(int k=0;k<5;k++){
		buffer[k]=0;
	}	
	unsigned long long theInt;
	buffer[4]=character;
	theInt=testFunc((unsigned long long)consecutive);
	sprintf(binary, "%lld", theInt);
	//printf("binary alue for %c: %s\n", character,binary);
	int charValue=0;
	binpoint=BinaryPointFndr(binary); //finding the array position where the binary array stops
	for(int j=0;j<4;j++){
		charValue=0;
		if(binpointproxy==-1){
			break;
		}
		for(int i=0;i<8;i++){
			if(binpoint-(j+1)*8<0){//used as chcking if the current j spot in the array is where the binary stops
				binpointproxy=(j+1)*8-binpoint;	
				//printf("binpoint %d  %d\n", binpoint, binpointproxy);
			}
			if(binary[j*8+i]==0){
				binpointproxy=-1;
				break;
			}
			else if(binary[j*8+i]=='1'){
				charValue+=pow(2,j*8+7-binpointproxy-i);
				//printf("rest of power:%d \n", 7-i-binpointproxy);
			}
		}
		
		buffer[j]=(char)charValue;	
	}
	//printf("in buffer: %c %d. Shouldbe %s\n",buffer[4], buffer[0],binary);
	fwrite(&buffer,sizeof(char[5]),1, stdout);
}

void WriteBinary( char *line){
	unsigned int loop=0,consecutive=1;
	unsigned char c,proxy;//, intproxy[4];
	
	while((c=*(line+loop))!='\n'){
		
		
		
		if(proxy==c){
			consecutive++;
		}else{
			//printf("int the write:%c consecutive: %d\n",c, consecutive);
			TurningIntoBinary(consecutive,proxy);
			//fwrite(&consecutive,sizeof(int),1, stdout);
			//fwrite(&c,sizeof(char),1, stdout);
			
			consecutive=1;
			
		}
		if(consecutive==1){
			proxy=c;
					
		}
		loop++;
	}
	TurningIntoBinary(consecutive,proxy);
	TurningIntoBinary(1,c);
	//fwrite(&consecutive,sizeof(int),1, stdout);
	//fwrite(&c,sizeof(char),1, stdout);
}

void FileRead(FILE *ptr){
	char buffer[MAX_SIZE];
	while(fgets(buffer,MAX_SIZE,ptr)!=NULL){
		//printf("%s\n",buffer);
		WriteBinary(buffer);
	}
}

void quickRead(FILE *ptr){
	char buffer[MAX_SIZE];
	while(fgets(buffer,MAX_SIZE,ptr)!=NULL){
		printf("%s\n",buffer);
	}
}

int main(int argc, char *argv[]){
	
	FILE *ptr;
	
	/*if((bPtr=fopen(argv[argc-1],"wb"))==NULL){
		printf("Error opening file: %s\n",strerror(errno));
		exit(1);
	}*/
	
	for(int i=0;i<argc-1;i++){
		if((ptr=fopen(argv[i+1],"r"))==NULL){
			printf("Error opening file %s: %s\n", argv[i+1],strerror(errno));
			exit(1);
		}
		//quickRead(ptr);
		FileRead(ptr);
		fclose(ptr);
	}
	//fclose(bPtr);
}
