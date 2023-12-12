#include "shell.h"

/**
 * create_new_args - Creates a new argument list replacing
 * "$?" with the last exit status
 * @args: The original argument list
 * @last_exit_status: The last exit status
 *
 * Return: A new argument list with "$?" replaced by the last exit status
 */

char **create_new_args(char **args, int last_exit_status)
{
	int i = 0;
	char **new_args;

	while (args[i] != NULL)
	{
		i++;
	}

	new_args = malloc((i + 1) * sizeof(char *));
	if (new_args == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	for (i = 0; args[i] != NULL; i++)
	{
		if (strcmp(args[i], "$?") == 0)
		{
			new_args[i] = handle_exit_status(last_exit_status);
			if (new_args[i] == NULL)
			{
				free(new_args);
				return (NULL);
			}
		}
		else
		{
			new_args[i] = _strdup(args[i]);
			if (new_args[i] == NULL)
			{
				free(new_args);
				return (NULL);
			}
		}
	}
	new_args[i] = NULL;

	return (new_args);
}

/**
 * handle_null_command_path - Handles the case when the command path is NULL
 * @args: The argument list
 * @new_args: The new argument list with "$?" replaced by the last exit status
 * @argv: The argument vector
 * @command_number: The command number
 * @i: The index of the current argument
 *
 * Return: The last exit status
 */

int handle_null_command_path(char **args, char **new_args, char **argv,
int command_number, int i)
{
	int last_exit_status, j;

	last_exit_status = handle_command_not_found(argv, args, command_number);
	command_number++;
	for (j = 0; j < i; j++)
	{
		if (strcmp(args[j], "$?") == 0)
		{
			free(new_args[j]);
		}
	}
	free(new_args);

	return (last_exit_status);
}

/**
 * cleanup_after_execution - Cleans up after executing a command
 * @args: The argument list
 * @new_args: The new argument list with "$?" replaced by the last exit status
 * @command_path: The path to the command
 * @i: The index of the current argument
 */

void cleanup_after_execution(char **args, char **new_args,
char *command_path, int i)
{
	int j;

	free(command_path);
	for (j = 0; j < i; j++)
	{
		if (strcmp(args[j], "$?") == 0)
		{
			free(new_args[j]);
			new_args[j] = NULL;
		}
	}
}

/**
 * process_alias_command - Checks if the first argument
 * is an alias and replaces it
 * @shell_data: A pointer to the shell data structure
 * @args: The argument list
 *
 * Return: 0 on success
 */

int process_alias_command(shell_data_t *shell_data, char **args)
{
	char *alias_command = get_alias_command(shell_data, args[0]);

	if (alias_command != NULL)
	{
		free(args[0]);
		args[0] = alias_command;
	}
	return (0);
}

/**
 * process_command_path_null - Handles the case when the command path is NULL
 * @args: The argument list
 * @new_args: The new argument list with "$?" replaced by the last exit status
 * @argv: The argument vector
 * @command_number: The command number
 * @i: The index of the current argument
 *
 * Return: The last exit status
 */

int process_command_path_null(char **args, char **new_args,
char **argv, int *command_number, int i)
{
	int last_exit_status;

	last_exit_status = handle_null_command_path
	(args, new_args, argv, *command_number, i);
	(*command_number)++;
	return (last_exit_status);
}
