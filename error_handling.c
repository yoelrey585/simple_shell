#include "simple_shell.h"

/**
 * _displayString - Prints the string input inside
 * @str: The string to be displayed
 *
 * Return: No return value (void)
 */
void _displayString(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		write_to_stderr(str[index]);
		index++;
	}
}

/**
 * write_to_stderr - Writes char 'c' to the stderr
 * @c: The char which will be printed
 *
 * Return: 1 (On success)
 *         -1 on error , and errno appropriately set
 */
int write_to_stderr(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 * _writeToFd - Outputs the character 'c'
 * to the provided file descriptor (file_desc)
 * @c: The character to be written
 * @file_desc: The target file descriptor for writing
 *
 * Return: 1 (On success)
 *         -1 on error , and errno appropriately set
 */
int _writeToFd(char c, int file_desc)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(file_desc, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 * _printStr - Prints an input string
 * @str: The string that will be printed
 * @file_desc: The targer descripter / identifier for writing
 *
 * Return: The count of characters printed
 */
int _printStr(char *str, int file_desc)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += _writeToFd(*str++, file_desc);
	}
	return (index);
}
