/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:58:27 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/06 13:50:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

void print_path_id_availability(char *ids, int nb_of_paths)
{
	int i;
	int printed;

	i = 1;
	printed = 0;
	while (i < MAX_PATHS && printed < nb_of_paths)
	{
		if (ids[i] == 1)
		{
			ft_putstr("NOT AVAILABLE: ");
			ft_putnbr(i);
			ft_putendl("");
			printed++;
		}
		else
		{
			ft_putstr("AVAILABLE: ");
			ft_putnbr(i);
			ft_putendl("");
		}
		i++;
	}
}

t_path	*find_optimal_path(t_path **paths, char *ids)
{
	int	i;
	int	shortest;
	int	shortest_index;

	shortest_index = -1;
	shortest = INT_MAX;
	i = 1;
	while (i < MAX_PATHS)
	{
		if (ids[i] == 1 && paths[i - 1]->ants + paths[i - 1]->path_length < shortest)
		{
			shortest = paths[i - 1]->ants + paths[i - 1]->path_length;
			shortest_index = i - 1;
		}
		i++;
	}
	if (DEBUGGING > 0)
	{
		ft_putstr("shortest path: (");
		ft_putnbr(paths[shortest_index]->id);
		ft_putstr(") len: ");
		ft_putnbr(paths[shortest_index]->path_length);
		ft_putstr(" ants: ");
		ft_putnbr(paths[shortest_index]->ants);
		ft_putendl("");
		
	}
	return (paths[shortest_index]);
}

t_graph	*create_graph(void)
{
	t_graph	*new_graph;

	new_graph = (t_graph *)malloc(sizeof(t_graph));
	new_graph->paths = (t_path **)malloc(sizeof(t_path *) * (MAX_PATHS + 1));
	new_graph->path_id_availability = (char *)malloc(MAX_PATHS + 1);
	new_graph->best_path_id_availability = (char *)malloc(MAX_PATHS + 1);
	new_graph->best_paths = (t_path **)malloc(sizeof(t_path *) * MAX_PATHS + 1);
	new_graph->nb_of_nodes = 0;
	new_graph->nb_of_edges = 0;
	new_graph->nb_of_paths = 0;
	new_graph->ants_placed = 0;
	new_graph->ants_finished = 0;
	new_graph->lines = 0;
	new_graph->least_nb_of_rounds = INT_MAX;
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
	free_all_paths(g->paths, g);
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
