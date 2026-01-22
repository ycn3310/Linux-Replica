#include <stdio.h>
#include <windows.h>
#include <string.h>


int main(int argc, char **argv){
    HANDLE filehandel;
    WIN32_FIND_DATA ffd;
    char path[MAX_PATH];

    int l =0;
    for(int i=1; i<argc; i++){
        if(argv[i][0]=='-' && strstr(argv[i], "l")){
            l =1;
        }
    }

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
    int count =0;
    if(l){
        do {
            count++;
            SYSTEMTIME st;
            FileTimeToSystemTime(&ffd.ftLastWriteTime, &st);
            unsigned long long filesize = ((unsigned long long)ffd.nFileSizeHigh << 32) | ffd.nFileSizeLow;

            if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ 
                printf("d %-10llu %02d/%02d/%d %02d:%02d %s\n" , filesize,st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, ffd.cFileName);
            } else{
                printf("- %-10llu %02d/%02d/%d %02d:%02d %s\n" , filesize,st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, ffd.cFileName);
            }
            
        } while (FindNextFile(filehandel, &ffd));
        printf("\n\ntotal: %i", count);
    }else{
        do {
            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printf("\033[32;1m%s \033[0m\n" , ffd.cFileName);
            } else if (ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {
                printf("\033[34;1m%s \n" , ffd.cFileName);
            } else {
                printf("\033[0;1m%s \033[0m\n" , ffd.cFileName);
            } 
        } while (FindNextFile(filehandel, &ffd));   
    }

    FindClose(filehandel);
    return 0;
}