#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * _custom_memset - Fills a mem area with a specific byte value.
 * @mem_area: Pointer of the memory area
 * @byte_value: Byte value used to fill
 * @length: The number of bytes to be used to fill
 *
 * Return: Address of the memory area which is modified
**/
char *_custom_memset(char *mem_area, char byte_value, unsigned int length)
{
	unsigned int index;

	for (index = 0; index < length; index++)
		mem_area[index] = byte_value;
	return (mem_area);
}

/**
 *  _custom_realloc - Resizes a previously allocated memory block.
 * @pntr: Pointer to the original allocated memory block
 * @old_size: Size in bytes of original block.
 * @new_size: Bytes of new block
 *
 * Return: A pointer to the resized memory block
 */
void *_custom_realloc(void *pntr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!pntr)
		return (malloc(new_size));
	if (!new_size)
		return (free(pntr), NULL);
	if (new_size == old_size)
		return (pntr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)pntr)[old_size];
	free(pntr);
	return (new_ptr);
}

/**
 * free_string_array - Frees an array of strings
 * @string_array: Array of strings to be freed
 *
 * Return: void
 */
void free_string_array(char **string_array)
{
	char **temp = string_array;

	if (!string_array)
		return;
	while (*string_array)
		free(*string_array++);
	free(temp);
}
