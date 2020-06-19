#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TOKEN_BUFFSIZE 64
#define TOKEN_DELIM " \n"


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
/*
this is to check if the file is in the current directory
*/
int checkdir(const char* filename) {
    FILE* file;
    if (file = fopen(filename, "r")) {
        fclose(file);
        return 1;
    }
    return 0;

}
int main(){
    char username[] = "cssc2165% ";
    char command[200];
    int condition = 1;
    while (condition = 1){
        printf("%s", username);
        scanf("%s\n", command);
    }
    return 0;
}

