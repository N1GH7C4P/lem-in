/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:02 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/13 16:48:31 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

t_node	*find_neighbour(t_node *node, t_graph *g)
{
	int i;

	i = 0;
	while (i < g->nb_of_nodes)
	{
		if (node->id != i && !check_start_end(node, g->nodes[i], g))
		{
			if (g->adj_matrix[node->id][i] == 1)
			{
				if (g->nodes[i]->visited == 0)
					return (g->nodes[i]);
			}
		}
		i++;
	}
	return (NULL);
}

void	free_edge(t_edge *e)
{
	free(e);
}

void	print_edges(t_edge **edges)
{
	int	i;

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
	ft_putstr(edge->start->name);
	ft_putstr("-");
	ft_putstr(edge->end->name);
}

t_edge	*create_edge(t_node *start, t_node *end)
{
	t_edge	*new_edge;

	new_edge = (t_edge *)malloc(sizeof(t_edge));
	new_edge->start = start;
	new_edge->end = end;
	return (new_edge);
}
