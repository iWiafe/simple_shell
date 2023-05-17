#include "shell.h"

/**
 * add_node - program start
 * @head: input 1
 * @str: input 2
 * @num: input 3
 * Return: Always 0
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *nh; /*declaration*/

	if (!head)
		return (NULL);
	nh = malloc(sizeof(list_t));
	if (!nh)
		return (NULL);
	_memset((void *)nh, 0, sizeof(list_t));
	nh->num = num;
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
 * @num: input 3
 * Return: Always 0
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *nn, *nd; /*declaration*/

	if (!head)
		return (NULL);

	nd = *head;
	nn = malloc(sizeof(list_t));
	if (!nn)
		return (NULL);
	_memset((void *)nn, 0, sizeof(list_t));
	nn->num = num;
	if (str)
	{
		nn->str = _strdup(str);
		if (!nn->str)
		{
			free(nn);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = nn;
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
	list_t *nd, *prvnd; /*declaration*/
	unsigned int x = 0; /*initialization*/

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nd = *head;
		*head = (*head)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *head;
	while (nd)
	{
		if (x == index)
		{
			prvnd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		x++;
		prvnd = nd;
		nd = nd->next;
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
	list_t *nd, *nn, *head; /*declaration*/

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nd = head;
	while (nd)
	{
		nn = nd->next;
		free(nd->str);
		free(nd);
		nd = nn;
	}
	*head_ptr = NULL;
}
