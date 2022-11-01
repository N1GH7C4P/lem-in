/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:02 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/02 00:28:12 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_node	*find_neighbour(t_node *node, t_graph *graph)
{
	int i;

	i = 0;
	while (i < graph->nb_of_edges && graph->edges[i])
	{
		if (graph->edges[i]->start->id == node->id)
		{
			if (graph->edges[i]->end->visited == 0)
				return (graph->edges[i]->end);
		}
		else if (graph->edges[i]->end->id == node->id)
		{
			if (graph->edges[i]->start->visited == 0)
				return (graph->edges[i]->start);
		}
		i++;
	}
	return (NULL);
}

void	print_edges(t_edge **edges)
{
	ft_putendl("printing edges");
	int i;

	i = 0;
	while (edges[i])
	{
		print_edge(edges[i]);
		ft_putendl("");
		i++;
	}
}

void	print_edge(t_edge *edge)
{
	print_node(edge->start, 0);
	ft_putstr(" -> ");
	print_node(edge->end, 0);
}

t_edge	*create_edge(t_node *start, t_node *end)
{
	t_edge	*new_edge;

	new_edge = (t_edge *)malloc(sizeof(t_edge));
	new_edge->start = start;
	new_edge->end = end;
	return (new_edge);
}