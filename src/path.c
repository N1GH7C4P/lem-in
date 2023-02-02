/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:24:57 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/02 15:21:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_path	*new_path(int len, int id)
{
	t_path	*p;

	p = (t_path *)malloc(sizeof(t_path));
	p->path_length = len;
	p->nodes = (t_node **)malloc(sizeof(t_node *) * (len + 1));
	p->nodes[len] = NULL;
	p->ants = 0;
	p->id = id;
	return (p);
}

t_path *copy_path(t_path *p)
{
	t_path *new_p;
	int		i;

	new_p = new_path(p->path_length, p->id);
	i = 0;
	while(i < p->path_length)
	{
		new_p->nodes[i] = p->nodes[i];
		i++;
	}
	new_p->nodes[i] = NULL;
	return (new_p);
}

void	free_path(t_path *p)
{
	free(p->nodes);
	free(p);
}

void	free_all_paths(t_path **paths, int nb_of_paths)
{
	int i;

	i = 0;
	while (i < nb_of_paths - 1)
	{
		ft_putstr("freeing path: ");
		ft_putnbr(i);
		ft_putendl("");
		free_path(paths[i]);
		i++;
	}
}

/*
static t_path *create_smallest_path(t_graph *g)
{
	t_path *smallest;
	
	smallest = new_path(2);
	smallest->nodes[0] = g->start;
	smallest->nodes[1] = g->end;
	return (smallest);
}
*/

