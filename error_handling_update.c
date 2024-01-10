#include "simple_shell.h"

/**
 * str_to_unsigned_int -  Converts string to an unsigned int
 * @str: String which will be converted
 *
 * Return: The converted integer on success, -1 on error
 */
int str_to_unsigned_int(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * display_error_message - Ouptuts an error message
 * @info: The structure holding parameter and return information
 * @estr: A string holding the error type
 * Return: 0 if no numbers are present in the string,
 *            otherwise the converted number.
 *        -1 in case of an error.
 *
 */
void display_error_message(info_t *info, char *estr)
{
	_displayString(info->fname);
	_displayString(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_displayString(": ");
	_displayString(info->argv[0]);
	_displayString(": ");
	_displayString(estr);
}

/**
 * print_decimal - This function prints a decimal (integer) number in base 10.
 * @input: The number that will be displayed
 * @file_d: The target file to write the output to.
 *
 * Return: The character_count of characters printed
 */
int print_decimal(int input, int file_d)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int _abs_, current;

	if (file_d == STDERR_FILENO)
		__putchar = write_to_stderr;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - A conversion function
 * @num: The number to be converted.
 * @base: The base for conversion.
 * @flags: Flags related to the argument.
 *
 * Return: A string as the result.
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comment_remover - This function removes comments
 * @buffer: Pointer to the string being modified.
 *
 * Return: 0 (On success)
 */
void comment_remover(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}
