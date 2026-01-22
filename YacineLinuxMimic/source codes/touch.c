#include <stdio.h>

int main(int argc, char **argv){
    FILE *Createfile;
    for(int i = 1; i<argc; i++){
        Createfile = fopen(argv[i], "a");
        if(Createfile == NULL){
            perror(argv[i]);
            continue;
        }
        fclose(Createfile);
    }
    return 0;
}