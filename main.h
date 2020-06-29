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

//change cs570A2 to just A2 for edoras
#ifndef cs570A2_MAIN_H
#define cs570A2_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define TOKEN_DELIM " \n\t"//token delimiters
#define MAX 255 //max size for input

char ***commands; //array for commands
int arguments = 0;//number of arguments being passed

/**
 * reads user input and returns it as output
 * @return line
 */
char* msh_read(void);
/**
 * tokenizes a line by a delimiter and splits the line
 * by a delimiter and converts it to tokens
 *
 * @param line
 * @return arguments
 */
void msh_tokenize_line(char* line);
/**
 * checks the string for character '|' and returns the
 * instances in the given string
 * @param line
 * @return number of pipes
 */
int execute(char ***commands);
/**
 * initializes the shell with a continuos loop that exists
 * once the value of running
 * is changed
 */
void msh_shell();

#endif //CS570A2_MAIN_H
