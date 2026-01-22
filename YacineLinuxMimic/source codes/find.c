#include <stdio.h>
#include <string.h>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

int main(int argc, char **argv){
    enableANSI();
    HANDLE filehandel;
    WIN32_FIND_DATA ffd;
    char path[MAX_PATH];

    if(argc==2){
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
    char *Filename = argv[1];

    filehandel = FindFirstFile(path, &ffd);

    DWORD attr = GetFileAttributes(argv[1]);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        printf("File does not exist\n");
        return 1;
    }

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
    do{
        if (!strcmp(ffd.cFileName, Filename))
        {
            GetFullPathName(Filename,MAX_PATH,path,NULL);
            printf("\033[32;1m%s\033[0m\n", path);
        }
        
        
    }while (FindNextFile(filehandel, &ffd));  
    FindClose(filehandel); 
}