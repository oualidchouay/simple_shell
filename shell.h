#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define DELIM " \t\n"
extern char **environ;

char *get_user_input(int status);
char **split_line(char *line);
int run_command(char **args, char **argv);
int main(int argc, char **argv);
void free_array(char **arr);
char *get_command_path(char *command);
int execute_command(char *command_path, char **args, char **argv, int *status);
int handle_command_not_found(char **argv, char **args, int command_number);
char *handle_exit_status(int last_exit_status);
int check_if_builtin_command(char *command);
void process_builtin_command(char **command, char **argv, int *status);
void terminate_shell(char **command, int *status);
void display_env_vars(int *status);
void cleanup_after_execution(char **args, char **new_args,
char *command_path, int i);
int handle_null_command_path(char **args, char **new_args,
char **argv, int command_number, int i);
char **create_new_args(char **args, int last_exit_status);
char *int_to_str(int num);

char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

#endif /* SHELL_H */
