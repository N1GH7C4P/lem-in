/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:58:50 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/26 18:41:06 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

int	bfs(t_graph *graph)
{
	t_queue	*q;
	t_node	*node;
	t_node	*neighbour;

	q = new_queue();
	enqueue(q, graph->start);
	graph->start->visited = 1;
	while (!is_empty(q))
	{
		node = dequeue(q);
		ft_putendl("Dequeue: ");
		print_node(node, 1);
		ft_putendl("");
		neighbour = find_univisited_node(node, graph);
		neighbour->visited = 1;
		while (neighbour)
		{
			if (neighbour->is_end == 1)
				return (1);
			if (neighbour)
			{
				ft_putendl("Enqueue: ");
				print_node(neighbour, 1);
				ft_putendl("");
				neighbour->visited = 1;
				enqueue(q, neighbour);
			}
			neighbour = find_univisited_node(node, graph);
		}
	}
	return (0);
}