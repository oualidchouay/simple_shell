#include "shell.h"

/**
 * handle_special_tokens - Handles special tokens in the command line
 * @token: The token to be checked
 * @last_exit_status: The last exit status of the previous command
 *
 * Return: The replaced token if it is a special token,
 * or the original token otherwise
 */

char *handle_special_tokens(char *token, int last_exit_status)
{
	if (strcmp(token, "$$") == 0)
	{
		return (int_to_str(getpid()));
	}

	if (strcmp(token, "$?") == 0)
	{
		return (int_to_str(last_exit_status));
	}

	if (*token == '$')
	{
		if (*(token + 1) == ' ' || *(token + 1) == '\0')
		{
			return ("$");
		}
		else
		{
			char *var = getenv(token + 1);

			return (var != NULL ? var : "");
		}
	}

	return (token);
}

/**
 * split_line - Splits the input line into tokens
 * @line: The input line to be split
 * @last_exit_status: The last exit status of the previous command
 *
 * Return: A pointer to the array of tokens
 */

char **split_line(char *line, int last_exit_status)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIM);

	while (token != NULL)
	{
		if (*token == '#')
			break;

		token = handle_special_tokens(token, last_exit_status);

		if (*token != '\0')
		{
			tokens[position] = token;
			position++;
		}

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("Allocation error");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}
