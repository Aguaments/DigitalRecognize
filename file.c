#include "file.h"

char ** AcquireFileList(char * filePath){
    DIR * dir;
    struct dirent * entry;
    int index = 0;

    char ** p = (char **) malloc(sizeof(char*) * 10);
    for(int i = 0; i < 10; ++ i){
        p[i] = (char*)malloc(sizeof(char) * 6);
    }
    if((dir = opendir(filePath)) == NULL){
        printf("Filepath not exists...\n");
//            break;
    }else{
        while((entry = readdir(dir)) != NULL){
            if(strstr(entry->d_name, ".pgm")){
                strcpy(p[index], entry->d_name);
                index ++;
            }
        }
    }
    closedir(dir);
    return p;
}

bool CheckName(char * fileName, char** fileArray){
    int eFlag = 0;

    for(int i = 0; i < 10; ++ i){
        if(strcmp(fileName, fileArray[i]) == 0){
            eFlag = 1;
        }
    }
    if(eFlag == 0) return false;
    return true;
}

char * GetEnterFileList(char * fileName){
    int len = 0, num = 0, index = 0;
    char *p = fileName;

    len = (int)strlen(fileName);
    if(fileName[len - 1] == '\n'){
        fileName[len - 1] = '\0';
    }
    return fileName;
}