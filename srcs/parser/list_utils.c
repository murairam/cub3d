#include "cub3d.h"

static void	free_array_on_error(char **array, int count)
{
	while (count > 0)
		free(array[--count]);
	free(array);
}

static int	copy_list_content(char **array, t_list *list)
{
	int		i;
	t_list	*current;

	current = list;
	i = 0;
	while (current)
	{
		array[i] = ft_strdup((char *)current->content);
		if (!array[i])
		{
			free_array_on_error(array, i);
			return (0);
		}
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (1);
}

char	**list_to_array(t_list *list)
{
	char	**array;
	int		size;

	size = ft_lstsize(list);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	if (!copy_list_content(array, list))
		return (NULL);
	return (array);
}
