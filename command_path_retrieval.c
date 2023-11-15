#include "shell.h"

/**
 * get_command_path - Retrieves the path of a given command
 * @command: The command to find the path for
 *
 * Return: The path of the command, or NULL if the command or path is not found
 */

char *get_command_path(char *command)
{
	char *path_env = getenv("PATH");
	char path[1024];
	char *command_path = NULL;
	char *path_token;

	if (command == NULL)
	{
		return (NULL);
	}

	if (strchr(command, '/') != NULL)
	{
		return (strdup(command));
	}

	if (path_env == NULL)
	{
		return (NULL);
	}
	strncpy(path, path_env, sizeof(path));
	path[sizeof(path) - 1] = '\0';
	path_token = strtok(path, ":");

	while (path_token != NULL)
	{
		char temp_path[1024];

		strcpy(temp_path, path_token);
		strcat(temp_path, "/");
		strcat(temp_path, command);

		if (access(temp_path, F_OK) != -1)
		{
			command_path = strdup(temp_path);
			break;
		}
		path_token = strtok(NULL, ":");
	}

	return (command_path);
}
