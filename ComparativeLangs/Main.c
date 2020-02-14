#include <time.h>
#include <stdio.h>
#include <stdlib.h>


time_t heap()
{
    time_t fTime, sTime;
    fTime = clock();

    char * myArray = malloc(sizeof(char)*10000);

    sTime = clock();
    return (sTime - fTime);

}

time_t statica()
{
    time_t fTime, sTime;
    fTime = clock();

    static char vector[10000];
    
    sTime = clock();
    return (sTime - fTime);

}

time_t stack()
{
    time_t fTime, sTime;
    fTime = clock();

    char vector[10000];

    sTime = clock();
    return (sTime - fTime);

}

int main(int argc, char* args[])
{
    time_t heapTime, staticTime, stackTime;
    heapTime = 0;
    staticTime = 0;
    stackTime = 0;

    int i = 0;
    for (i = 0; i < 100000; i++){
        heapTime += heap();
        staticTime += statica();
        stackTime += stack();
    }
    printf("heap: %ld, static: %ld, and stack:%ld", heapTime, staticTime, stackTime);

}