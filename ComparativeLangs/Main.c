#include <time.h>;
#include <stdio.h>;

int main(int argc, char* args[])
{
    time_t heapTime, staticTime, stackTime;
    heapTime = heap();
    staticTime = static();
    stackTime = stack();
    printf("heap: %d, staic: %d, and stack:%d", heapTime, staticTime, stackTime);

}

time_t heap()
{
    time_t fTime, sTime;
    fTime = clock();

    char * myArray = malloc(sizeof(char)*10000);

    sTime = clock();
    return (sTime - fTime);

}

time_t static()
{
    time_t fTime, sTime;
    fTime = clock();

    static char vector[10000] myArray;

    sTime = clock();
    return (sTime - fTime);

}

time_t stack()
{
    time_t fTime, sTime;
    fTime = clock();

    char vector[10000] myArray;

    sTime = clock();
    return (sTime - fTime);

}