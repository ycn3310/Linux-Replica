#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    FILE* file;
    if(argc<3){
        printf("grep [option] [pattern] [path]");
        return 1;
    }

    file = fopen(argv[argc-1], "r");
    if(file == NULL){
        printf("couldn't open the file\n");
        return 1;
    }
    
    char str[4096];
    char line[8192];
    size_t line_len =0;
    size_t n;
    int count =0;
    size_t found = 0;
    size_t v = strlen(argv[1]);

    char* pattern = argv[argc-2];
    char* path = argv[argc-1];
    
    char LinesParameter[] = "-n";
    char Matchinglines[] = "-c";
    char IncaseSensitive[] = "-i";
    while(fgets(line, sizeof(line), file)){
        if(strstr(line, pattern)){
            found ++;
            if(strstr(argv[1], LinesParameter)){ 
                printf("%i %s",count, line);
            } else if (strstr(argv[1], Matchinglines)){
                printf("lines matching: %i" ,found);
            } else {
                printf("%s", line);
            }
        }
        count++;
    }
    
    fclose(file);
    return 0;
}