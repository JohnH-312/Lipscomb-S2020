#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include<dirent.h>

void printList(char ** out, int len){
    int i;
    for (i =0; i< len; i++) {
        //printf("%d",i);
        printf("%s", out[i]);
        printf("\n");
    }
}

int main(int argc, char *argv[]) 
{
    DIR * directory;
    struct dirent * file;
    int max = 1000;
    char ** buffer = malloc(max*sizeof(char *));
    int filenum = 0;

    if (argc == 1) {
        directory = opendir(".");
    } else {
        directory = opendir(argv[1]);
    }
    if (directory == NULL) {
        fprintf(stderr, "ERROR");
        return 0;
    } else {
        while ((file = readdir(directory)) != NULL) {
            if (file->d_name[0] != '.') {
                if (file->d_type == DT_DIR) {
                    //directory
                    //printf("%s/\n", file->d_name);
                    buffer[filenum] = strcat(file->d_name, "/\n");
                } else {
                    //not directorys
                    //printf("%s\n", file->d_name);
                    buffer[filenum] = strcat(file->d_name, "\n");
                }
            }
            filenum++;
            if (filenum >= max) {
                max = max * 2;
                buffer = realloc(buffer, max*sizeof(char *));
            }
        }
    }
    printList(buffer, filenum);
    closedir(directory);


    int j;
    for (j = 0; j < filenum; j++) {
        free(buffer[filenum]);
    }
    free(buffer);
    return 0;

}
