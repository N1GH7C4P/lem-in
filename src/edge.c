/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:31:02 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/06 14:25:24 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

static int check_start_end(t_node *a, t_node *b, t_graph *g)
{
	if ((a->is_start || a->is_end) && (b->is_end || b->is_start))
	{
		//ft_putendl("Smallest path found. ");
		if (g->smallest_path == 1)
		{
			//ft_putendl("...And smallest path alreaydy exists!");
			return (1);
		}
		else
		{
			g->smallest_path = 1;
			//ft_putendl("...And it is the first one.");
		}
	}
	return (0);
}

t_node	*find_neighbour(t_node *node, t_graph *graph)
{
	int		i;
	t_node	*n;

	i = 0;
	while (i < graph->nb_of_edges && graph->edges[i])
	{
		if (graph->edges[i]->start->id == node->id)
		{
			if (graph->edges[i]->end->visited == 0)
			{
				n = graph->edges[i]->end;
				if(!check_start_end(node, n, graph))
					return (n);
			}
		}
		else if (graph->edges[i]->end->id == node->id)
		{
			if (graph->edges[i]->start->visited == 0)
			{
				n = graph->edges[i]->start;
				if(!check_start_end(node, n, graph))
					return (n);
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
