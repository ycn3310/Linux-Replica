#include <stdio.h>

int main(int argc, char **argv){
    char str[4096];
    size_t n;
    FILE* file;
    file = fopen(argv[1], "r");

    if(file == NULL){
        printf("couldn't open the file\n");
        return 0;
    } 
    while((n = fread(str, 1, sizeof(str), file))>0){
        fwrite(str,1,n, stdout);
    }
    fclose(file);
    return 0;
}