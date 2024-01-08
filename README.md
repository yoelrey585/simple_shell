# simple_shell
---

Simple UNIX command interpreter
Can handle command line with arguments, variables replacement and comments

### GCC command to compile

`
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
`

To run the code execute the hsh file

### FILES AND THE FUNCTIONS THEY CONTAIN
***
#### **built-in_funcs.c**
 * shellExit
 * switchDir
 * showHelp
####  **built-in_funcs1.c**
* showHistory
* unsetAlias
* setAlias
* print_singleAlias
* manageAlias

#### **custom_atoi.c**
* is_interactive
* is_delimeter
* _isalphabetic
* _atoi

#### **environment_utils.c**
- printEnv
- findEnv_variables
- setEnv_variables
- unsetEnv_variables
- populateEnv_list
```
========== error_handling.c ==========
_displayString
write_to_stderr
_writeToFd
_printStr

========== error_handling_update.c ==========
~ str_to_unsigned_int
~ display_error_message
~ print_decimal
~ convert_number
~ comment_remover
```
#### extended_string_ops.c
- _strncpy
- _strncat
- _strchr

#### get_environment.c
- getEnv
- unsetEnv
- setEnv

#### get_info.c
- initialize_info
- setInfo
- release_info

#### get_line.c
- bufferChained_commands
- getInput
- readBuffer
- custom_getline
- sigintHandler

#### history_management.c
- obtain_history_file_path
- store_history_to_file
- read_history
- append_history_list
- refresh_history_numbers

#### list_ops.c
- add_node
- my_append_node
- print_string_list
- remove_node_at_index
- empty_list

#### list_ops_update.c
- list_length
- list_to_string_arr
- display_list
- node_start_finder
- get_node_position

#### main.c
- main

#### memory_managment.c
- free_and_nullify

#### path_resolution.c
- isExecutable_cmd
- duplicate_char
- findCmd_path

#### reallocation.c
- _custom_memset
- free_string_array
- _custom_realloc

#### shell_processes.c
- hsh
- find_builtin

#### shell_processes1.c
- fork_and_execute_cmd
- find_and_execute_cmd

#### str_manipulation.c
- check_chain_delim
- check_chain_cond
- replace_alias
- replace_variable
- replaceStr

#### string.c
- my_strlen
- compare_strings
- find_substring
- concatenate_strings

#### string_split.c
- strSplit
- strSplit2

#### string_update.c
- string_copy
- string_duplicate
- puts
- _putchar
