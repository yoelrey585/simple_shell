#include "simple_shell.h"
#include "simple_shell1.h"

/**
 * bufferChained_commands - stores chained commands
 * to be executed sequentially
 * @info: Structure containing argument parameters
 * @chain_buf: Address of chained command buffer
 * @buf_len: Address of buffer length variable
 *
 * Return: Number of bytes read
 */

ssize_t bufferChained_commands(info_t *info, char **chain_buf, size_t *buf_len)
{
	ssize_t bytes_read = 0;
	size_t buffer_len = 0;

	if (!*buf_len)
	{

		free(*chain_buf);
		*chain_buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(chain_buf, &buffer_len, stdin);
#else
		bytes_read = custom_getline(info, chain_buf, &buffer_len);
#endif
		if (bytes_read > 0)
		{
			if ((*chain_buf)[bytes_read - 1] == '\n')
			{
				(*chain_buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;

			append_history_list(info, *chain_buf, info->histCount++);
			{
				*buf_len = bytes_read;
				info->cmd_buf = chain_buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * getInput - Retrieves a line excluding the newline character
 * @info: Structure containing parameter arguments
 *
 * Return: Number of bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *chain_buf;
	static size_t row, j, buf_len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *pt;

	_putchar(BUF_FLUSH);
	bytes_read = bufferChained_commands(info, &chain_buf, &buf_len);
	if (bytes_read == -1)
		return (-1);
	if (buf_len)
	{
		j = row;
		pt = chain_buf + row;

		check_chain_cond(info, chain_buf, &j, row, buf_len);
		while (j < buf_len)
		{
			if (check_chain_delim(info, chain_buf, &j))
				break;
			j = j + 1;
		}

		row = 1 + j;
		if (row >= buf_len)
		{
			row = buf_len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = pt;
		return (my_strlen(pt));
	}

	*buf_p = chain_buf;
	return (bytes_read);
}

/**
 * sigintHandler - Handles the Ctrl-C interrupt signal
 * @sigNum: The signal number
 */
void sigintHandler(__attribute__((unused)) int sigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * readBuffer - Job to read from a buffer
 * @info: Structure containing parameter of argument
 * @buffer: Buffer
 * @pos_z: Size
 *
 * Return: bytes_read
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *pos_z)
{
	ssize_t bytes_read = 0;

	if (*pos_z)
		return (0);
	bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*pos_z = bytes_read;
	return (bytes_read);
}

/**
 * custom_getline - Reads the next line of input from STDIN
 * @info: Structure containing parameter argument
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: total_bytes_read
 */
int custom_getline(info_t *info, char **pntr, size_t *leng)
{
	static char chain_buf[READ_BUF_SIZE];
	static size_t i, buf_len;
	ssize_t s = 0, bytes_read = 0;
	size_t col_k;
	char *p = NULL, *newPtr = NULL, *ch;

	p = *pntr;
	if (p && leng)
		s = *leng;
	if (i == buf_len)
		i = buf_len = 0;

	bytes_read = readBuffer(info, chain_buf, &buf_len);
	if (bytes_read == -1 || (bytes_read == 0 && buf_len == 0))
		return (-1);

	ch = _strchr(chain_buf + i, '\n');
	col_k = ch ? 1 + (unsigned int)(ch - chain_buf) : buf_len;
	newPtr = _custom_realloc(p, s, s ? s + col_k : col_k + 1);
	if (!newPtr)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(newPtr, chain_buf + i, col_k - i);
	else
		_strncpy(newPtr, chain_buf + i, col_k - i + 1);

	s += col_k - i;
	i = col_k;
	p = newPtr;

	if (leng)
		*leng = s;
	*pntr = p;
	return (s);
}


