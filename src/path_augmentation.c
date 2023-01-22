/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_augmentation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:48:26 by kpolojar          #+#    #+#             */
/*   Updated: 2023/01/22 19:39:43 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

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
		if (ret)
		{
			ft_putendl("free node found");
			print_node(ret);
			return (ret);
		}
		i++;
	}
	i = 0;
	/*
		ft_putendl("no free path");
		if (!n->is_start)
		{
		while (i < g->nb_of_edges - 1)
		{
		ret = check_aug_edge(g->edges[i], n, 1);
		if (ret)
		{
			ft_putendl("current node: ");
			print_node(n);
			ft_putendl("crossing path at: ");
			print_edge(g->edges[i]);
			ft_putendl("");
			print_node(ret);
			return (ret);
		}
		i++;
		}
	}
	*/
	ft_putendl("dead end");
	reset_visit_status(g);
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
			if (g->edges[i]->end->path_id == n->path_id)
			{
				ft_putendl("backpedal found");
				print_edge(g->edges[i]);
				if (g->edges[i]->end->is_start == 0)
					return (g->edges[i]->end);
			}
		}
		if (g->edges[i]->end == n)
		{
			if (g->edges[i]->start->path_id == n->path_id)
			{
				ft_putendl("backpedal found");
				print_edge(g->edges[i]);
				if (g->edges[i]->start->is_start == 0)
					return (g->edges[i]->start);
			}
		}
		i++;
	}
	return (NULL);
}

void	backpedal_existing_path(t_node *n, t_queue *q, t_graph *g)
{
	t_node *backpedal;
	
	if (g->backpedaled == 1)
	{
		backpedal = find_augmenting_neighbour(n, g);
		if (backpedal)
		{
			g->backpedaled = 0;
			enqueue(q, backpedal);
			return;
		}
	}
	backpedal = find_backpedal_node(n, g);
	if (backpedal)
	{
		g->backpedaled = 1;
		backpedal->visited = 1;
		g->history[backpedal->id] = n;
		n->next = backpedal;
		backpedal->previous = n;
		enqueue(q, backpedal);
	}
}

int	augmenting_bfs(t_graph *g, int direction)
{
	t_node	*node;
	t_node	*neighbour;
	static	t_queue* q; 

	q = new_queue(g->nb_of_nodes + 1);
	g->history = (t_node **)malloc(sizeof(t_node *) * (g->nb_of_nodes + 1));
	set_start_node(q, g, direction);
	while (!is_empty(q) && g->path_found != 1)
	{
		node = dequeue(q);
		ft_putendl("queue");
		print_node(node);
		if (node->path_id > 0 && !node->is_start && !node->is_end)
		{
			ft_putendl("backpedalling");
			backpedal_existing_path(node, q, g);
		}
		else
		{
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
	if (g->path_found == 1)
	{
		//print_nodes(g->nodes);
		ft_putendl("backtracking");
		backtrack(g, direction);
	}
	return (free_bfs(g, q));
}

int	find_augmenting_paths(t_graph *g)
{
	int ret;

	//print_nodes(g->nodes);
	//ft_putendl("nodes printed");
	ret = augmenting_bfs(g, 1);
	//print_nodes(g->nodes);
	if (ret == 1)
		g->paths[g->nb_of_paths] = create_path(g, g->nb_of_paths);
	return (0);
}