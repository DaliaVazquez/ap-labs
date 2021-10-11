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

int main(int argc, char **argv)
{
	if(argc<4 || argc > 6){
		printf("Invalid number of arguments\n");
		return 0;
	}

	FILE * archivo; 
    char* outputFile=NULL;
    char* fileToRead=NULL;
	char *sortType ="no";

	int numeric = 0;
	
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	if (strcmp(argv[1],"-n")==0){
        archivo = fopen(argv[2], "r");
        fileToRead=argv[2];
		numeric = 1;
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
			sortType=argv[i];
		}else if(strcmp(argv[i], "-mergesort")==0){
			sortType=argv[i];
		}
	}
    if(strcmp(sortType, "no") == 0){
        printf("Please input a sort type\n");
        return 0;
	}
    if(outputFile==NULL) {
		char* tmp = "sorted_";
		outputFile = (char*) malloc(strlen(fileToRead)+strlen(tmp)+1);
		strcpy(outputFile, tmp);
		strcat(outputFile, fileToRead);
	}
	int lineNum = 0;
	while((read = getline(&line, &len, archivo)) != -1) {
		lineNum++;
	}

	fseek(archivo, 0, SEEK_SET);
	char **inputArray = (char **)malloc(lineNum*sizeof(char*));
	int index = 0;
	while((read = getline(&inputArray[index], &len, archivo)) != -1) {
		index++;
	}
	fclose(archivo);

	if(strcmp(sortType, "-quicksort") == 0) {
		printf("... sorting strings.txt file with quicksort\n");
		if(numeric) {
			quicksort((void **) inputArray, 0, lineNum-1, (int(*)(void*, void*))(numcmp));
		} else {
			quicksort((void **) inputArray, 0, lineNum-1, (int(*)(void*, void*))(strcmp));
		}
	} else if(strcmp(sortType, "-mergesort") == 0) {
		printf("... sorting strings.txt file with mergesort\n");
		if(numeric) {
			mergesort((void **) inputArray, 0, lineNum-1, (int(*)(void*, void*))(numcmp));
		} else {
			mergesort((void **) inputArray, 0, lineNum-1, (int(*)(void*, void*))(strcmp));
		}
	} else {
		printf("Error: The only available algorithms are: -quicksort and -mergsort\n");
		return 0;
	}

	archivo = fopen(outputFile, "w");

	for(int i = 0; i < lineNum; i++) {
		fprintf(archivo, "%s", inputArray[i]);
	}

	printf("... Results file can be found at %s\n", outputFile);
	fclose(archivo);
    return 0;
}
