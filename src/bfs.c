/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:58:50 by kpolojar          #+#    #+#             */
/*   Updated: 2022/11/03 22:32:42 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int	backtrack(t_node **history, t_graph *graph)
{
	t_node	*node;
	node = graph->end;
	graph->nb_of_paths = graph->nb_of_paths + 1;
	node->path_id = graph->nb_of_paths;
	while (node)
	{
		node = history[node->id];
		node->path_id = graph->nb_of_paths;
		node->visited = 2;
		if (node->is_start)
			break ;
	}
	reset_visit_status(graph);
	return (1);
}

int	bfs(t_graph *graph)
{
	t_queue	*q;
	t_node	*node;
	t_node	*neighbour;
	t_node	**prev;

	prev = (t_node **)malloc(sizeof(t_node *) * (graph->nb_of_nodes + 1));
	q = new_queue(graph->nb_of_nodes);
	enqueue(q, graph->start);
	graph->start->visited = 1;
	while (!is_empty(q))
	{
		node = dequeue(q);
		neighbour = find_neighbour(node, graph);
		while (neighbour)
		{
			neighbour->visited = 1;
			prev[neighbour->id] = node;
			enqueue(q, neighbour);
			if (neighbour->is_end == 1)
			{
				backtrack(prev, graph);
				free_queue(q);
				free(prev);
				return (1);
			}
			neighbour = find_neighbour(node, graph);
		}
	}
	free(prev);
	free_queue(q);
	return (0);
}
