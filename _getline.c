#include "shell.h"

/**
 * input_buf - a function that buffers chained commands
 * @info: struct parameter
 * @buf: buffer address
 * @len: len address
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t ken_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &ken_p, stdin);
#else
		a = _getline(info, buf, &ken_p);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0';
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - a function that gets a line minus the newline
 * @info: struct parameter
 * Return: bytes to be read
 */
ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t a, b, ken;
	ssize_t z = 0;
	char **buf_m = &(info->arg), *m;

	_putchar(BUF_FLUSH);
	z = input_buf(info, &buff, &ken);
	if (z == -1)
		return (-1);
	if (ken)
	{
		b = a;
		m = buff + a;

		check_chain(info, buff, &b, a, ken);
		while (b < ken)
		{
			if (is_chain(info, buff, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= ken)
		{
			a = ken = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_m = m;
		return (_strlen(m));
	}

	*buf_m = buff;
	return (z);
}

/**
 * read_buf - a function that reads a buffer
 * @info: struct parameter
 * @buf: buffer
 * @i: size
 * Return: buffer
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t a = 0;

	if (*i)
		return (0);
	a = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}

/**
 * _getline - a function that gets the next line of input from STDIN
 * @info: struct parameter
 * @ptr: address of a pointer to buffer
 * @length: preallocated ptr buffer size if not NULL
 * Return: z
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static size_t a, ken;
	static char buf[READ_BUF_SIZE];
	size_t b;
	ssize_t z = 0, n = 0;
	char *m = NULL, *new_m = NULL, *s;

	m = *ptr;
	if (m && length)
		z = *length;
	if (a == ken)
		a = ken = 0;

	n = read_buf(info, buf, &ken);
	if (n == -1 || (n == 0 && ken == 0))
		return (-1);

	s = _strchr(buf + a, '\n');
	b = s ? 1 + (unsigned int)(s - buf) : ken;
	new_m = _realloc(m, z, z ? z + b : b + 1);
	if (!new_m)
		return (m ? free(m), -1 : -1);

	if (z)
		_strncat(new_m, buf + a, b - a);
	else
		_strncpy(new_m, buf + a, b - a + 1);

	z += b - a;
	a = b;
	m = new_m;

	if (length)
		*length = z;
	*ptr = m;
	return (z);
}

/**
 * sigintHandler - a function that blocks ctrl-C
 * @sig_num: signal number
 * Return: nothing
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

