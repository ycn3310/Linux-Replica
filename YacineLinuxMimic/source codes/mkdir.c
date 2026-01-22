#include <stdio.h>
#include <direct.h>

int main(int argc, char **argv){
    for(int i = 1; i< argc; i++){
        char *FolderName = argv[i];
        if(_mkdir(FolderName) !=0){
            perror("Error creating folder");
        }
    }
    return 0;
}