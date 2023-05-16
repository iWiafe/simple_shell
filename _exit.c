#include "shell.h"

/**
 **_strncpy - a function that copies a string
 *@dest: string destination
 *@src: source string
 *@n: number of characters to be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *ds = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (ds);
}

/**
 **_strncat - a function that concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: maximum number of bytes to be used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *ds = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (ds);
}

/**
 **_strchr - a function that locates a character in a string
 *@s: string
 *@c: character
 *Return: a pointer (s) to the memory area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}

