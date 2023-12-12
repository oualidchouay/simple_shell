#include "shell.h"

/**
 * get_user_input - Reads a line of input from the user
 * @status: The exit status to use if the end of file is reached
 * @fp: The file pointer to read from
 *
 * Return: The line read from the user
 */

char **get_user_input(int status, FILE *fp)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t len;

	len = getline(&line, &bufsize, fp);
	if (len == -1)
	{
		free(line), line = NULL;

		if (feof(fp))
		{
			if (fp == stdin && isatty(STDIN_FILENO))
				write(1, "\n", 1);
			exit(status);
		}
		else
		{
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}

	if (fp == stdin && !isatty(STDIN_FILENO) && len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';

	return (split_commands(line));
}

/**
 * split_commands - Splits the input line into commands
 * @line: The input line to be split
 *
 * Return: A pointer to the array of commands
 */

char **split_commands(char *line)
{
	int bufsize = 64, position = 0;
	char **commands = malloc(bufsize * sizeof(char *));
	char *command;

	if (!commands)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	command = strtok(line, "&&||;");

	while (command != NULL)
	{
		commands[position] = command;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			commands = realloc(commands, bufsize * sizeof(char *));
			if (!commands)
			{
				perror("Allocation error");
				exit(EXIT_FAILURE);
			}
		}

		command = strtok(NULL, "&&||;");
	}
	commands[position] = NULL;
	return (commands);
}

/**
 * handle_exit_status - Converts the last exit status to a string
 * @last_exit_status: The last exit status
 *
 * Return: The string representation of the last exit status
 */

char *handle_exit_status(int last_exit_status)
{
	int temp = last_exit_status;
	int len = 0, j;
	char *num_str = malloc(12);

	if (num_str == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	if (temp == 0)
	{
		num_str[0] = '0';
		num_str[1] = '\0';
	}
	else
	{
		while (temp != 0)
		{
			len++;
			temp /= 10;
		}

		temp = last_exit_status;
		for (j = len - 1; j >= 0; j--)
		{
			num_str[j] = (temp % 10) + '0';
			temp /= 10;
		}
		num_str[len] = '\0';
	}

	return (num_str);
}

/**
 * int_to_str - Converts an integer to a string
 * @num: The integer to be converted
 *
 * Return: The string representation of the integer
 */

char *int_to_str(int num)
{
	char *str;
	int temp, digits = 0;

	temp = num;
	do {
		digits++;
		temp /= 10;
	} while (temp != 0);

	str = malloc(digits + 1);
	if (str == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	str[digits] = '\0';
	while (digits > 0)
	{
		str[digits - 1] = (num % 10) + '0';
		num /= 10;
		digits--;
	}

	return (str);
}

/**
 * handle_command_not_found - Handles the case when a command is not found
 * @argv: The argument vector
 * @args: The argument list
 * @command_number: The command number
 *
 * Return: 127 to indicate that the command was not found
 */

int handle_command_not_found(char **argv, char **args, int command_number)
{
	char *command_number_str = int_to_str(command_number);
	(void) argv;

	write(STDERR_FILENO, "./hsh: ", 7);
	write(STDERR_FILENO, command_number_str, _strlen(command_number_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, args[0], _strlen(args[0]));
	write(STDERR_FILENO, ": not found\n", 12);
	free(command_number_str);
	return (127);
}
