#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(int argc, char **argv){
    HANDLE filehandel;
    WIN32_FIND_DATA ffd;
    char path[MAX_PATH];

    if(argc==1){
        strcpy(path, ".\\*");
    } else {
        char *lastarg = argv[argc-1];
        if(lastarg[0]=='-'){
            strcpy(path, ".\\*");
        } else { 
            strcpy(path, lastarg);
            if(path[strlen(path)-1] != '\\'){
                strcat(path, "\\");
            }
            strcat(path, "*");
        }
    }

    filehandel = FindFirstFile(path, &ffd);

    if(INVALID_HANDLE_VALUE == filehandel){
        switch(GetLastError()){
            case 3:
            printf("coudn't find the path");
            break;

            case 5:
            printf("Access denied");
            break;

            case 123:
            printf("Error in path format");
            break;

            default:
            printf("error code:%lu", GetLastError());
            break;
        } 
        return 1;
    }
    char *Filename = argv[1];
    do{
        if (ffd.cFileName == Filename)
        {
            printf("")
        }
        
        
    }while (FindNextFile(filehandel, &ffd));   
}