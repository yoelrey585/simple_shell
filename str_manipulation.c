#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * check_chain_delim - Checks if the current character in the
 * buffer is a chain delimiter.
 * @info: The parameter structure
 * @buf: The character buffer.
 * @pos: The address of the current position in the buffer.
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */
int check_chain_delim(info_t *info, char *buf, size_t *pos)
{
	size_t idx = *pos;

	if (buf[idx] == '|' && buf[idx + 1] == '|')
	{
		buf[idx] = 0;
		idx++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[idx] == '&' && buf[idx + 1] == '&')
	{
		buf[idx] = 0;
		idx++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[idx] == ';')
	{
		buf[idx] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = idx;
	return (1);
}

/**
 * check_chain_cond - Determines whether chaining should continue
 * based on the previous status.
 * @info: The parameter structure.
 * @buf: The character buffer.
 * @pos: The address of the current position in the buffer.
 * @i: The starting position in the buffer.
 * @len: The length of the buffer.
 *
 * Return: Void.
 */
void check_chain_cond(info_t *info, char *buf,
		size_t *pos, size_t i, size_t len)
{
	size_t idx = *pos;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			idx = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			idx = len;
		}
	}

	*pos = idx;
}

/**
 * replace_alias - Substitutes aliases in the tokenized string
 * with their corresponding values.
 * @info: The parameter structure.
 *
 * Return: 1 if replacement occurs, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *pos;

	for (i = 0; i < 10; i++)
	{
		node = node_start_finder(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pos = _strchr(node->str, '=');
		if (!pos)
			return (0);
		pos = string_duplicate(pos + 1);
		if (!pos)
			return (0);
		info->argv[0] = pos;
	}
	return (1);
}

/**
 * replace_variable - Substitutes variables in the tokenized
 * string with their values.
 * @info: The parameter structure.
 *
 * Return: 1 if replacement occurs, 0 otherwise.
 */
int replace_variable(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!compare_strings(info->argv[i], "$?"))
		{
			replaceStr(&(info->argv[i]),
				string_duplicate(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!compare_strings(info->argv[i], "$$"))
		{
			replaceStr(&(info->argv[i]),
				string_duplicate(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start_finder(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceStr(&(info->argv[i]),
				string_duplicate(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceStr(&info->argv[i], string_duplicate(""));

	}
	return (0);
}

/**
 * replaceStr - Replaces an old string with a new string.
 * @old_str: The address of the old string to be replaced.
 * @new_str: The new string to use for replacement.
 *
 * Return: 1 if replacement occurs, 0 otherwise.
 */
int replaceStr(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
