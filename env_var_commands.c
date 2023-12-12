#include "shell.h"

/**
 * set_env_var - Sets an environment variable
 * @command: The command to process
 * @status: The exit status of the last command executed
 * @command_number: The number of the current command
 */

void set_env_var(char **command, int *status, int command_number)
{
	if (command[1] == NULL || command[2] == NULL)
	{
		write(STDERR_FILENO, "./hsh: ", 7);
		write(STDERR_FILENO, int_to_str(command_number),
		_strlen(int_to_str(command_number)));
		write(STDERR_FILENO, ": setenv: Too few arguments\n", 27);
		*status = 2;
	}
	else if (setenv(command[1], command[2], 1) == -1)
	{
		perror("./hsh");
		*status = 2;
	}
}

/**
 * unset_env_var - Unsets an environment variable
 * @command: The command to process
 * @status: The exit status of the last command executed
 * @command_number: The number of the current command
 */

void unset_env_var(char **command, int *status, int command_number)
{
	if (command[1] == NULL)
	{
		write(STDERR_FILENO, "./hsh: ", 7);
		write(STDERR_FILENO, int_to_str(command_number),
		_strlen(int_to_str(command_number)));
		write(STDERR_FILENO, ": unsetenv: Too few arguments\n", 29);
		*status = 2;
	}
	else if (unsetenv(command[1]) == -1)
	{
		perror("./hsh");
		*status = 2;
	}
}
