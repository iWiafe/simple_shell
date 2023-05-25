#include "shell.h"

/**
 * list_len - main function
 * @h: input
 *
 * Return: Always o
 */
size_t list_len(const list_t *h)
{
	size_t f = 0;

	while (h)
	{
		h = h->next;
		f++;
	}
	return (f);
}

/**
 * list_to_strings - program start
 * @head: entry
 * Return: Always 0
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t f = list_len(head), y;
	char **strs;
	char *str;

	if (!head || !f)
		return (NULL);
	strs = malloc(sizeof(char *) * (f + 1));
	if (!strs)
		return (NULL);
	for (f = 0; node; node = node->next, f++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < f; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[f] = str;
	}
	strs[f] = NULL;
	return (strs);
}


/**
 * print_list - main function
 * @h: first input
 *
 * Return:size
 */
size_t print_list(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
		_puts(convert_number(h->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		b++;
	}
	return (b);
}

/**
 * node_starts_with - start of program
 * @node: input
 * @prefix: input
 * @c: input
 * Return: match the nodes
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *v = NULL;

	while (node)
	{
		v = starts_with(node->str, prefix);
		if (v && ((c == -1) || (*v == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - program start
 * @head: input
 * @node: input
 * Return: Always 0
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t v = 0;

	while (head)
	{
		if (head == node)
			return (v);
		head = head->next;
		v++;
	}
	return (-1);
}

