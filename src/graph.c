/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:58:27 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/01 23:26:16 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

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