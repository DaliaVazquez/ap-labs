#include <stdio.h>                                  
                                                    
char* reverse(char *word) {                         
    char *reversed_word;                            
    return reversed_word;                           
}                                                   
                                                    
int main(int argc, char **argv){                    
    // Place your magic here                        
    char *word;                                     
                                                    
    word = argv[1];                                 
                                                    
    printf("Original Word: %s \n", word);           
                                                    
    printf("Reversed Word: %s\n", reverse(word));   
    return 0;                                       
}   