#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>

int main(int argc, char **argv){
    char pwd[MAX_PATH];
    if(getcwd(pwd, sizeof(pwd))==NULL){
        printf("coudn't get the current working directory");
    }
    printf("%s", pwd);
    return 0;
}