#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * printEnv - Shows the current working env
 * @info: Structure that holds future arguments.
 *
 * Return: 0 for success
 */
int printEnv(info_t *info)
{
	print_string_list(info->env);
	return (0);
}

/**
 * setEnv_variables - Creates a new environment
 * or makes changes to an already made env variable
 * @info: Structure that holds future arguments
 *
 * Return: 0 for success
 */
int setEnv_variables(info_t *info)
{
	if (info->argc != 3)
	{
		_displayString("Wrong number of arguments\n");
		return (1);
	}
	if (setEnv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnv_variables - Deletes an environment variable
 * @info: Structure that holds future arguments
 *
 * Return: 0 for Success
 */

int unsetEnv_variables(info_t *info)
{
	int check;

	if (info->argc == 1)
	{
		_displayString("Arguments are too little\n");
		return (1);
	}
	for (check = 1; check <= info->argc; check++)
		unsetEnv(info, info->argv[check]);

	return (0);
}

/**
 * populateEnv_list - Adds the environment linked list
 * @info: Structure holding future argument.
 *
 * Return: 0 for success
 */
int populateEnv_list(info_t *info)
{
	size_t check;
	list_t *node = NULL;

	for (check = 0; environ[check]; check++)
		my_append_node(&node, environ[check], 0);
	info->env = node;
	return (0);
}

/**
 * findEnv_variables - Retrieves the value of an _environ variable
 * @info: Structure holding argument
 * @var_name: Name of Environment variable
 *
 * Return: NULL or var_value
 */
char *findEnv_variables(info_t *info, const char *var_name)
{
	char *var_value;
	list_t *node = info->env;

	while (node)
	{
		var_value = find_substring(node->str, var_name);
		if (var_value && *var_value)
			return (var_value);
		node = node->next;
	}
	return (NULL);
}
