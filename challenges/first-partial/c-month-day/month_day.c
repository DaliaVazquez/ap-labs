#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday){
    int bis = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    char dmes[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
    
    if((bis == 0 && yearday > 365) || (bis == 1 && yearday > 366) || (yearday < 1)){
        printf("Dias incorrectos\n");
        exit(0); 
    }
    for (int i = 0; i < 12; i++){
        *pmonth = i;
        if (*pday <= dmes[bis][i]){
            return; 
        }
        *pday -= dmes[bis][i];
    }
}

int main(int argc, char **argv) {
    if(argc==3){
        for (int i = 1; i < argc; ++i) {
            for(int j=0; j < strlen(argv[i]); j++){
                if(!isdigit(argv[i][j])){
                    printf("Character no valido\n");
                    return -1;
                } 
            }
        }
        int year = atoi(argv[1]);
        int day = atoi(argv[2]);
        int num=0;
        static char *mes[12] = {"January", "February", "March","April", "May", "June",
            "July", "August", "September","October", "November", "December"};
        month_day(year, day, &num, &day);
        printf("%s %02d, %d\n",mes[num], day, year);
    }
    else{
        printf("Numero incorrecto de argumentos\n");
        return 0;
    }
}