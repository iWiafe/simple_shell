#include "shell.h"

/**
 * is_cmd - start of program
 * @info: input one
 * @path: Second input
 * Return: Always 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat x;

	(void)info;
	if (!path || stat(path, &x))
		return (0);

	if (x.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - main function
 * @pathstr: input one
 * @start: input two
 * @stop: input three
 * Return: Always 0
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int w = 0, g = 0;

	for (g = 0, w = start; w < stop; w++)
		if (pathstr[w] != ':')
			buffer[g++] = pathstr[w];
	buffer[g] = 0;
	return (buffer);
}

/**
 * find_path - main function
 * @info: input info
 * @pathstr: path
 * @cmd: input
 * Return: Always 0
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int z = 0, cp = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[z] || pathstr[z] == ':')
		{
			p = dup_chars(pathstr, cp, z);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[z])
				break;
			cp = z;
		}
		z++;
	}
	return (NULL);
}
