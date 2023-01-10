/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:58:50 by kpolojar          #+#    #+#             */
/*   Updated: 2022/12/14 17:47:40 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

int	backtrack(t_node **history, t_graph *graph)
{
	t_node	*node;

	node = graph->end;
	graph->nb_of_paths = graph->nb_of_paths + 1;
	node->path_id = graph->nb_of_paths;
	while (node)
	{
		if (node->is_end && history[node->id]->is_start)
			if (!graph->smallest_path)
				graph->smallest_path = 1;
		node = history[node->id];
		node->path_id = graph->nb_of_paths;
		node->visited = 2;
		if (node->is_start)
			break ;
	}
	reset_visit_status(graph);
	return (1);
}

static int	free_bfs(t_node **prev, t_queue *q, int ret)
{
	free_queue(q);
	free(prev);
	return (ret);
}

int	bfs(t_graph *graph, t_queue *q, t_node	*neighbour, t_node **prev)
{
	t_node	*node;

	q = new_queue(graph->nb_of_nodes + 1);
	prev = (t_node **)malloc(sizeof(t_node *) * (graph->nb_of_nodes + 1));
	enqueue(q, graph->start);
	graph->start->visited = 1;
	while (!is_empty(q))
	{
		node = dequeue(q);
		neighbour = find_neighbour(node, graph, 0, NULL);
		while (neighbour)
		{
			neighbour->visited = 1;
			prev[neighbour->id] = node;
			enqueue(q, neighbour);
			if (neighbour->is_end == 1)
			{
				backtrack(prev, graph);
				return (free_bfs(prev, q, 1));
			}
			neighbour = find_neighbour(node, graph, 0, NULL);
		}
	}
	return (free_bfs(prev, q, 0));
}
