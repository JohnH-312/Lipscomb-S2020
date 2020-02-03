#include<stdio.h>
#include<string.h>

int contains(char buff[], char str[]) {
    if (strstr(buff, str)) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) 
{
    int i;          //will track which file we are outputting
    FILE * filepointer;
    char buffer[1000];  //will be repetatively filled with info to be printed

    for (i = 2; i < argc; i++) {    //loops over each file
        filepointer = fopen(argv[i], "r");  //This takes the name provided, opens it to be read
        if (!filepointer) {     //returns false if there is no filepointer
            fprintf(stderr, "Error, No file found!!!");
            return 1;
        }

        while (fgets(buffer, 1000, filepointer)) {      // This is in a while for each line
            if (contains(buffer, argv[1])){
                printf("%s", buffer);
            }
        }

        fclose(filepointer);
    }
    
    return 0;

}
