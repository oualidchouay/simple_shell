#include "shell.h"

/**
 * check_if_builtin_command - asked if it is a builtin command
 * @command: the execution command
 * Return: 0 if succeeded
 */

int check_if_builtin_command(char *command)
{
	char *builtins_cmd[] = {
		"exit", "env", "setenv",
		"cd", NULL
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
 * process_builtin_command - handle the builtin command
 * @command: the execution command
 * @argv: (void) argv
 * @status: the number of commands to exit with
 */

void process_builtin_command(char **command, char **argv, int *status)
{
	(void) argv;

	if (_strcmp(command[0], "exit") == 0)
	{
		terminate_shell(command, status);
	}
	else if (_strcmp(command[0], "env") == 0)
	{
		display_env_vars(status);
	}
}

/**
 * terminate_shell - exit shell if the command is exit
 * @command: the execution command
 * @status: number of commands
 */

void terminate_shell(char **command, int *status)
{
	free_array(command);
	exit(*status);
}

/**
 * display_env_vars - print the environment
 * @status: the number of commands
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
