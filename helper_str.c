#include "shell.h"

/**
 * _memcpy - copies n bytes from the memory area src to memory
 * area destination
 * @src: source
 * @dest: destination
 * @n: number of bytes to copy
 * Return: dest
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * _memset - sets first n bytes of memory area
 * @s: array to set
 * @b: what to set it to
 * @n: first n bytes
 * Return: s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * _strcat - appends strings
 * @dest: destination
 * @src: source
 * Return: poitner to destination
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	j = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		j++;
		i++;
	}
	/*i++*/
	dest[i] = '\0';
	return (dest);
}
/**
 * _strncat - concats one string to anothe given nums of bytes
 * @dest: destinatin
 * @src: source
 * @n: number of bytes
 * Return: dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
	{

	}
	j = 0;
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strstr - finds the first occurence of substring needle int he
 * string haystack
 * @haystack: string to search
 * @needle: string to find
 * Return: pointer to beginning of the located subsring
 */
char *_strstr(char *haystack, char *needle)
{
	while (*haystack != '\0')
	{
		char *beginning = haystack;
		char *pattern = needle;

		while (*pattern == *haystack && *pattern != '\0' && *haystack != '\0')
		{
			haystack++;
			pattern++;
		}
		if (*pattern == '\0')
			return (beginning);
		haystack = beginning + 1;
	}
	return (NULL);
}
