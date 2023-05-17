#include "shell.h"

/**
 * clear_info - start of programme
 *
 * @info: structure input
 *
 */

void clear_info(info_t *info)
{
	info->argv = NULL;
	info->argc = 0;
	info->path = NULL;
	info->arg = NULL;
}

/**
 * set_info - main entry
 * @av: input
 * @info: input
 */
void set_info(info_t *info, char **av)
{
	int g = 0; /*intialization*/

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (g = 0; info->argv && info->argv[g]; g++)
			;
		info->argc = g;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - program start
 *
 * @info: input1
 *
 *
 * @all: input2
 */

void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg); /*freeing information*/
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
