/*
 * Program 2
 *
 *
 *Brandon Castor 817046315 cssc 2129
 *
 * Alexander Howes 820184866 cssc 2165
 *
 * cs 570
 *
 *date: 6/29/2020
 *
 * program2: acts as a simple unix shell interpreter,  it reads a line from
 * stdin and tokenizes the line into executable arguments that are passed into
 * an execute function which then uses piping to execute those commands in the shell.
 * The only built in unix function availble is exit.
 */


#include "main.h"

char* msh_read(void){


    char line[MAX];

    fgets(line, MAX, stdin);

    int len = strlen(line);
    //replace new line with null pointer
    if(line[strlen(line) - 1 == '\n']){

        line[strlen(line) - 1] = '\0';

    }

    char *str = malloc(len + 1);
    //return copy of the input pointer
    return strcpy(str, line);

}


void msh_tokenize_line(char* line){
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

int execute(char ***commands){

    pid_t pid;
    int i = 0;
    int fd[2];
    int stat;
    int f_in;
    int j;

    //checks the line for exit commands end returns 0 if found
    for(j = 0; j <= arguments; j++){

        if(strcmp(commands[j][0],"exit") == 0){

            return 0;
        }
    }
    //go through every command and fork for every argument
    while(i <= arguments){
    //parent
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
                    printf("ERROR CODE: %d", WEXITSTATUS(stat));
                }
            }
            f_in = fd[0];
            if(i == arguments){
                printf("\n \n");
            }
        }
        else{//child
            dup2(f_in,0);

            if(i != arguments){
                dup2(fd[1],1);//write to pipe
            }
            close(fd[0]);
            //execute command and args
            execvp(commands[i][0], *commands);
            exit(EXIT_FAILURE);
        }

        i++;//next command

    }
    return 1;

}

void msh_shell(){

    char username[] = "cssc2165% ";
    char *input;
    int running;

    do{

        fflush(stdin);//clear stdin
        fflush(stdout);
        printf("%s", username);
        input = msh_read();// read line
        msh_tokenize_line(input);// tokenize
        running = execute(commands);// execute commands and arguments
        free(commands);

    }   //run until execute returns 0 in case of exit
    while (running);{
    }

}

int main(){

    //initialize unix shell
    msh_shell();

    return EXIT_SUCCESS;
}

