/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:58:27 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/07 19:50:18 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

t_path	*find_optimal_path(t_graph *g)
{
	int	i;
	int	shortest;
	int	shortest_index;

	shortest_index = -1;
	shortest = INT_MAX;
	i = 0;
	while (g->paths[i] && i < g->nb_of_paths)
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
	new_graph->ants_placed = 0;
	new_graph->ants_finished = 0;
	new_graph->lines = 0;
	return (new_graph);
}

void	free_graph(t_graph *g)
{
	int	i;

	i = 0;
	while (g->nodes[i] && i < g->nb_of_nodes)
		free_node(g->nodes[i++]);
	free(g->nodes);
	i = 0;
	while (g->edges[i] && i < g->nb_of_edges)
		free_edge(g->edges[i++]);
	free(g->edges);
	i = 0;
	while (g->ants[i] && i < g->ants_finished)
		free_ant(g->ants[i++]);
	free(g->ants);
	i = 0;
	while (g->paths[i] && i < g->nb_of_paths)
		free_path(g->paths[i++]);
	free(g->paths);
	free(g);
}

void	reset_visit_status(t_graph *g)
{
	int	i;

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
