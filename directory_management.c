#include "shell.h"

/**
 * change_directory - Changes the current working directory
 * @command: The command to process
 * @status: The exit status of the last command executed
 */

void change_directory(char **command, int *status)
{
	char *oldpwd = getcwd(NULL, 0);
	char *newdir;
	char *pwd = getcwd(NULL, 0);

	if (oldpwd == NULL || pwd == NULL)
	{
		perror("getcwd");
		return;
	}

	newdir = get_new_directory(command, oldpwd);
	if (chdir(newdir) != 0)
	{
		handle_chdir_error(newdir, status);
	}
	else
	{
		update_directory(oldpwd, pwd);
	}
}

/**
 * get_new_directory - Gets the new directory to change to
 * @command: The command to process
 * @oldpwd: The old working directory
 *
 * Return: The new directory to change to
 */

char *get_new_directory(char **command, char *oldpwd)
{
	char *newdir;

	if (command[1] == NULL)
	{
		newdir = getenv("HOME");
		if (newdir == NULL)
		{
			newdir = oldpwd;
		}
	}
	else if (_strcmp(command[1], "-") == 0)
	{
		newdir = getenv("OLDPWD");
		if (newdir == NULL)
		{
			newdir = oldpwd;
		}
		if (chdir(newdir) == 0)
		{
			char *pwd = getcwd(NULL, 0);

			write(STDOUT_FILENO, pwd, _strlen(pwd));
			write(STDOUT_FILENO, "\n", 1);
			free(pwd);
		}
		return (newdir);
	}
	else
	{
		newdir = command[1];
	}

	return (newdir);
}

/**
 * handle_chdir_error - Handles an error when changing directories
 * @newdir: The directory to change to
 * @status: The exit status of the last command executed
 */

void handle_chdir_error(char *newdir, int *status)
{
	write(STDERR_FILENO, "./hsh: 1: cd: can't cd to ", 26);
	write(STDERR_FILENO, newdir, _strlen(newdir));
	write(STDERR_FILENO, "\n", 1);
	*status = 2;
}

/**
 * update_directory - Updates the current working directory
 * @oldpwd: The old working directory
 * @pwd: The new working directory
 */

void update_directory(char *oldpwd, char *pwd)
{
	if (oldpwd != NULL)
	{
		setenv("OLDPWD", oldpwd, 1);
		free(oldpwd);
	}
	setenv("PWD", pwd, 1);
	free(pwd);
}
