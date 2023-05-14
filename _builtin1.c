#include "shell.h"

/**
 * _myhistory - a function that displays the history list, one command by line,
 * preceded with line numbers, starting from 0.
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: 0 (Success)
 */
int _myhistory(info_t *info)
{
	print_list(info->history);

	return (0);
}

/**
 * unset_alias - a function that sets alias to string
 * @info: struct parameter
 * @str: string alias
 * Return: Always 0 on success, on error 1
 */
int unset_alias(info_t *info, char *str)
{
	char *a, b;
	int outcome;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	outcome = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*a = b;
	return (outcome);
}

/**
 * set_alias - a function that sets alias to string
 * @info: struct parameter
 * @str: string alias
 * Return: Always 0 on success, on error 1
 */
int set_alias(info_t *info, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a)
	{
		return (1);
	}
	if (!*++a)
	{
		return (unset_alias(info, str));
	}

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - a function that prints an alias string
 * @node: alias node
 * Return: Always 0 on success, on error 1
 */
int print_alias(list_t *node)
{
	char *a = NULL, *b = NULL;

	if (node)
	{
		a = _strchr(node->str, '=');
		for (b = node->str; b <= a; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(a + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - a function that mimics the alias builtin (man alias)
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: 0 (Success)
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		b = _strchr(info->argv[a], '=');
		if (b)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}
	return (0);
}

