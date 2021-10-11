#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if(v1 < v2) 
        return -1;
    if(v1 > v2)
        return 1;
    return 0;
}

int readlines(FILE *input, int nlines)
{
    char *line;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, input) != -1))
    {
        if (nlines == MAXLINES)
        {
            printf("File too big to be sorted");
            exit(0);
        }
        lineptr[nlines] = malloc(strlen(line));
        strcpy(lineptr[nlines++], line);
    }
    return nlines;
}

int main(int argc, char **argv)
{
	if(argc<4 || argc > 6){
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
	int nlines = 0;
	nlines = readlines(archivo, nlines);
    fclose(archivo);	

    return 0;
}
