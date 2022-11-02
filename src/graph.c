/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:58:27 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/02 17:32:40 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

void	place_all_ants(t_graph *g)
{
	t_path *p;

	while (g->ants > 0)
	{
		p = find_optimal_path(g);
		place_ant_on_path(p);
		g->ants--;
	}
}

t_path	*find_optimal_path(t_graph *g)
{
	int i;
	int shortest;
	int	shortest_index;

	shortest_index = -1;
	shortest = INT_MAX;
	i = 1;
	while (i <= g->nb_of_paths)
	{
		if (g->paths[i]->ants + g->paths[i]->path_length < shortest)
		{
			shortest = g->paths[i]->ants + g->paths[i]->path_length;
			shortest_index = i;
		}
		i++;
	}
	return (g->paths[shortest_index]);
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
