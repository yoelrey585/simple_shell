#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * getEnv - obtains a string array copy of our _environ
 * @info: Contains future arguments
 *
 * Return: 0 sucess
 */

char **getEnv(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_string_arr(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


/**
 * setEnv - create a new env variable or changes it
 * @info: Holds future arguments
 * @varia: String property of the environment variable.
 * @valu: String value to be assigned to the environment variable
 *
 * Return: 0 for Succes
 */
int setEnv(info_t *info, char *varia, char *valu)
{
	char *buf = NULL;
	char *ptr;
	list_t *node;

	if (!varia || !valu)
		return (0);

	buf = malloc(my_strlen(varia) + my_strlen(valu) + 2);
	if (!buf)
		return (1);
	_string_copy(buf, varia);
	concatenate_strings(buf, "=");
	concatenate_strings(buf, valu);
	node = info->env;
	while (node)
	{
		ptr = find_substring(node->str, varia);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	my_append_node(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * unsetEnv - remove an environment variable using the unsetEnv function.
 * @info: Holds possible arguments
 * @varia: String property of the environment variable to be removed
 *
 * Return: 1 if the variable is successfully deleted, 0 otherwise.
 */

int unsetEnv(info_t *info, char *varia)
{
	size_t idx = 0;
	list_t *node = info->env;
	char *ptr;

	if (!node || !varia)
		return (0);

	while (node)
	{
		ptr = find_substring(node->str, varia);
		if (ptr && *ptr == '=')
		{
			info->env_changed = remove_node_at_index(&(info->env), idx);
			idx = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		idx++;
	}
	return (info->env_changed);
}
