

int mystrlen(char *str){
    int i = 0;
    char c;
    while(c=str[i]!='\0'){
        i++;
    }
    return i;
}

char *mystradd(char *origin, char *addition){
    char *res = origin + mystrlen(origin);
    while (*addition != '\0'){
        *res++ = *addition++;
    }

    *res = '\0';
    return origin;
}

int mystrfind(char *origin, char *substr){
    int ver = mystrlen(substr);
    int i = 0;
    int j = 0;
    int n = 0;

    while (origin[i] != '\0') {
        n = i;
        while (origin[i] != '\0' && origin[i] == substr[j]) {
            i++;
            j++;
        }
        if (j == ver) {
            return n;
        }
        i++;
        j = 0;
    }
    return 0;
}
