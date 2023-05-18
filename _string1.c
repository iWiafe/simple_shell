#include "shell.h"

/**
 * _strcpy - main function
 * @dest: input one
 * @src: input two source
 * Return: Always 0
 */

char *_strcpy(char *dest, char *src)
{
	int z = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[z])
	{
		dest[z] = src[z];
		z++;
	}
	dest[z] = 0;
	return (dest);
}

/**
 * _strdup - main function
 * @str: input string
 * Return: Always 0
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *u;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	u = malloc(sizeof(char) * (len + 1));
	if (!u)
		return (NULL);
	for (len++; len--;)
		u[len] = *--str;
	return (u);
}

/**
 * _puts - start of program
 * @str: input string
 * Return: Always 0
 */

void _puts(char *str)
{
	int y = 0; /* intialization*/

	if (!str)
		return;
	while (str[y] != '\0')
	{
		_putchar(str[y]);
		y++;
	}
}

/**
 * _putchar - main function
 * @c: input main
 * Return: Always 0
 */

int _putchar(char c)
{
	static int x; /*declaration*/
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buffer, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buffer[x++] = c;
	return (1);
}
