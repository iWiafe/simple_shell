#include "shell.h"

/**
 * hsh - main shell loop
 * @info: input
 * @av: input
 * Return: Always 0
 */
int hsh(info_t *info, char **av)
{
	ssize_t c = 0;
	int g = 0;

	while (c != -1 && g != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		c = get_input(info);
		if (c != -1)
		{
			set_info(info, av);
			g = find_builtin(info);
			if (g == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (g == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (g);
}

/**
 * find_builtin - main function
 * @info: input
 * Return: Always 0
 */

int find_builtin(info_t *info)
{
	int y, bt = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (y = 0; builtintbl[y].type; y++)
		if (_strcmp(info->argv[0], builtintbl[y].type) == 0)
		{
			info->line_count++;
			bt = builtintbl[y].funct(info);
			break;
		}
	return (bt);
}

/**
 * find_cmd - program begins
 * @info: input
 * Return:  void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int r, v;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (r = 0, v = 0; info->arg[r]; r++)
		if (!is_delim(info->arg[r], " \t\n"))
			v++;
	if (!v)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - main entry
 * @info: input
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t ch;

	ch = fork();
	if (ch == -1)
	{
		perror("Error:");
		return;
	}
	if (ch == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
