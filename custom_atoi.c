#include "simple_shell.h"

/**
 * is_interactive - Determines whether the shell is operating
 * in interactive mode
 * @info: Pointer the structure
 *
 * Return: Outputs 1 if shell is in interactive mode, otherwise 0
 */

int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimeter - Validates if a character functions as a delimiter
 * @c: The character to validate
 * @delim_str: Delimiter's string
 *
 * Return: Outputs 0 if false, 1 if true
 */

int is_delimeter(char c, char *delim_str)
{
	while (*delim_str)
		if (*delim_str++ == c)
			return (1);
	return (0);
}

/**
 * _isalphabetic - Verifies if a char is an alphabetic character
 * @x: The character to check
 *
 * Return: 1 if 'x' is an alphabetic character,
 * otherwise returns 0
 */
int _isalphabetic(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Changes a given string into an integer
 * @str: The input string
 *
 * Return: converted integer, otherwise 0 if string has no numbers
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, convertedValue;
	unsigned int intValue = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			intValue *= 10;
			intValue += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		convertedValue = -intValue;
	else
		convertedValue = intValue;

	return (convertedValue);
}
