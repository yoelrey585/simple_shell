#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * *_string_copy - Duplicates a string.
 * @dest: The destination buffer.
 * @source: The source string to be duplicated.
 *
 * Return: A pointer to the destination buffer.
 */
char *_string_copy(char *dest, char *source)
{
	int idx = 0;

	if (dest == source || source == 0)
		return (dest);
	while (source[idx])
	{
		dest[idx] = source[idx];
		idx++;
	}
	dest[idx] = 0;
	return (dest);
}

/**
 * string_duplicate - Creates a duplicate of a string.
 * @str: The string to be duplicated.
 *
 * Return: A pointer to the duplicated string.
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * _puts - Displays a given input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int idx = 0;

	if (!str)
		return;
	while (str[idx] != '\0')
	{
		_putchar(str[idx]);
		idx++;
	}
}

/**
 * _putchar - Outputs the character 'c' to the standard output (stdout).
 * @c: The character to be written.
 *
 * Return: Returns 1 on success.
 * On error, returns -1 and sets the appropriate errno.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
