#include <stdio.h>
#include <stdlib.h>


char *month_name(int n) {

   static char *name[] = {
       "Illegal month",
       "January", "February", "March",
       "April", "May", "June",
       "July", "August", "September",
       "October", "November", "December"
   };

   return (n < 1 || n > 12) ? name[0] : name[n];
}


int main(int argc, char **argv){

    printf(month_name(atoi(argv[1])));

}
