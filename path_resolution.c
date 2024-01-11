#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * isExecutable_cmd - Parsing, syntax analysis, or syntactic analysis
 * @info: Structure containing parameter of arguments
 * @file_path: Path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutable_cmd(info_t *info, char *file_path)
{
	struct stat file_stat;

	(void)info;
	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * findCmd_path - finds command in the PATH string
 * @info: Structure containing parameter argument
 * @path_str: the PATH string
 * @command: The command to find
 *
 * Return: The full path of command if found otherwise NULL
 */
char *findCmd_path(info_t *info, char *path_str, char *command)
{
	int index = 0, cur_Pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((my_strlen(command) > 2) && find_substring(command, "./"))
	{
		if (isExecutable_cmd(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[index] || path_str[index] == ':')
		{
			path = duplicate_char(path_str, cur_Pos, index);
			if (!*path)
				concatenate_strings(path, command);
			else
			{
				concatenate_strings(path, "/");
				concatenate_strings(path, command);
			}
			if (isExecutable_cmd(info, path))
				return (path);
			if (!path_str[index])
				break;
			cur_Pos = index;
		}
		index++;
	}
	return (NULL);
}

/**
 * duplicate_char - Duplicate characters from a string
 * @src_str: Source string
 * @start_idx: Start index
 * @stop_idx: Stop index
 *
 * Return: pointer to new buffer containing duplicated characters
 */
char *duplicate_char(char *src_str, int start_idx, int stop_idx)
{
	static char buf[1024];
	int index = 0, src_idx = 0;

	for (src_idx = 0, index = start_idx; index < stop_idx; index++)
		if (src_str[index] != ':')
			buf[src_idx++] = src_str[index];
	buf[src_idx] = 0;
	return (buf);
}
