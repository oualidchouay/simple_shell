#include "shell.h"

/**
 * free_array - Frees a 2D array to prevent memory leaks
 * @arr: The 2D array to be freed
 */

void free_array(char **arr)
{
	char **temp = arr;

	if (!arr)
		return;

	while (*temp)
	{
		free(*temp);
		*temp = NULL;
		temp++;
	}
	free(arr);
	arr = NULL;
}
