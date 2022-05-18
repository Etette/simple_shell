#include "shell.h"

/**
 * _str_match - check_match 2 strings
 * @s1: string 1
 * @s2: string 2
 * Return: 1 on success, 0 on failure
 */
int _str_match(char *s1, char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return (1);
		if (_is_whitespace(s1[i]) || _is_whitespace(s2[i]))
			return (1);
	}
	if (s1[i] == '\0' || s2[i] == '\0')
		return (1);
	if (_is_whitespace(s1[i]) || _is_whitespace(s2[i]))
		return (1);
	return (0);
}

/**
 * string_match - find if str match, w multiple delims to stop the match
 * @s1: string 1
 * @s2: string 2
 * @delim: delim to stop the match
 * Return: 1 if match, 0 if no match
 */

int string_match(char *s1, char *s2, char *delim)
{
	int i;

	if (s1 == NULL || s2 == NULL || delim == NULL)
		return (0);
	for (i = 0; s1[i] == s2[i]; i++)
		if (char_match(s1[i], delim))
			return (1);
	if (char_match(s1[i], delim) || char_match(s2[i], delim))
		return (1);

	return (0);
}

/**
 * char_match - check if character matches given needles
 * @c: character to macth
 * @needles: string to search for matching character
 * Return: 1 if match else 0
 */

int char_match(char c, char *needles)
{
	if (needles == NULL)
		return (0);

	do {
		if (c == *needles)
			return (1);
	} while (*needles++);
	return (0);
}
