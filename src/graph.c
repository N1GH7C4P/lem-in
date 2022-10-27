/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:58:27 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/27 17:00:59 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_node	*find_path(t_node *node, t_graph *graph, int path_id)
{
	int i;

	i = 0;
	while (graph->edges[i++])
	{
		// Correct start node
		if (graph->edges[i]->start->id == node->id)
		{
			if (graph->edges[i]->end->path_id == path_id)
			{
				ft_putstr("Path found: ");
				print_edge(graph->edges[i]);
				ft_putendl("");
				return (graph->edges[i]->end);
			}
		}
		else if (graph->edges[i]->end->id == node->id)
		{
			if (graph->edges[i]->start->path_id == path_id)
			{
				ft_putstr("Path found: ");
				print_edge(graph->edges[i]);
				ft_putendl("");
				return (graph->edges[i]->start);
			}
		}
	}
	return (NULL);
}

int	traverse_path(t_graph *g, int path_id)
{
	t_node	*node;
	t_node	*neighbour;

	node = g->start;
	neighbour = find_path(node, g, path_id);
	while (neighbour)
	{
		neighbour = find_path(node, g, path_id);
		if (neighbour->is_end)
			return (1);
	}
	return (0);
}

void traverse_paths(t_graph *g)
{
	int i;

	i = 0;
	while (i < g->nb_of_paths)
	{
		traverse_path(g, i);
		i++;
	}
}

t_graph	*create_graph(void)
{
	t_graph	*new_graph;

	new_graph = (t_graph *)malloc(sizeof(t_graph));
	new_graph->nb_of_nodes = 0;
	new_graph->nb_of_edges = 0;
	new_graph->nb_of_paths = 0;

	return (new_graph);
}

void	reset_visit_status(t_graph *g)
{
	int i;

	i = 0;
	g->start->visited = 0;
	g->end->visited = 0;
	while (g->edges[i])
	{
		if (g->edges[i]->start->visited == 1)
			g->edges[i]->start->visited = 0;
		if (g->edges[i]->end->visited == 1)
			g->edges[i]->end->visited = 0;
		i++;
	}
}