#ifndef SIMPLE_SHELL_H_
#define SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly-linked list definition
 * @num: number field
 * @str: textual string data
 * @next: reference to the following/next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - define pseudo-arguments which will pass into a func,
 * establishes a consistent prototype for a ptr-function struct.
 * @arg: String containing arguments (gotten from get_line)
 * @argv: Array of strings (gotten from 'arg')
 * @path: A string representing the path for the current command
 * @argc: The count of arguments
 * @line_count:To keep track of error couns.
 * @err_num: Error code for any 'exit()'
 * @linecount_flag: checks if line of input is valid
 * @fname: file name
 * @env: local copy of _environ (linked_list)
 * @environ: Custom made _enviro (linked_list)
 * @history: Node for the history
 * @alias: Alias' node
 * @env_changed: Indicates whether _environ was edited
 * @status: The status of the command last executed
 * @cmd_buf: Contains address of pointer to command_buffer
 * @cmd_buf_type: Represents the command_type (||, &&, ;)
 * @readfd: The File descriptor used to read line input
 * @histcount: Count of history line numbers
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
	int histcount;
} info_t;

#define INFO_INIT                            \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

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

/* custom_atoi.c */
int is_interactive(info_t *);
int is_delimeter(char, char *);
int _isalphabetic(int);
int _atoi(char *);

/* shell_processes.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_and_execute_cmd(info_t *);
void fork_and_execute_cmd(info_t *);

/* path_resolution.c */
int isExecutable_cmd(info_t *, char *);
char *duplicate_char(char *, int, int);
char *findCmd_path(info_t *, char *, char *);

int loophsh(char **);

/* error_handling.c */
void _displayString(char *);
int write_to_stderr(char);
int _writeToFd(char c, int fd);
int _printStr(char *str, int fd);

/* string.c */
int my_strlen(char *);
int compare_strings(char *, char *);
char *find_substring(const char *, const char *);
char *concatenate_strings(char *, char *);

/* string_update.c */
char *_string_copy(char *, char *);
char *string_duplicate(const char *);
void _puts(char *);
int _putchar(char);

/* string_split.c */
char **strSplit(char *, char *);
char **strSplit2(char *, char);

/* extended_string_ops.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* reallocation.c */
char *_custom_memset(char *, char, unsigned int);
void free_string_array(char **);
void *_custom_realloc(void *, unsigned int, unsigned int);

/* memory_management.c */
int free_and_nullify(void **);

/* errors_handling_update.c */
int str_to_unsigned_int(char *);
void display_error_message(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void comment_remover(char *);

/* builtin_funcs.c */
int shellExit(info_t *);
int switchDir(info_t *);
int showHelp(info_t *);

/* builtin_funcs_update.c */
int showHistory(info_t *);
int manageAlias(info_t *);

/*get_line.c */
ssize_t getInput(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* info_management.c */
void initialize_info(info_t *);
void setInfo(info_t *, char **);
void release_info(info_t *, int);

/* environment_utils.c */
char *findEnv_variables(info_t *, const char *);
int printEnv(info_t *);
int setEnv_variables(info_t *);
int unsetEnv_variables(info_t *);
int populateEnv_list(info_t *);

/* get_environment.c */
char **getEnv(info_t *);
int unsetEnv(info_t *, char *);
int setEnv(info_t *, char *, char *);

/* history_management.c */
char *obtain_history_file_path(info_t *info);
int store_history_to_file(info_t *info);
int read_history(info_t *info);
int append_history_list(info_t *info, char *buf, int linecount);
int refresh_history_numbers(info_t *info);

/* list_ops.c */
list_t *add_node(list_t **, const char *, int);
list_t *my_append_node(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void empty_list(list_t **);

/* list_ops_update.c */
size_t list_length(const list_t *);
char **list_to_string_arr(list_t *);
size_t display_list(const list_t *);
list_t *node_start_finder(list_t *, char *, char);
ssize_t get_node_position(list_t *, list_t *);

/* manipulate_str.c */
int check_chain_delim(info_t *, char *, size_t *);
void check_chain_cond(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variable(info_t *);
int replaceStr(char **, char *);

#endif /* SIMPLE_SHELL_H */

