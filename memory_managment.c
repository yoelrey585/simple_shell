#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * free_and_nullify - Releases memory associated with a pointer and
 * sets the address to NULL.
 * @ptr: The address of the pointer to be freed.
 *
 * Return: 1 if the memory is free, 0 if not
 */
int free_and_nullify(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

