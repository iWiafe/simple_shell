#include "shell.h"

/**
 * is_chain - main function
 * @info: input one
 * @buf: input two
 * @p: input
 * Return: Always 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t f = *p; /*intialization*/

	if (buf[f] == '|' && buf[f + 1] == '|')
	{
		buf[f] = 0;
		f++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[f] == '&' && buf[f + 1] == '&')
	{
		buf[f] = 0;
		f++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[f] == ';') /* else condition */
	{
		buf[f] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = f;
	return (1);
}

/**
 * check_chain - main function
 * @info: input struct
 * @buf: second input
 *
 * @p: input 3 address
 * @i: input 4
 * @len: input 5
 * Return: Always 0
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t m = *p; /*intialization*/

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}

	*p = m;
}

/**
 * replace_alias - main function
 * @info: input
 * Return: Always 0
 */

int replace_alias(info_t *info)
{
	int x;/*declaration*/
	list_t *nd; /*declaration*/
	char *y;/*declaration*/

	for (x = 0; x < 10; x++)
	{
		nd = node_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		y = _strchr(nd->str, '=');
		if (!y)
			return (0);
		y = _strdup(y + 1);
		if (!y)
			return (0);
		info->argv[0] = y;
	}
	return (1);
}

/**
 * replace_vars - program start
 * @info: input main
 *
 * Return: Always 0
 */

int replace_vars(info_t *info)
{
	int c = 0;/*declaration*/
	list_t *nd;/*declaration*/

	for (c = 0; info->argv[c]; c++)
	{
		if (info->argv[c][0] != '$' || !info->argv[c][1])
			continue;

		if (!_strcmp(info->argv[c], "$?"))
		{
			replace_string(&(info->argv[c]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[c], "$$"))
		{
			replace_string(&(info->argv[c]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(info->env, &info->argv[c][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[c]),
					_strdup(_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[c], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - beginning of program
 * @old: previous string
 * @new: new string
 * Return: Always 0
 */

int replace_string(char **old, char *new)
{
	free(*old);/*freeing*/
	*old = new;
	return (1);
}
