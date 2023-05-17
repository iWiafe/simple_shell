#include "shell.h"

/**
 * get_history_file - beginning of program
 * @info: input
 * Return: Always 0
 */
char *get_history_file(info_t *info)
{
	char *buffer, *direction;

	direction = _getenv(info, "HOME=");
	if (!direction)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(direction) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, direction);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
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
	int k, endd, counters = 0;
	ssize_t fdoc, readlen, file_size = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(info);

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
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	readlen = read(fdoc, buffer, file_size);
	buffer[file_size] = 0;
	if (readlen <= 0)
		return (free(buffer), 0);
	close(fdoc);
	for (k = 0; k < file_size; k++)
		if (buffer[k] == '\n')
		{
			buffer[k] = 0;
			build_history_list(info, buffer + endd, counters++);
			endd = k + 1;
		}
	if (endd != k)
		build_history_list(info, buffer + endd, counters++);
	free(buffer);
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
	list_t *n = info->history;
	int v = 0;

	while (n)
	{
		n->num = v++;
		n = n->next;
	}
	return (info->histcount = v);
}
