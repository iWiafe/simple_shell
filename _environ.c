#include "shell.h"

/**
 * _myenv - a function that prints the current environment
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: 0 (Success)
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);

	return (0);
}

/**
 * _getenv - a function gets the value of an environ variable
 * @info: containing potential arguments. Used to maintain function prototype
 * @name: environment variable name
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *a;

	while (node)
	{
		a = starts_with(node->str, name);
		if (a && *a)
		{
			return (a);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a function that initialize a new environment variable
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: 0 (Success)
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _myunsetenv - a function that removes an environment variable
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: 0 (Success)
 */
int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);
	return (0);
}

/**
 * populate_env_list - a function that populates env linked list
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: 0 (Success)
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}

