#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * unsetAlias - Removes an alias string from the alias list
 * @info: Structure holding arguments
 * @str: String to be removed as an alias
 *
 * Return: 0 for success, 1 for error
 */
int unsetAlias(info_t *info, char *str)
{
	int retV;
	char *pointer, temp_char;

	pointer = _strchr(str, '=');
	if (!pointer)
		return (1);
	temp_char = *pointer;
	*pointer = 0;
	retV = remove_node_at_index(&(info->alias),
		get_node_position(info->alias, node_start_finder(info->alias, str, -1)));
	*pointer = temp_char;
	return (retV);
}

/**
 * showHistory - Shows history of most recent commands
 * @info: holds future arguments
 *
 * Return: 0 for success
 */
int showHistory(info_t *info)
{
	printf("\nList of Previous Commands\n");
	display_list(info->history);
	return (0);
}

/**
 * setAlias - Adds an alias string to the alias list
 * @info: Structure holding future arguments
 * @str: The string to be used as an alias.
 *
 * Return: 0 for success, 1 for an error
 */
int setAlias(info_t *info, char *str)
{
	char *pointer;

	pointer = _strchr(str, '=');
	if (!pointer)
		return (1);
	if (!*++pointer)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (my_append_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_singleAlias - Displays alias
 * @node: The node to be printed.
 *
 * Return: 0 for success, 1 for error.
 */
int print_singleAlias(list_t *node)
{
	char *alias_value = NULL, *pointer = NULL;

	if (node)
	{
		pointer = _strchr(node->str, '=');
		for (alias_value = node->str; alias_value <= pointer; alias_value++)
			_putchar(*alias_value);
		_putchar('\'');
		_puts(pointer + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAlias - Simulates the behavior of the 'alias' builtin
 * @info: Structure holding future arguments
 *
 * Return: 0 all the time
 */
int manageAlias(info_t *info)
{
	char *pointer = NULL;
	list_t *node = NULL;
	int i = 0;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_singleAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		pointer = _strchr(info->argv[i], '=');
		if (pointer)
			setAlias(info, info->argv[i]);
		else
			print_singleAlias(node_start_finder(info->alias, info->argv[i], '='));
	}

	return (0);
}
