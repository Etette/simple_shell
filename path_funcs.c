#include "shell.h"

/**
 * get_path - copies the $PATH into the string path
 * @path: string to copy $PATH into
 * @list: environmental variable list
 * Return: 0 on success, 1 if it fails
 */

int get_path(char *path, env_t *list)
{
	env_t *temp;

	temp = list;
	for (; temp->next != NULL; temp = temp->next)
	{
		if (_str_match_tonull(temp->value, "PATH=") != 0)
		{
			_strcpy(path, temp->value);
			return (0);
		}
	}
	return (1);
}

/**
 * tokenize_path - creates an array of strings, each string is a dir
 * in the $PATH variable
 * @search_path: array of strings that contains a searchable path
 * for each string space
 * @path: string that contains the path
 * @size: buffer size
 * Return: a 2D array of tokens
 */

char **tokenize_path(char **search_path, char *path, int size)
{
	int i, count, s_index;
	char *temp, *buffer;

	buffer = safe_malloc(sizeof(char *) * size);
	buffer[0] = '\0';
	for (i = 0, count = 1; path[i] != '\0'; i++)
	{
		if (path[i] == ':')
			count++;
	}
	count++;
	search_path = safe_malloc(sizeof(char *) * count);
	/* skip the PATH= */
	for (temp = path; *temp != '='; temp++)
		;
	temp++, s_index = 0;
	do {
		if (*temp == ':' || *temp == '\0')
		{
			_strncat(buffer, "/", 1);
			search_path[s_index] = safe_malloc(sizeof(char) * size);
			search_path[s_index][0] = '\0';
			_strncat(search_path[s_index], buffer, _strlen(buffer));
			s_index++;
			buffer[0] = '\0';
		}
		else
			_strncat(buffer, temp, 1);
	} while (*temp++);
	search_path[s_index] = safe_malloc(sizeof(char *));
	search_path[s_index] = NULL;
	return (search_path);
}

/**
 * create_path - checks if command exist
 * @cmd: command to append to end of string from stdin
 * @search_path: array of path strings for command checking
 * Return: 0 on success, 1 if failed
 * this function opens commands in different dirs to check if
 * the command exist
 */

int create_path(char *cmd, char **search_path)
{
	int i, fd;

	for (i = 0; search_path[i] != NULL; i++)
	{
		_strncat(search_path[i], cmd, _strlen(cmd));
		fd = open(search_path[i], O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			_strcpy(cmd, search_path[i]);
			return (0);
		}
	}
	write(0, "Error: command not found\n", 25);
	return (-1);
}
