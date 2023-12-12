#include "shell.h"

/**
 * main - The main entry point of the shell program
 * @argc: The number of command-line arguments
 * @argv: The array of command-line arguments
 *
 * Return: EXIT_SUCCESS
 */

int main(int argc, char **argv)
{
	char **lines;
	int command_number = 1, status = 0, i;
	FILE *fp = stdin;
	shell_data_t *shell_data = malloc(sizeof(shell_data_t));

	if (shell_data == NULL)
	{
		perror("Error allocating memory for shell_data");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 64; i++)
	{
		shell_data->aliases[i] = NULL, shell_data->values[i] = NULL;
	}
	if (argc > 1)
	{
		fp = fopen(argv[1], "r");
		if (!fp)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": 0: Can't open ", 16);
			write(STDERR_FILENO, argv[1], _strlen(argv[1]));
			write(STDERR_FILENO, "\n", 1);
			exit(127);
		}
	}
	do {
		if (fp == stdin && isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		lines = get_user_input(status, fp);
		if (lines == NULL)
		{
			if (fp == stdin && isatty(STDIN_FILENO))
				write(1, "\n", 2);
			return (status);
		}
		process_lines(shell_data, lines, argv, &status, &command_number);
	} while (1);
	free(shell_data);
	return (status);
}

/**
 * process_lines - Processes each line of commands
 * @shell_data: A pointer to the shell data structure
 * @lines: The lines of commands
 * @argv: The array of command-line arguments
 * @status: The exit status of the last command executed
 * @command_number: The number of the current command
 */

void process_lines(shell_data_t *shell_data,
char **lines, char **argv, int *status, int *command_number)
{
	char **tokens;
	int i;

	for (i = 0; lines[i] != NULL; i++)
	{
		tokens = split_line(lines[i], *status);
		if (!tokens)
			continue;
		if (tokens[0] && check_if_builtin_command(tokens[0]))
			process_builtin_command(shell_data, tokens, argv, status, *command_number);
		else
			*status = run_command(shell_data, tokens, argv);
		(*command_number)++;

		free(tokens);
		tokens = NULL;
	}
	free(lines);
	lines = NULL;
}
