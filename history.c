#include "shell.h"

/**
 * get_history_file - beginning of program
 * @info: input
 * Return: Always 0
 */
char *get_history_file(info_t *info)
{
	char *buf, *direction;

	direction = _getenv(info, "HOME=");
	if (!direction)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(direction) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, direction);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - program begins
 * @info: input
 * Return: Always 0
 */

int write_history(info_t *info)
{
	ssize_t fdoc;
	char *fname = get_history_file(info); /* writing history*/
	list_t *s = NULL;

	if (!fname)
		return (-1);

	fdoc = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fdoc == -1)
		return (-1);
	for (s = info->history; s; s = s->next)
	{
		_putsfd(s->str, fdoc);
		_putfd('\n', fdoc);
	}
	_putfd(BUF_FLUSH, fdoc);
	close(fdoc);
	return (1);
}

/**
 * read_history - program begins
 * @info: input
 * Return: Always 0
 */
int read_history(info_t *info)
{
	int k = 0, endd = 0, counters = 0;
	ssize_t fdoc, readlen, file_size = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fdoc = open(filename, O_RDONLY);
	free(filename);
	if (fdoc == -1)
		return (0);
	if (!fstat(fdoc, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);
	readlen = read(fdoc, buf, file_size);
	buf[file_size] = 0;
	if (readlen <= 0)
		return (free(buf), 0);
	close(fdoc);
	for (k = 0; k < file_size; k++)
		if (buf[k] == '\n')
		{
			buf[k] = 0;
			build_history_list(info, buf + endd, counters++);
			endd = k + 1;
		}
	if (endd != k)
		build_history_list(info, buf + endd, counters++);
	free(buf);
	info->histcount = counters;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - beginning of function
 * @info: input one
 * @buf: input two
 * @linecount: input three
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *n = NULL;

	linecount = 0;
	if (info->history)
		n = info->history;
	add_node_end(&n, buf, linecount);

	if (!info->history)
		info->history = n;
	return (0);
}

/**
 * renumber_history - main function
 * @info: input
 * Return: Always 0
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int v = 0;

	while (node)
	{
		node->numb = v++;
		node = node->next;
	}
	return (info->histcount = v);
}
