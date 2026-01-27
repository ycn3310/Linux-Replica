#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(int argc, char **argv){
    HANDLE filehandle;
    WIN32_FIND_DATA ffd;
    char *name=NULL, *type=NULL, *size=NULL, *mtime=NULL, *filepath=argv[argc-1];
    int   nameFlag=0, typeFlag=0, sizeFlag=0, mtimeFlag=0;

    if(argc<2){
        printf("where [options] [path]");
    } else{
        for(int i =1; i<argc; i++){
            if(!strcmp(argv[i], "-name")&& i + 1 < argc){
                name = argv[i+1]; nameFlag=1;
            }
            if(!strcmp(argv[i], "-type")&& i + 1 < argc){
                type = argv[i+1]; typeFlag=1;
            }
            if(!strcmp(argv[i], "-size")&& i + 1 < argc){
                size = argv[i+1]; sizeFlag=1;
            }
            if(!strcmp(argv[i], "-mtime")&& i + 1 < argc){
                mtime = argv[i+1]; mtimeFlag=1;
            }
        }
    }

    if(argc == 3 || !strcmp(filepath,"./")){
        strcpy(filepath, ".\\*");
    } else{
        strcat(filepath, "\\*");
    }
    filehandle = FindFirstFile(filepath,&ffd);

    do{
        if(!(nameFlag&&sizeFlag&&mtimeFlag&&typeFlag)){
            printf("no name was provided!");
            FindClose(filehandle);
            return 1;
        } else {
            if(typeFlag){
                if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && strcmp(ffd.cFileName, Filename)==0)
                {
                    GetFullPathName(Filename,MAX_PATH,path,NULL);
                    printf("\033[32;1m%s\033[0m\n", path);
                }
            } else {

            }
        }
    }while(FindNextFile(filehandle, &ffd));

    FindClose(filehandle);
    return 0;
}
