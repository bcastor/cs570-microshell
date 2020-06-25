#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define TOKEN_DELIM " \n\t"

char *commands[100][100];
int arguments = 0;

/**
 * reads user input and returns it as output
 * @return line
 */
char *msh_read(void){

    char *line = NULL;
    size_t buffsize = 0;

    if(getline(&line, &buffsize, stdin) == 0){
        if(feof(stdin)){
            exit(EXIT_SUCCESS);//end of line
        }

        else{
            perror(">> Input error!\n");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}
/**
 * tokenizes a line by a delimiter and splits the line
 * by a delimiter and converts it to tokens
 *
 * @param line
 * @return arguments
 */
char **msh_tokenize_line(char *line){

    int i = 0;

    //clear array
    memset(commands, 0, sizeof(commands[0][0]) * 100 * 100);
    char *token;
    char *token2;

    //tokenize by delimiter
    token = strtok(line, TOKEN_DELIM);

    token2 = token;
    //move each token into tokens
    while (token2 != NULL){

        if(strcmp(token2,"|") != 0){

            commands[arguments][i]  = token2;
            i++;
            token2 = strtok(NULL, TOKEN_DELIM);
        }
       else{//argument was found
           commands[arguments][i] = NULL;
           arguments++;
           i = 0;
           token2 = strtok(NULL, TOKEN_DELIM);
       }
    }

    commands[arguments][i] = NULL;

    return commands;
}
///*
//this is to check if the file is in the current directory
//*/
//int checkdir(const char* filename) {
//    FILE* file;
//    if (file = fopen(filename, "r")) {
//        fclose(file);
//        return 1;
//    }
//    return 0;
//}
/**
 * checks the string for character '|' and returns the
 * instances in the given string
 * @param line
 * @return number of pipes
 */


int execute(char *commands[100][100]){

    pid_t pid;
    int i = 0;
    int fd[2];
    int stat;
    int f_in;

    while(i <= arguments){

        pipe(fd);
        pid = fork();

        if(pid != 0) {
            //close once child ends process
            waitpid(pid, &stat, 0);
            close(fd[1]);
            if (WIFEXITED(stat)) {

                if (WIFEXITED(stat) == 0) {

                } else if (WEXITSTATUS(stat) == 255) {
                    printf(" %s does not exist \n", commands[i][0]);
                } else {
                    printf("ERROR: ERROR code: %d", WEXITSTATUS(stat));
                }
            }
            f_in = fd[0];
            if(i == arguments){
                printf("\n \n");
            }
        }
        else{
            dup2(f_in,0);

            if(i != arguments){
                dup2(fd[1],1);//write to pipe
            }
            close(fd[0]);
            exit(execvp(commands[i][0], commands[i]));
            return 0;
        }

        i++;

    }
    return 1;

}
//int checkexe(const char* filename){
//    char *symlinkpath = filename;
//    char actualpath [PATH_MAX+1];
//    char *ptr;
//    ptr = realpath(symlinkpath, actualpath);
//    if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
//        return 1;
//    else
//        return 0;
//}

int main(){
    char username[] = "cssc2165% ";
    char *input;
    int running;

    do{
        printf("%s", username);
        input = msh_read();
        running = execute(msh_tokenize_line(input));

    }
    while (running);{
    }
    return 0;
}

