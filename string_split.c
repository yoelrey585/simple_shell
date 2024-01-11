#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * **strSplit - Splits a string into words using specified delimiters
 * @str: string to be input
 * @delim: The delimiters
 *
 * Return: Pointer to an array of strings
 * NULL if failed
 */
char **strSplit(char *str, char *delim)
{
	int i, j, word_len, char_count, num_words = 0;
	char **result;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimeter(str[i], delim) &&
				(is_delimeter(str[i + 1], delim) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimeter(str[i], delim))
			i++;
		word_len = 0;
		while (!is_delimeter(str[i + word_len], delim) && str[i + word_len])
			word_len++;
		result[j] = malloc((word_len + 1) * sizeof(char));
		if (!result[j])
		{
			for (word_len = 0; word_len < j; word_len++)
				free(result[word_len]);
			free(result);
			return (NULL);
		}
		for (char_count = 0; char_count < word_len; char_count++)
			result[j][char_count] = str[i++];
		result[j][char_count] = 0;
	}
	result[j] = NULL;
	return (result);
}

/**
 * strSplit2 - Splits a string into words using single character delimiter
 * @str: string to be input
 * @delim: Chosen delimiter
 *
 * Return: Pointer to array of strings,
 * NULL if failed
 */
char **strSplit2(char *str, char delim)
{
	int i, j, word_len, char_count, num_words = 0;
	char **result;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		word_len = 0;
		while (str[i + word_len] != delim && str[i + word_len]
				&& str[i + word_len] != delim)
			word_len++;
		result[j] = malloc((word_len + 1) * sizeof(char));
		if (!result[j])
		{
			for (word_len = 0; word_len < j; word_len++)
				free(result[word_len]);
			free(result);
			return (NULL);
		}
		for (char_count = 0; char_count < word_len; char_count++)
			result[j][char_count] = str[i++];
		result[j][char_count] = 0;
	}
	result[j] = NULL;
	return (result);
}
