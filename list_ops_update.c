#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * list_length - Checks length of nodes in linked list
 * @head_node: first node pntr
 *
 * Return: Length of the list
 */
size_t list_length(const list_t *head_node)
{
	size_t count = 0;

	while (head_node)
	{
		head_node = head_node->next;
		count = count + 1;
	}
	return (count);
}

/**
 * list_to_string_arr - Changes a list of strings into a string array
 * @head: Pointer to first node of the list
 *
 * Return: Array of combined strings
 */
char **list_to_string_arr(list_t *head)
{
	size_t count = list_length(head), index;
	list_t *node = head;
	char **string_array;
	char *strn;

	if (!head || !count)
		return (NULL);
	string_array = malloc(sizeof(char *) * (count + 1));
	if (!string_array)
		return (NULL);
	for (count = 0; node; node = node->next, count++)
	{
		strn = malloc(my_strlen(node->str) + 1);
		if (!strn)
		{
			for (index = 0; index < count; index++)
				free(string_array[index]);
			free(string_array);
			return (NULL);
		}

		strn = _string_copy(strn, node->str);
		string_array[count] = strn;
	}
	string_array[count] = NULL;
	return (string_array);
}

/**
 * display_list - Displays all elements of a linked list of type list_t.
 * @head_node: Pointer to the first node of the list.
 *
 * Return: The total nodes in the list
 */
size_t display_list(const list_t *head_node)
{
	size_t count = 0;

	while (head_node)
	{
		_puts(convert_number(head_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head_node->str ? head_node->str : "(nil)");
		_puts("\n");
		head_node = head_node->next;
		count++;
	}
	return (count);
}

/**
 * node_start_finder - Locates node with a given prefix
 * @node: Pointer of the head node.
 * @prefix: The prefix to match against
 * @char_to_match: The character to match
 *
 * Return: The similar node or NULL if no match found
 */
list_t *node_start_finder(list_t *node, char *prefix, char char_to_match)
{
	char *suffix = NULL;

	while (node)
	{
		suffix = find_substring(node->str, prefix);
		if (suffix && ((char_to_match == -1) || (*suffix == char_to_match)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_position - Retrieves the (index) of a node
 * @head: Pointer of the head node
 * @target_node: Pointer to the node we're searching for
 *
 * Return: The position (index) of the node or
 * -1 if the node is not found
 */
ssize_t get_node_position(list_t *head, list_t *target_node)
{
	size_t count = 0;

	while (head)
	{
		if (head == target_node)
			return (count);
		head = head->next;
		count++;
	}
	return (-1);
}
