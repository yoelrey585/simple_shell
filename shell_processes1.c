#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * find_and_execute_cmd - Locates cmd in the file PATH and executes it
 * @info: Struct containing information
 *
 * Return: void, nothing
 */
void find_and_execute_cmd(info_t *info)
{
	char *path = NULL;
	int index, arg_count;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (index = 0, arg_count = 0; info->arg[index]; index++)
		if (!is_delimeter(info->arg[index], " \t\n"))
			arg_count++;
	if (!arg_count)
		return;

	path = findCmd_path(info, findEnv_variables(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_and_execute_cmd(info);
	}
	else
	{
		if ((is_interactive(info) || findEnv_variables(info, "PATH=")
					|| info->argv[0][0] == '/') && isExecutable_cmd(info, info->argv[0]))
			fork_and_execute_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			display_error_message(info, "not found\n");
		}
	}
}

/**
 * fork_and_execute_cmd - Forks a new process to execute a command
 * @info: Struct holding parameter and the return info
 *
 * Return: void
 */
void fork_and_execute_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getEnv(info)) == -1)
		{
			release_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				display_error_message(info, "Permission denied\n");
		}
	}
}
