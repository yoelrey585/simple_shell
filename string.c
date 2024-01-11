#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * my_strlen - Returns the length of a string
 * @str: The string whose length to check
 *
 * Return: Integer length of the string
 */
int my_strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * compare_strings - compares two strings
 * @string1: First string
 * @string2: Next string
 *
 * Return: A negative value if string1 < string2,
 * a positive value if string1 > string2,
 * and zero if string1 == string2.
 */
int compare_strings(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * *find_substring - Determines if a string starts with a given substring
 * @text: Main string to search
 * @substring: The substring to look for
 *
 * Return: Pointer to next char
 * or NULL
 */
char *find_substring(const char *text, const char *substring)
{
	while (*substring)
		if (*substring++ != *text++)
			return (NULL);
	return ((char *)text);
}

/**
 * *concatenate_strings - Concatenates two strings
 * @dest: Buffer destination
 * @source: Source buffer
 *
 * Return: Address of the destination buffer
 */
char *concatenate_strings(char *dest, char *source)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*source)
		*dest++ = *source++;
	*dest = *source;
	return (result);
}
