/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:02 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/02 17:04:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_edge *find_double_used_edge(t_graph *g)
{
	int i;

	i = 0;
	while (i < g->nb_of_edges)
	{
		if (g->edges[i]->start->old_path_id && g->edges[i]->end->old_path_id)
		{
			ft_putendl("doublle used edge found");
			print_edge(g->edges[i]);
			ft_putendl("");
			return (g->edges[i]);
		}
		i++;
	}
	return (NULL);
}

// Checks if either node of the edge (e) matches to a given node (n) in graph (g)
static t_node *check_edge(t_edge *e, t_node *n, t_graph *g, int tolerate_visit)
{
	if (!e || !n || !g)
		return (NULL);
	if (n == e->end)
	{
		if (e->start->visited == 0)
		{
			if (e->start->path_id == 0 || (tolerate_visit == 1 && e->start->visited == 2) || e->start->is_end == 1)
					return (e->start);
		}
	}
	if (n == e->start)
	{
		if(e->end->visited == 0)
		{
			if (e->end->path_id == 0 || (tolerate_visit == 1 && e->end->visited == 2) || e->end->is_end == 1)
				return (e->end);
		}
	}
	return (NULL);
}

// Finds neighbous of node (n) in graph (g)
t_node	*find_neighbour(t_node *n, t_graph *g, int tolerate_visit)
{
	int 	i;
	t_node	*ret;

	i = 0;
	while (i < g->nb_of_edges)
	{
		ret = check_edge(g->edges[i], n, g, tolerate_visit);
		if (ret)
			return (ret);
		i++;
	}
	return (NULL);
}

void	free_edge(t_edge *e)
{
	free(e);
}

t_edge	*create_edge(t_node *start, t_node *end, t_graph *g)
{
	t_edge	*new_edge;

	new_edge = (t_edge *)malloc(sizeof(t_edge));
	new_edge->start = start;
	new_edge->end = end;
	if (start == g->start || start == g->end)
		if (end == g->start || end == g->end)
			g->smallest_path = 1;
	return (new_edge);
}
