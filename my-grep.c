#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 255

typedef struct stringNode{
	char string[MAX_SIZE];
	struct stringNode *next;
}*node;


void ClearNodes(node headNode){
	node proxy=headNode;
	while(proxy!=NULL){
		proxy=headNode->next;
		free(headNode);
		headNode=proxy;
	}
}

int FindMatch(char *ptr,char *word){
	int i=0, loop=0;
	char c;
	while((c=*(ptr+loop))!='\n' || *(word+i)==0){
		
		if(*(word+i)==0){
			return 1;
		}
		if(c==(*(word+i))){
			//printf("%c %d %c\n",c,i,*(word+i+1));
			i++;
		}else{
			i=0;
		}
		loop++;
	}
	return 0;
}

void FileRead(FILE *ptr, char *word){
	char buffer[MAX_SIZE];
	char *charptr=malloc(sizeof(char*));
	while(fgets(buffer,MAX_SIZE,ptr)){
		charptr=buffer;
		if(FindMatch(charptr,word)){
			printf("%s",buffer);			
		}
	}
	printf("\n");
}


void ReadUserInput(char *word){
	node head=NULL, proxy;
	char ptr[MAX_SIZE];
	while(fgets(ptr,MAX_SIZE,stdin)){
		if(head==NULL){
			head=malloc(sizeof(node));
			proxy=head;
			proxy->next=NULL;
		}
		if(*ptr=='\n'){
			break;
		}
		strcpy(proxy->string,ptr);	
		proxy->next=malloc(sizeof(node));
		proxy=proxy->next;
		proxy->next=NULL;
				
	}
	proxy=head;
	while(proxy!=NULL){
		if(FindMatch(proxy->string,word)){
			printf("match :%s\n",proxy->string);	
		}
		proxy=proxy->next;
	}
	
	ClearNodes(head);
}

int main(int argc, char *argv[]){
	if(argc<2){
		fprintf(stderr,"Too few arguments!\nUsage: ./my-grep searchterm [file..]\n");
		exit(0);
	}
	FILE *fileptr;
	if(argc<3){
		ReadUserInput(argv[1]);
	}
	else{
		if((fileptr=fopen(argv[2],"r"))==NULL){
			printf("Error in file opening: %s\n", strerror(errno));
			exit(1);
		}
		FileRead(fileptr,argv[1]);
		fclose(fileptr);
	}	
	return 0;
}
