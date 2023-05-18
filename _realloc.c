#include "shell.h"

/**
 * _memset - main entry
 * @s: input 1
 * @b: pointer input 2
 * @n: input 3
 * Return: Return 0
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int y; /*intialization*/

	for (y = 0; y < n; y++)
		s[y] = b;
	return (s);
}

/**
 * ffree - start program
 *
 * @pp: main input
 */

void ffree(char **pp)
{
	char **v = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(v);
}

/**
 * _realloc - program start
 * @ptr: input 1
 * @old_size: input 2
 * @new_size: input 3
 * Return: Always 0
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *v;

	if (!ptr)
		return (malloc(new_size)); /*memory allocation*/
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	v = malloc(new_size);
	if (!v)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		v[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (v);
}
