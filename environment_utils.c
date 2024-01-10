#include "simple_shell.h"

/**
 * printEnv - Prints the current working environment
 * @info: Structure that contains all  potential arguments.
 * Employed to maintain constant function prototype.
 *
 * Return: Always 0 on success
 */
int printEnv(info_t *info)
{
	print_string_list(info->env);
	return (0);
}

/**
 * findEnv_variables - Retrieves the value of an _environ variable
 * @info: Structure containing potential arguments.
 * Employed to maintain constant function prototype
 * @var_name: Environment variable name
 *
 * Return: NULL or var_value
 */
char *findEnv_variables(info_t *info, const char *var_name)
{
	list_t *node = info->env;
	char *var_value;

	while (node)
	{
		var_value = find_substring(node->str, var_name);
		if (var_value && *var_value)
			return (var_value);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnv_variables - Initializes a new environment variable
 * or modify an already existing environment variable
 * @info: Structure containing potential arguments.
 * Employed to maintain constant function prototype.
 *
 * Return: Always 0 on success
 */
int setEnv_variables(info_t *info)
{
	if (info->argc != 3)
	{
		_displayString("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnv_variables - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 *
 * Return: Always 0 (Success)
 */

int unsetEnv_variables(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_displayString("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnv(info, info->argv[i]);

	return (0);
}

/**
 * populateEnv_list - Populates the environment linked list
 * @info: Structure containing potential arguments.
 * Employed to maintain constant function prototype.
 *
 * Return: Always 0 on success
 */
int populateEnv_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		my_append_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
