#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * display_error_message - Shows error msg
 * @info: Holds input and returns information
 * @estr: A string holding the error type
 * Return: 0 for no numbers, or the converted number
 * or -1 for an error.
 *
 */
void display_error_message(info_t *info, char *estr)
{
	_displayString(info->fname);
	_displayString(" : ");
	print_decimal(info->line_count, STDERR_FILENO);
	_displayString(" : ");
	_displayString(info->argv[0]);
	_displayString(" : ");
	_displayString(estr);
}

/**
 * print_decimal - This function prints a dec number
 * @input: The number that will be displayed
 * @file_d: The target file to write the output to.
 *
 * Return: The character_count of chars printed
 */
int print_decimal(int input, int file_d)
{
	int  cnt = 0, index;
	int (*__putchar)(char) = _putchar;
	unsigned int _abs_, curnt;

	if (file_d == STDERR_FILENO)
		__putchar = write_to_stderr;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = input;
	curnt = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + curnt / index);
			cnt++;
		}
		curnt %= index;
	}
	__putchar('0' + curnt);
	cnt++;

	return (cnt);
}

/**
 * convert_number - A conversion function
 * @flags: Flags related to the argument.
 * @base: The base for conversion.
 * @num: The number to be converted.
 *
 * Return: A string as the result.
 */

char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	static char *arr;
	char *pointer;
	char sign = 0;
	unsigned long long_n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		long_n = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = arr[long_n % base];
		long_n /= base;
	} while (long_n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * str_to_unsigned_int -  Changes string to an int
 * @str: String which will be converted
 *
 * Return: The converted integer on success, -1 on error
 */
int str_to_unsigned_int(char *str)
{
	unsigned long int result = 0;
	int index = 0;

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
