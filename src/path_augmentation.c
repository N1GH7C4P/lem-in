/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_augmentation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:48:26 by kpolojar          #+#    #+#             */
/*   Updated: 2023/02/03 14:31:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"
#include "../libft/libft.h"

static t_node *check_aug_edge(t_edge *e, t_node *n, int tolerate_visit)
{
	if (n == e->end && e->start->visited == 0)
	{
		if (tolerate_visit == 1 && e->start->is_start == 0)
			return (e->start);
		else if (e->start->path_id == 0)
			return (e->start);
	}
	else if (n == e->start && e->end->visited == 0)
	{
		if (tolerate_visit == 1 && e->end->is_start == 0)
			return (e->end);
		else if (e->end->path_id == 0)
			return (e->end);
	}
	return (NULL);
}

// Finds neighbous of node (n) in graph (g)
static t_node	*find_augmenting_neighbour(t_node *n, t_graph *g)
{
	int 	i;
	t_node	*ret;

	i = 0;
	while (i < g->nb_of_edges - 1)
	{
		if (n->is_start == 1)
			ret = check_aug_edge(g->edges[i], n, 0);
		else
			ret = check_aug_edge(g->edges[i], n, 1);
		if (ret && ret->first_node_in_path != 1)
		{
			if (DEBUGGING > 0)
			{
				ft_putendl("free node found");
				print_node(ret);
			}
			return (ret);
		}
		i++;
	}
	i = 0;
	if (DEBUGGING > 0)
		ft_putendl("no more free nodes");
	return (NULL);
}

t_node *find_backpedal_node(t_node *n,  t_graph *g)
{
	int i;

	i = 0;
	while (i < g->nb_of_edges)
	{
		if (g->edges[i]->start == n)
		{
			if (g->edges[i]->end->path_id == n->path_id && g->edges[i]->used_backwards == 1)
			{
				if (g->edges[i]->end->is_start == 0 && g->edges[i]->end->first_node_in_path == 0)
				{
					if (DEBUGGING > 0)
					{
						ft_putendl("backpedal found");
						print_edge(g->edges[i]);
						ft_putendl("");
						print_node(g->edges[i]->end);
					}
					return (g->edges[i]->end);
				}
				else
				{
					if (DEBUGGING > 0)
						ft_putendl("no backpedaling to start node.");
				}
			}
		}
		if (g->edges[i]->end == n)
		{
			if (g->edges[i]->start->path_id == n->path_id && g->edges[i]->used_forwards == 1)
			{
				if (g->edges[i]->start->is_start == 0 && g->edges[i]->start->first_node_in_path != 1)
				{
					if (DEBUGGING > 0)
					{
						ft_putendl("backpedal found");
						print_edge(g->edges[i]);
						ft_putendl("");
						print_node(g->edges[i]->start);
					}
					return (g->edges[i]->start);
				}
				else
				{
					if (DEBUGGING > 0)
						ft_putendl("no backpedaling to start node.");
				}
			}
		}
		i++;
	}
	if (DEBUGGING > 0)
		ft_putendl("impossible to backpedal");
	return (NULL);
}

int	check_backpedal_history(t_node *n)
{
	t_node	*prev;
	
	prev = n->previous;
	while (prev)
	{
		if (DEBUGGING > 0)
		{
			ft_putendl("prev: ");
			print_node(prev);
		}
		if (prev->is_start)
			return (0);
		if (prev->backpedaled == 1)
			return (1);
		prev = prev->previous;
	}
	return (0);
}

void	backpedal_existing_path(t_node *n, t_queue *q, t_graph *g)
{
	t_node *backpedal;
	
	if (check_backpedal_history(n) == 1)
	{
		if (DEBUGGING > 0)
			ft_putendl("Backpedal present in history");
		backpedal = find_augmenting_neighbour(n, g);
		if (backpedal)
		{
			visit_neighbour(n, backpedal, q, g);
			return;
		}
	}
	backpedal = find_backpedal_node(n, g);
	if (backpedal)
	{
		if (backpedal->first_node_in_path == 1)
		{
			if (DEBUGGING > 0)
				ft_putendl("No backpedaling to first node in path");
			return;
		}
		n->backpedaled = 1;
		backpedal->visited = 1;
		g->history[backpedal->id] = n;
		n->next = backpedal;
		backpedal->previous = n;
		visit_neighbour(n, backpedal, q, g);
	}
}

int	augmenting_bfs(t_graph *g, t_node *start, t_node *end)
{
	t_node	*node;
	t_node	*neighbour;
	static	t_queue* q; 
	
	if (DEBUGGING > 0)
		ft_putendl("augmenting bfs");
	q = new_queue(g->nb_of_nodes + 1);
	g->history = (t_node **)malloc(sizeof(t_node *) * (g->nb_of_nodes + 1));
	set_start_node(q, g, start);
	while (!is_empty(q) && g->path_found != 1)
	{
		node = dequeue(q);
		if (DEBUGGING > 0)
		{
			ft_putendl("queue");
			print_node(node);
		}
		if (node == end)
		{
			g->path_found = 1;
			break;
		}
		if (node->path_id > 0 && !node->is_start && !node->is_end && !g->backpedaled)
		{
			if (DEBUGGING > 0)
				ft_putendl("backpedalling");
			backpedal_existing_path(node, q, g);
		}
		else
		{
			if (DEBUGGING > 0)
				ft_putendl("finding aug path");
			neighbour = find_augmenting_neighbour(node, g);
			//print_node(node);
			while (neighbour)
			{
				visit_neighbour(node, neighbour, q, g);
				neighbour = find_augmenting_neighbour(node, g);
			}
		}
	}
	return (free_bfs(g, q));
}

int	find_augmenting_paths(t_graph *g)
{
	int ret;
	int path_id;

	ret = augmenting_bfs(g, g->start, g->end);
	if (ret == 1)
	{
		path_id = find_first_free_path_id(g);
		backtrack(g, g->start, g->end, path_id);
		g->paths[path_id - 1] = create_path(g, path_id);
		return (1);
	}
	return (0);
}