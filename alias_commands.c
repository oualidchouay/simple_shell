#include "shell.h"


/**
 * handle_alias_command - Handles the alias command
 * @shell_data: A pointer to the shell data structure
 * @command: The command to process
 * @status: The exit status of the last command executed
 */
void handle_alias_command(shell_data_t *shell_data,
char **command, int *status)
{
	int i;

	if (command[1] == NULL)
	{
		display_aliases(shell_data);
	}
	else
	{
		for (i = 1; command[i] != NULL; i++)
		{
			char *name = strtok(command[i], "=");
			char *value = strtok(NULL, "=");

			if (value == NULL)
			{
				display_alias(shell_data, name);
			}
			else
			{
				set_or_update_alias(shell_data, name, value);
			}
		}
	}
	*status = 0;
}

/**
 * display_aliases - Displays all aliases
 * @shell_data: A pointer to the shell data structure
 */

void display_aliases(shell_data_t *shell_data)
{
	int i;

	for (i = 0; shell_data->aliases[i] != NULL; i++)
	{
		write(STDOUT_FILENO, shell_data->aliases[i],
		_strlen(shell_data->aliases[i]));
		write(STDOUT_FILENO, "='", 2);
		write(STDOUT_FILENO, shell_data->values[i],
		_strlen(shell_data->values[i]));
		write(STDOUT_FILENO, "'\n", 2);
	}
}

/**
 * display_alias - Displays a specific alias
 * @shell_data: A pointer to the shell data structure
 * @name: The name of the alias to display
 */

void display_alias(shell_data_t *shell_data, char *name)
{
	int j;

	for (j = 0; shell_data->aliases[j] != NULL; j++)
	{
		if (_strcmp(shell_data->aliases[j], name) == 0)
		{
			write(STDOUT_FILENO, shell_data->aliases[j],
			_strlen(shell_data->aliases[j]));
			write(STDOUT_FILENO, "='", 2);
			write(STDOUT_FILENO, shell_data->values[j],
			_strlen(shell_data->values[j]));
			write(STDOUT_FILENO, "'\n", 2);
			break;
		}
	}
}

/**
 * set_or_update_alias - Sets or updates an alias
 * @shell_data: A pointer to the shell data structure
 * @name: The name of the alias
 * @value: The value of the alias
 */

void set_or_update_alias(shell_data_t *shell_data,
char *name, char *value)
{
	int j;

	for (j = 0; shell_data->aliases[j] != NULL; j++)
	{
		if (_strcmp(shell_data->aliases[j], name) == 0)
		{
			free(shell_data->values[j]);
			shell_data->values[j] = _strdup(value);
			break;
		}
	}
	if (shell_data->aliases[j] == NULL)
	{
		shell_data->aliases[j] = _strdup(name);
		shell_data->values[j] = _strdup(value);
	}
}

/**
 * get_alias_command - Gets the command for an alias
 * @shell_data: A pointer to the shell data structure
 * @command: The alias to get the command for
 *
 * Return: The command for the alias
 */

char *get_alias_command(shell_data_t *shell_data, char *command)
{
	int i;

	for (i = 0; shell_data->aliases[i] != NULL; i++)
	{
		if (_strcmp(shell_data->aliases[i], command) == 0)
		{
			return (_strdup(shell_data->values[i]));
		}
	}

	return (NULL);
}
