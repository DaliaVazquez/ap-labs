#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>

#define REPORT_FILE "report.txt"
#define SIZE 1000

void analizeLog(char *logFile, char *report);

struct Node{
    char  *data;
    struct Node *next;
};
struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
    struct Node *val;
};

struct nlist *hashtable[SIZE];

unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 * hashval;
    }
    return hashval % SIZE;
}

struct nlist *lookup(char *s){
    struct nlist *np;
    for(np = hashtable[hash(s)]; np !=NULL; np = np->next){
        if(strcmp(s,np->name)==0){
            return np;
        }
    }
    return NULL;
}

void crea(struct Node** r, char *dato){
    struct Node* nodo = (struct Node*)calloc(1,sizeof(struct Node));
    nodo->data  =strdup(dato);
    nodo->next = (*r);
    (*r)= nodo;
}
struct nlist *install(char *name, char *defn){
    struct nlist *np;
    unsigned hashval;
    if((np=lookup(name))==NULL){ //not found
        np = (struct nlist *) calloc(1,sizeof(*np));
        if(np == NULL || (np->name=strdup(name))==NULL){
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtable[hashval];
        hashtable[hashval] = np;
        np->val=NULL;
    }else
        free((void *)np->defn);
    if((np->defn = strdup(defn))==NULL)
        return NULL;
    crea(&np->val,defn);
    return np;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);
    // Implement your solution here.
    mode_t param = S_IRUSR |  S_IWGRP|S_IWUSR | S_IRGRP | S_IROTH | S_IWOTH;
    int bandera = O_CREAT | O_WRONLY | O_TRUNC;
    int file = open(logFile,O_RDONLY);
    int salida = open(report,bandera,param);
    if (file == -1 || salida == -1){
        printf("Error: abrir archivo\n");
        exit(-1);
    }
    
    struct nlist *ini;
    struct Node *nodes;
    off_t n;
    char buf[10];
    long tam=0;
    ssize_t num;
    while ((num = read(file, buf, 1)) > 0){
        if(strcmp(buf,"\n")!=0){
            tam++;
        }else{
            if((n=lseek(file,-tam-1,SEEK_CUR))==-1){
                printf("Error\n");
                exit(-1);
            }
            ssize_t lineread;
            int fin=0, inicio = 14;
            char *line = (char *) calloc(tam,sizeof(char));
            if((lineread= read(file,line,tam))<0){
                free(line);
                printf("Error: line\n");
                exit(-1);
            }
            int len = strlen(line);
            char *categoria=calloc(len,sizeof(char));
            char *log=calloc(len,sizeof(char));
            for(int i=inicio;i<len-1;i++){
                if(line[i]==':'&&line[i+1]==' '){
                    fin=i;
                    i=len;
                }
            }
            if(fin==0){
                categoria="general\0";
                log=line;
                log[len]='\0';
            }else{
                int ind=0;
                for (int i = inicio; i < fin; i++)
                {
                    categoria[ind++]=line[i];
                }
                categoria[ind]='\0';
                ind = 0;
                for (int i = 0; i < inicio; i++)
                {
                    log[ind++]=line[i];
                }
                for (int i = fin; i < len; i++)
                {
                    log[ind++]=line[i];
                }
                log[ind]='\0';
            }
            install(categoria,log);
            tam=0;
            if((n=lseek(file,1,SEEK_CUR))==-1){
                free(line);
                printf("Error: line\n");
                exit(-1);
            }
            free(line);
        }
    }

    if (tam>0){
        if((n=lseek(file,-tam,SEEK_CUR))==-1){
            printf("Error\n");
            exit(-1);
        }
        char *line = (char *) calloc(tam,sizeof(char));
        ssize_t lineread;
        if((lineread= read(file,line,tam))<0){
            printf("Error: line\n");
            free(line);
            exit(-1);
        }
        int len = strlen(line);
        int inicio = 14, fin=0;
        char *log=(char *)calloc(len,sizeof(char));
        char *categoria=(char *)calloc(len,sizeof(char));
        for(int i=inicio;i<len-1;i++){
            if(line[i]==':'&&line[i+1]==' '){
                fin=i;
                i=len;
            }
        }
        if(fin!=0){
            int ind=0;
            for (int i = inicio; i < fin; i++){
                categoria[ind++]=line[i];
            }
            categoria[ind]='\0';
            ind = 0;
            for (int i = 0; i < inicio; i++){
                log[ind++]=line[i];
            }
            for (int i = fin; i < len; i++) {
                log[ind++]=line[i];
            }
            log[ind]='\0';
        }else{
            log=line;
            log[len]='\0';
            categoria="general\0";
        }
        tam=0;
        install(categoria,log);
        free(line);
    }

    for (int i=0;i<SIZE;i++){
        ini = hashtable[i];
        if (ini!=NULL){
            int tam=0;
            for(int i=0;i<strlen(ini->name);i++){
                tam++;
                if(ini->name[i]=='\0'){
                    i=strlen(ini->name);
                }
            }
            if (write(salida, ini->name, tam) <0 || write(salida, ":\n", 2) <0)
                exit(-1);
            for (nodes=ini->val;nodes!=NULL;nodes=nodes->next){
                int tam2=0;
                for(int i=0;i<strlen(nodes->data);i++){
                    tam2++;
                    if(nodes->data[i]=='\0'){
                        i=strlen(nodes->data);
                    }
                }
                if (write(salida, "  ", 2) <0 )
                    exit(-1);
                else if (write(salida, nodes->data, tam2) <0)
                    exit(-1);
                else if (write(salida, "\n", 1) <0)
                    exit(-1);
                    
            }
        }
    }

    if (num == -1)
        exit(-1); 
    if (close(file) == -1 || close(salida) == -1){
        printf("Error: cerrar \n");
        exit(-1);
    }

    printf("Report is generated at: [%s]\n", report);
}

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./dmesg-analizer logfile.txt\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}