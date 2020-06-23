#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define TOKEN_BUFFSIZE 64
#define TOKEN_DELIM " |"


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
 * @return tokens
 */
char **msh_tokenize_line(char *line){

    int buff = TOKEN_BUFFSIZE;
    int i = 0;
    //allocate memory for tokens
    char **tokens = malloc(buff * sizeof(char*));
    char *token;
    //tokenize by delimiter
    token = strtok(line, TOKEN_DELIM);
    //move each token into tokens
    while (token != NULL){
        tokens[i] = token;
        i++;
        token = strtok(NULL, TOKEN_DELIM);
    }

    tokens[i] = NULL;
    return tokens;
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
int pipes_num(char *line){

    int count = 0;
    char p =  '|';

    for(int i = 0; line[i] != '\0'; i++) {
        if (p == line[i]) {
            count++;
        }
    }

    return count;
}

int execute(char **args, int pipes){

    if(args[0] == NULL){
        // nothing on the command line
        return 1;
    }

    else if(strncmp(args[0],"exit",4) == 0){
        // execute exit command
        return 0;
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
    char **commands;
    int running;
    int pipes;
    do{
        printf("%s", username);
        input = msh_read();
        pipes = pipes_num(input);
        commands = msh_tokenize_line(input);
        running = execute(commands,pipes);

    }
    while (running);{
    }
    return 0;
}

