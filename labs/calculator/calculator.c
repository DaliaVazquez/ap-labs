#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {
    int res = values[2];
    printf("%i", res);
    for (int i = 3; i < nValues; i++){
        if(operator == 1){
            printf(" + %i", values[i]);
            res += values[i];
        }else if(operator == 2){
            printf(" - %i", values[i]);
            res -= values[i];
        }else{
            printf(" * %i", values[i]);
            res *= values[i];
        }
    } 
    printf(" = %i \n", res); 
   
    return 0;
}

int main(int argc, char **argv) {

    if(argc > 3){
        int val[argc];
        int op = 0;
        if(strcmp("add", argv[1]) == 0){
            op = 1;
        }else if(strcmp("sub", argv[1]) == 0){
            op = 2;     
        }else if(strcmp("mult", argv[1]) == 0){
            op = 3;
        }else{
            printf("El operador no es valido \n");
            return 0;
        }

        for (int i = 2; i < argc; ++i) {
            for(int j=0; j < strlen(argv[i]); j++){
                if(!isdigit(argv[i][j])){
                    printf("Character no valido \n");
                    return 0;
                } 
            }
            val[i]=atoi(argv[i]);   
        }
        
        calc(op,argc, val);
    }else{
        printf("Operacion invalida\n");
    }

    return 0;

}
