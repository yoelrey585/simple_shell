#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * _displayString - Prints the string input
 * @string: String to be displayed
 *
 * Return: No return value (void)
 */
void _displayString(char *string)
{
	int index = 0;

	if (!string)
		return;
	while (string[index] != '\0')
	{
		write_to_stderr(string[index]);
		index++;
	}
}

/**
 * _printStr - Displays an input string
 * @string: The string that will be printed
 * @file_desc: The targer descripter / identifier for writing
 *
 * Return: The count of characters printed
 */
int _printStr(char *string, int file_desc)
{
	int index = 0;

	if (!string)
		return (0);
	while (*string)
	{
		index += _writeToFd(*string++, file_desc);
	}
	return (index);
}


/**
 * write_to_stderr - Inputs char 'c' to the stderr
 * @chars: Char which will be printed
 *
 * Return: 1 for success, -1 error
 */
int write_to_stderr(char chars)
{
	static char buf[WRITE_BUF_SIZE];
	static int index;

	if (chars == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (chars != BUF_FLUSH)
		buf[index++] = chars;
	return (1);
}

/**
 * _writeToFd - Outputs the character 'c'
 * to the provided file descriptor (file_desc)
 * @ch: The character to be written
 * @file_desc: The target file descriptor for writing
 *
 * Return: 1 (On success)
 *         -1 on error , and errno appropriately set
 */
int _writeToFd(char ch, int file_desc)
{
	static char buf[WRITE_BUF_SIZE];
	static int index;

	if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(file_desc, buf, index);
		index = 0;
	}
	if (ch != BUF_FLUSH)
		buf[index++] = ch;
	return (1);
}

