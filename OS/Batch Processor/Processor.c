#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    FILE *fp;
    fp = fopen(argv[1], "r");
    char *line;
    size_t max = 1000;
    char *buffer[1000];
    int i = 0;
    //printf("hulo\n");
    char *path[1000];
    path[0] = "/bin";
    int pathcount = 1;
    int maxpathcount = 0;
    //char newout[1000];
    //int makenewout = 0;
    //int diffout = 0;
    char copypath[1000];
    //int outfile = 0;
    //int stdsave = 0;
    int somthin = 0;

    while (getline(&line, &max, fp) >= 0){
        //diffout = 0;
        //strcpy(newout, "stdout");
        //printf("bah\n");
        buffer[0] = strtok(line, " ");
        //printf("boo\n");
        if (buffer[0] == NULL) {
            continue; //blank line
        }
        buffer[0][strcspn(buffer[0], "\n")] = 0;
        //printf("%s\n", buffer[0]);
        //makenewout = 0;
        for (i = 1;; i++){
            buffer[i] = strtok(NULL, " ");
            /*if(makenewout == 1){
                strcpy(newout, buffer[i]);
                makenewout = 0;
                diffout = 1;
                printf("Your new out is %s, i is %d, bufs are %s and %s\n", newout, i, buffer[i], buffer[i-1]);
                
                i = i - 1;
                break;
            }*/
            if (buffer[i] == NULL || strcmp(buffer[i], "#") == 0) {
                break;
            } /*else if (strcmp(buffer[i], ">") == 0) {
                makenewout = 1;
            } */
            buffer[i][strcspn(buffer[i], "\n")] = 0;
        }
        //printf("If time, i is %d\n", i);
        if (strcmp(buffer[0], "#") == 0){
            continue;
        }
        if (strcmp(buffer[0], "path") == 0){
            //does path stuff
            int f = 0;
            if (i == 1) {
                for (f = 0; f < pathcount; f++){
                    printf("%s \n", path[f]);
                }
                continue;
            }
            //printf("modifying path %d \n", i);
            pathcount = 0;
            for (f = 1; f < i ;f++) {
                path[pathcount] = malloc(strlen(buffer[f])+1);
                strcpy(path[pathcount], buffer[f]);
                //printf("%s %s\n", path[pathcount], buffer[f]);
                pathcount++;
                if (pathcount >= maxpathcount) {
                    maxpathcount = pathcount;
                }
            }
            
        } else if (strcmp(buffer[0], "exit") == 0){
            //does exit stuff
            //printf("exit time\n");
            if (buffer[1] != NULL) {
                fprintf(stderr, "Well... well... well... you tried to exit with a parameter.\n");
            } else {
                //printf("im done\n");
                break;
                //printf("oops i didnt break\n");
            }
        } else if (strcmp(buffer[0], "&") == 0) {
            // background stuff
            //printf("I'd do a background thing rn\n");
            /*int t = 0;
            for (t = 0; t < i; t++) {
                printf("%s%d\n", buffer[t], i);
            }*/
            pid_t childPID = fork();
            
            if (childPID < 0) {
                //Error occured
                fprintf(stderr, "Fork failed to create child.\n");
                //exit(-1);
            } else if (childPID > 0) {
                //this process is the parent
                //printf("I'm the parent %d and the child is %d\n",getpid(), childPID);
                //wait(NULL);
                fprintf(stderr, "%s: started\n", buffer[0]);
            } else {
                // This process is the child
                //printf("I'm the child %d, and the parent is %d\n", getpid(), getppid());
                /*if (diffout == 1) {
                    fflush(stdout);
                    stdsave = dup(1);
                    outfile = open(newout, O_WRONLY|O_CREAT);
                    dup2(outfile, 1);
                    close(outfile);
                }*/
                    
                //char * args[i];
                //int m = 0;
                //for (m = 0; m < i; m++){
                 //   args[m] = buffer[m];
                //}
                int k = 0;
                strcpy(copypath, "");
                for (k = 0; k < pathcount; k++){
                    //printf("checking path %d, my num is %d and the path is %s and the file is %s\n", k, access(strcat(strcat(path[k], "/"), buffer[0]), F_OK), path[k], buffer[0]);
                    strcpy(copypath, path[k]);
                    if (access(strcat(strcat(copypath, "/"), buffer[1]), F_OK) == 0) {
                        //printf("I am going to execute it NOW\n");
                        
                        execv(copypath, &buffer[1]);
                        break;
                    }
                }
                /*if (diffout == 1) {    
                    fflush(stdout);
                    dup2(stdsave, 1);
                    close(stdsave);
                }*/
            }
        } else {
            //does thing
            //printf("I'd do that thing for ya %d\n", diffout);
            
            pid_t childPID = fork();
            //printf("passed that blob %d\n", childPID);
            if (childPID < 0) {
                //Error occured
                fprintf(stderr, "Fork failed to create child.\n");
                //exit(-1);
            } else if (childPID > 0) {
                //this process is the parent
                //printf("I'm the parent %d and the child is %d\n",getpid(), childPID);
                wait(&somthin);
                if(WIFEXITED(somthin)) {
                    fprintf(stderr, "%s: exited with %d\n", buffer[0], WEXITSTATUS(somthin));
                }
            } else {
                // This process is the child
                //printf("I'm the child %d, and the parent is %d\n", getpid(), getppid());
                //printf("%d",diffout);
                /*if (diffout == 1) {
                    fflush(stdout);
                    stdsave = dup(1);
                    outfile = open(newout, O_WRONLY|O_CREAT);
                    dup2(outfile, 1);
                    close(outfile);
                }*/
                    //printf("Yes hello im alive still \n");
                //char * args[i];
                //int m = 0;
                //printf("about to for \n");
                //for (m = 0; m < i; m++){
                    //printf("No\n");
                    //args[m] = buffer[m];
                    //printf("Yes\n");
                //}
                //printf("Yes I copied the args\n");
                int k = 0;
                strcpy(copypath, "");
                for (k = 0; k < pathcount; k++){
                    //printf("checking path %d, my num is %d and the path is %s and the file is %s\n", k, access(strcat(strcat(path[k], "/"), buffer[0]), F_OK), path[k], buffer[0]);
                    strcpy(copypath, path[k]);
                    if (access(strcat(strcat(copypath, "/"), buffer[0]), F_OK) == 0) {
                        //printf("I am going to execute it NOW\n");
                        execv(copypath, &buffer[0]);
                        break;
                    }
                }
                //printf("this is what the copy path was%s\n", copypath);
                //int t = 0;
                //for (t = 0; t < i; t++) {
                    //printf("%s %d\n", args[t], i);
                //}
                /*if (diffout == 1) {    
                    fflush(stdout);
                    dup2(stdsave, 1);
                    close(stdsave);
                }*/
            }
        }
    }
    int j = 1;
    for (j = 1; j < maxpathcount ;j++) {
        free(path[j]);
    }
    return 0;
    


}