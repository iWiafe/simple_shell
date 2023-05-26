#include "shell.h"

/**
 * get_environ - a function that returns the string
 * array copy of our environ
 * @info: Structure with potential arguments
 * Return: 0 (Success)
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - a function that removes an environment variable
 * @info: with potential arguments
 * Return: 1 on delete, otherwise 0
 * @var: string environment variable
 */
int _unsetenv(info_t *info, char *var)
{
	size_t a = 0;
	char *m;
	list_t *node = info->env;

	if (!node || !var)
	{
		return (0);
	}
	while (node)
	{
		m = starts_with(node->str, var);
		if (m && *m == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - a function that initialize a new environment variable,
 * or modify an existing one
 * @info: Structure with potential arguments
 * @var: string env var
 * @value: value of string env variable
 * Return: 0 (success)
 */
int _setenv(info_t *info, char *var, char *value)
{
	list_t *node;
	char *m;
	char *buff = NULL;

	if (!var || !value)
	{
		return (0);
	}
	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
	{
		return (1);
	}
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		m = starts_with(node->str, var);
		if (m && *m == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

