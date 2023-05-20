#include "shell.h"

/**
 * list_len - function starts
 * @h: inputs
 *
 * Return: Always 0
 */

size_t list_len(const list_t *h)
{
	size_t y = 0;

	while (h)
	{
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * list_to_strings - main function
 * @head: inputs
 * Return: Always 0
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t w = list_len(head);
	size_t x;
	char **b;
	char *z;

	if (!head || !w)
		return (NULL);
	b = malloc(sizeof(char *) * (w + 1));
	if (!b)
		return (NULL);
	for (w = 0; node; node = node->next, w++)
	{
		z = malloc(_strlen(node->z) + 1);
		if (!z)
		{
			for (x = 0; x < w; x++)
				free(b[x]);
			free(b);
			return (NULL);
		}

		z = _strcpy(z, node->z);
		b[w] = z;
	}
	b[w] = NULL;
	return (b);
}


/**
 * print_list - entry point
 * @h: main input
 * Return: Always 0
 */

size_t print_list(const list_t *h)
{
	size_t s = 0;

	while (h)
	{
		_puts(convert_number(h->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * node_starts_with - main function
 * @node: input one
 * @prefix: input two
 * @c: input three
 * Return: Always 0
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *f = NULL;

	while (node)
	{
		f = starts_with(node->z, prefix);
		if (f && ((c == -1) || (*f == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - main entry
 * @head: input 1
 *
 * @node: input 2
 * Return: Always 0
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t g = 0;

	while (head)
	{
		if (head == node)
			return (g);
		head = head->next;
		g++;
	}
	return (-1);
}
