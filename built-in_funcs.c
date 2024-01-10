#include "simple_shell.h"

/**
 * shellExit - Terminates the shell gracefully.
 * @info: structure with potential arguments
 *
 * This function enables controlled shell termination. If info.argv[0]
 * isn't "exit", it exits with status 0. Otherwise, it concludes
 * the shell execution after necessary cleanup.
 *
 * Return: Exits with specified status; returns 0 if info.argv[0]
 *         isn't "exit".
 */
int shellExit(info_t *info)
{
	int exitStatus;

	if (info->argv[1])
	{
		exitStatus = str_to_unsigned_int(info->argv[1]);
		if (exitStatus == -1)
		{
			info->status = 2;
			display_error_message(info, "Illegal number: ");
			_displayString(info->argv[1]);
			write_to_stderr('\n');
			return (1);
		}
		info->err_num = str_to_unsigned_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * switchDir - Alters the process' working directory
 * @info: structure ontaining potential arguments.
 * Employed for maintaining a uniform function prototype.
 *
 * Return: 0 (Success)
 */
int switchDir(info_t *info)
{
	char *currentPath, *newPath, buffer[1024];
	int chdir_result;

	currentPath = getcwd(buffer, 1024);
	if (!currentPath)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		newPath = findEnv_variables(info, "HOME=");
		if (!newPath)
			chdir_result =
				chdir((newPath = findEnv_variables(info, "PWD=")) ? newPath : "/");
		else
			chdir_result = chdir(newPath);
	}
	else if (compare_strings(info->argv[1], "-") == 0)
	{
		if (!findEnv_variables(info, "OLDPWD="))
		{
			_puts(currentPath);
			_putchar('\n');
			return (1);
		}
		_puts(findEnv_variables(info, "OLDPWD=")), _putchar('\n');
		chdir_result =
			chdir((newPath = findEnv_variables(info, "OLDPWD=")) ? newPath : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		display_error_message(info, "can't cd to ");
		_displayString(info->argv[1]), write_to_stderr('\n');
	}
	else
	{
		setEnv(info, "OLDPWD", findEnv_variables(info, "PWD="));
		setEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * showHelp - Display help information
 * @info: Structure containing potential arguments.
 * Employed for maintaining a uniform fucntion prototype
 *
 * Return: Always 0 (Success)
 */
int showHelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
