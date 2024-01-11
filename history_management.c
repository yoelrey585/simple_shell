#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * obtain_history_file_path - Retrieves the history file.
 * @info: A parameter structure containing information
 *
 * Return: An string with the history file.
 */
char *obtain_history_file_path(info_t *info)
{
	char *buffer, *home_d;

	home_d = findEnv_variables(info, "HOME=");
	if (!home_d)
		return (NULL);
	buffer = malloc(sizeof(char) * (my_strlen(home_d)
				+ my_strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_string_copy(buffer, home_d);
	concatenate_strings(buffer, "/");
	concatenate_strings(buffer, HIST_FILE);
	return (buffer);
}

/**
 * read_history - Reads the history file's data or infp
 * @info: Parameter containing information
 *
 * Return: Success( The number of history items), 0 if failed
 */
int read_history(info_t *info)
{
	int idx, lineCounter = 0, last = 0;
	struct stat st;
	ssize_t fil_desc, fsize = 0, rdlen;
	char *buffer = NULL, *filename = obtain_history_file_path(info);

	if (!filename)
		return (0);

	fil_desc = open(filename, O_RDONLY);
	free(filename);
	if (fil_desc == -1)
		return (0);
	if (!fstat(fil_desc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fil_desc, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fil_desc);
	for (idx = 0; idx < fsize; idx++)
		if (buffer[idx] == '\n')
		{
			buffer[idx] = 0;
			append_history_list(info, buffer + last, lineCounter++);
			last = idx + 1;
		}
	if (last != idx)
		append_history_list(info, buffer + last, lineCounter++);
	free(buffer);
	info->histCount = lineCounter;
	while (info->histCount-- >= HIST_MAX)
		remove_node_at_index(&(info->history), 0);
	refresh_history_numbers(info);
	return (info->histCount);
}

/**
 * store_history_to_file - Makes a new history file or adds to existing file
 * @info: A struct parameter containing info
 *
 * Return: 1 (Success), or -1 (failure)
 */
int store_history_to_file(info_t *info)
{
	ssize_t fil_desc;
	char *filename = obtain_history_file_path(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fil_desc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fil_desc == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_printStr(node->str, fil_desc);
		_writeToFd('\n', fil_desc);
	}
	_writeToFd(BUF_FLUSH, fil_desc);
	close(fil_desc);
	return (1);
}

/**
 * refresh_history_numbers - Recounts linked list after modifications.
 * @info: holds potential arguments
 *
 * Return: The updated history item count.
 */
int refresh_history_numbers(info_t *info)
{
	list_t *node = info->history;
	int count = 0;

	while (node)
	{
		node->num = count++;
		node = node->next;
	}
	return (info->histCount = count);
}

/**
 * append_history_list - Adds an entry to a linked list for history tracking
 * @info: holds potential arguments
 * @path_buf: The buffer to be added to the history list.
 * @line_count: The count of the history line
 *
 * Return: 0 for Success
 */
int append_history_list(info_t *info, char *path_buf, int line_count)
{
	list_t *new_node = NULL;

	if (info->history)
		new_node = info->history;
	my_append_node(&new_node, path_buf, line_count);

	if (!info->history)
		info->history = new_node;
	return (0);
}

