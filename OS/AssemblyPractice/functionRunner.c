#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
The point of this program is to test the homemade strlen functions
against what the getline function returns. This is done by printing
all integer array's at the end of the program. All values are
initialized to -1, so if it has not been modified, it will be -1.
*/
int strlen1(char * s);
int strlen2(char * s);
int strlen3(char * s);

int main(int argc, char* argv[])
{
    /*Given a file with 10 lines, test the following answers for parts 2, 3, and 4 against
      a built in c function*/
    FILE * fr;
    char * fileStrings[100];
    //char ** basePointer = fileStrings;
    size_t stringLength = 0;
    int i = 0;
    int answers[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int test1[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int test2[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int test3[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    /*Part 0 -> Opening a file and putting into an array to test all functions from */
    fr = fopen(argv[1], "r");
    for(i = 0; i < 10; i++)
    {
      //printf("%d, ", i);
      fileStrings[i] = NULL; 
      stringLength=0;
      getline(&fileStrings[i], &stringLength, fr); 
    }
    i=0;

    /*Part 1 -> Finds the answer of how long the string is using built in function*/
    for(i = 0; i < 10; i++)
    {
      answers[i] = strlen(fileStrings[i]); 
    }

    /*Part 2 -> Testing strlen1 (function using recursion)*/
    for(i = 0; i<10; i++)
    {
      test1[i] = strlen1(fileStrings[i]);
    }

    /*Part 3 -> Testing strlen2 (function using array indexes)*/
    for(i = 0; i<10; i++)
    {
      test2[i] = strlen2(fileStrings[i]);
    }
    
    /*Part 4 -> Testing strlen3 (function using a pointer)*/
    for(i=0; i<10; i++)
    {
      //printf("hit\n");
      test3[i] = strlen3(fileStrings[i]);
    }

    /*Part 5 -> Outputting all answers to the string lengths*/
    printf("Proper Answers:\n");
    for(i = 0; i < 9; i++)
    {
      printf("%d, ",answers[i]);
    }
    printf("%d.\n\n", answers[9]);

    printf("strlen1 function:\n");
    for(i = 0; i < 9; i++)
    {
      printf("%d, ",test1[i]);
    }
    printf("%d.\n\n", test1[9]);

    printf("strlen2 functions:\n");
    for(i = 0; i < 9; i++)
    {
      printf("%d, ",test2[i]);
    }
    printf("%d.\n\n", test2[9]);

    printf("strlen3 functions:\n");
    for(i = 0; i < 9; i++)
    {
      printf("%d, ",test3[i]);
    }
    printf("%d.\n", test3[9]);

    /* Part 6 -> Free everything and end program*/
    //free(fileStrings);
    return 0;
}