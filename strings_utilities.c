#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @str: The string to be duplicated.
 *
 * Return: A pointer to the duplicated string,
 * or NULL if insufficient memory was available.
 */

char *_strdup(const char *str)
{
	char *ptr;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		len++;
		str++;
	}
	str = str - len;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	for (i = 0; i <= len; i++)
		ptr[i] = str[i];
	return (ptr);
}

/**
 * _strcmp - Compares two strings s1 and s2.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: An integer indicating the result of the comparison.
 */

int _strcmp(char *s1, char *s2)
{
	int cmp;

	cmp = (int)*s1 - (int)*s2;
	while (*s1)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		cmp = (int)*s1 - (int)*s2;
	}
	return (cmp);
}

/**
 * _strlen - Returns the length of a string s.
 * @s: The string to be measured.
 *
 * Return: The length of the string.
 */

int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * _strcat - This function appends the src string
 * to the dest string, overwriting the
 * terminating null byte ('\0') at the end of dest,
 * and then adds a terminating null byte.
 *
 * @dest: The destination string
 * @src: The source string
 *
 * Return: A pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	char *p = dest;

	while (*p)
		p++;
	while (*src)
	{
		*p = *src;
		p++;
		src++;
	}
	*p = *src;
	return (dest);
}

/**
 * _strcpy - This function copies the string pointed to by 'src', including the
 * terminating null byte ('\0'), to the buffer pointed to by 'dest'.
 * @dest: The destination string
 * @src: The source string
 *
 * Return: A pointer to the destination string dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
