#include "shell.h"

/**
 * main - main function
 * @av: input 1
 *
 * @ac: imput 2
 *
 * Return: Always 0
 */

int main(int ac, char **av)
{
	info_t information[] = { INFO_INIT }; /*initialization*/
	int fdoc = 2; /*intialization*/

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdoc)
			: "r" (fdoc));

	if (ac == 2)
	{
		fdoc = open(av[1], O_RDONLY); /*file document opens*/
		if (fdoc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info_it~>readfd = fdoc;
	}
	populate_env_list(information);
	read_history(information);
	hsh(information, av);
	return (EXIT_SUCCESS);
}
