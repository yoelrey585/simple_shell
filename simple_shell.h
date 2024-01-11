#ifndef SIMPLE_SHELL_H_
#define SIMPLE_SHELL_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define USE_GETLINE 0
#define USE_STRTOK 0

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

extern char **environ;

/**
 * struct listStr - list definition for single link
 * @num: integers
 * @str: textual string data
 * @next: reference to the following/next node
 */
typedef struct listStr
{
	char *str;
	int num;
	struct listStr *next;
} list_t;

/**
 * struct passinfo - define pseudo-arguments which will pass into a func
 *
 * @argv: Array of strings (gotten from 'arg')
 * @path: A string representing the path for the current command
 * @argc: The count of arguments
 * @line_count:To keep track of error couns.
 * @arg: String containing arguments (gotten from get_line)
 * @err_num: Error code for any 'exit()'
 * @linecount_flag: checks if line of input is valid
 * @env_changed: Indicates whether _environ was edited
 * @status: The status of the command last executed
 * @cmd_buf: Contains address of pointer to command_buffer
 * @cmd_buf_type: Represents the command_type (||, &&, ;)
 * @readfd: The File descriptor used to read line input
 * @histCount: Count of history line numbers
 * @fname: file name
 * @env: local copy of _environ (linked_list)
 * @environ: Custom made _enviro (linked_list)
 * @history: Node for the history
 * @alias: Alias' node
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;

	int linecount_flag;
	char *fname;
	list_t *env;

	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histCount;
} info_t;


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function program will execute
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

#define INFO_INIT                            \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

#endif /* SIMPLE_SHELL_H */

