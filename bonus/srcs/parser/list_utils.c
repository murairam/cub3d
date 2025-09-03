/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:37:55 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:37:56 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
			array[i] = NULL;
			ft_free_split(array);
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
