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

/**
 * struct shell_data - Struct to hold shell data
 * @aliases: Array of alias strings
 * @values: Array of corresponding value strings
 */

typedef struct shell_data
{
	char *aliases[64];
	char *values[64];
} shell_data_t;

char **get_user_input(int status, FILE *fp);
void handle_alias_command(shell_data_t *shell_data,
char **command, int *status);
int process_alias_command(shell_data_t *shell_data, char **args);
int process_command_path_null
(char **args, char **new_args, char **argv, int *command_number, int i);
void display_aliases(shell_data_t *shell_data);
void display_alias(shell_data_t *shell_data, char *name);
void set_or_update_alias(shell_data_t *shell_data,
char *name, char *value);
void process_lines(shell_data_t *shell_data,
char **lines, char **argv, int *status, int *command_number);
char *get_alias_command(shell_data_t *shell_data, char *command);
char **split_line(char *line, int last_exit_status);
char **split_commands(char *line);
int run_command(shell_data_t *shell_data, char **args, char **argv);
int main(int argc, char **argv);
void free_array(char **arr);
char *get_command_path(char *command);
int execute_command(char *command_path, char **args, char **argv, int *status);
int handle_command_not_found(char **argv, char **args, int command_number);
char *handle_exit_status(int last_exit_status);
int check_if_builtin_command(char *command);
void process_builtin_command(shell_data_t *shell_data, char **command,
char **argv, int *status, int command_number);
void set_env_var(char **command, int *status, int command_number);
void unset_env_var(char **command, int *status, int command_number);
void change_directory(char **command, int *status);
char *get_new_directory(char **command, char *oldpwd);
void handle_chdir_error(char *newdir, int *status);
void update_directory(char *oldpwd, char *pwd);
void terminate_shell(char **command, int *status, int command_number);
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
