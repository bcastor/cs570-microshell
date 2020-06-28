#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define TOKEN_DELIM " \n\t"

char ***commands;
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
void msh_tokenize_line(char *line){
    int i;
    int j;
    int k = 0;

    //allocate memory for array
    commands = malloc(10 * sizeof(char **));
    for (i = 0; i < 10; i++){
        commands[i] = malloc(10 * sizeof(char  *));
    }

    for (i = 0; i < 2; i++){
        for(j = 0; j < 10; j++){
            commands[i][j] = malloc(10 * sizeof(char));
        }
    }


    char *token;
    char *token2;

    //tokenize by delimiter
    token = strtok(line, TOKEN_DELIM);

    token2 = token;
    //move each token into tokens
    while (token != NULL){

        if(strcmp(token2,"|") != 0){

            commands[arguments][k]  = token;
            k++;
            token = strtok(NULL, TOKEN_DELIM);
        }
       else{//argument was found
           commands[arguments][k] = NULL;
           arguments++;
           k = 0;
           token = strtok(NULL, TOKEN_DELIM);
       }
    }

    commands[arguments][k] = NULL;

}

/**
 * checks the string for character '|' and returns the
 * instances in the given string
 * @param line
 * @return number of pipes
 */


int execute(char ***commands){

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
                    printf("ERROR CODE:: %d", WEXITSTATUS(stat));
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
            exit(execvp(commands[i][0], *commands));
            return 0;
        }

        i++;

    }
    return 1;

}

void msh_shell(){

    char username[] = "cssc2165% ";
    char *input;
    int running;

    do{
        printf("%s", username);
        input = msh_read();
        msh_tokenize_line(input);
        running = execute(commands);
        free(commands);

    }
    while (running);{
    }

}

int main(){

    msh_shell();

    return EXIT_SUCCESS;
}

