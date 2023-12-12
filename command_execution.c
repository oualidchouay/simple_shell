#include "shell.h"

/**
 * free_new_args - Frees the memory allocated for the new argument list
 * @new_args: The new argument list to be freed
 */

void free_new_args(char **new_args)
{
	int i;

	for (i = 0; new_args[i] != NULL; i++)
		free(new_args[i]);
	free(new_args);
}

/**
 * run_command - Runs a command and handles the exit status and cleanup
 * @shell_data: A pointer to the shell data structure
 * @args: The argument list
 * @argv: The argument vector
 *
 * Return: The exit status of the command
 */

int run_command(shell_data_t *shell_data, char **args, char **argv)
{
	static int command_number = 1;
	static int last_exit_status;
	int status, i = 0;
	char *command_path = get_command_path(args[0]);
	char **new_args;

	if (args[0] == NULL || args[0][0] == '\0')
		return (0);

	new_args = create_new_args(args, last_exit_status);
	if (new_args == NULL)
		return (0);

	args = new_args;

	while (args[i] != NULL)
		i++;

	process_alias_command(shell_data, args);

	if (command_path == NULL)
	{
		last_exit_status = process_command_path_null
		(args, new_args, argv, &command_number, i);
		return (last_exit_status);
	}
	execute_command(command_path, args, argv, &status);

	if (WIFEXITED(status))
		last_exit_status = WEXITSTATUS(status);
	cleanup_after_execution(args, new_args, command_path, i);
	command_number++;

	free_new_args(new_args);

	return (last_exit_status);
}

