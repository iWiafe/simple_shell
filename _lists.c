#include "shell.h"

/**
 * add_node - program start
 * @head: input 1
 * @str: input 2
 * @numb: input 3
 * Return: Always 0
 */
list_t *add_node(list_t **head, const char *str, int numb)
{
	list_t *nh; /*declaration*/

	if (!head)
		return (NULL);
	nh = malloc(sizeof(list_t));
	if (!nh)
		return (NULL);
	_memset((void *)nh, 0, sizeof(list_t));
	nh->numb = numb;
	if (str)
	{
		nh->str = _strdup(str);
		if (!nh->str)
		{
			free(nh);
			return (NULL);
		}
	}
	nh->next = *head;
	*head = nh;
	return (nh);
}

/**
 * add_node_end - main function
 * @head: input 1
 * @str: input 2
 * @numb: input 3
 * Return: Always 0
 */
list_t *add_node_end(list_t **head, const char *str, int numb)
{
	list_t *nn, *node; /*declaration*/

	numb = 0;
	if (!head)
		return (NULL);

	node = *head;
	nn = malloc(sizeof(list_t));
	if (!nn)
		return (NULL);
	_memset((void *)nn, 0, sizeof(list_t));
	nn->numb = numb;
	if (str)
	{
		nn->str = _strdup(str);
		if (!nn->str)
		{
			free(nn);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = nn;
	}
	else
		*head = nn;
	return (nn);
}

/**
 * print_list_str - program starts
 * @h: input 1
 * Return: Always 0
 */

size_t print_list_str(const list_t *h)
{
	size_t w = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		w++;
	}
	return (w);
}

/**
 * delete_node_at_index - main function
 * @head: input 1
 * @index: input 2
 * Return: Always 0
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prvnd; /*declaration*/
	unsigned int x = 0; /*initialization*/

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (x == index)
		{
			prvnd->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prvnd = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - start
 * @head_ptr: input
 * Return: Always
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *nn, *head; /*declaration*/

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		nn = node->next;
		free(node->str);
		free(node);
		node = nn;
	}
	*head_ptr = NULL;
}
