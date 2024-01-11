#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * hsh - Main shell loop
 * @info: Pointer to Struct containing input and output info
 * @command_line_args: Array of arguments from the main() function
 * Return: 0 (success)
 * 1 - (error), or an error code
 */
int hsh(info_t *info, char **command_line_args)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		initialize_info(info);
		if (is_interactive(info))
			_puts("$ ");
		write_to_stderr(BUF_FLUSH);
		r = getInput(info);
		if (r != -1)
		{
			setInfo(info, command_line_args);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_and_execute_cmd(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		release_info(info, 0);
	}
	store_history_to_file(info);
	release_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Locates any command in library
 * @info: Pointer to struct
 * Return: -1 not found, 0 on success, 1 - cmd is found but not executed,
 *         -2 if built-in command signals exit()
 */
int find_builtin(info_t *info)
{
	int index, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shellExit},
		{"env", printEnv},
		{"help", showHelp},
		{"history", showHistory},
		{"setenv", setEnv_variables},
		{"unsetenv", unsetEnv_variables},
		{"cd", switchDir},
		{"alias", manageAlias},
		{NULL, NULL}};

	for (index = 0; builtintbl[index].type; index++)
		if (compare_strings(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[index].func(info);
			break;
		}
	return (built_in_ret);
}
