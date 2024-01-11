#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * *add_node - Adds a cur_node to beginning of linked list
 * @head_node: Pointer to the head_node cur_node
 * @str_data: "str" data of the new cur_node
 * @index: Index for cur_node
 *
 * Return: Size of the list
 */
list_t *add_node(list_t **head_node, const char *str_data, int index)
{
	list_t *new_head;

	if (!head_node)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_custom_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = index;
	if (str_data)
	{
		new_head->str = string_duplicate(str_data);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head_node;
	*head_node = new_head;
	return (new_head);
}

/**
 * *my_append_node - Adds cur_node at the end of list
 * @head_node: Pointer to head_node cur_node
 * @data: "str" field of the cur_node
 * @num_index: Node index
 *
 * Return: Size of updated linked list
 */
list_t *my_append_node(list_t **head_node, const char *data, int num_index)
{
	list_t *new_node, *cur_node;

	if (!head_node)
		return (NULL);

	cur_node = *head_node;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_custom_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num_index;
	if (data)
	{
		new_node->str = string_duplicate(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (cur_node)
	{
		while (cur_node->next)
			cur_node = cur_node->next;
		cur_node->next = new_node;
	}
	else
		*head_node = new_node;
	return (new_node);
}

/**
 * print_string_list - Displays "str" element of a linked list
 * @head_node: Pointer of the head_node
 *
 * Return: Linked list's size/data bytes
 */
size_t print_string_list(const list_t *head_node)
{
	size_t count = 0;

	while (head_node)
	{
		_puts(head_node->str ? head_node->str : "(nil)");
		_puts("\n");
		head_node = head_node->next;
		count++;
	}
	return (count);
}

/**
 * remove_node_at_index - Removes a specified cur_node at an index
 * @head_node: Pointer of first/head_node cur_node
 * @index: Index of the cur_node to be removed
 *
 * Return: 1 (success), 0 otherwise
 */
int remove_node_at_index(list_t **head_node, unsigned int index)
{
	list_t *cur_node, *prev_node;
	unsigned int count = 0;

	if (!head_node || !*head_node)
		return (0);

	if (!index)
	{
		cur_node = *head_node;
		*head_node = (*head_node)->next;
		free(cur_node->str);
		free(cur_node);
		return (1);
	}
	cur_node = *head_node;
	while (cur_node)
	{
		if (count == index)
		{
			prev_node->next = cur_node->next;
			free(cur_node->str);
			free(cur_node);
			return (1);
		}
		count++;
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
	return (0);
}

/**
 * empty_list - Releases memory occupied by nodes in list
 * @head_ptr: Pointer to the head_node cur_node
 *
 * Return: Void
 */
void empty_list(list_t **head_ptr)
{
	list_t *cur_node, *next_node, *head_node;

	if (!head_ptr || !*head_ptr)
		return;
	head_node = *head_ptr;
	cur_node = head_node;
	while (cur_node)
	{
		next_node = cur_node->next;
		free(cur_node->str);
		free(cur_node);
		cur_node = next_node;
	}
	*head_ptr = NULL;
}
