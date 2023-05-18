#include "shell.h"

/**
 * **strtow - main function
 * @str: input 1
 * @d: input 2
 * Return: Always 0
 */

char **strtow(char *str, char *d)
{
	int f, g, u, x; /*Declaration*/
	int wd = 0; /*initialization*/
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (f = 0; str[f] != '\0'; f++)
		if (!is_delim(str[f], d) && (is_delim(str[f + 1], d) || !str[f + 1]))
			wd++;

	if (wd == 0)
		return (NULL);
	s = malloc((1 + wd) * sizeof(char *));
	if (!s)
		return (NULL);
	for (f = 0, g = 0; g < wd; g++)
	{
		while (is_delim(str[f], d))
			f++;
		u = 0;
		while (!is_delim(str[f + u], d) && str[f + u])
			u++;
		s[g] = malloc((u + 1) * sizeof(char));
		if (!s[g])
		{
			for (u = 0; u < g; u++)
				free(s[u]);
			free(s);
			return (NULL);
		}
		for (x = 0; x < u; x++)
			s[g][x] = str[f++];
		s[g][x] = 0;
	}
	s[g] = NULL;
	return (s);
}

/**
 * **strtow2 - program start
 * @str: string input
 * @d: input 2
 * Return: Always 0
 */
char **strtow2(char *str, char d)
{
	int x, l, k, n; /*Declaration*/
	int ws = 0; /*initialization*/
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
				    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			ws++;
	if (ws == 0)
		return (NULL);
	s = malloc((1 + ws) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, l = 0; l < ws; l++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		k = 0;
		while (str[x + k] != d && str[x + k] && str[x + k] != d)
			k++;
		s[l] = malloc((k + 1) * sizeof(char));
		if (!s[l])
		{
			for (k = 0; k < l; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			s[l][n] = str[x++];
		s[l][n] = 0;
	}
	s[l] = NULL;
	return (s);
}
