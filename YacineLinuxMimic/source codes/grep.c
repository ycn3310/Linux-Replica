#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc<3){
        printf("grep [option] [pattern] [path]");
        return 1;
    }

    FILE* file;
    file = fopen(argv[argc-1], "r");
    if(file == NULL){
        printf("couldn't open the file\n");
        return 1;
    }

    int l = 0;
    int c = 0;
	int n = 0;
    int v = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && strstr(argv[i], "l")) {
            l = 1;
        }
        if (argv[i][0] == '-' && strstr(argv[i], "c")) {
            c = 1;
        }
        if (argv[i][0] == '-' && strstr(argv[i], "n")) {
            n = 1;
        }
        if (argv[i][0] == '-' && strstr(argv[i], "v")) {
            v = 1;
        }
    }

    char* pattern = argv[argc - 2];
    char* path = argv[argc - 1];

    if (argc == 1) {
        strcpy(path, ".\\*");
    }
    else {
        char* lastarg = argv[argc - 1];
        if (lastarg[0] == '-') {
            strcpy(path, ".\\*");
        }
        else {
            strcpy(path, lastarg);
            if (path[strlen(path) - 1] != '\\') {
                strcat(path, "\\");
            }
            strcat(path, "*");
        }
    }
    
    char str[4096];
    char line[8192];
    size_t line_len =0;
    size_t found = 0;


    int count = 1;

    
    
    while (fgets(line, sizeof(line), file)) {
        int match = strstr(line, pattern) != NULL;
        if (v) {
            match = !match;
        }
        if (match) {
            found++;
            if (!c) {
                if (n) {
                    printf("%d:%s", count, line);
                }
                else {
                    printf("%s", line);
                }
            }
        }
        count++;
    }
    
    if (c) {
        printf("%d\n", found);
    }
    
    fclose(file);
    return 0;
}
