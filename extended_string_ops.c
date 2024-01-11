#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * _strncat - Joins two strings together
 * @destination: Intial string
 * @source: Next string
 * @max_chars: The maximum number characters from 'source'
 *
 * Return: The combined string
 */
char *_strncat(char *destination, char *source, int max_chars)
{
	char *st = destination;
	int dest_index, source_idx;

	dest_index = 0;
	source_idx = 0;
	while (destination[dest_index] != '\0')
		dest_index++;
	while (source[source_idx] != '\0' && source_idx < max_chars)
	{
		destination[dest_index] = source[source_idx];
		dest_index++;
		source_idx++;
	}
	if (source_idx < max_chars)
		destination[dest_index] = '\0';
	return (st);
}

/**
 * *_strchr - Finds the first instance of a character in a string
 * @string: The string to search within
 * @ch: The character to locate
 *
 * Return: A pointer to the first occurrence of the char,
 * or NULL if not found
 */
char *_strchr(char *string, char ch)
{
	do {
		if (*string == ch)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

/**
 * _strncpy - Replicates string input
 * @destination: The target string for to coping
 * @source: The original string
 * @max_chars: The number of characters to copy
 *
 * Return: pointer to the beginning of the combined string
 */
char *_strncpy(char *destination, char *source, int max_chars)
{
	char *sr = destination;
	int source_index, dest_idx;

	source_index = 0;
	while (source[source_index] != '\0' && source_index < max_chars - 1)
	{
		destination[source_index] = source[source_index];
		source_index++;
	}
	if (source_index < max_chars)
	{
		dest_idx = source_index;
		while (dest_idx < max_chars)
		{
			destination[dest_idx] = '\0';
			dest_idx++;
		}
	}
	return (sr);
}

