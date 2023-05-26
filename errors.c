#include "shell.h"

/**
 * _eputs - a function that prints an input string
 * @str: string to print
 * Return: void
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
	{
		return;
	}
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - a function that writes the character c to stderr
 * @c: character to be printed
 * Return: 1 on success, -1 is returned on error,
 * and errno is set appropriately
 */
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putfd - a function that writes the character c to given fd
 * @c: character to be printed
 * @fd: filedescriptor to write
 * Return: 1 on success, -1 is returned on success,
 * and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putsfd - a file that prints an input string
 * @str: string to print
 * @fd: filedescriptor to write
 * Return: number of chars
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}

