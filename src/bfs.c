/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:58:50 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/27 17:14:48 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int	backtrack(t_node **history, t_graph *graph)
{
	t_node	*node;

	node = graph->end;
	while (node)
	{
		node->path_id = graph->nb_of_paths;
		node = history[node->id];
		node->visited = 2;
		if (node->is_start)
			break ;
	}
	graph->nb_of_paths++;
	reset_visit_status(graph);
	return (1);
}

int	bfs(t_graph *graph)
{
	t_queue	*q;
	t_node	*node;
	t_node	*neighbour;
	t_node	**prev;

	ft_putstr("nb_of_nodes: ");
	ft_putnbr(graph->nb_of_nodes);
	ft_putendl("");
	prev = (t_node **)malloc(sizeof(t_node *) * (graph->nb_of_nodes + 1));
	q = new_queue(graph->nb_of_nodes);
	enqueue(q, graph->start);
	graph->start->visited = 1;
	while (!is_empty(q))
	{
		node = dequeue(q);
		ft_putendl("Dequeue: ");
		print_node(node, 1);
		ft_putendl("");
		neighbour = find_neighbour(node, graph);
		neighbour->visited = 1;
		while (neighbour)
		{
			ft_putendl("neighbour found!");
			print_node(neighbour, 1);
			ft_putendl("");
			ft_putstr("neighbour id: ");
			ft_putnbr(neighbour->id);
			ft_putendl("");
			ft_putendl("parent: ");
			print_node(node, 1);
			ft_putendl("");
			prev[neighbour->id] = node;
			enqueue(q, neighbour);
			ft_putendl("Enqueued");
			if (neighbour->is_end == 1)
			{
				ft_putendl("End node found!");
				backtrack(prev, graph);
				return (1);
			}
			neighbour = find_neighbour(node, graph);
			neighbour->visited = 1;
		}
	}
	return (0);
}