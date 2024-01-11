#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * setInfo - Configures the struct info_t
 * @infor: Address of the structure
 * @argument_vector: The argument vector
 */
void setInfo(info_t *infor, char **argument_vector)
{
	int index = 0;

	infor->fname = argument_vector[0];
	if (infor->arg)
	{
		infor->argv = strSplit(infor->arg, " \t");
		if (!infor->argv)
		{

			infor->argv = malloc(sizeof(char *) * 2);
			if (infor->argv)
			{
				infor->argv[0] = string_duplicate(infor->arg);
				infor->argv[1] = NULL;
			}
		}
		for (index = 0; infor->argv && infor->argv[index]; index++)
			;
		infor->argc = index;

		replace_alias(infor);
		replace_variable(infor);
	}
}

/**
 * initialize_info - Makes info_t struct field initialized
 * @info: Pointer to the info_t struct
 */
void initialize_info(info_t *info)
{
	info->argv = NULL;
	info->arg = NULL;
	info->argc = 0;
	info->path = NULL;
}

/**
 * release_info - reallocates memory in info_t struct
 * @info: Address of the structure
 * @free_all: Boolean indicating whether to free all fields
 */
void release_info(info_t *info, int free_all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (free_all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			empty_list(&(info->env));
		if (info->history)
			empty_list(&(info->history));
		if (info->alias)
			empty_list(&(info->alias));
		free_string_array(info->environ);
			info->environ = NULL;
		free_and_nullify((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
