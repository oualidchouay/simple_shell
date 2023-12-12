#include "shell.h"

/**
 * check_if_builtin_command - Checks if a command is a built-in command
 * @command: The command to check
 *
 * Return: 1 if the command is a built-in command, 0 otherwise
 */

int check_if_builtin_command(char *command)
{
	char *builtins_cmd[] = {
		"exit", "env", "setenv",
		"unsetenv", "cd", "alias", NULL
	};
	int a;

	for (a = 0; builtins_cmd[a]; a++)
	{
		if (_strcmp(command, builtins_cmd[a]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * process_builtin_command - Processes a built-in command
 * @shell_data: A pointer to the shell data structure
 * @command: The command to process
 * @argv: The argument vector
 * @status: The exit status of the last command executed
 * @command_number: The number of the current command
 */

void process_builtin_command(shell_data_t *shell_data, char **command,
char **argv, int *status, int command_number)
{
	(void) argv;

	if (_strcmp(command[0], "exit") == 0)
	{
		terminate_shell(command, status, command_number);
	}
	else if (_strcmp(command[0], "env") == 0)
	{
		display_env_vars(status);
	}
	else if (_strcmp(command[0], "setenv") == 0)
	{
		set_env_var(command, status, command_number);
	}
	else if (_strcmp(command[0], "unsetenv") == 0)
	{
		unset_env_var(command, status, command_number);
	}
	else if (_strcmp(command[0], "cd") == 0)
	{
		change_directory(command, status);
	}
	else if (_strcmp(command[0], "alias") == 0)
	{
		handle_alias_command(shell_data, command, status);
	}
}

/**
 * terminate_shell - Terminates the shell
 * @command: The command that caused the shell to terminate
 * @status: The exit status of the last command executed
 * @command_number: The number of the current command
 */

void terminate_shell(char **command, int *status, int command_number)
{
	int exit_status = 0;

	if (command[1] != NULL)
	{
		char *endptr;

		exit_status = strtol(command[1], &endptr, 10);
		if (*endptr != '\0' || endptr == command[1] || exit_status < 0)
		{
			write(STDERR_FILENO, "./hsh: ", 7);
			write(STDERR_FILENO, int_to_str(command_number),
			_strlen(int_to_str(command_number)));
			write(STDERR_FILENO, ": exit: Illegal number: ", 24);
			write(STDERR_FILENO, command[1], _strlen(command[1]));
			write(STDERR_FILENO, "\n", 1);
			*status = 2;
			return;
		}
	}
	else
	{
		exit_status = *status;
	}

	if (command[0] != NULL)
	{
		free(command[0]);
	}
	free(command);
	exit(exit_status);
}

/**
 * display_env_vars - Displays the environment variables
 * @status: The exit status of the last command executed
 */

void display_env_vars(int *status)
{
	int i;
	char *vars[] = {
	"LANGUAGE", "HOSTNAME", "SHLVL", "HOME", "OLDPWD", "PATH",
	"LANG", "PWD", "LC_ALL", "TZ", "LESSOPEN", "USER",
	"GIT_ASKPASS", "TERM_PROGRAM_VERSION", "VSCODE_IPC_HOOK_CLI",
	"VSCODE_GIT_ASKPASS_MAIN", "VSCODE_GIT_ASKPASS_NODE",
	"DBUS_SESSION_BUS_ADDRESS", "COLORTERM", "WSL_DISTRO_NAME",
	"WAYLAND_DISPLAY", "LOGNAME", "NAME", "WSL_INTEROP", "PULSE_SERVER",
	"TERM", "XDG_RUNTIME_DIR", "DISPLAY", "LS_COLORS",
	"VSCODE_GIT_IPC_HANDLE", "TERM_PROGRAM", "SHELL", "LESSCLOSE",
	"VSCODE_GIT_ASKPASS_EXTRA_ARGS", "XDG_DATA_DIRS",
	"WSL2_GUI_APPS_ENABLED", "HOSTTYPE", "WSLENV", "HBTN", NULL
};
	for (i = 0; vars[i] != NULL; i++)
	{
		char *value = getenv(vars[i]);

		if (value != NULL)
		{
			write(STDOUT_FILENO, vars[i], _strlen(vars[i]));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, value, _strlen(value));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	*status = 0;
}

