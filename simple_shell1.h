#ifndef SIMPLE_SHELL_1_H_
#define SIMPLE_SHELL_1_H_


#include "simple_shell.h"

/*Funcs in custom_atoi.c */
int _atoi(char *);
int is_delimeter(char, char *);
int _isalphabetic(int);
int is_interactive(info_t *);

/*Funcs in path_resolution.c */
int isExecutable_cmd(info_t *, char *);
char *duplicate_char(char *, int, int);
char *findCmd_path(info_t *, char *, char *);

/*Funcs in error_handling.c */
void _displayString(char *);
int _printStr(char *str, int fd);
int write_to_stderr(char);
int _writeToFd(char c, int fd);


/*Funcs in shell_processes.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_and_execute_cmd(info_t *);
void fork_and_execute_cmd(info_t *);

int loophsh(char **);

/*Funcs in string.c */
int my_strlen(char *);
int compare_strings(char *, char *);
char *find_substring(const char *, const char *);
char *concatenate_strings(char *, char *);

/*Funcs in string_split.c */
char **strSplit(char *, char *);
char **strSplit2(char *, char);

/*Funcs in string_update.c */
char *_string_copy(char *, char *);
char *string_duplicate(const char *);
void _puts(char *);
int _putchar(char);

/*Funcs in get_line.c */
ssize_t getInput(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*Funcs in extended_string_ops.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);


/*Funcs in memory_management.c */
int free_and_nullify(void **);

/*Funcs in errors_handling_update.c */
void display_error_message(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
int str_to_unsigned_int(char *);

/*Funcs in info_management.c */
void initialize_info(info_t *);
void setInfo(info_t *, char **);
void release_info(info_t *, int);

/*Funcs in built-in_funcs.c */
int switchDir(info_t *);
int shellExit(info_t *);
int showHelp(info_t *);

/*Funcs in built-in_funcs_update.c */
int showHistory(info_t *);
int manageAlias(info_t *);

/*Funcs in reallocation.c */
char *_custom_memset(char *, char, unsigned int);
void free_string_array(char **);
void *_custom_realloc(void *, unsigned int, unsigned int);

/*Funcs in history_management.c */
char *obtain_history_file_path(info_t *info);
int read_history(info_t *info);
int store_history_to_file(info_t *info);
int refresh_history_numbers(info_t *info);
int append_history_list(info_t *info, char *buf, int linecount);


/*Funcs in environment_utils.c */
int printEnv(info_t *);
int setEnv_variables(info_t *);
int unsetEnv_variables(info_t *);
int populateEnv_list(info_t *);
char *findEnv_variables(info_t *, const char *);

/*Funcs in get_environment.c */
char **getEnv(info_t *);
int setEnv(info_t *, char *, char *);
int unsetEnv(info_t *, char *);


/*Funcs in list_ops.c */
list_t *add_node(list_t **, const char *, int);
list_t *my_append_node(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void empty_list(list_t **);

/*Funcs in list_ops_update.c */
size_t list_length(const list_t *);
char **list_to_string_arr(list_t *);
size_t display_list(const list_t *);
list_t *node_start_finder(list_t *, char *, char);
ssize_t get_node_position(list_t *, list_t *);

/*Funcs in manipulate_str.c */
int check_chain_delim(info_t *, char *, size_t *);
void check_chain_cond(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variable(info_t *);
int replaceStr(char **, char *);

#endif /* SIMPLE_SHELL_1_H */
