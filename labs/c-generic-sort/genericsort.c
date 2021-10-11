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
	if(argc<3 || argc > 6){
		printf("Invalid number of arguments\n");
		return 0;
	}

	FILE * file; 
    char* outputFile=NULL;
    char* readFile=NULL;
	char *sort ="no";

	int isNum = 0;
	
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	if (strcmp(argv[1],"-n")==0){
        file = fopen(argv[2], "r");
        readFile=argv[2];
		isNum = 1;
    }else{
        file = fopen(argv[1], "r");
        readFile=argv[1];
    }
    
	if (file == NULL){
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
			sort=argv[i];
		}else if(strcmp(argv[i], "-mergesort")==0){
			sort=argv[i];
		}
	}
    if(strcmp(sort, "no") == 0){
        printf("Error: no sort type\n");
        return 0;
	}
    if(outputFile==NULL) {
		char* tmp = "sorted_";
		outputFile = (char*) malloc(strlen(readFile)+strlen(tmp)+1);
		strcpy(outputFile, tmp);
		strcat(outputFile, readFile);
	}
	int lineNum = 0;
	while((read = getline(&line, &len, file)) != -1) {
		lineNum++;
	}

	fseek(file, 0, SEEK_SET);
	char **arr = (char **)malloc(lineNum*sizeof(char*));
	int index = 0;
	while((read = getline(&arr[index], &len, file)) != -1) {
		index++;
	}
	fclose(file);

	if(strcmp(sort, "-quicksort") == 0) {
		if(isNum) {
			quicksort((void **) arr, 0, lineNum-1, (int(*)(void*, void*))(numcmp));
		} else {
			quicksort((void **) arr, 0, lineNum-1, (int(*)(void*, void*))(strcmp));
		}
		printf("sorting strings.txt file with quicksort\n");
	} else if(strcmp(sort, "-mergesort") == 0) {
		if(isNum) {
			mergesort((void **) arr, 0, lineNum-1, (int(*)(void*, void*))(numcmp));
		} else {
			mergesort((void **) arr, 0, lineNum-1, (int(*)(void*, void*))(strcmp));
		}
		printf("sorting strings.txt file with mergesort\n");
	}

	file = fopen(outputFile, "w");

	for(int i = 0; i < lineNum; i++) {
		fprintf(file, "%s", arr[i]);
	}

	printf("Results file can be found at %s\n", outputFile);
	fclose(file);
    return 0;
}
