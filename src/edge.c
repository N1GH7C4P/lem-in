/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:02 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/18 18:23:57 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

// Checks if either node of the edge (e) matches to a given node (n) in graph (g)
static t_node *check_edge(t_edge *e, t_node *n, t_graph *g)
{
	if (!e || !n || !g)
		return (NULL);
	if (n == e->end)
	{
		if (e->start->visited == 0)
			return (e->start);
	}
	if (n == e->start)
	{
		if (e->end->visited == 0)
			return (e->end);
	}
	return (NULL);
}

// Finds neighbous of node (n) in graph (g)
t_node	*find_neighbour(t_node *n, t_graph *g)
{
	int 	i;
	t_node	*ret;

	i = 0;
	while (i < g->nb_of_edges - 1)
	{
		ret = check_edge(g->edges[i], n, g);
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
