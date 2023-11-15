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
	char *line;
	char **tokens;
	int status;
	(void) argc;

		do {
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		line = get_user_input(status);
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 2);
			return (status);
		}
		tokens = split_line(line);
		if (!tokens)
			continue;
		if (tokens[0] && check_if_builtin_command(tokens[0]))
			process_builtin_command(tokens, argv, &status);
		else
			status = run_command(tokens, argv);

		free(line);
		line = NULL;
		free(tokens);
		tokens = NULL;
	} while (1);
	return (status);
}