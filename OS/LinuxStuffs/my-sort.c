#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int contains(char buff[], char str[]) {
    if (strstr(buff, str)) {
        return 1;
    } else {
        return 0;
    }
}

void printList(char ** out, int len){
    int i;
    for (i =0; i< len; i++) {
        //printf("%d",i);
        printf("%s\n", out[i]);
    }
}

int comparestr(const void *a, const void *b) {
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

void chomp(char * boop) {
    int i;
    for (i = 0; boop[i] != 0; i++) {
        if (boop[i] == '\n') {
            boop[i] = 0;
            return;
        }
    }
}

int dothings(FILE * filepointer, char ** buffer, char ** lines, int num, int max) {
    size_t n = 1000;
    int linenum = num;
    while (getline(buffer, &n, filepointer) != -1) {      // This is in a while for each line
        lines[linenum] = strdup(*buffer);
        chomp(lines[linenum]);
        linenum ++;
        if (linenum >= max) {
            max = max * 2;
            lines = realloc(lines, max*sizeof(char *));
        }
    }
    return linenum;
}

int main(int argc, char *argv[]) 
{
    int i;          //will track which file we are outputting
    FILE * filepointer;
    int max = 1000;
    char ** lines = malloc(max*sizeof(char *));
    char * buffer = malloc(1000*sizeof(char));  //will be repetatively filled with info to be printed
    int linenum = 0;


    if (argc == 0) {
        filepointer = stdin;
        linenum += dothings(filepointer, &buffer, lines, linenum, max);
        while (linenum >= max) {
            max = max * 2;
        }
    } else {
        for (i = 1; i < argc; i++) {    //loops over each file
            filepointer = fopen(argv[i], "r");  //This takes the name provided, opens it to be read
            if (!filepointer) {     //returns false if there is no filepointer
                fprintf(stderr, "Error, No file found!!!\n");
                return 1;
            }
            linenum += dothings(filepointer, &buffer, lines, linenum, max);
            while (linenum >= max) {
                max = max * 2;
            }

            fclose(filepointer);
            
        }
    }
    qsort(lines, linenum, sizeof(char *), comparestr);
    //printf("ding\n");
    printList(lines, linenum);
    //printf("done\n");
    int j;
    for (j = 0; j < linenum; j++) {
        free(lines[linenum]);
    }
    free(lines);
    free(buffer);
    return 0;

}
