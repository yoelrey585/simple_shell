#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * main - Where the code begins to execute
 * @argCount: short forArgument count
 * @argVector: short for Argument vector
 *
 * Return: 0 for success, 1 for error
 */
int main(int argCount, char **argVector)
{
	int file_d = 2;
	info_t info[] = { INFO_INIT };

	printf("\t\t\t Simple Shell\n");

	asm ("mov %0, %1\n\t"
		"add $10, %0"
		: "=r" (file_d)
		: "r" (file_d));

	if (argCount == 2)
	{
		file_d = open(argVector[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_displayString(argVector[0]);
				_displayString(": 0: Cannot open ");
				_displayString(argVector[1]);
				write_to_stderr('\n');
				write_to_stderr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = file_d;
	}
	populateEnv_list(info);
	read_history(info);
	hsh(info, argVector);
	return (EXIT_SUCCESS);
}
