#include <stdio.h>                                  
                                                    
#include <stdio.h>                                   
#include <string.h>                                  
                                                     
                                                     
char* reverse(char *word) {                          
    char *reversed_word;                             
    char tmp;                                        
    int lenght = strlen(word);                       
                                                     
    reversed_word = word;                            
                                                     
    for (int i = 0; i < lenght/2; i++) {             
        tmp = reversed_word[i];                      
        reversed_word[i] = reversed_word[lenght-i-1];
        reversed_word[lenght - i - 1]  = tmp;        
    }                                                
                                                     
    return reversed_word;                            
}                                                    
                                                     
int main(int argc, char **argv){                     
                                                     
    char *word;                                      
    word = argv[1];                                  
                                                     
    printf("Original Word: %s \n", word);            
                                                     
    printf("Reversed Word: %s\n", reverse(word));    
    return 0;                                        
}       