#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));


int main(int argc, char **argv)
{
	if(argc<4){
		printf("Invalid number of arguments\n");
		return 0;
	}

	FILE * archivo; 
    char* outputFile=NULL;
    char* fileToRead=NULL;
	char sortType ='n';

	if (strcmp(argv[1],"-n")==0){
        archivo = fopen(argv[2], "r");
        fileToRead=argv[2];
    }else{
        archivo = fopen(argv[1], "r");
        fileToRead=argv[1];
    }
    
	if (archivo == NULL){
       printf("Error: file null  \n");
       return 0;
    }
	for (int i=2; i<argc; i++) {
		if(strcmp(argv[i], "-o")==0){
			if(i+1>=argc){
				printf("Error: no file after -o\n");
				return 0;
			}
			outputFile=argv[i+1];
		}else if(strcmp(argv[i], "-quicksort")==0){
			sortType='q';
		}else if(strcmp(argv[i], "-mergesort")==0){
			sortType='m';
		}
	}
    if(sortType=='n'){
        printf("Please input a sort type\n");
        return 0;
	}
    if(outputFile==NULL) {
		char* tmp = "sorted_";
		outputFile = (char*) malloc(strlen(fileToRead)+strlen(tmp)+1);
		strcpy(outputFile, tmp);
		strcat(outputFile, fileToRead);
	}

    return 0;
}
